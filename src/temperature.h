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

#ifndef DEVDUINO_TEMPERATURE_H
#define DEVDUINO_TEMPERATURE_H

#include <stdint.h>


  /** 
   * \brief High level driver for MCP9808 of devduino.
   * 
   * You must call "begin" method before being able to use it.
   * 
   * For more information on internal behavior, the temperature sensor datasheet is available <a href="http:\\www.datasheetspdf.com\datasheet\MCP9808" target="_blank">here</a>.
   */
  class Temperature {
  public:
	/**
	* \brief Initialize temperature sensor on DevDuino.
	*
	* This method must be called before any other method of this class.
	*/
	void begin();

    /** 
     * \brief Read temperature frorm sensor.
     * 
     * Temperature is read in ° Celsius.
     */
    float read();

    /**
     * \brief Shutdown the sensor.
     * 
     * The sensor must be wake-up before being able to read temperature again.
     * 
     * \see wakeup().
     */
    void shutdown();

    /**
     * \brief Wake-up the sensor.
     * 
     * This method must be called prior to reading a temperature if shut-down has been called.
     * 
     * \see shutdown().
     */
    void wakeup();
  };


#endif //DEVDUINO_TEMPERATURE_H