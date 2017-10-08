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
	Console::Console(const Oled& oled, bool autoFlush) :
		oled(oled), 
		autoFlush(autoFlush)
	{
		oled.setTextPosition(0, 64);
	}

	Console& Console::write(const char* value, size_t buffer_size) {
		oled.write(value, buffer_size);
		if (autoFlush) {
			flush();
		}
		return *this;
	}

	Console& Console::write(const String& value) {
		oled.write(value);
		if (autoFlush) {
			flush();
		}
		return *this;
	}

	Console& Console::writeln(const char* value, size_t buffer_size) {
		oled.write(value, buffer_size);
		oled.write("\n");
		if (autoFlush) {
			flush();
		}
		return *this;
	}

	Console& Console::writeln(const String& value) {
		oled.write(value);
		oled.write("\n");
		if (autoFlush) {
			flush();
		}
		return *this;
	}

	Console& Console::flush() {
		oled.display();
		return *this;
	}

	Console& Console::enableAutoFlush(bool autoFlush) {
		this->autoFlush = autoFlush;
		return *this;
	}

	//------------------------------------------------------------------------//
	//--------------------------- Private methods ----------------------------//
	//------------------------------------------------------------------------//

} // namespace devduino