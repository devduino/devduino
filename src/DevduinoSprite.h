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

#ifndef DEVDUINO_SPRITE
#define DEVDUINO_SPRITE

#include "sprite.h"

/**
* Default implementation of Sprite class for DevDuino.
*/
class DevduinoSprite : public Sprite {
public:
	/**
	 * \brief Construct a sprite from the given buffer, width and height.
	 * 
	 * \remark Sprite buffer can be constructed using the sprite connverter available on DevDuino web-site (http://devduino.cc).
	 */
	DevduinoSprite(const uint8_t* buffer, uint8_t width, uint8_t height);

	const uint8_t* getBuffer();
	uint8_t getWidth();
	uint8_t getHeight();

private:
	const uint8_t* buffer;
	uint8_t width;
	uint8_t height;
};

#endif //DEVDUINO_SPRITE