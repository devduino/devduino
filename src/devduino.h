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

/**
 * The pin for "Interrupt" button on devduino board.
 */
#define PIN_INT_BUTTON 7

#include <stdint.h>
#include <Arduino.h>

//Include adafruit default font if allowed. 
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY) && !defined(NO_GLOBAL_DISPLAY_FONT) && !defined(PREFER_DEVDUINO_FONT)
#include "adafruitFont.h"
#endif

//Include devduino default font if allowed. 
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY) && defined(NO_GLOBAL_DISPLAY_FONT) && defined(PREFER_DEVDUINO_FONT)
#include "devduinoFont.h"
#endif

#include "rtc.h"
#include "temperature.h"
#include "buzzer.h"
#include "display.h"
#include "console.h"
#include "spreadsheet.h"

	/**
	 * \brief Board of devduino.
	 *
	 * This class allows to initialize DevDuino board.
	 */
	class DevDuino {
	public:
		/**
		 * \brief Default constructor.
		 *
		 * Initialize board with functionalities that must be done prior to begin().
		 */
		DevDuino();

		/**
		 * \brief Initialize DevDuino board.
		 *
		 * This method must be called before any other method of this class.
		 */
		void begin();

		/**
		* \brief Tell whole board API to update.
		*
		* Some methods of API needs to be called repeatedly. To allow the API to works well with such methods, this update method needs to be called in a loop as much often as possible.
		*/
		void update();

		/**
		 * \brief Attach function to "Interrupt" button.
		 *
		 * \param callback The function to attach.
		 * \param mode The pin mode of button to attach.
		 */
		void attachToIntButton(void (*callback)(), int mode = FALLING);
	private:
	};

//Define global board variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_BOARD)
extern DevDuino devduino;
#endif

//Define global default adafruit font variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY) && !defined(NO_GLOBAL_DISPLAY_FONT) && !defined(PREFER_DEVDUINO_FONT)
extern AdafruitFont defaultFont;
#endif

//Define global default devduino font variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY) && !defined(NO_GLOBAL_DISPLAY_FONT) && defined(PREFER_DEVDUINO_FONT)
extern DevduinoFont defaultFont;
#endif

//Define global rtc variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_RTC)
extern Rtc rtc;
#endif

//Define global temperature variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_TEMPERATURE)
extern Temperature temperature;
#endif

//Define global buzzer variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_BUZZER)
extern Buzzer buzzer;
#endif

//Define global display variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY)
extern Display display;
#endif

//Define global console variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY) && !defined(NO_GLOBAL_CONSOLE)
extern Console console;
#endif

//Define global spreadsheet variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY) && !defined(NO_GLOBAL_SPREADSHEET)
extern Spreadsheet spreadsheet;
#endif

#endif //DEVDUINO_BOARD_H
