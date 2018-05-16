// =============================================================================
//                                PROJECT NAME
// =============================================================================
// Description:
/* This template aims to make your new project developpement easier than
 * starting from scratch.
 * It already includes basics methods so you can just uncomment/copy/paste/delete 
 * what you need or don't need and not waste too much time with syntax errors.
 * Hope it will help!
 */
// =============================================================================
// Date: 
// Author:
// License: MIT
// =============================================================================
/*=============================================================================
                                   INCLUDES
==============================================================================*/
//#include <Wire.h>
//#include <SoftwareSerial.h>
#include <devduino.h>
#include "devduinoLogo.h"
/*=============================================================================
                                  DEFINITIONS
==============================================================================*/
//#define RED_LED     13
/*=============================================================================
                                GLOBAL VARIABLES
==============================================================================*/
//String messageFromUART= "";
/*=============================================================================
                                   INSTANCES
==============================================================================*/
//SoftwareSerial UART(10,12);

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

  // ---------------------------------------------------------------------------
  // DO YOUR INIT HERE...  
  // ---------------------------------------------------------------------------
  
  /*============================================================================
                                   DIGITAL IN
  =============================================================================*/
   //pinMode(RED_LED, OUTPUT);
   //digitalWrite(RED_LED, HIGH);
  /*============================================================================
                                   DIGITAL OUT
  =============================================================================*/
  // pinMode(8, INPUT_PULLUP);
  // int buttonState = digitalRead(8);
  /*============================================================================
                                   ANALOG OUT
  =============================================================================*/
  // pinMode(6, OUTPUT);
  // analogWrite(6, 255);
  /*============================================================================
                                   ANALOG IN
  =============================================================================*/
  // int sensorValue = analogRead(A0);
  // float voltage = sensorValue * (5.0 / 1023.0);
  /*============================================================================
                                CONSOLE/TERMINAL
  =============================================================================*/
  // console.println("... Your string here...");  
  /*============================================================================
                                   DISPLAY
  =============================================================================*/
  // display.print(String("... Your string here..."), 128, 64, &defaultFont);
  //display.setScale(1); // 1 or 2
  /*============================================================================
                                  SCROLL DOWN
  =============================================================================*/
  /*
  for (;;)
  {
    display.verticalScroll(-1, false);
    display.flush();
    delay(100);
  }
  */  
}
// =============================================================================
//                               INFINITE LOOP      
//                          -> -> -> -> -> -> -> ->
//                          |                     |              
//                          <- <- <- <- <- <- <- <-
// =============================================================================
void loop()
{
  // ---------------------------------------------------------------------------
  // DO YOUR INFINITE LOOP HERE...
  // ---------------------------------------------------------------------------
  
  delay(1);
  /*============================================================================
                                 UART READING
  =============================================================================*/  
  /*    
        
   while(UART.available()) 
   {
    delay(3);
     char c = UART.read();
    messageFromUART+= c;
   }
   if (messageFromUART.length() >0) 
   {  
    console.println(messageFromUART);
    if ((messageFromUART.indexOf("D00") != -1)) 
    {
     if ((messageFromUART.indexOf("ON") != -1)) 
     {
      digitalWrite(0,HIGH);      
     }
    }
    messageFromUART="";
   }   
  /*============================================================================
                               TEMPERATURE READING
  =============================================================================*/
  /*
  float currentTemperature = temperature.read();
 
  display.clear();  
  display.setScale(2);
  display.print(String(currentTemperature) + " C", 10, 10, &defaultFont);
  display.print(String("o"), 40, 12, &defaultFont);  
  display.flush();
  display.setScale(1);

  */
  /*============================================================================
                                  RTC READING
  =============================================================================*/
  /*
  
  DateTime currentClock = rtc.now();
  uint8_t hour = currentClock.getHour();
  uint8_t minute = currentClock.getMinute();
  uint8_t second = currentClock.getSecond();
  
  char dateBuffer[10];
  sprintf(dateBuffer, "%04d-%02d-%02d", currentClock.getYear(), currentClock.getMonth(), currentClock.getDay());
  char timeBuffer[9];
  sprintf(timeBuffer, "%02dh%02dm%02ds", currentClock.getHour(), currentClock.getMinute(), currentClock.getSecond());
  display.clear();
  display.print(String(timeBuffer), 30, 30, &defaultFont);
  display.flush();
  
  */    
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
    // ---------------------------------------------------------------------------
    // DO YOUR INTERRUPTION HERE...   
    // ---------------------------------------------------------------------------
  }   
  last_interrupt_time = interrupt_time;
}