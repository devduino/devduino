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

#ifndef DEVDUINO_FONT_H
#define DEVDUINO_FONT_H

#include <stdint.h>

/**
* Default namespace for devduino related code.
*/
namespace devduino {
	/**
	 * \brief A font is the graphical representation of a set of characters to display.
	 *
	 * A font is composed of glyphs which are a graphical representation of a character.
	 */
	class Font {
	public:
		/**
		 * \brief Get the size of font.
		 *
		 * Size of font correspond to its height.
		 */
		virtual uint8_t getSize() = 0;

		/**
		 * Get the width of the glyph.
		 */
		virtual uint8_t getGlyphWidth(uint8_t characterCode) = 0;

		/**
		 * Get the height of the glyph.
		 */
		virtual uint8_t getGlyphHeight(uint8_t characterCode) = 0;

		/**
		 * Get the pixels of the glyph.
		 * 
		 * \attention The ordering of the buffer of pixels must be compatible with the display buffer.
		 */
		virtual const uint8_t* getGlyphPixels(uint8_t characterCode) = 0;

		/**
		 * Get the kerning of the glyph.
		 */
		virtual int8_t getGlyphKerning(uint8_t characterCode, uint8_t previousCharacterCode) = 0;
	};
} // namespace devduino

#endif //DEVDUINO_FONT_H