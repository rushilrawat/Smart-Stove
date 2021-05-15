long distance,duration;
#include<Servo.h>
Servo knob;
const int redpin = 2;
const int redpin2 = 3;
const int greenpin = 4;
const int greenpin2 = 5;
const int whitepin = 6;
const int whitepin2 = 7;
const int redswitch = 8;
const int greenswitch = 9;
const int whiteswitch = 10;
const int triggerpin = 11;
const int echopin = 12;
int redswitch_state=0;
int greenswitch_state=0;
int whiteswitch_state=0;
int pos = 0;

void setup() {
  knob.attach(13);
  pinMode(redpin,OUTPUT);
  pinMode(redpin2,OUTPUT);
  pinMode(greenpin,OUTPUT);
  pinMode(greenpin2,OUTPUT);
  pinMode(whitepin,OUTPUT);
  pinMode(whitepin2,OUTPUT);
  pinMode(redswitch,INPUT_PULLUP);
  pinMode(greenswitch,INPUT_PULLUP);
  pinMode(whiteswitch,INPUT_PULLUP);
  pinMode(triggerpin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.begin(9600); 
}

void loop() {
  digitalWrite(triggerpin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin,LOW);
  delayMicroseconds(2);
  duration = pulseIn(echopin,HIGH);
  distance = duration/58.0;
  if (distance <=23){
    redswitch_state=digitalRead(redswitch);
    if (redswitch_state==LOW){
      digitalWrite(redpin,HIGH);
      digitalWrite(redpin2,LOW);
      for (pos=0;pos<=180;pos+=1){
        knob.write(pos);
        delay(15);
       }
       delay(5*1000);
       for (pos=180;pos>=0;pos-=1){
        knob.write(pos);
        delay(15);
       }
       digitalWrite(redpin,LOW);
       digitalWrite(redpin2,LOW);
    }
      greenswitch_state=digitalRead(greenswitch);
      if (greenswitch_state==LOW){
      digitalWrite(greenpin,HIGH);
      digitalWrite(greenpin2,LOW);
      for (pos=0;pos<=180;pos+=1){
        knob.write(pos);
        delay(15);
       }
       delay(10*1000);
       for (pos=180;pos>=0;pos-=1){
        knob.write(pos);
        delay (15);
       }
       digitalWrite(greenpin,LOW);
       digitalWrite(greenpin2,LOW);
    }
      whiteswitch_state=digitalRead(whiteswitch);
      if (whiteswitch_state==LOW){
      digitalWrite(whitepin,HIGH);
      digitalWrite(whitepin2,LOW);
      for (pos=0;pos<=180;pos+=1){
        knob.write(pos);
        delay(15);
       }
       delay(15*1000);
       for (pos=180;pos>=0;pos-=1){
        knob.write(pos);
        delay(15);
       }
       digitalWrite(whitepin,LOW);
       digitalWrite(whitepin2,LOW);
    }
  }
}
