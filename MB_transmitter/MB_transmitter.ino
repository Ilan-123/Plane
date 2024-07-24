#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int Vry = A2;
const int Vrx = A3;
const int potPin = A5;

RF24 radio(7, 8);

const byte address[6] = "00069";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  Serial.begin(9600);  // Initialize Serial communication
}

void loop() {
   //delay(5);
  int potValue = analogRead(potPin);  // Read the potentiometer value (0-1023)
  int motorSpeed = map(potValue, 0, 1023 , 0, 180);  // Map potentiometer value to motor speed (0-180)
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
  Serial.println(motorSpeed);
  radio.write(&motorSpeed, sizeof(motorSpeed));

  int potX = analogRead(Vrx);            
  int airlerons = map(potX, 1023, 0, 0, 180);                  
  int potY = analogRead(Vry);
  int elevator = map(potY, 1023, 0, 0, 180);
  Serial.println(potY);
  Serial.println(potX);
 radio.write(&airlerons, sizeof(airlerons));
 radio.write(&elevator, sizeof(elevator));  
  
     delay(200);
}

// Remove any propeller on the motor.
//Unplug the battery from ESC and switch off the radio.
//Put the throttle stick to highest throttle and turn on the radio.
//Make sure the battery is fully charged. Plug the battery to the ESC.
//Listen - Once you hear the first 'beeps' from the motor and ESC immediately pull down the throttle stick to the lowest point.
//The ESC/Motor will do another 'beeps' to confirm the calibration setup.
//You shouldn't have any continuous beeps problem once you get it right.
