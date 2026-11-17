#define BUTTON 2
#define VARIABLE_R A1
#define LIGHT A3

int prev_value = 0;

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(VARIABLE_R, INPUT);
  pinMode(LIGHT, INPUT);

  Serial.begin(9600);
}

void loop() {
  int value1 = analogRead(VARIABLE_R);
  int value2 = analogRead(LIGHT);

  Serial.print(value1);
  Serial.print(",");

  Serial.print(value2);
  Serial.print(",");

  int value3 = digitalRead(BUTTON);

  if (value3 == 0 && prev_value == 1) {
    Serial.println("pressed");
  } else {
    Serial.println("unpressed");
  }

  prev_value = value3;

  delay(30);
}