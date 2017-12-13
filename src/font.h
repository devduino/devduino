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
		 *
		 * \return the size of font.
		 */
		virtual uint8_t getSize() = 0;

		/**
		 * \brief Get the width of the glyph.
		 *
		 * \param characterCode The code of the character to get width for.
		 *
		 * \return the width of glyph.
		 */
		virtual uint8_t getGlyphWidth(uint8_t characterCode) = 0;

		/**
		 * \brief Get the height of the glyph.
		 *
		 * \param characterCode The code of the character to get height for.
		 *
		 * \return the height of glyph.
		 */
		virtual uint8_t getGlyphHeight(uint8_t characterCode) = 0;

		/**
		 * \brief Get the pixels of the glyph.
		 * 
		 * \attention For implementors, the ordering of the buffer of pixels must be compatible with the display buffer.
		 *
		 * \param characterCode The code of the character to get pixels for.
		 *
		 * \return A pointer to the pixels of glyph.
		 */
		virtual const uint8_t* getGlyphPixels(uint8_t characterCode) = 0;

		/**
		 * \brief Get the kerning of the glyph.
		 *
		 * \param characterCode The code of the character to get kerning for.
		 * \param previousCharacterCode The code of the character preceding the one to get kerning for.
		 *
		 * \return The kerning to apply between this character and previous one.
		 */
		virtual int8_t getGlyphKerning(uint8_t characterCode, uint8_t previousCharacterCode) = 0;

		/**
		 * \brief Get the number of pixels to advance on X axis after having rendered this font.
		 *
		 * \param characterCode The code of the character to get advance for.
		 *
		 * \return The number of pixels representing advancement.
		 */
		virtual uint8_t getGlyphXAdvance(uint8_t characterCode) = 0;

		/**
		* \brief Get the number of pixels to advance on X axis before rendering this font.
		*
		* \param characterCode The code of the character to get offset for.
		*
		* \return The number of pixels representing offset.
		*/
		virtual int8_t getGlyphXOffset(uint8_t characterCode) = 0;

		/**
		* \brief Get the number of pixels to advance on Y axis before rendering this font.
		*
		* \param characterCode The code of the character to get offset for.
		*
		* \return The number of pixels representing offset.
		*/
		virtual int8_t getGlyphYOffset(uint8_t characterCode) = 0;
	};


#endif //DEVDUINO_FONT_H