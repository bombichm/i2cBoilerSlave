// ATTiny based I2C relay control
// ForkRobotics 2012
//
 
#include "TinyWireS.h"                  // wrapper class for I2C slave routines
 
#define I2C_SLAVE_ADDR  0x3            // i2c slave address
#define Relay1_PIN  7
#define Relay2_PIN  5
#define Relay3_PIN  3
#define LED1_PIN    0
#define LED2_PIN    1
#define LED3_PIN    2
 
void setup()
{
  pinMode(Relay1_PIN,OUTPUT);
  pinMode(Relay2_PIN,OUTPUT);
  pinMode(Relay3_PIN,OUTPUT);
  pinMode(LED1_PIN,OUTPUT);
  pinMode(LED2_PIN,OUTPUT);
  pinMode(LED3_PIN,OUTPUT);
  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
}
 
void loop()
{
  //1 = Assert off
  //2 = Assert on, set to OFF
  //3 = LOW
  //4 = MEDIUM
  //5 = HIGH
  
  byte byteRcvd = 0;
  if (TinyWireS.available()){           // got I2C input!
    byteRcvd = TinyWireS.receive();     // get the byte from master
      switch (byteRcvd) {
        case 0x01:                      //assert relay off
          digitalWrite(Relay1_PIN, LOW);
          digitalWrite(Relay2_PIN, LOW);
          digitalWrite(Relay3_PIN, LOW);
          digitalWrite(LED1_PIN, LOW);
          digitalWrite(LED2_PIN, LOW);
          digitalWrite(LED3_PIN, LOW);
        break;
        
        case 0x02:                      //assert relay on (initialize, LED function test, and set to OFF)
          digitalWrite(Relay1_PIN, HIGH);
          digitalWrite(Relay2_PIN, HIGH);
          digitalWrite(Relay3_PIN, HIGH);
          digitalWrite(LED1_PIN, HIGH);
          digitalWrite(LED2_PIN, HIGH);
          digitalWrite(LED3_PIN, HIGH);
          delay(1000);
          digitalWrite(LED1_PIN, LOW);
          digitalWrite(LED2_PIN, LOW);
          digitalWrite(LED3_PIN, LOW);
        break;
        
        case 0x03:                      //LOW
          digitalWrite(Relay2_PIN, HIGH);
          digitalWrite(Relay3_PIN, LOW);
          digitalWrite(LED1_PIN, HIGH);
          digitalWrite(LED2_PIN, LOW);
          digitalWrite(LED3_PIN, LOW);
        break;
        
        case 0x04:                      //MEDIUM
          digitalWrite(Relay2_PIN, LOW);
          digitalWrite(Relay3_PIN, HIGH);
          digitalWrite(LED1_PIN, LOW);
          digitalWrite(LED2_PIN, HIGH);
          digitalWrite(LED3_PIN, LOW);
        break;
        
        case 0x05:                      //HIGH
          digitalWrite(Relay2_PIN, LOW);
          digitalWrite(Relay3_PIN, LOW);
          digitalWrite(LED1_PIN, LOW);
          digitalWrite(LED2_PIN, LOW);
          digitalWrite(LED3_PIN, HIGH);
        break;
        
      }
 
  }
}

