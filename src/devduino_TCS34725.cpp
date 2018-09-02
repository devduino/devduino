#include <Arduino.h>
#include <Wire.h>
#include "devduino_TCS34725.h"
#include <devduino.h>

/*=============================================================================
                             PUBLIC METHODS
=============================================================================*/

/*=============================================================================
                              POWER ON THE TCS3472
==============================================================================*/
boolean DevDuino_TCS3472::ready() 
{
  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_DEVICE_ID);
  Wire.endTransmission();

  Wire.requestFrom(TCS3472_DEVICE_ADDRESS, 1); 
  /*console.println("Device ID is: " + String(Wire.read(), HEX));  */
  deviceID = Wire.read();
  
  if ((deviceID != 0x44) && (deviceID != 0x4D))
  {
    return false;
  }
	
  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_ENABLE);
  Wire.write(TCS3472_REGISTER_VALUE_POWER_ON);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_ENABLE);
  Wire.write(TCS3472_REGISTER_VALUE_POWER_ON | TCS3472_REGISTER_VALUE_RGBC_ENABLE);
  Wire.endTransmission(); 
  
  return true;  
}
  
/*=============================================================================
                             SET THE INTEGRATION TIME
==============================================================================*/
void DevDuino_TCS3472::setIntegrationTime(unsigned int integrationTime)
{
  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_INTEGRATION_TIME_CONTROL);

  switch (integrationTime)
  {
    case 3:
      Wire.write(TCS3472_REGISTER_VALUE_INTEGRATION_TIME_2_4ms);
      break;
    case 24:
      Wire.write(TCS3472_REGISTER_VALUE_INTEGRATION_TIME_24ms);
      break;
    case 101:
      Wire.write(TCS3472_REGISTER_VALUE_INTEGRATION_TIME_101ms);
      break;
    case 154:
      Wire.write(TCS3472_REGISTER_VALUE_INTEGRATION_TIME_154ms);
      break;
    case 700:
      Wire.write(TCS3472_REGISTER_VALUE_INTEGRATION_TIME_700ms);
      break;
  } 
  Wire.endTransmission(); 
  delay(10);
}

/*=============================================================================
                                SET THE GAIN
==============================================================================*/

void DevDuino_TCS3472::setGain(unsigned int gain)
{
  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_GAIN_CONTROL);
 
  switch (gain)
  {
    case 1:
      Wire.write(TCS3472_REGISTER_VALUE_GAIN_1X);
      break;
    case 4:
      Wire.write(TCS3472_REGISTER_VALUE_GAIN_4X);
      break;
    case 16:
      Wire.write(TCS3472_REGISTER_VALUE_GAIN_16X);
      break;
    case 60:
      Wire.write(TCS3472_REGISTER_VALUE_GAIN_60X);
      break;
  } 
  Wire.endTransmission();
}

/*=============================================================================
                                READ THE CLEAR
==============================================================================*/

