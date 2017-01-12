// ATTiny based I2C relay control
// ForkRobotics 2012
//
 
#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#include <avr/wdt.h>

#define I2C_SLAVE_ADDR  0x3            // i2c slave address (0x3 for boiler, 0x4 for furnace)
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
  
  wdt_enable(WDTO_8S);                  //8 second watchdog timer
}
 
void loop()
{
  wdt_reset();
  //1 = Assert on
  //2 = OFF (Relay1 HIGH, Relay2 HIGH)
  //3 = LOW (Relay1 HIGH, Relay2 LOW)
  //4 = MEDIUM (Relay1 LOW, Relay2 HIGH)
  //5 = HIGH (Relay1 LOW, Relay2 LOW)
  
  byte byteRcvd = 0;
  if (TinyWireS.available())
  {           // got I2C input!
    byteRcvd = TinyWireS.receive();     // get the byte from master
      switch (byteRcvd) 
      {
        case 0x01:                      //assert relay on
          digitalWrite(Relay1_PIN, HIGH);
          toggleLEDs();
        break;
        
        case 0x02:                      //OFF
          digitalWrite(Relay2_PIN, HIGH);
          digitalWrite(Relay3_PIN, HIGH);
          digitalWrite(LED1_PIN, HIGH);
          digitalWrite(LED2_PIN, HIGH);
          digitalWrite(LED3_PIN, HIGH);
          delay(100);
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
        
      }//end switch case
   }//end if TinyWireS.available
}//end loop

void toggleLEDs()
{
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, HIGH);
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
    digitalWrite(LED3_PIN, !digitalRead(LED3_PIN));
    delay(250);
  }
}

