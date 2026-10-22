// 2023111657 장재웅
#define BUTTON 2
#define VARIABLE_R A1
#define BUZZER 13

const int LED[] = { 6, 7, 8, 12 };

unsigned long currentTime;
unsigned long previousTime = 0;

int buzzerState = 0;
int toneValue = 0;

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(VARIABLE_R, INPUT);
  pinMode(BUZZER, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(LED[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  int value = digitalRead(BUTTON);

  int percent = sensorPercent(VARIABLE_R);

  Serial.print("Percent: ");
  Serial.println(percent);

  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], LOW);
  }

  int num = map(percent, 0, 100, 0, 4);

  for (int i = 0; i < num; i++) {
    digitalWrite(LED[i], HIGH);
  }

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

  if (value == 0) {
    blink(200);
  }

  delay(100);
}

void blink(int time) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], HIGH);
  }

  delay(time);

  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], LOW);
  }

  delay(time);
}

int sensorPercent(int pin) {
  int val = analogRead(pin);
  int percent = map(val, 0, 1023, 0, 100);

  return percent;
}