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
#ifndef DEVDUINO_ADAFRUIT_FONT_H
#define DEVDUINO_ADAFRUIT_FONT_H

#include <Arduino.h>

#include "font.h"

/**
* \brief Class to represent the default font from Adafruit GFX library: https://github.com/adafruit/Adafruit-GFX-Library.
*
* Special not for Alexandre Pailhoux: This class is implemented because you don't like my devduino font :/
* \attention Special note for other readers: Alexandre Pailhoux nickname is Papayou: https://www.youtube.com/watch?v=Wv1cX9o8JJM.
*/
class AdafruitFont : public Font {
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
};


#endif //DEVDUINO_ADAFRUIT_FONT_H
