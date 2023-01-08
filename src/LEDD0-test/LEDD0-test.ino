#define LEDD0 13  // PC1
#define LEDD1 14  // PC2

void setup() {
  pinMode(LEDD0, OUTPUT);
  pinMode(LEDD1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDD0, LOW); // IR LEDS gaan aan
  delay(500);
  digitalWrite(LEDD0, HIGH); // IR LEDS gaan uit
  delay(500);
  digitalWrite(LEDD1, LOW); // IR LEDS gaan aan
  delay(500);
  digitalWrite(LEDD1, HIGH); // IR LEDS gaan uit
  delay(500);
}
