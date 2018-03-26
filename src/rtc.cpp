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

#include <Wire.h>

#include "rtc.h"
#include "bcd.h"

//------------------------------------------------------------------------//
//---------------------------- Pre-processors ----------------------------//
//------------------------------------------------------------------------//
#define PCF8523_I2C_ADDRESS 0x68
#define PCF8523_SECONDS_REGISTER_ADDRESS 0x03
#define PCF8523_CONTROL_3_REGISTER_ADDRESS 0x02

	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//
	void Rtc::begin() {
		Wire.beginTransmission(PCF8523_I2C_ADDRESS);
		Wire.write(PCF8523_CONTROL_3_REGISTER_ADDRESS);
		Wire.write(0x80); //(Enable switch-over, no interrupt)
		Wire.endTransmission();
	}

	void Rtc::begin(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0) {
		begin();
		setDateTime(year, month, day, hour, minute, second);
	}

	void Rtc::setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0) {
		Wire.beginTransmission(PCF8523_I2C_ADDRESS);
		Wire.write(PCF8523_SECONDS_REGISTER_ADDRESS);
		Wire.write(Bcd::fromBinary(second));
		Wire.write(Bcd::fromBinary(minute));
		Wire.write(Bcd::fromBinary(hour));
		Wire.write(Bcd::fromBinary(day));
		Wire.write(0); // skip weekdays
		Wire.write(Bcd::fromBinary(month));
		Wire.write(Bcd::fromBinary(year - 2000));
		Wire.endTransmission();
	}

	//------------------------------------------------------------------------//
	//---------------------------- Private methods ---------------------------//
	//------------------------------------------------------------------------//
	DateTime Rtc::now() {
		//Request seconds register.
		Wire.beginTransmission(PCF8523_I2C_ADDRESS);
		Wire.write(PCF8523_SECONDS_REGISTER_ADDRESS);
		Wire.endTransmission();

		// The 20 registers of the PCF8523 are auto-incrementing after each read or write data byte up to register 13h.
		Wire.requestFrom(PCF8523_I2C_ADDRESS, 7);
		//The registers Seconds, Minutes, Hours, Days, Weekdays, Months, and Years are all coded in Binary Coded Decimal(BCD) format.
		//Bit 7 is for clock integrity check, so remove it.
		uint8_t second = Bcd::toBinary(Wire.read() & 0x7F);
		//Bit 7 is unused on minutes.
		uint8_t minute = Bcd::toBinary(Wire.read() & 0x7F);
		//Bits 6 & 7 are unused on hours.
		uint8_t hour = Bcd::toBinary(Wire.read() & 0x3F);
		//Bits 6 & 7 are unused on days.
		uint8_t day = Bcd::toBinary(Wire.read() & 0x3F);
		// Read to auto-increment register address and skip weekdays which is calculated.
		Wire.read(); 
		//Bits 5, 6 & 7 are unused on months.
		uint8_t month = Bcd::toBinary(Wire.read() &0x1F);
		uint16_t year = 2000 + Bcd::toBinary(Wire.read());

		dateTime.setDateTime(year, month, day, hour, minute, second);

		return dateTime;
	}

	Rtc::RtcDateTime::RtcDateTime() : DateTime(2016, 1, 1) {}
