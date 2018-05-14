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

//The sprite representing the clock.
#include "clockSprite.h"

//Define if you want to set the RTC and the exact time you want to set
#define SET_RTC             false // true when you want to set the RTC
#define SET_YEAR            2018
#define SET_MONTH           03
#define SET_DAY             25
#define SET_HOUR            16 //24 hours format
#define SET_MINUTE          48
#define SET_SECOND          0

//Define constants for a unitary angle for hours and minutes.
#define HOUR_ANGLE M_PI   / 6
#define MINUTE_ANGLE M_PI / 30

//Define constants for clock graphical display.
#define CENTER_X          27
#define CENTER_Y          31
#define HOUR_HAND_SIZE    10
#define MINUTE_HAND_SIZE  15
#define SECOND_HAND_SIZE  20

//Initialize program.
void setup()
{
  //First thing to do is to initialize DevDuino board.
  devduino.begin();
  
  //Draw splash screen to buffer.
  display.drawSprite(devduinoLogo, 37, 0);
  //Then transfer buffer to screen.
  display.flush();

  //Set an arbitrary time to RTC (The date when DevDuino was launched on KickStarter (sort of epoch of DevDuino)).
  if(SET_RTC)
  {
    rtc.setDateTime(SET_YEAR, SET_MONTH, SET_DAY, SET_HOUR, SET_MINUTE, SET_SECOND);
  }
  
  //Sleep for 1 second with splash screen displayed to be able to see it before continuing.
  delay(1000);
}

//Loop over program execution.
void loop()
{
  //Erase whole display buffer. No need to flush right now, we will flush on next drawing operation.
  display.clear();

  //Draw text on top right corner of screen.
  display.print(String("RTC"), 60, 50, &defaultFont);
  display.print(String("example"), 60, 43, &defaultFont);

  //Read time from RTC.
  DateTime currentClock = rtc.now();

  //Draw the time using a graphical represention.
  drawGraphicalClock(currentClock);
  
  //Draw the same time using a simple text represention.
  drawTextClock(currentClock);

  //Render display buffer that has been updated by the "draw..." and "print..." functions.
  display.flush();
}

//Draw the clock and its hands.
void drawGraphicalClock(DateTime currentClock)
{
  //Draw the clock sprite.
  display.drawSprite(clockSprite, 0, 2);

  //Get hour/minute/seconnd from clock.
  uint8_t hour = currentClock.getHour();
  uint8_t minute = currentClock.getMinute();
  uint8_t second = currentClock.getSecond();

  //Calculate the angle of hour clock hand.
  //3 hours are substracted because an hour of "0" would be computed as horizontal and so be rendered on hour "3".
  float hourX = cos(HOUR_ANGLE * (hour - 3) + ((HOUR_ANGLE / 60) * minute));
  float hourY = -sin(HOUR_ANGLE * (hour - 3) + ((HOUR_ANGLE / 60) * minute));
  
  //Calculate the angle of minute clock hand.
  //Same process than hours is used on minutes where 0 would be horizontal (positioned on minute 15) instead of being vertical.
  float minuteX = cos(MINUTE_ANGLE * (minute - 15));
  float minuteY = -sin(MINUTE_ANGLE * (minute - 15));
  
  //Calculate the angle of second clock hand.
  float secondX = cos(MINUTE_ANGLE * (second - 15));
  float secondY = -sin(MINUTE_ANGLE * (second - 15));

  //Draw clock hands for hour/minute/second to display buffer.
  display.drawLine(CENTER_X, CENTER_Y, CENTER_X + hourX * HOUR_HAND_SIZE, CENTER_Y + hourY * HOUR_HAND_SIZE);
  display.drawLine(CENTER_X, CENTER_Y, CENTER_X + minuteX * MINUTE_HAND_SIZE, CENTER_Y + minuteY * MINUTE_HAND_SIZE);
  display.drawLine(CENTER_X, CENTER_Y, CENTER_X + secondX * SECOND_HAND_SIZE, CENTER_Y + secondY * SECOND_HAND_SIZE);
}

//Draw time as a simple text.
void drawTextClock(DateTime currentClock)
{
  //Create date text.
  char dateBuffer[10];
  sprintf(dateBuffer, "%04d-%02d-%02d", currentClock.getYear(), currentClock.getMonth(), currentClock.getDay());

  //Write date to display buffer.
  display.print(String(dateBuffer), 60, 15, &defaultFont);

  //Create time text.
  char timeBuffer[9];
  sprintf(timeBuffer, "%02dh%02dm%02ds", currentClock.getHour(), currentClock.getMinute(), currentClock.getSecond());
  
  //Write time to display buffer.
  display.print(String(timeBuffer), 60, 6, &defaultFont);
}
