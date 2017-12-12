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

#ifndef DEVDUINO_BUZZER_H
#define DEVDUINO_BUZZER_H

#include <stdint.h>

/**
 * \brief Constant defining duration of a short tone.
 */
#define BUZZER_SHORT_DURATION 100
 /**
 * \brief Constant defining duration of a short tone.
 */
#define BUZZER_STANDARD_DURATION 500
 /**
 * \brief Constant defining duration of a long tone.
 */
#define BUZZER_LONG_DURATION 1000

/**
 * Default namespace for devduino related code.
 */

  /** 
   * \brief High level driver for buzzer of devduino.
   * 
   * You must call "begin" method before being able to use it.
   */
  class Buzzer {
  public:
	/**
	 * \brief Initialize buzzer on DevDuino.
	 *
	 * This method must be called before any other method of this class.
	 */
	void begin();
	
	/**
	 * \brief Update buzzer internal behavior.
	 *
	 * This method is genarally only called by method update of class Board.
	 * You should call it only if you need to update buzzer internal behavior more often than board.
	 */
	void update();

	/**
	 * \brief play a "music".
	 *
	 * Play the music specified by frequencies and durations.
	 * The size of frequencies and durations arrays must be equal to nbSounds.
	 *
	 * \attention frequencies and durations needs to be in PROGMEM.
	 *
	 * \param frequencies The frequencies of each sound to play one after the other use a very low frenquency or 0 to play silences.
	 * \param durations The duration of each sound to play one after the other.
	 * \param nbSounds The size of frequencies and durations arrays.
	 */
	void play(const uint16_t frequencies[], const uint16_t durations[], uint8_t nbSounds);

	/**
	 * \brief Check if a music is currently playing.
	 *
	 * \return true if a music is currently playing, false otherwise.
	 */
	bool isPlaying();

	/**
	 * \brief Stop playing a "music".
	 */
	void stop();

	/**
	 * \brief play a tone.
	 *
	 * Play a tone for given ms at given frequency.
	 *
	 * \param frequency The frequency of tone or 4000 Hz if not specified.
	 * \param duration The duration of tone or BUZZER_STANDARD_DURATION ms if not specified.
	 */
	void tone(uint16_t frequency = 4000, uint32_t duration = BUZZER_STANDARD_DURATION);

	/**
	 * \brief play a short tone.
	 *
	 * Play a short tone (BUZZER_SHORT_DURATION ms) at given frequency.
	 *
	 * \param frequency The frequency of tone or 4000 Hz if not specified.
	 */
	void toneShort(uint16_t frequency = 4000);

	/**
	 * \brief play a long tone.
	 *
	 * Play a short tone (BUZZER_LONG_DURATION ms) at given frequency.
	 *
	 * \param frequency The frequency of tone or 3000 Hz if not specified.
	 */
	void toneLong(uint16_t frequency = 3000);

  private:
	  /**
	   * \brief The time in ms when play started.
	   */
	  uint32_t startMs;
	  /**
	   * \brief The index of sound currently played.
	   */
	  uint8_t currentIndex;
	  /**
	   * \brief The list of frequencies of sounds to play.
	   */
	  const uint16_t* frequencies;
	  /**
	   * \brief The duration of sounds to play.
	   */
	  const uint16_t* durations;
	  /**
	   * \brief The number of sounds to play.
	   */
	  uint8_t nbSounds;
  };


#endif //DEVDUINO_BUZZER_H