unsigned int DevDuino_TCS3472::getCLEAR()
{ 
  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_CDATA);
  Wire.endTransmission();

  Wire.requestFrom(TCS3472_DEVICE_ADDRESS, 1);
  LSB = Wire.read();

  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_CDATAH);
  Wire.endTransmission();

  Wire.requestFrom(TCS3472_DEVICE_ADDRESS, 1);
  MSB = Wire.read();
  MSB <<= 8;
  
  return valueCLEAR = MSB | LSB; 
}
/*=============================================================================
                                READ THE RED
==============================================================================*/
unsigned int DevDuino_TCS3472::getRED()
{ 
  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_RDATA);
  Wire.endTransmission();

  Wire.requestFrom(TCS3472_DEVICE_ADDRESS, 1);
  LSB = Wire.read();

  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_RDATAH);
  Wire.endTransmission();

  Wire.requestFrom(TCS3472_DEVICE_ADDRESS, 1);
  MSB = Wire.read();
  MSB <<= 8;
  
  return valueRED = MSB | LSB; 
}
/*=============================================================================
                                READ THE GREEN
==============================================================================*/
unsigned int DevDuino_TCS3472::getGREEN()
{   
  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_GDATA);
  Wire.endTransmission();

  Wire.requestFrom(TCS3472_DEVICE_ADDRESS, 1);
  LSB = Wire.read();

  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_GDATAH);
  Wire.endTransmission();

  Wire.requestFrom(TCS3472_DEVICE_ADDRESS, 1);
  MSB = Wire.read();
  MSB <<= 8;
  
  return valueGREEN = MSB | LSB; 
}
/*=============================================================================
                                READ THE BLUE
==============================================================================*/
unsigned int DevDuino_TCS3472::getBLUE()
{ 
  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_BDATA);
  Wire.endTransmission();

  Wire.requestFrom(TCS3472_DEVICE_ADDRESS, 1);
  LSB = Wire.read();

  Wire.beginTransmission(TCS3472_DEVICE_ADDRESS);
  Wire.write(TCS3472_REGISTER_VALUE_COMMAND_BIT | TCS3472_REGISTER_ADDRESS_BDATAH);
  Wire.endTransmission();

  Wire.requestFrom(TCS3472_DEVICE_ADDRESS, 1);
  MSB = Wire.read();
  MSB <<= 8;
  
  return valueBLUE = MSB | LSB; 
}
/*=============================================================================
                     DISPLAY RGBC ON THE OLED AND RGB LED
==============================================================================*/
void DevDuino_TCS3472::displayRGBC(unsigned int r, unsigned int g, unsigned int b, unsigned int c, unsigned int integrationTime)
{
	display.clear(); 
	if ((deviceID == 0x44))
	  {
		display.print(String("TCS34725"), 40, 55, &defaultFont);
	  }
	else if ((deviceID == 0x4D))
      {
		display.print(String("TCS34727"), 40, 55, &defaultFont);
	  }
	display.drawLine(5, 52, 125, 52);
  
	switch (integrationTime)
	  {
		case 3:
		  maxResolution=1024;
		  break;
		case 24:
		  maxResolution=10240;
		  break;
		case 101:
		  maxResolution=44032;
		  break;
		case 154:
		  maxResolution=65535;
		  break;
		case 700:
		  maxResolution=65535;
		  break;
	  } 
	if (c < (maxResolution/IGNORING_COEFFICIENT))
	{
		analogWrite(LED_PINOUT_RED, 255);
		analogWrite(LED_PINOUT_BLUE, 255);
		analogWrite(LED_PINOUT_GREEN, 255);
		
		display.print(String("R: ")+ String(r), 0, 37, &defaultFont);
		display.print(String((float)r / c * 100.0) + String(" %"), 70, 37, &defaultFont);
		
		display.print(String("G: ")+ String(g), 0, 25, &defaultFont);
		display.print(String((float)g / c * 100.0) + String(" %"), 70, 25, &defaultFont);
		
		display.print(String("B: ")+ String(b), 0, 13, &defaultFont);
		display.print(String((float)b / c * 100.0) + String(" %"), 70, 13, &defaultFont);
		
		display.print(String("C: ")+ String(c), 0, 1, &defaultFont);	
		
		display.print(String((float)( r + g + b) / c * 100.0) + String(" %"), 70, 1, &defaultFont);
		
		display.flush();
		
	}
	/*else if (r==maxResolution || g==maxResolution || b==maxResolution || c==maxResolution)
	  {
		
		display.setScale(2);
		display.print(String("SATURATION"), 2, 10, &defaultFont);
		display.setScale(1);
        display.print(String(maxResolution), 48, 10, &defaultFont);		
		display.flush();
	  }  */
	  
   else
	  {  
		display.print(String("R: ")+ String(r), 0, 37, &defaultFont);
		display.print(String((float)r / c * 100.0) + String(" %"), 70, 37, &defaultFont);
		
		display.print(String("G: ")+ String(g), 0, 25, &defaultFont);
		display.print(String((float)g / c * 100.0) + String(" %"), 70, 25, &defaultFont);
		
		display.print(String("B: ")+ String(b), 0, 13, &defaultFont);
		display.print(String((float)b / c * 100.0) + String(" %"), 70, 13, &defaultFont);
		
		display.print(String("C: ")+ String(c), 0, 1, &defaultFont);		
		display.print(String((float)( r + g + b) / c * 100.0) + String(" %"), 70, 1, &defaultFont);
		
		c = map(c, 0, maxResolution, 0, 255);
	  
		if (r>=b && r>=g)
		{		  
		  g = map(g, 0, r, 0, c);
		  b = map(b, 0, r, 0, c);  		  
		  
		  analogWrite(LED_PINOUT_RED, map(c, 0,255, 255, OFFSET_RGB_LED_RED )); 
		  analogWrite(LED_PINOUT_BLUE, map(b, 0,255, 255, OFFSET_RGB_LED_BLUE));  
		  analogWrite(LED_PINOUT_GREEN, map(g, 0,255, 255, OFFSET_RGB_LED_GREEN ));  	  
  
		}
		else if (g>=b && g>=r)
		{
		  r = map(r, 0, g, 0, c);
		  b = map(b, 0, g, 0, c);  		  
		  
		  analogWrite(LED_PINOUT_RED, map(r, 0,255, 255, OFFSET_RGB_LED_RED )); 
		  analogWrite(LED_PINOUT_BLUE, map(b, 0,255, 255, OFFSET_RGB_LED_BLUE));  
		  analogWrite(LED_PINOUT_GREEN, map(c, 0,255, 255, OFFSET_RGB_LED_GREEN ));  		
		}
		else if (b>=r && b>=g)
		{
		  g = map(g, 0, b, 0, c);
		  r = map(r, 0, b, 0, c);  		  
		  
		  analogWrite(LED_PINOUT_RED, map(r, 0,255, 255, OFFSET_RGB_LED_RED )); 
		  analogWrite(LED_PINOUT_BLUE, map(c, 0,255, 255, OFFSET_RGB_LED_BLUE));  
		  analogWrite(LED_PINOUT_GREEN, map(g, 0,255, 255, OFFSET_RGB_LED_GREEN ));  			
		}  	
	   }
	display.flush();  	   
}

