/*
  SmartStove
  Contributors: Rushil Rawat, Arghya Shubhshiv
*/


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
unsigned long lastBuzzTime = 0;
unsigned long lastDisplayUpdate = 0;
bool cooking = false;
bool wasButtonPressed = false;
const int EEPROM_ADDR = 0;

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

  mode = EEPROM.read(EEPROM_ADDR);
  if (mode < 0 || mode > 3) mode = OFF;

  lcd.print("Smart Stove");
  delay(2000);
  lcd.clear();
  lcd.print("Last Mode: ");
  lcd.print(getModeLabel(mode));
  delay(2000);
  lcd.clear();
}

void loop() {
  checkButton();
  displayStatus();
  monitorSafety();

  if (cooking) {
    unsigned long remaining = (startTime + duration) - millis();

    if (remaining <= 0) {
      shutOffStove();
      lcd.setCursor(0, 1);
      lcd.print("Cooking Done     ");
      cooking = false;
    } else {
      // Update display every 1s
      if (millis() - lastDisplayUpdate > 1000) {
        showTime(remaining);
        lastDisplayUpdate = millis();
      }

      // Buzz in last 5 seconds
      if (remaining <= 5000 && millis() - lastBuzzTime > 1000) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(200);
        digitalWrite(BUZZER_PIN, LOW);
        lastBuzzTime = millis();
      }
    }
  }
}

void checkButton() {
  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(BUTTON_PIN);

  // Detect rising edge
  if (lastButtonState == HIGH && buttonState == LOW) {
    if (!cooking) {
      mode = (mode + 1) % 4;
      EEPROM.write(EEPROM_ADDR, mode); // Save to EEPROM

      switch (mode) {
        case OFF: shutOffStove(); break;
        case FAST: startCooking(10 * 1000); break;
        case MEDIUM: startCooking(20 * 1000); break;
        case SLOW: startCooking(30 * 1000); break;
      }
    } else {
      // Extend cooking time if already cooking
      duration += 10 * 1000;
      lcd.setCursor(0, 1);
      lcd.print("Time Extended    ");
      delay(1000);
    }
  }

  lastButtonState = buttonState;
  delay(50); // debounce
}

void startCooking(unsigned long cookTime) {
  stoveKnob.write(openPos);
  startTime = millis();
  duration = cookTime;
  cooking = true;
  lcd.clear();
  lcd.print("Cooking Started");
  delay(1000);
}

void shutOffStove() {
  stoveKnob.write(closePos);
  mode = OFF;
  cooking = false;
  lcd.clear();
  lcd.print("Stove Off");
  delay(1000);
}

void displayStatus() {
  int tempC = analogRead(TEMP_PIN) * 0.488;
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempC);
  lcd.print("C M:");
  lcd.print(getModeLabel(mode));
}

void showTime(unsigned long msLeft) {
  lcd.setCursor(0, 1);
  int sec = msLeft / 1000;
  int min = sec / 60;
  sec %= 60;
  lcd.print("Time Left: ");
  if (min < 10) lcd.print('0');
  lcd.print(min);
  lcd.print(':');
  if (sec < 10) lcd.print('0');
  lcd.print(sec);
  lcd.print(" ");
}

const char* getModeLabel(int m) {
  switch (m) {
    case OFF: return "OFF ";
    case FAST: return "FAST";
    case MEDIUM: return "MED ";
    case SLOW: return "SLOW";
    default: return "UNK ";
  }
}

void monitorSafety() {
  float distance = getDistance();
  int gas = analogRead(GAS_PIN);
  int smoke = analogRead(SMOKE_PIN);
  int tempC = analogRead(TEMP_PIN) * 0.488;

  if (distance < 10) {
    alertUser("Milk Overflow!");
  }

  if (tempC > 120) {
    alertUser("Overheating!");
    shutOffStove();
  }

  if (gas > 400) {
    alertUser("Gas Leak!");
    shutOffStove();
  }

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
  return duration * 0.034 / 2;
}

void alertUser(const char* message) {
  digitalWrite(BUZZER_PIN, HIGH);
  lcd.clear();
  lcd.print(message);
  delay(3000);
  digitalWrite(BUZZER_PIN, LOW);
}
