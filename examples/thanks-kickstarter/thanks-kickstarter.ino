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
#include <devduinoLogo.h>

//Thanks sprite.
#include "thanksSprite.h"

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

  //Draw thanks sprite.
  display.clear();
  display.drawSprite(thanksSprite, 0, 0);
  display.flush();
}

void loop()
{
  display.verticalScroll(-1, false);
  display.flush();
}
