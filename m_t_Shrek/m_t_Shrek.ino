#include <Servo.h>

unsigned int oldTime = 0;

const int dragonServoPin = 2;
const int dragonButtonPin = 12;

const int fionaServoPin = 3;
const int fionaButtonPin = 11;

const int crowdServoPin = 4;
const int crowdButtonPin1 = 10;
const int crowdButtonPin2 = 9;


Servo dragonServo;
Servo fionaServo;
Servo crowdServo;

void setup() {
  dragonServo.attach(dragonServoPin);
  fionaServo.attach(fionaServoPin);
  crowdServo.attach(crowdServoPin);
  
  pinMode(dragonButtonPin, INPUT);
  pinMode(fionaButtonPin, INPUT);
  pinMode(crowdButtonPin1, INPUT);
  pinMode(crowdButtonPin2, INPUT);
  
  dragonServo.write(0);
  fionaServo.write(0);
  crowdServo.write(0);
}

void loop() {
  if (digitalRead(dragonButtonPin) == HIGH) {
    dragonServo.write(90);
    crowdServo.write(70);
  }

  if (digitalRead(fionaButtonPin) == HIGH) {
    fionaServo.write(180);
  }

  if (digitalRead(crowdButtonPin1) == HIGH) {
    crowdServo.write(35);
  }
  if (digitalRead(crowdButtonPin2) == HIGH) {
    crowdServo.write(0);
  }
}
unsigned long delta() {
  unsigned long currentTime = millis();
  unsigned long deltaTime = currentTime - oldTime;
  oldTime = currentTime;
  return deltaTime;
}
