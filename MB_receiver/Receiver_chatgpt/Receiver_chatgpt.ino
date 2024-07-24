#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);

const byte address[6] = "00069";

Servo motor;
Servo aileron1;
Servo aileron2;
Servo elevatorServo;

struct ControlData {
  int motorSpeed;
  int ailerons;
  int elevator;
};

void setup() {
  Serial.begin(9600);

  motor.attach(6, 1000, 2000);

  motor.write(180);
  delay(2000);
  motor.write(0);
  
  aileron1.attach(5, 900, 2000);
  aileron2.attach(3, 900, 2000);
  elevatorServo.attach(9, 900, 2000);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {
  if (radio.available()){
    while (radio.available()){
    ControlData receivedData;
    radio.read(&receivedData, sizeof(receivedData));

    motor.write(receivedData.motorSpeed);
    aileron1.write(receivedData.ailerons);
    aileron2.write(map(receivedData.ailerons, 0, 180, 180, 0));
    elevatorServo.write(receivedData.elevator);

    Serial.print("Received Motor Speed: ");
    Serial.println(receivedData.motorSpeed);
    Serial.print("Received Ailerons: ");
    Serial.println(receivedData.ailerons);
    Serial.print("Received Elevator: ");
    Serial.println(receivedData.elevator);
    delay(250);
  }}
}
