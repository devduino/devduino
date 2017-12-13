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

#include "devduino.h"
#include "console.h"

//The first ASCII code to be coded in font.
#define CONSOLE_FONT_FIRST_CODE 33


	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//
	Console::Console(const Display& display, const Font* font, bool autoFlush) :
		display(display), 
		autoFlush(autoFlush)
	{
		if (font == nullptr) {
			//If no font is set but default font accepted, we set it.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_DISPLAY) && !defined(NO_GLOBAL_DISPLAY_FONT)
			setFont(&defaultFont);
#endif
		}
		else {
			setFont(font);
		}
		setTextPosition(0, (display.getHeight() - 1) - this->font->getSize());
	}

	const Display& Console::getDisplay() {
		return display;
	}

	Console& Console::setTextPosition(uint8_t x, uint8_t y) {
		textX = x;
		textY = y;
		return *this;
	}

	Console& Console::setFont(const Font* font) {
		this->font = font;
		return *this;
	}

	const Font* Console::getFont() {
		return font;
	}

	Console& Console::setFontSize(uint8_t size) {
		fontSize = size;
		return *this;
	}

	uint8_t Console::getFontSize() {
		return fontSize;
	}

	Console& Console::newLine() {
		textX = 0;
		textY -= fontSize * font->getSize() + 1;

		if (autoFlush) {
			flush();
		}

		return *this;
	}

	Console& Console::print(String text) {
		return print(text.c_str(), text.length());
	}

	Console& Console::print(const char *buffer, size_t bufferSize) {
		while (bufferSize--) {
			print(*buffer++);
		}
		if (autoFlush) {
			flush();
		}
		return *this;
	}

	Console& Console::println(const String& text) {
		return println(text.c_str(), text.length());
	}

	Console& Console::println(const char* buffer, size_t bufferSize) {
		bool currentAutoFlush = autoFlush;
		enableAutoFlush(false);

		print(buffer, bufferSize);
		print("\n");

		if (currentAutoFlush) {
			enableAutoFlush(true);
			flush();
		}
		return *this;
	}

	Console& Console::flush() {
		display.flush();
		return *this;
	}

	Console& Console::enableAutoFlush(bool autoFlush) {
		this->autoFlush = autoFlush;
		return *this;
	}

	Console& Console::clear() {
		display.clear();

		setTextPosition(0, (display.getHeight() - 1) - this->font->getSize());

		return *this;
	}

	//------------------------------------------------------------------------//
	//--------------------------- Private methods ----------------------------//
	//------------------------------------------------------------------------//

	void Console::print(uint8_t characterCode, uint8_t previousCharacterCode) {
		if (characterCode == '\n') {
			newLine();
		}
		else {
			int8_t kerning = font->getGlyphKerning(characterCode, previousCharacterCode);
			uint8_t width = font->getGlyphWidth(characterCode);

			newLine(kerning + width);

			uint8_t height = font->getGlyphHeight(characterCode);

			if (textY < 0) {
				display.verticalScroll(textY);
				textY = 0;
			}

			uint8_t y = textY + display.getVerticalScroll();
			display.drawBuffer(font->getGlyphPixels(characterCode), textX + kerning, y, width, height / 8 + 1, false, true);

			incrementTextPosition(width + kerning);
		}
	}

	void Console::incrementTextPosition(uint8_t pixels) {
		textX += fontSize * pixels + 1;
	}

	Console& Console::newLine(uint8_t pixels) {
		if (textX + fontSize * pixels > display.getWidth()) {
			if (autoFlush) {
				enableAutoFlush(false);
				newLine();
				enableAutoFlush(true);
			}
			else {
				newLine();
			}
		}
		return *this;
	}

