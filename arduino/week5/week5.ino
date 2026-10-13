#define BUTTON 2
#define VARIABLE_R A1

const int LED[] = {6, 7, 8, 12};

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(VARIABLE_R, INPUT);

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
    digitalWrite(LED[i], 0);
  }

  int num = map(percent, 0, 100, 0, 4);

  for (int i = 0; i < num; i++) {
    digitalWrite(LED[i], 1);
  }

  if (value == 0) {
    blink(200);
  }

  delay(100);
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