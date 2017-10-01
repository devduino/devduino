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

#include "console.h"

namespace devduino {
	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//
	Console::Console(const Oled& oled) : oled(oled) {
		oled.setTextPosition(0, 64);
	}

	Console& Console::operator<<(const uint8_t* value) {
		oled.write(value);
		oled.display();
		return *this;
	}

	Console& Console::operator<<(const String value) {
		oled.write(value);
		oled.display();
		return *this;
	}

	Console& Console::operator<<(const OutputStream& value) {
		for (int i = 0; i < value.nbCharacters(); i++) {
			oled.write(value.nextCharacter());
		}
		oled.display();
		return *this;
	}

	Console& Console::write(const uint8_t* value) {
		oled.write(value);
		return *this;
	}

	Console& Console::write(const String value) {
		oled.write(value);
		return *this;
	}

	Console& Console::write(const OutputStream& value) {
		for (int i = 0; i < value.nbCharacters(); i++) {
			oled.write(value.nextCharacter());
		}
		return *this;
	}

	Console& Console::writeln(const uint8_t* value) {
		oled.write(value);
		oled.write("\n");
		return *this;
	}

	Console& Console::writeln(const String value) {
		oled.write(value);
		oled.write("\n");
		return *this;
	}

	Console& Console::writeln(const OutputStream& value) {
		for (int i = 0; i < value.nbCharacters(); i++) {
			oled.write(value.nextCharacter());
		}
		oled.write("\n");
		return *this;
	}

	Console& Console::flush() {
		oled.display();
		return *this;
	}

	//------------------------------------------------------------------------//
	//--------------------------- Private methods ----------------------------//
	//------------------------------------------------------------------------//

} // namespace devduino

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_CONSOLE)
	devduino::Console console(oled);
#endif