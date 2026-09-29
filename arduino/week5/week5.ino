#define TRIG A4
#define ECHO A5

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

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

  delay(100);
}