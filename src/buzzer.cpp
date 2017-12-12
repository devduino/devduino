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

#include <Arduino.h>

#include "buzzer.h"

//------------------------------------------------------------------------//
//---------------------------- Pre-processors ----------------------------//
//------------------------------------------------------------------------//
//Pin of buzzer.
#define PIN_BUZZER 6


	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//

	void Buzzer::begin() {
		startMs = 0;
	}

	void Buzzer::update() {
		if (startMs != 0) {
			uint16_t duration = pgm_read_word(&durations[currentIndex]);
			while (millis() - startMs >= duration) {
				startMs += duration;
				currentIndex++;
				duration = pgm_read_word(&durations[currentIndex]);

				if (currentIndex >= nbSounds) {
					startMs = 0;
					::noTone(PIN_BUZZER);
				}
				else {
					::tone(PIN_BUZZER, pgm_read_word(&frequencies[currentIndex]), duration);
				}
			}
		}
	}

	void Buzzer::play(const uint16_t frequencies[], const uint16_t durations[], uint8_t nbSounds) {
		startMs = millis();
		currentIndex = 0;
		this->frequencies = frequencies;
		this->durations = durations;
		this->nbSounds = nbSounds;

		::tone(PIN_BUZZER, pgm_read_word(&frequencies[0]), pgm_read_word(&durations[0]));
	}

	bool Buzzer::isPlaying() {
		return startMs != 0;
	}

	void Buzzer::stop() {
		::noTone(PIN_BUZZER);
		startMs = 0;
	}

	void Buzzer::tone(uint16_t frequency, uint32_t duration) {
		::tone(PIN_BUZZER, frequency, duration);
	}

	void Buzzer::toneShort(uint16_t frequency) {
		::tone(PIN_BUZZER, frequency, BUZZER_SHORT_DURATION);
	}

	void Buzzer::toneLong(uint16_t frequency) {
		::tone(PIN_BUZZER, frequency, BUZZER_LONG_DURATION);
	}

	//------------------------------------------------------------------------//
	//--------------------------- Private methods ----------------------------//
	//------------------------------------------------------------------------//

