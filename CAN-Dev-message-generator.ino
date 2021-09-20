#include <SPI.h>
#include <string.h>
#include "mcp2515_can.h"
#include "FrameGenerator.h"

const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

#define framesCount 10
CanFrame frames[framesCount];
FrameGenerator generator(framesCount);

volatile bool state = true;

byte switchBtn = 3;
byte stateLED = 7;
byte dataLED = 6;
byte canIntLED = 5;

bool canIntState = false;

void setup() {
  pinMode(stateLED, OUTPUT);
  pinMode(dataLED, OUTPUT);
  pinMode(canIntLED, OUTPUT);
  pinMode(switchBtn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), switchMode, FALLING);
  attachInterrupt(digitalPinToInterrupt(2), testCANInt, CHANGE);
  Serial.begin(115200);

  while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_8MHz)) {             // init can bus : baudrate = 500k, crystal oscillator = 8 MHz
      Serial.write(20);
      delay(100);
  }
  Serial.write(10);
}


void loop() {
  digitalWrite(stateLED, LOW);
  while (state) {
    digitalWrite(stateLED, HIGH);
    digitalWrite(dataLED, HIGH);
    generator.generateFrames(frames, framesCount);
    
    for (byte i = 0; i < framesCount; ++i) {
      CAN.sendMsgBuf(frames[i].id, 0, frames[i].dlc, frames[i].data, true);
      delay(2);
    }
    digitalWrite(dataLED, LOW);
    if (state) {
      delay(200);
    }
  }
}

void switchMode() {
  state = !state;
}

void testCANInt() {
  canIntState = !canIntState;
  digitalWrite(canIntLED, canIntState);
}
  
//  if (CAN.checkReceive() == CAN_MSGAVAIL) {         // check if data available
//    CanFrame frame;
//    unsigned char len;
//    
//    frame.id = CAN.getCanId();
//    CAN.readMsgBuf(&frame.dlc, frame.data);    // read data,  len: data length, frame.data: data buf

    // sending received data
//    Serial.write(frame.id);
//    for (byte i = 0; i < 8; ++i) {
//      Serial.write(frame.data[i]);
//    }

//    Serial.print(frame.id, HEX);
//    for (byte i = 0; i < 8; ++i) {
//      Serial.print(' ');
//      Serial.print(frame.data[i]), HEX;
//    }
//    Serial.print('\n');
//  }
  // отправляем случайные данные
//  CanFrame frame;
//  unsigned char len;
//
//  frame.id = random();
//  for (byte i = 0; i < 8; ++i) {
//    frame.data[i] = random(256);
//  }
//
//  Serial.write(frame.id);
//  for (byte i = 0; i < 8; ++i) {
//    Serial.write(frame.data[i]);
//  }
    
//    if (Serial.available() > 0) {  //если есть доступные данные
//        // считываем байт
//        int bytesAvailable = Serial.available();
//        for (int i = 0; i < bytesAvailable; ++i) {
//          incomingBytes[i] = Serial.read();
//          
//          Serial.print("Byte = ");
//          Serial.print(incomingBytes[i], HEX);
//          Serial.print("\n");
//        }
//
//        // отсылаем то, что получили
//        Serial.print("I received: ");
//        
//        for (byte i = 0; i < bytesAvailable; ++i) {
//          Serial.write(incomingBytes[i]);
//          //Serial.print("\n");
//        }   
//    }
//    delay(500);

//END FILE
