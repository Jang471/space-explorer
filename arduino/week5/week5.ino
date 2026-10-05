#include <Servo.h>

#define TRIG A4
#define ECHO A5
#define BUZZER 13

#define LIGHT A3
#define DC_FWD 9
#define DC_BWD 10

#define SERVO A0
#define VARIABLE_R A1

#define BUTTON 2
#define LED 6

Servo myServo;

unsigned long currentTime;
unsigned long previousTime = 0;

int motorState = 0;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(LIGHT, INPUT);
  pinMode(DC_FWD, OUTPUT);
  pinMode(DC_BWD, OUTPUT);

  myServo.attach(SERVO);
  pinMode(VARIABLE_R, INPUT);

  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  int distance = pulseIn(ECHO, HIGH) * 0.017;

  if (distance < 20) {
    tone(BUZZER, 262);
  } else {
    noTone(BUZZER);
  }

  int lightValue = analogRead(LIGHT);
  currentTime = millis();

  if (lightValue < 500) {
    if (currentTime - previousTime >= 1000) {
      previousTime = currentTime;

      if (motorState == 0) {
        digitalWrite(DC_FWD, HIGH);
        digitalWrite(DC_BWD, LOW);
        motorState = 1;
      } else {
        digitalWrite(DC_FWD, LOW);
        digitalWrite(DC_BWD, LOW);
        motorState = 0;
      }
    }
  } else {
    digitalWrite(DC_FWD, LOW);
    digitalWrite(DC_BWD, LOW);
    motorState = 0;
    previousTime = currentTime;
  }

  int value = analogRead(VARIABLE_R);
  int num = value / 256;
  // 서보모터 작동 이상
  switch (num) {
    case 0:
      myServo.write(20);
      break;

    case 1:
      myServo.write(60);
      break;

    case 2:
      myServo.write(120);
      break;

    case 3:
      myServo.write(160);
      break;
  }

  int buttonValue = digitalRead(BUTTON);

  if (buttonValue == 0) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED, HIGH);
      delay(200);

      digitalWrite(LED, LOW);
      delay(200);
    }
  }
}