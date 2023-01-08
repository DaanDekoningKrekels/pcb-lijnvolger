#define LEDD0 7  // PC1
#define LEDD1 8  // PC2

#define SENSE0 3 // PB0
#define SENSE1 2 // PB1

void setup() {
  pinMode(LEDD0, OUTPUT);
  pinMode(SENSE0, INPUT);
  pinMode(SENSE1, INPUT);
}

void loop() {
  digitalWrite(LEDD0, LOW); // IR LEDS gaan aan
  delay(10);
  byte sense0 = analogRead(SENSE0);
  byte sense1 = analogRead(SENSE1);


  delay(500);
  digitalWrite(LEDD0, HIGH); // IR LEDS gaan uit
  delay(500);
}