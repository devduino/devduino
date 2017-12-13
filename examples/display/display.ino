/** MIT License
*
* Copyright(c) 2017 DevDuino
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

//Include board with DevDuino components.
#include <devduino.h>

//DevDuino logo to display a splash screen before example.
#include "devduinoLogo.h"

#define DISPLAY_PERIOD  25

unsigned int exampleId = 0;
boolean startExample = false;


void setup()
{
  //First thing to do is to initialize DevDuino board.
  devduino.begin();

  //Attach "interrupt" button to "buttonPressed" function.
  devduino.attachToIntButton(buttonPressed);
  
  //Draw splash screen to buffer.
  display.drawSprite(devduinoLogo, 37, 0);
  //Then transfer buffer to screen.
  display.flush();
  
  //Sleep for 1 second with splash screen displayed to be able to see it before continuing.
  delay(1000);

  //Display "example" message.
  exampleMessage();
}

void loop()
{
  if (startExample == true)
  {    
    if(exampleId < DISPLAY_PERIOD)
    {
      exampleShapes();
    }
    else if(exampleId < DISPLAY_PERIOD * 2)
    {
      exampleBuffer();
    }
    else if(exampleId < DISPLAY_PERIOD * 3)
    {
      exampleSprite();
    }
    else if(exampleId < DISPLAY_PERIOD * 4)
    {
      exampleScale();
    }
    else if(exampleId < DISPLAY_PERIOD * 5)
    {
      exampleScrolling();
    }
    else if(exampleId < DISPLAY_PERIOD * 6)
    {
        exampleId = 0;
    }
    exampleId++;
  }
  
  delay(100);
}

void exampleMessage()
{
  display.clear();

  display.print(String("Please push \"INT\" button"), 0, 56, &defaultFont);
  display.print(String("to continue example."), 0, 48, &defaultFont);
  
  display.flush();
}

void exampleShapes()
{
  if(exampleId == 1) {
    display.clear();
  
    display.drawLine(0, 0, 40, 20);
    display.drawHorizontalLine(43, 83, 10);
    display.drawVerticalLine(100, 0, 20);
    display.drawRectangle(0, 30, 30, 30);
    display.fillRectangle(32, 30, 30, 30);
    display.drawCircle(80, 45, 15);
    display.fillCircle(112, 45, 15);
    
    display.flush();
  }
}

const uint8_t buffer[32] PROGMEM = {255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0};
  
void exampleBuffer()
{
  if(exampleId == DISPLAY_PERIOD) {
    display.clear();
  
    display.drawBuffer(buffer, 59, 16, 8, 4);
    
    display.flush();
  }
}

void exampleSprite()
{
  if(exampleId == DISPLAY_PERIOD * 2) {
    display.clear();
    
    display.drawSprite(devduinoLogo, 37, 0);
    
    display.flush();
  }
}

void exampleScale()
{
  if(exampleId == DISPLAY_PERIOD * 3) {
    display.clear();

    display.setScale(1);
    display.drawCircle(8, 8, 4);
    
    display.setScale(2);
    display.print(String("Even text"), 10, 15, &defaultFont);
    display.print(String("is zoomed!"), 10, 0, &defaultFont);
    display.drawCircle(16, 16, 8);
    
    display.setScale(3);
    display.drawCircle(32, 32, 16);
    
    display.flush();
  } else if(exampleId == DISPLAY_PERIOD * 4 - 1) {
    display.setScale(1);
  }
}

void exampleScrolling()
{
  if(exampleId == DISPLAY_PERIOD * 4) {
    display.clear();
    
    display.drawSprite(devduinoLogo, 37, 0);
    
    display.flush();
  } else if(exampleId == DISPLAY_PERIOD * 5 - 1) {
    display.resetVerticalScroll();
    
    display.clear();
    
    display.flush();
  } else {
    display.verticalScroll(-1);
    
    display.flush();
  }
}

void buttonPressed()
{
  startExample = true;
}

