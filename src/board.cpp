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

#include <arduino.h>

#include "board.h"

namespace devduino {
	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//
	void Board::begin() {
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_RTC)
		rtc.begin();
#endif

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_TEMPERATURE)
		temperature.begin();
#endif

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED)
		oled.begin();
#endif

		//Set "INT" button as input pullup.
		pinMode(PIN_INT_BUTTON, INPUT_PULLUP);
	}

	void Board::attachToIntButton(void(*callback)(), int mode) {
		attachInterrupt(digitalPinToInterrupt(PIN_INT_BUTTON), callback, mode);
	}

	//------------------------------------------------------------------------//
	//---------------------------- Private methods ---------------------------//
	//------------------------------------------------------------------------//
} // namespace devduino

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_BOARD)
devduino::Board board;
#endif

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_RTC)
devduino::Rtc rtc;
#endif

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_TEMPERATURE)
devduino::Temperature temperature;
#endif

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED)
devduino::Oled oled;
#endif

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_CONSOLE)
devduino::Console console(oled);
#endif

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_SPREADSHEET)
devduino::Spreadsheet spreadsheet(oled);
#endif