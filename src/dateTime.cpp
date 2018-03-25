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

#include "dateTime.h"


	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//
	DateTime::DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0) {
		setDateTime(year, month, day, hour, minute, second);
	}

	uint16_t DateTime::getYear() {
		return 2016 + (dateTime >> 26);
	}

	uint8_t DateTime::getMonth() {
		return (dateTime >> 22) & 0x0F;
	}

	uint8_t DateTime::getDay() {
		return (dateTime >> 17) & 0x1F;
	}

	uint8_t DateTime::getHour() {
		return (dateTime >> 12) & 0x1F;
	}

	uint8_t DateTime::getMinute() {
		return (dateTime >> 6) & 0x3F;
	}

	uint8_t DateTime::getSecond() {
		return dateTime & 0x3F;
	}

	uint16_t DateTime::toDayEpoch() {
		return (toDay() - toDay(1970, 1, 1)) * 24 * 60 * 60;
	}

	uint32_t DateTime::toDay() {
		return toDay(getYear(), getMonth(), getDay());
	}

	uint8_t DateTime::toDayOfWeek() {
		return toDayOfWeek(getYear(), getMonth(), getDay());
	}

	static uint32_t DateTime::toDay(uint16_t year, uint8_t month, uint8_t day) {
		if (month < 3) {
			month += 12;
			year -= 1;
		}

		return (day + ((153 * (month - 3) + 2) / 5) + 365 * year + year / 4 - year / 100 + year / 400) + 59;
	}

	static uint8_t DateTime::toDayOfWeek(uint16_t year, uint8_t month, uint8_t day) {
		return ((toDay(year, month, day) + 5) % 7) + 1;
	}

	//------------------------------------------------------------------------//
	//---------------------------- Private methods ---------------------------//
	//------------------------------------------------------------------------//
	void DateTime::setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0) {
		dateTime = (year - 2016) & 0x3F;
		dateTime = (dateTime << 4) | (month & 0x0F); //4 bit shift for months.
		dateTime = (dateTime << 5) | (day & 0x1F); //5 bit shift for days.
		dateTime = (dateTime << 5) | (hour & 0x1F); //5 bit shift for hours.
		dateTime = (dateTime << 6) | (minute & 0x3F); //6 bit shift for minutes.
		dateTime = (dateTime << 6) | (second & 0x3F); //6 bit shift for seconds.
	}
