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

#ifndef DEVDUINO_BOARD_H
#define DEVDUINO_BOARD_H

#define PIN_INT_BUTTON 7

#include <stdint.h>
#include <arduino.h>

#include "rtc.h"
#include "temperature.h"
#include "oled.h"
#include "console.h"
#include "spreadsheet.h"

/**
* Default namespace for devduino related code.
*/
namespace devduino {
	/**
	* \brief Board of devduino.
	*
	* This class allows to initialize DevDuino board.
	*/
	class Board {
	public:
		/**
		* \brief Initialize DevDuino board.
		*
		* This method must be called before any other method of this class.
		*/
		void begin();

		void attachToIntButton(void (*callback)(), int mode = FALLING);
	private:
	};
} // namespace devduino

//Define global board variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_BOARD)
extern devduino::Board board;
#endif

//Define global rtc variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_RTC)
extern devduino::Rtc rtc;
#endif

//Define global temperature variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_TEMPERATURE)
extern devduino::Temperature temperature;
#endif

//Define global oled variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED)
extern devduino::Oled oled;
#endif

//Define global console variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_CONSOLE)
extern devduino::Console console;
#endif

//Define global console variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_SPREADSHEET)
extern devduino::Spreadsheet spreadsheet;
#endif

#endif //DEVDUINO_BOARD_H