void DevDuino_TCS3472::displayChart(unsigned int r, unsigned int g, unsigned int b, unsigned int c, unsigned int integrationTime)
{
	display.clear(); 
  
	switch (integrationTime)
	  {
		case 3:
		  maxResolution=1024;
		  break;
		case 24:
		  maxResolution=10240;
		  break;
		case 101:
		  maxResolution=44032;
		  break;
		case 154:
		  maxResolution=65535;
		  break;
		case 700:
		  maxResolution=65535;
		  break;
	  } 
	if (c < (maxResolution/IGNORING_COEFFICIENT))
	{
		analogWrite(LED_PINOUT_RED, 255);
		analogWrite(LED_PINOUT_BLUE, 255);
		analogWrite(LED_PINOUT_GREEN, 255);	

		  display.drawLine(5, 55, 125, 55);
		  display.drawVerticalLine(5, 0, 55);
		  display.drawVerticalLine(35, 0, 55);
		  display.drawVerticalLine(65, 0, 55);
		  display.drawVerticalLine(95, 0, 55);
		  display.drawVerticalLine(125, 0, 55);	
		  
		  display.print("R", 18, 56, &defaultFont);  
		  display.fillRectangle(10, 0, 20, map(r, 0,maxResolution, 0, 55));
		  
		  display.print("G", 48, 56, &defaultFont);
		  display.fillRectangle(40, 0, 20, map(g, 0,maxResolution, 0, 55));
		  
		  display.print("B", 78, 56, &defaultFont);
		  display.fillRectangle(70, 0, 20, map(b, 0,maxResolution, 0, 55));	
		  
		  display.print("C", 108, 56, &defaultFont);
          display.fillRectangle(100, 0, 20, map(c, 0,maxResolution, 0, 55));	
		 
		c = map(c, 0, maxResolution, 0, 255);
		
		display.flush();
		
	}		
	/*else if (r==maxResolution || g==maxResolution || b==maxResolution || c==maxResolution)
	  {		
		
		display.setScale(2);
		display.print(String("SATURATION"), 2, 10, &defaultFont);
		display.setScale(1);
        display.print(String(maxResolution), 48, 10, &defaultFont);		
		display.flush();
	  }  */
   else
	  {  		
		  display.drawLine(5, 55, 125, 55);
		  display.drawVerticalLine(5, 0, 55);
		  display.drawVerticalLine(35, 0, 55);
		  display.drawVerticalLine(65, 0, 55);
		  display.drawVerticalLine(95, 0, 55);
		  display.drawVerticalLine(125, 0, 55);		  
		  
		  display.print("R", 18, 56, &defaultFont);  
		  display.fillRectangle(10, 0, 20, map(r, 0,maxResolution, 0, 55));
		  
		  display.print("G", 48, 56, &defaultFont);
		  display.fillRectangle(40, 0, 20, map(g, 0,maxResolution, 0, 55));
		  
		  display.print("B", 78, 56, &defaultFont);
		  display.fillRectangle(70, 0, 20, map(b, 0,maxResolution, 0, 55));	
		  
		  display.print("C", 108, 56, &defaultFont);
          display.fillRectangle(100, 0, 20, map(c, 0,maxResolution, 0, 55));	

		 
		c = map(c, 0, maxResolution, 0, 255);
	  
		if (r>=b && r>=g)
		{		  
		  g = map(g, 0, r, 0, c);
		  b = map(b, 0, r, 0, c);  		  
		  
		  analogWrite(LED_PINOUT_RED, map(c, 0,255, 255, OFFSET_RGB_LED_RED )); 
		  analogWrite(LED_PINOUT_BLUE, map(b, 0,255, 255, OFFSET_RGB_LED_BLUE));  
		  analogWrite(LED_PINOUT_GREEN, map(g, 0,255, 255, OFFSET_RGB_LED_GREEN ));  	  
  
		}
		else if (g>=b && g>=r)
		{
		  r = map(r, 0, g, 0, c);
		  b = map(b, 0, g, 0, c);  		  
		  
		  analogWrite(LED_PINOUT_RED, map(r, 0,255, 255, OFFSET_RGB_LED_RED )); 
		  analogWrite(LED_PINOUT_BLUE, map(b, 0,255, 255, OFFSET_RGB_LED_BLUE));  
		  analogWrite(LED_PINOUT_GREEN, map(c, 0,255, 255, OFFSET_RGB_LED_GREEN ));  		
		}
		else if (b>=r && b>=g)
		{
		  g = map(g, 0, b, 0, c);
		  r = map(r, 0, b, 0, c);  		  
		  
		  analogWrite(LED_PINOUT_RED, map(r, 0,255, 255, OFFSET_RGB_LED_RED )); 
		  analogWrite(LED_PINOUT_BLUE, map(c, 0,255, 255, OFFSET_RGB_LED_BLUE));  
		  analogWrite(LED_PINOUT_GREEN, map(g, 0,255, 255, OFFSET_RGB_LED_GREEN ));  			
		}  	
		display.flush();
	   }	
}


/*=============================================================================
                             CONSTRUCTOR
=============================================================================*/
DevDuino_TCS3472::DevDuino_TCS3472(){}