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

//The sprite representing the thermometer.
#include "thermometerSprite.h"

//Initialize program.
void setup()
{
  //First thing to do is to initialize DevDuino board.
  devduino.begin();
  
  //Draw splash screen to buffer.
  display.drawSprite(devduinoLogo, 37, 0);
  //Then transfer buffer to screen.
  display.flush();
  
  //Sleep for 1 second with splash screen displayed to be able to see it before continuing.
  delay(1000);
}

//Loop over program execution.
void loop()
{
  //Erase whole display buffer. No need to flush right now, we will flush on next drawing operation.
  display.clear();

  //Draw text on top right corner of screen.
  display.print(String("Temperature"), 60, 50, &defaultFont);
  display.print(String("example"), 60, 43, &defaultFont);

  //Read temperature from sensor.
  float currentTemperature = temperature.read();

  //Draw the temperature using a graphical represention.
  drawGraphicalTemperature(currentTemperature);
  
  //Draw the same temperature using a simple text represention.
  drawTextTemperature(currentTemperature);

  //Render buffer that has been updated by the "draw..." and "write" functions.
  display.flush();

  //No need to refresh very quickly.
  delay(500);
}

//Draw the thermometer and its temperature bar.
void drawGraphicalTemperature(float currentTemperature)
{
  //Draw the sprite of thermometer.
  display.drawSprite(thermometerSprite, 0, 0);

  //Fill temperature bar.
  display.fillRectangle(33, 7, 5, (currentTemperature - 15) * 2);
}

//Draw temperature as a simple text.
void drawTextTemperature(float currentTemperature)
{
  //Display text except for "degree" symbol (let an empty space for it) which is not part of DevDuino font.
  display.print(String(currentTemperature) + "  C", 60, 15, &defaultFont);
  //Display a lowercase 'o' above the previous text to simulate the degree (°) symbol.
  display.print(String("o"), 95, 19, &defaultFont);
}

