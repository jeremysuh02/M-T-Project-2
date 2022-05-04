#include <Servo.h>

unsigned int oldTime = 0;

const int dragonServoPin = 2;
const int dragonButtonPin = 12;
const int piezoPin = 8;

const int fionaServoPin = 3;
const int fionaButtonPin = 11;

const int crowdServoPin = 4;
const int crowdButtonPin1 = 10;
const int crowdButtonPin2 = 9;

unsigned long songTimer = 0;
bool playingSong = false;


int fionaLastHigh = 0;
int songNotes[35] = {3135.96, 0, 4698.63, 3951.07, 3951.07, 0, 3520.00, 3135.96, 3135.96, 4186.01, 0, 3951.07, 3951.07, 3520.00, 3520.00, 3135.96, 0, 3135.96, 4186.01, 3951.07, 3951.07, 3520.00, 3520.00, 3135.96, 3520.00, 2637.02, 0, 2349.02, 0, 0, 0};
int currentNote = 0;

unsigned long alarmTimer = 0;

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
  pinMode(piezoPin, INPUT);  
  dragonServo.write(90);
  fionaServo.write(0);
  crowdServo.write(35);


}

void loop() {
  songTimer += delta();
  if (playingSong) {
    if (songTimer > 250) {
      tone(piezoPin, songNotes[currentNote], 50);
      currentNote += 1;
      if (currentNote == 34) {
        currentNote = 0;
        playingSong = false;
      }
      songTimer = 0;
    }
  }
  
  if (digitalRead(dragonButtonPin) == HIGH) {
    dragonServo.write(0);
    crowdServo.write(70);
    fionaServo.write(180);
    playingSong = true;
  }
  if (digitalRead(crowdButtonPin1) == HIGH) {
    crowdServo.write(35);
  }
  if (digitalRead(crowdButtonPin2) == HIGH) {
    crowdServo.write(0);
    alarmTimer += delta();
    if (alarmTimer > 100) {
      tone(piezoPin, 1760, 50);
      alarmTimer = 0;
    }
  }
  if (digitalRead(fionaButtonPin) == HIGH) {
    crowdServo.write(0);
    fionaLastHigh = millis();
  } else {
    if (fionaLastHigh - millis() < 100) {
      crowdServo.write(35);
    }
  }
  
}

unsigned long delta() {
  unsigned long currentTime = millis();
  unsigned long deltaTime = currentTime - oldTime;
  oldTime = currentTime;
  return deltaTime;
}
