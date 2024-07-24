#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte address[6] = "00069";

const int potPin = A5;
const int Vrx = A3;
const int Vry = A2;

struct ControlData {
  int motorSpeed;
  int ailerons;
  int elevator;
};

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int motorSpeed = map(potValue, 0, 1023, 0, 180);

  int potX = analogRead(Vrx);
  int ailerons = map(potX, 0, 1023, 0, 180);

  int potY = analogRead(Vry);
  int elevator = map(potY, 0, 1023, 0, 180);

  ControlData dataToSend = {motorSpeed, ailerons, elevator};

  Serial.print("Motor Speed: ");
  Serial.println(dataToSend.motorSpeed);
  Serial.print("Ailerons: ");
  Serial.println(dataToSend.ailerons);
  Serial.print("Elevator: ");
  Serial.println(dataToSend.elevator);

  radio.write(&dataToSend, sizeof(dataToSend));

delay(250);
}
