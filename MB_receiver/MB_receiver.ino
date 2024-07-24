#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo motor;
Servo airleron1;
Servo airleron2;
Servo elevatorServo;

int elevator;
int motorSpeed;
int airlerons;

RF24 radio(7, 8);

const byte address[6] = "00069";

void setup() {
  motor.attach(6, 1000, 2000);
  airleron1.attach(5, 900, 2000);
  airleron2.attach(3, 900, 2000);
  elevatorServo.attach(9, 900, 2000);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();

  Serial.begin(9600);
  
}

void loop() {
 
 
  if (radio.available()) {
    while(radio.available()){
    

    radio.read(&motorSpeed, sizeof(motorSpeed));
  
        motor.write(motorSpeed);  // Set motor speed
        
        Serial.print("Received Motor Speed: ");
        Serial.println(motorSpeed);

    radio.read(&elevator, sizeof(elevator));

        elevatorServo.write(elevator);
       
        Serial.print("Received elevator: ");
      Serial.println(elevator);

    radio.read(&airlerons, sizeof(airlerons));

        airleron1.write(airlerons);
      int air2 = map(airlerons, 180, 0, 0, 180);
      airleron2.write(air2);
      
Serial.print("Received airleron: ");
      Serial.println(airlerons);

      delay(200);
    }
       
       
    }
  }
