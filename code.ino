#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// Define pins
const int TRIG_PIN = 11;
const int ECHO_PIN = 12;
const int TEMP_PIN = A0;
const int GAS_PIN = A1;
const int SMOKE_PIN = A2;
const int BUZZER_PIN = 8;
const int BUTTON_PIN = 9;

Servo stoveKnob;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Cooking mode settings
enum Mode { OFF, FAST, MEDIUM, SLOW };
int mode = OFF;
unsigned long startTime = 0;
unsigned long duration = 0;

// Servo range
int openPos = 90;
int closePos = 0;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  stoveKnob.attach(13);
  lcd.begin();
  lcd.backlight();

  lcd.print("Smart Stove");
  delay(2000);
  lcd.clear();
}

void loop() {
  checkButton();
  displayStatus();
  monitorSafety();

  if (mode != OFF && millis() - startTime >= duration) {
    shutOffStove();
    lcd.setCursor(0, 1);
    lcd.print("Cooking Done     ");
  }
}

void checkButton() {
  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && buttonState == LOW) {
    mode = (mode + 1) % 4;
    switch (mode) {
      case OFF:
        shutOffStove();
        break;
      case FAST:
        startCooking(10 * 1000);
        break;
      case MEDIUM:
        startCooking(20 * 1000);
        break;
      case SLOW:
        startCooking(30 * 1000);
        break;
    }
  }
  lastButtonState = buttonState;
  delay(100); // debounce
}

void startCooking(unsigned long cookTime) {
  stoveKnob.write(openPos);
  startTime = millis();
  duration = cookTime;
  lcd.clear();
  lcd.print("Cooking Started");
}

void shutOffStove() {
  stoveKnob.write(closePos);
  mode = OFF;
  lcd.clear();
  lcd.print("Stove Off");
  delay(1000);
}

void displayStatus() {
  int tempC = analogRead(TEMP_PIN) * 0.488; // LM35 conversion
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempC);
  lcd.print("C ");

  lcd.print("M:");
  switch (mode) {
    case OFF: lcd.print("OFF "); break;
    case FAST: lcd.print("FAST"); break;
    case MEDIUM: lcd.print("MED "); break;
    case SLOW: lcd.print("SLOW"); break;
  }
}

void monitorSafety() {
  float distance = getDistance();
  int gas = analogRead(GAS_PIN);
  int smoke = analogRead(SMOKE_PIN);
  int tempC = analogRead(TEMP_PIN) * 0.488;

  // Milk overflow detection
  if (distance < 10) {
    alertUser("Milk Overflow!");
  }

  // Overheating
  if (tempC > 120) {
    alertUser("Overheating!");
    shutOffStove();
  }

  // Gas leak
  if (gas > 400) {
    alertUser("Gas Leak!");
    shutOffStove();
  }

  // Smoke detected
  if (smoke > 400) {
    alertUser("Smoke Alert!");
    shutOffStove();
  }
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float dist = duration * 0.034 / 2;
  return dist;
}

void alertUser(const char* message) {
  digitalWrite(BUZZER_PIN, HIGH);
  lcd.clear();
  lcd.print(message);
  delay(3000);
  digitalWrite(BUZZER_PIN, LOW);
}
