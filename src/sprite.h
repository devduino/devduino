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

#ifndef DEVDUINO_SPRITE_INTERFACE_H
#define DEVDUINO_SPRITE_INTERFACE_H

#include <stdint.h>

/**
 * Default namespace for devduino related code.
 */

	/**
	 * \brief A sprite represents an image for displaying.
	 */
	class Sprite {
	public:
		/**
		* \brief Get the buffer of pixels of this sprite.
		*
		* \remark Because each pixel is coded as a single boolean, each byte returned contains the pixels for 8 consecutive vertical pixels.
		*
		* \return The buffer of the sprite.
		*/
		virtual const uint8_t* getBuffer() = 0;

		/**
		 * \brief Get the width in pixels of this sprite.
		 * 
		 * \return The width of the sprite.
		 */
		virtual uint8_t getWidth() = 0;

		/**
		 * \brief Get the height in pixels of this sprite.
		 *
		 * \return The height of the sprite.
		 */
		virtual uint8_t getHeight() = 0;
	};


#endif //DEVDUINO_SPRITE_INTERFACE_H