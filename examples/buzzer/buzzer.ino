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
#include <devduinoLogo.h>

//Define the frequencies of sounds to play.
const uint16_t frequencies[] PROGMEM = {494, 988, 740, 622, 988, 740, 622, 523, 1046, 784, 659, 1046, 784, 659, 494, 988, 740, 622, 988, 740, 622, 622, 659, 698, 698, 739, 783, 783, 831, 880, 988};
//Define the durations of sounds to play.
const uint16_t durations[] PROGMEM = {150, 150, 150, 150, 75, 225, 300, 150, 150, 150, 150, 75, 225, 300, 150, 150, 150, 150, 75, 225, 300, 75, 75, 150, 75, 75, 150, 75, 75, 150, 225};

boolean startExample = false;

//Initialize program.
void setup()
{
  //First thing to do is to initialize DevDuino board.
  devduino.begin();
  
  //Draw splash screen to buffer.
  display.drawSprite(devduinoLogo, 37, 0);
  //Then transfer buffer to screen.
  display.flush();

  //Play a short tone at default frequency.
  buzzer.toneShort();
  delay(BUZZER_SHORT_DURATION + 300);

  //Play a short tone at custom frequency.
  buzzer.toneShort(3000);
  delay(BUZZER_SHORT_DURATION + 300);
  
  //Play a tone at default frequency and default duration.
  buzzer.tone();
  delay(BUZZER_STANDARD_DURATION + 300);
  
  //Play a tone at custom frequency and custom duration.
  buzzer.tone(3000, 300);
  delay(600);
  
  //Play a long tone at default frequency.
  buzzer.toneLong();
  delay(BUZZER_LONG_DURATION + 300);

  //Play a long tone at custom frequency.
  buzzer.toneLong(3000);
  delay(BUZZER_LONG_DURATION + 300);

  //Attach "interrupt" button to "buttonPressed" function.
  devduino.attachToIntButton(buttonPressed);
}

//Loop over program execution.
void loop()
{
  //Update board and buzzer to let API do its job as well as possible.
  devduino.update();

  //If button has been pressed, play a music.
  if(startExample && !buzzer.isPlaying()) {    
    buzzer.play(frequencies, durations, 31);
  }
  
  //No need to refresh very quickly but quick enough to play music correctly.
  delay(25);
}

void buttonPressed()
{
  if(startExample) {
    startExample = false;
    buzzer.stop();
  } else {
    startExample = true;
  }
}
