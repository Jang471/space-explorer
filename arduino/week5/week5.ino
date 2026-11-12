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
  pinMode(BUTTON, INPUT);
  pinMode(VARIABLE_R, INPUT);
  pinMode(BUZZER, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(LED[i], OUTPUT);
  }

  Serial.begin(9600);

  Serial.println("set,0 / reset,0 / check,0 / toggle,0");
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
    String command = Serial.readStringUntil(',');

    int bitNum = Serial.parseInt();

    Serial.readStringUntil('\n');

    int checkBit = 1 << bitNum;

    if (command.equals("set")) {
      ledState = ledState | checkBit;
    } else if (command.equals("reset")) {
      ledState = ledState & ~checkBit;
    } else if (command.equals("check")) {
      if (ledState & checkBit) {
        Serial.println("BIT ON");
      } else {
        Serial.println("BIT OFF");
      }
    } else if (command.equals("toggle")) {
      ledState = ledState ^ checkBit;
    }

    Serial.print("LED STATE: ");
    Serial.println(ledState, BIN);
  }

  for (int i = 0; i < 4; i++) {
    int ledBit = 1 << i;

    if (ledState & ledBit) {
      digitalWrite(LED[i], 1);
    } else {
      digitalWrite(LED[i], 0);
    }
  }

  if (buttonValue == 0) {
    blink(200);
  }
}

void blink(int time) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], 1);
  }

  delay(time);

  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], 0);
  }

  delay(time);
}

int sensorPercent(int pin) {
  int val = analogRead(pin);

  int percent = map(val, 0, 1023, 0, 100);

  return percent;
}