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

#ifndef DEVDUINO_DEFAULT_FONT_H
#define DEVDUINO_DEFAULT_FONT_H

#include <Arduino.h>

#include "font.h"

/**
 * Default namespace for devduino related code.
 */
	/**
	* \brief The default font for devduino.
	*/
	class DevduinoFont : public Font {
	public:
		uint8_t getSize();
		uint8_t getGlyphWidth(uint8_t characterCode);
		uint8_t getGlyphHeight(uint8_t characterCode);
		const uint8_t* getGlyphPixels(uint8_t characterCode);
		int8_t getGlyphKerning(uint8_t characterCode, uint8_t previousCharacterCode);
		uint8_t getGlyphXAdvance(uint8_t characterCode);
		int8_t getGlyphXOffset(uint8_t characterCode);
		int8_t getGlyphYOffset(uint8_t characterCode);

	private:
		/**
		 * \brief The pixels of glyphs.
		 */
		static const uint8_t glyphsBuffer[95][5] PROGMEM;

		/**
		 * \brief the width in pixels of each glyph.
		 */
		static const uint8_t glyphsWidth[95] PROGMEM;

		/**
		 * \brief The x position of first pixel of glyph in its bouding box.
		 */
		static const uint8_t glyphsPosition[95] PROGMEM;

		/**
		 * \brief Get the x position of first pixel of glyph in its bounding box.
		 */
		uint8_t getGlyphPosition(uint8_t characterCode);
	};


#endif //DEVDUINO_DEFAULT_FONT_H
