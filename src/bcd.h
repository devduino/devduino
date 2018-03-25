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

#ifndef DEVDUINO_BCD_H
#define DEVDUINO_BCD_H

#include <stdint.h>

/**
 * Default namespace for devduino related code.
 */

	/**
	 * \brief Utility class to work with BCD encoding.
     * 
     * For more information on bcd, you can visit <a href="https://en.wikipedia.org/wiki/Binary-coded_decimal" target="_blank">wikipedia</a>.
	 */
	class Bcd {
	public:
		/**
		 * Utility method to convert from bcd to binary.
		 *
		 * \param bcd The BCD to convert to binary.
		 * \return decoded BCD as binary.
		 */
		static uint8_t toBinary(uint8_t bcd);

		/**
		 * Utility method to convert from binary to bcd.
		 *
		 * \param binary The binary to convert to BCD.
		 * \return encoded binary as BCD.
		 */
		static uint8_t fromBinary(uint8_t binary);

	private:
		/**
		 * \brief Bcd is a utility class that only exposes static method and cannot be instanciated.
		 */
		Bcd();
	};


#endif //DEVDUINO_BCD_H