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

#ifndef DEVDUINO_DATE_TIME_H
#define DEVDUINO_DATE_TIME_H

#include <stdint.h>

/**
* Default namespace for devduino related code.
*/
namespace devduino {
	class DateTime {
	public:
		DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0);

		uint16_t getYear();
		uint8_t getMonth();
		uint8_t getDay();
		uint8_t getHour();
		uint8_t getMinute();
		uint8_t getSecond();

		uint16_t toDayEpoch();
		uint32_t toDay();
		uint8_t toDayOfWeek();

		static uint32_t toDay(uint16_t year, uint8_t month, uint8_t day);
		static uint8_t toDayOfWeek(uint16_t year, uint8_t month, uint8_t day);

	protected:
		uint32_t dateTime;

		void setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0);
	};
} // namespace devduino

#endif //DEVDUINO_DATE_TIME_H