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

#ifndef DEVDUINO_CONSOLE_H
#define DEVDUINO_CONSOLE_H

#include "oled.h"
#include "endl.h"

/**
* Default namespace for devduino related code.
*/
namespace devduino {
  /** 
   * \brief Console writer for devduino.
   * 
   * This class allows to display text on OLED screen in a console way by auto-scrolling.
   *
   * \remark This class must not be used while using the lowest level Oled class. This would lead to unexpected behaviour.
   */
  class Console {
  public:
	/** \brief Construct a console working with the given oled display.
	 */
	Console(const Oled& oled);

	/**
	* \brief Write a text to oled and flush display.
	*
	* Write the text to oled, scroll if needed and refresh oled display.
	*/
	Console& operator<<(const uint8_t* value);

    /**
     * \brief Write a text to oled and flush display.
     * 
     * Write the text to oled, scroll if needed and refresh oled display.
     */
	Console& operator<<(const String value);

	/**
	* \brief Write a text to oled and flush display.
	*
	* Write the text to oled, scroll if needed and refresh oled display.
	*/
	Console& operator<<(const OutputStream& value);

	/**
	* \brief Write a text to oled.
	*
	* Write the text to oled, scroll if needed but do not refresh oled display.
	* Use the \see flush method to flush the console to display.
	*/
	Console& write(const uint8_t* value);

	/**
	* \brief Write a text to oled.
	*
	* Write the text to oled, scroll if needed but do not refresh oled display.
	* Use the \see flush method to flush the console to display.
	*/
	Console& write(const String value);

	/**
	* \brief Write a text to oled.
	*
	* Write the text to oled, scroll if needed but do not refresh oled display.
	* Use the \see flush method to flush the console to display.
	*/
	Console& write(const OutputStream& value);

	/**
	* \brief Write a text to oled and jump to next line.
	*
	* Write the text to oled, end line, scroll if needed but do not refresh oled display.
	* Use the \see flush method to flush the console to display.
	*/
	Console& writeln(const uint8_t* value);

	/**
	* \brief Write a text to oled and jump to next line.
	*
	* Write the text to oled, end line, scroll if needed but do not refresh oled display.
	* Use the \see flush method to flush the console to display.
	*/
	Console& writeln(const String value);

	/**
	* \brief Write a text to oled and jump to next line.
	*
	* Write the text to oled, end line, scroll if needed but do not refresh oled display.
	* Use the \see flush method to flush the console to display.
	*/
	Console& writeln(const OutputStream& value);

	/**
	* \brief Flush the console to display.
	*
	* \remark Console needs to be flushed if "write" methods are used.
	*/
	Console& flush();

  private:
	  //The oled to display console output.
	  const Oled& oled;
  };
} // namespace devduino

//Define global console variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_CONSOLE)
	extern devduino::Console console;
#endif

#endif //DEVDUINO_CONSOLE_H