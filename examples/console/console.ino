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

//Include board constants to get "INT" button pin.
#include <devduino.h>

//DevDuino logo to display a splash screen before example.
#include "devduinoLogo.h"

//Initialize program.
void setup()
{
  //First step is to initialize DevDuino board.
  devduino.begin();

  //Attach "interrupt" button to "buttonPressed" function.
  devduino.attachToIntButton(buttonPressed);
  
  //Draw splash screen to buffer.
  display.drawSprite(devduinoLogo, 37, 0);
  //Then transfer buffer to screen.
  display.flush();
  
  //Sleep for 1 second with splash screen displayed to be able to see it before continuing.
  delay(1000);

  //Erase splash screen from display buffer. No need to flush right now, we will flush on next drawing operation.
  display.clear();
  
  //Display text with console as example.
  console.println("Use write to simply write text or writeln to jump to next line after text rendering.");
}

//runExample is set to true or false when button is pressed.
bool runExample = false;

//The identifier of line currently ydisplayed.
int lineNumber = 0;

//Loop over program execution.
void loop()
{
  //If we must run example.
  if(runExample) {
      //Print in a loop to demonstrate auto-scrolling capability of console.
    console.println("Line " + String(lineNumber++) + " is displayed.");

    //Wait for 100 ms to not display lines to quickly.
    delay(100);
  }
}

//This method has been bound to "INT" button of DevDuino board in the above "setup" method.
void buttonPressed()
{
  //Toggle runExample boolean to continue or pause example.
  runExample = !runExample;
}

