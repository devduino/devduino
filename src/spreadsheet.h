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

#ifndef DEVDUINO_SPREADSHEET_H
#define DEVDUINO_SPREADSHEET_H

#include <arduino.h>

#include "oled.h"

/**
* Default namespace for devduino related code.
*/
namespace devduino {
  /** 
   * 
   */
  class Spreadsheet {
  public:
	Spreadsheet(const Oled& oled, uint8_t nbRows = 4, uint8_t nbColumns = 1, bool autoFlush = true);

	Spreadsheet& write(uint8_t cellId, const char* value, size_t buffer_size);

	Spreadsheet& write(uint8_t cellId, const String& value);

	Spreadsheet& setGrid(uint8_t nbRows, uint8_t nbColumns);

	/**
	* \brief Flush the console to display.
	*
	* \remark Console needs to be flushed if "write" methods are used.
	*/
	Spreadsheet& flush();

	Spreadsheet& enableAutoFlush(bool autoFlush);

  private:
	  //The oled to display console output.
	  const Oled& oled;

	  bool autoFlush;
	  uint8_t nbRows;
	  uint8_t nbColumns;
  };
} // namespace devduino

//Define global console variable.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_SPREADSHEET)
	extern devduino::Spreadsheet spreadsheet;
#endif

#endif //DEVDUINO_SPREADSHEET_H