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

#ifndef DEVDUINO_RTC_H
#define DEVDUINO_RTC_H

#include "dateTime.h"

/**
 * Default namespace for devduino related code.
 */

	/**
	 * \brief High level driver for PCF8523 of devduino.
     * 
     * You must call "begin" method before being able to use it.
     * 
     * For more information on internal behavior, the rtc datasheet is available <a href="http:\\www.datasheetspdf.com\datasheet\PCF8523" target="_blank">here</a>.
	 */
	class Rtc {
	public:
		/**
		* \brief Initialize rtc on DevDuino.
		*
		* This method must be called before any other method of this class.
		*/
		void begin();

		/**
		* \brief Initialize rtc on DevDuino.
		*
		* This method must be called before any other method of this class.
		* 
		* \remark If you call this method, you don't need to call method "setDateTime()".
		*
		* \param year The year to set to the devduino.
		* \param month The month to set to the devduino.
		* \param day The day to set to the devduino.
		* \param hour The hour to set to the devduino or 0 if none specified.
		* \param minute The minute to set to the devduino or 0 if none specified.
		* \param second The second to set to the devduino or 0 if none specified.
		*/
		void begin(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0);

		/**
		* \brief Set the current date and time on RTC.
		*
		* \remark If this method is never called, the date and time of rtc is set to factory defaults and will not represent the "real" date and time.
		*
		* \param year The year to set to the devduino.
		* \param month The month to set to the devduino.
		* \param day The day to set to the devduino.
		* \param hour The hour to set to the devduino or 0 if none specified.
		* \param minute The minute to set to the devduino or 0 if none specified.
		* \param second The second to set to the devduino or 0 if none specified.
		*/
		void setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0);

		/**
		 * \brief Return the current date and time according to the default date/time set.
		 *
		 * \remark You must call "setDateTime" or "begin" with parameters to get a "real" date and time.
		 *
		 * \see setDateTime();
		 * \see begin();
		 *
		 * \return The current date/time according to the one set in devduino.
		 */
		DateTime now();

	private:
		/**
		* \brief Specialization of dateTime class to allow RTC class to set date and time.
		*
		* This is needed because dateTime is a "sort of" immutable.
		* This specialization allows the RTC to not allocate a dateTime for each use but to use the same instance and  to not let caller change its value.
		*/
		class RtcDateTime : DateTime {
		public:
			/**
			* \brief Allow Rtc class to access date and time.
			*/
			friend class Rtc;

			/**
			* \brief construct a date and time on 01/01/2016 00:00.
			*/
			RtcDateTime();
		};

		/**
		 * \brief the instance of dateTime used.
		 */
		RtcDateTime dateTime;
	};


#endif //DEVDUINO_RTC_H