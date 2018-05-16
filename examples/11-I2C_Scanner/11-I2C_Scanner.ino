// =============================================================================
//                           DEVDUINO I2C SCANNER 
// =============================================================================
// Description:
// Search for I2C devices and display their address.
// =============================================================================
// Date: 11/5/2018
// Author: Alexandre Pailhoux
// License: MIT
// =============================================================================
/*=============================================================================
                                  INCLUDES
==============================================================================*/
#include <Wire.h>
#include <devduino.h>
#include "devduinoLogo.h"

byte error, address;
int nDevices;

boolean scanAgain = false;
int tempo = 500;
// =============================================================================
//                                INITIALIZATION
// =============================================================================
void setup()
{
  /*============================================================================
                                  DEVDUINO INIT.
  =============================================================================*/
  devduino.begin();
  devduino.attachToIntButton(buttonPushed);
  display.drawSprite(devduinoLogo, 37, 0);
  display.flush();
  delay(1000);
  display.clear();  
  /*============================================================================
                                  SCAN I2C ONCE
  =============================================================================*/ 
  scanI2C();
}
// =============================================================================
//                                INFINITE LOOP      
//                           -> -> -> -> -> -> -> ->
//                           |                     |              
//                            <- <- <- <- <- <- <- <-
// =============================================================================
void loop()
{
  /*============================================================================
                              SCAN I2C IF BUTTON PUSHED
  =============================================================================*/
  if(scanAgain)
  {
    scanI2C(); 
    scanAgain = false;   
  }
  delay(1);      
}
// =============================================================================
//                                INTERRUPTION                        
//                                     ||          
//                                     ||          
//                               O-----------O    
//                          ------O         0-------                       
// =============================================================================
void buttonPushed()
{
  /*============================================================================
                                  DEBOUNCING FILTER
  =============================================================================*/
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {
    scanAgain=true;
  }   
  last_interrupt_time = interrupt_time;
}
// =============================================================================
//                                I2C SCANNER
// =============================================================================
void scanI2C()
{
  console.println("---------------------");
  console.println("Scanning I2C...");
  console.println("");
  delay(tempo); 
  
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();    
    if (error == 0)
    {
      console.print("Device at:0x");
      if (address<16)
      console.print("0");
      String addressinHEX =  String(address, HEX);
      console.print(addressinHEX);   
      if (addressinHEX.equals("18"))
      {
        console.print(" (TEMP)");     
      }
      else if (addressinHEX.equals("3c"))
      {
        console.print(" (OLED)"); 
      }
      else if (addressinHEX.equals("68"))
      {
        console.print(" (RTC)");    
      }
      else
      {
        console.print(" <----");     
      }
      console.println(""); 
      nDevices++;
      delay(tempo); 
      }
      else if (error==4)
      {
        console.print("Error at:0x");
        if (address<16)
        Serial.print("0");
        String addressinHEX =  String(address, HEX);
        console.print(addressinHEX);
      } 
   }
   delay(tempo); 
   if (nDevices == 0)
   {
    console.println("");
    console.println("No I2C device found.\n");
    console.println("");
   }
   else
   {
    console.println("");
    console.println("Scanning complete.\n");
   }         
}
