// =============================================================================
//                  DEVDUINO TCS3472 COLOR SENSOR WITH RGB LED
// =============================================================================
// Description:
/* Get the RGBC of the TCS3472 color sensor and display a chart on the OLED.
 * Use the push button to display the raw data.
 * You can adjust gain and integration time of the sensor.
 */
// =============================================================================
// Date: 14/05/2018
// Author: Alexandre Pailhoux
// License: MIT
// =============================================================================
/*=============================================================================
                                   INCLUDES
==============================================================================*/
#include <Wire.h>
#include <Arduino.h>
#include <devduino.h>
#include <devduino_TCS34725.h>
#include <devduinoLogo.h>
/*=============================================================================
                                  DEFINITIONS
==============================================================================*/
/*=============================================================================
                                GLOBAL VARIABLES
==============================================================================*/
uint16_t  valueRED   = 0;
uint16_t  valueGREEN = 0;
uint16_t  valueBLUE  = 0;
uint16_t  valueCLEAR = 0;

uint8_t gain = 4;  //1 or 4 or 16 or 60
uint16_t integrationTime = 24;  //3 or 24 or 101 or 154 or 700

boolean displayRawData = false;
/*=============================================================================
                                   INSTANCES
==============================================================================*/
DevDuino_TCS3472 TCS3472 = DevDuino_TCS3472();
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
                                   DIGITAL OUT
  =============================================================================*/
  pinMode(LED_PINOUT_WHITE, OUTPUT);
  TCCR3B = TCCR3B & 0b11111000 | 0x01;
  TCCR1B = TCCR1B & 0b11111000 | 0x01;
  TCCR0B = TCCR0B & 0b11111000 | 0x01;
  analogWrite(LED_PINOUT_WHITE, 100);

  if (!TCS3472.ready()) 
  {    
    console.println("TCS3472 not found! :(");  
    console.println("");    
    console.println("Get yours on:");
    console.println("");
    console.println("devduino.cc :)");
    while (1);
  }   
  delay(1000);
  TCS3472.setGain(gain);
  TCS3472.setIntegrationTime(integrationTime);  
}
// =============================================================================
//                               INFINITE LOOP      
//                          -> -> -> -> -> -> -> ->
//                          |                     |              
//                          <- <- <- <- <- <- <- <-
// =============================================================================
void loop()
{
  delay(integrationTime);

  valueCLEAR = TCS3472.getCLEAR();
  valueRED   = TCS3472.getRED();
  valueGREEN = TCS3472.getGREEN();
  valueBLUE = TCS3472.getBLUE();  
  
  if (displayRawData)
  {
    TCS3472.displayRGBC(valueRED,valueGREEN,valueBLUE,valueCLEAR,integrationTime);
  }
  else
  {
    TCS3472.displayChart(valueRED,valueGREEN,valueBLUE,valueCLEAR,integrationTime);
  }  
}   
 //=============================================================================
 //                              INTERRUPTION                        
 //                                   ||          
 //                                   ||          
 //                             O-----------O    
 //                        ------O         0-------                       
 //=============================================================================
void buttonPushed()
{
  //============================================================================
  //                             DEBOUNCING FILTER
  //=============================================================================

  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200)
  {  
    displayRawData = !displayRawData;      
  }
 last_interrupt_time = interrupt_time; 
}