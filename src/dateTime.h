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

	/**
	 * \brief Class used to represent a date and time and perform simple conversions.
	 */
	class DateTime {
	public:
		/** \brief Construct a DateTime.
		 *
		 * \param year The year of date to represent.
		 * \param month The month of date to represent.
		 * \param day The day of date to represent.
		 * \param hour The hour of time to represent.
		 * \param minute The minute of time to represent.
		 * \param second The second of time to represent.
		 */
		DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0);

		/** \brief Get year from date.
		 *
		 * \return The year of date to represent.
		 */
		uint16_t getYear();

		/** \brief Get month from date.
		 *
		 * \return month The month of date to represent.
		 */
		uint8_t getMonth();

		/** \brief Get day from date.
		 *
		 * \return The day of date to represent.
		 */
		uint8_t getDay();

		/** \brief Get hour from time.
		 *
		 * \return The hour of time to represent.
		 */
		uint8_t getHour();

		/** \brief Get minute from time.
		 *
		 * \return The hour of time to represent.
		 */
		uint8_t getMinute();

		/** \brief Get second from time.
		 *
		 * \return The second of time to represent.
		 */
		uint8_t getSecond();

		/** \brief Convert to number of days since epoch.
		 *
		 * \return The number of days since epoch (01/01/1970).
		 */
		uint16_t toDayEpoch();

		/** \brief Convert to number of days since 01/01/0000.
		 *
		 * \return The number of days since 01/01/0000.
		 */
		uint32_t toDay();

		/**
		 * \brief Convert to number of days from start of week in ISO format (starting at monday).
		 *
		 * \return The number of days since start of week.
		 */
		uint8_t toDayOfWeek();

		/**
		 * \brief Convert to number of days since 01/01/0000.
		 * 
		 * \param year The year of date to convert.
		 * \param month The month of date to convert.
		 * \param day The day of date to convert.
		 *
		 * \return The number of days since 00/00/0000.
		 */
		static uint32_t toDay(uint16_t year, uint8_t month, uint8_t day);

		/**
		 * \brief Convert to number of days from start of week in ISO format (starting at monday).
		 *
		 * \param year The year of date to convert.
		 * \param month The month of date to convert.
		 * \param day The day of date to convert.
		 *
		 * \return The number of days since start of week.
		 */
		static uint8_t toDayOfWeek(uint16_t year, uint8_t month, uint8_t day);

	protected:
		/**
		 * \brief The internal representation of date and time.
		 */
		uint32_t dateTime;

		/**
		 * \brief Set the date and time of this object.
		 *
		 * \param year The year of date to set.
		 * \param month The month of date to set.
		 * \param day The day of date to set.
		 * \param hour The hour of time to set.
		 * \param minute The minute of time to set.
		 * \param second The second of time to set.
		 */
		void setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0);
	};


#endif //DEVDUINO_DATE_TIME_H