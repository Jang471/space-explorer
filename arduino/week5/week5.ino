#define TRIG A4
#define ECHO A5
#define BUZZER 13

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  int distance = pulseIn(ECHO, HIGH) * 0.017;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  if (distance < 20) {
    tone(BUZZER, 262);
  } else {
    noTone(BUZZER);
  }

  delay(100);
}