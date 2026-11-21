// C++ code

#define t1 500
#define t2 20

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}
void loop() {
  digitalWrite(5, HIGH);
  delay(0);
  digitalWrite(3, HIGH);
  delay(t1);

  digitalWrite(5, LOW);
  delay(0);
  digitalWrite(3, LOW);
  delay(t2);

  digitalWrite(2, HIGH);
  delay(0);
  digitalWrite(6, HIGH);
  delay(0);
  digitalWrite(4, HIGH);
  delay(t1);

  digitalWrite(2, LOW);
  delay(0);
  digitalWrite(6, LOW);
  delay(0);
  digitalWrite(4, LOW);
  delay(t2);
}
