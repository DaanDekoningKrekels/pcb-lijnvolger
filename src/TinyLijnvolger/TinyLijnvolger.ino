#include <Wire.h>


#define LEDD0 PIN_PC1  // PC1
#define LEDD1 PIN_PC2  // PC2

#define AANTAL_SENSE_PINS 8
#define SENSE0 PIN_PB0  // PB0
#define SENSE1 PIN_PB1  // PB1
#define SENSE2 PIN_PA6  // PA6
#define SENSE3 PIN_PA7  // PA7
#define SENSE4 PIN_PA5  // PA5
#define SENSE5 PIN_PA4  // PA4
#define SENSE6 PIN_PB4  // PB4
#define SENSE7 PIN_PB5  // PB5

const byte SENSE_PINS[AANTAL_SENSE_PINS] = { SENSE0, SENSE1, SENSE2, SENSE3, SENSE4, SENSE5, SENSE6, SENSE7 };
char readings_to_send[AANTAL_SENSE_PINS];

// De master kan verschillende werkingsmodi selecteren door een byte te sturen
// de FAST modi verbruiken meer stroom omdat de IR LED's daar altijd aan staan
// ANALOG stuurt een byte met de analoge waarde van de fotointerruptor
// DIGITAL stuurt een byte met 1 of 0
enum STATES { IDLE,
              FAST_DIGITAL,
              FAST_ANALOG,
              ANALOG,
              DIGITAL };
STATES current_state = IDLE;
STATES new_state = IDLE;

void setup() {
  pinMode(LEDD0, OUTPUT);
  pinMode(LEDD1, OUTPUT);
  for (byte i = 0; i < AANTAL_SENSE_PINS; i++) {
    pinMode(SENSE_PINS[i], INPUT);
  }

  Wire.pins(PIN_PA1, PIN_PA2);
  Wire.begin(0x55);                 // join i2c bus met adres 0x55
  Wire.onRequest(requestEvent);     // register event
  Wire.onReceive(receiveNewState);  // give the Wire library the name of the function
}

void loop() {
  if (new_state != current_state) {
    switch (new_state) {
      case FAST_ANALOG:
        digitalWrite(LEDD0, LOW);  // IR LEDS gaan aan
        digitalWrite(LEDD1, LOW);  // IR LEDS gaan aan

        break;
      case FAST_DIGITAL:
        digitalWrite(LEDD0, LOW);  // IR LEDS gaan aan
        digitalWrite(LEDD1, LOW);  // IR LEDS gaan aan

        break;
      case ANALOG:
        digitalWrite(LEDD0, HIGH);  // IR LEDS gaan uit
        digitalWrite(LEDD1, HIGH);  // IR LEDS gaan uit

        break;
      case DIGITAL:
        digitalWrite(LEDD0, HIGH);  // IR LEDS gaan uit
        digitalWrite(LEDD1, HIGH);  // IR LEDS gaan uit
        break;
      default:
        break;
    }
    current_state = new_state;
  }

  delay(1);
}

bool prepare_readings() {
  switch (new_state) {
    case FAST_ANALOG:
      read_pins_analog_fast();
      return true;
      break;
    case FAST_DIGITAL:
      read_pins_digital_fast();
      return true;
      break;
    case ANALOG:
      read_pins_analog();
      return true;
      break;
    case DIGITAL:
      read_pins_digital();
      return true;
      break;
    default:
      return false;
      ;
  }
}

void read_pins_analog_fast() {
    readings_to_send[0] = (char)analogRead(SENSE_PINS[0]);
    readings_to_send[1] = (char)analogRead(SENSE_PINS[1]);
    readings_to_send[2] = (char)analogRead(SENSE_PINS[2]);
    readings_to_send[3] = (char)analogRead(SENSE_PINS[3]);
    readings_to_send[4] = (char)analogRead(SENSE_PINS[4]);
    readings_to_send[5] = (char)analogRead(SENSE_PINS[5]);
    readings_to_send[6] = (char)analogRead(SENSE_PINS[6]);
    readings_to_send[7] = (char)analogRead(SENSE_PINS[7]);
}

// Idealiter maakt deze functie één byte met iedere bit de waarde van een pin
void read_pins_digital_fast() {
    readings_to_send[0] = (char)digitalRead(SENSE_PINS[0]);
    readings_to_send[1] = (char)digitalRead(SENSE_PINS[1]);
    readings_to_send[2] = (char)digitalRead(SENSE_PINS[2]);
    readings_to_send[3] = (char)digitalRead(SENSE_PINS[3]);
    readings_to_send[4] = (char)digitalRead(SENSE_PINS[4]);
    readings_to_send[5] = (char)digitalRead(SENSE_PINS[5]);
    readings_to_send[6] = (char)digitalRead(SENSE_PINS[6]);
    readings_to_send[7] = (char)digitalRead(SENSE_PINS[7]);
}

void read_pins_analog() {
  digitalWrite(LEDD0, LOW);  // IR LEDS gaan aan
  digitalWrite(LEDD1, LOW);  // IR LEDS gaan aan
  delay(10);

  for (byte i = 0; i < AANTAL_SENSE_PINS; i++) {
    readings_to_send[i] = (char)analogRead(SENSE_PINS[i]);
  }

  delay(10);
  digitalWrite(LEDD0, HIGH);  // IR LEDS gaan uit
  digitalWrite(LEDD1, HIGH);  // IR LEDS gaan uit
}

// Idealiter maakt deze functie één byte met iedere bit de waarde van een pin
void read_pins_digital() {
  digitalWrite(LEDD0, LOW);  // IR LEDS gaan aan
  digitalWrite(LEDD1, LOW);  // IR LEDS gaan aan
  delay(10);

  for (byte i = 0; i < AANTAL_SENSE_PINS; i++) {
    readings_to_send[i] = (char)digitalRead(SENSE_PINS[i]);
  }

  delay(10);
  digitalWrite(LEDD0, HIGH);  // IR LEDS gaan uit
  digitalWrite(LEDD1, HIGH);  // IR LEDS gaan uit
}

// Aanvraag voor de waarde van de fotointerrupters
void requestEvent() {
  if (prepare_readings()){
    Wire.print(readings_to_send);  // respond with message of 8 bytes
  }else{
    Wire.write(0x00);
  }
}

// Wanneer de master een nieuwe status doorgeeft
void receiveNewState(int16_t numBytes) {  // the Wire API tells us how many bytes
  if (numBytes == 1) {
    new_state = STATES(Wire.read());
  }
}