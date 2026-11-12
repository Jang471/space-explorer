#define BUTTON 2
#define VARIABLE_R A1
#define BUZZER 13

const int LED[] = {6, 7, 8, 12};

int ledState = 0;

unsigned long currentTime;
unsigned long previousTime = 0;

int buzzerState = 0;
int toneValue = 0;

void setup() {
  myServo.attach(SERVO);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int buttonValue = digitalRead(BUTTON);

  int percent = sensorPercent(VARIABLE_R);

  int num = map(percent, 0, 100, 0, 4);

  switch (num) {
    case 0:
      toneValue = 0;
      break;

    case 1:
      toneValue = 262;
      break;

    case 2:
      toneValue = 330;
      break;

    case 3:
      toneValue = 392;
      break;

    case 4:
      toneValue = 523;
      break;
  }

  currentTime = millis();

  if (currentTime - previousTime >= 1000) {
    previousTime = currentTime;

    if (buzzerState == 0) {
      buzzerState = 1;
    } else {
      buzzerState = 0;
    }
  }

  if (toneValue == 0) {
    noTone(BUZZER);
  } else if (buzzerState == 1) {
    tone(BUZZER, toneValue);
  } else {
    noTone(BUZZER);
  }

  if (Serial.available()) {
    int servoValue = Serial.parseInt();
    int ledValue = Serial.parseInt();

    Serial.readStringUntil('\n');

    myServo.write(servoValue);
    analogWrite(LED, ledValue);
  }
}