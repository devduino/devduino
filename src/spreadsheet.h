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

#include <Arduino.h>

#include "console.h"

/**
 * Default namespace for devduino related code.
 */

  /** 
   * Split and print to screen like on a spreadsheet.
   */
  class Spreadsheet {
  public:
	/**
	 * \brief Construct a spreadsheet with the given number of rows and columns.
	 *
	 * \param console The console display output to.
	 * \param nbRows The number of rows of the spreadsheet.
	 * \param nbColumns The number of columns of the spreadsheet.
	 * \param drawBorders true if borders must be drawn, false otherwise.
	 * \param autoFlush true to flush automatically on each API call, false otherwise.
	 */
	Spreadsheet(const Console& console, uint8_t nbRows = 4, uint8_t nbColumns = 1, bool drawBorders = false, bool autoFlush = true);

	/**
	* \brief Initialize spreadsheet.
	*
	* This method must be called before any other method of this class.
	*/
	void begin();

	/**
	 * \brief Print to the given cell of the spreadsheet.
	 *
	 * \param cellId The cell to ouput value to.
	 * \param value The buffer containing value to output.
	 * \param bufferSize The size of value buffer.
	 *
	 * \return A reference to this spreadsheet.
	 */
	Spreadsheet& print(uint8_t cellId, const char* value, size_t bufferSize);

	/**
	 * \brief Print to the given cell of the spreadsheet.
	 *
	 * \param cellId The cell to ouput value to.
	 * \param value The value to output.
	 *
	 * \return A reference to this spreadsheet.
	 */
	Spreadsheet& print(uint8_t cellId, const String& value);

	/**
	 * \brief Set the number of rows and columns of the spreadsheet.
	 *
	 * \param nbRows The number of rows of the spreadsheet.
	 * \param nbColumns The number of columns of the spreadsheet.
	 *
	 * \return A reference to this spreadsheet.
	 */
	Spreadsheet& setGrid(uint8_t nbRows, uint8_t nbColumns);

	/**
	 * \brief Flush the console to display.
	 *
	 * \remark Console needs to be flushed if "print" methods are used.
	 *
	 * \return A reference to this spreadsheet.
	 */
	Spreadsheet& flush();

	/**
	 * \brief Defines if spreadsheet should be auto-flushed.
	 *
	 * \param autoFlush true if spreadsheet must be auto-flushed, false otherwise.
	 *
	 * \return A reference to this spreadsheet.
	 */
	Spreadsheet& enableAutoFlush(bool autoFlush);

	/**
	 * \brief Defines is borders must be drawn.
	 *
	 * \param shouldDrawBorders true if borders must be drawn, false otherwise.
	 *
	 * \return A reference to this spreadsheet.
	 */
	Spreadsheet& enableDrawBorders(bool shouldDrawBorders);

  private:
	  /**
	   * \brief The console to display output to.
	   */
	  const Console& console;

	  /**
	   * \brief Defines if spreadsheet should be auto-flushed.
	   */
	  bool autoFlush;

	  /**
	   * \brief Defines if spreadsheet should be auto-flushed.
	   */
	  bool shouldDrawBorders;

	  /**
	   * \brief The number of rows of the spreadsheet.
	   */
	  uint8_t nbRows;

	  /**
	   * \brief The number of columns of the spreadsheet.
	   */
	  uint8_t nbColumns;

	  /**
	   * \brief The x position in  screen coordinates of next character to display.
	   */
	  uint8_t textX;
	  /**
	   * \brief The y position in  screen coordinates of next character to display.
	   */
	  uint8_t textY;

	  /**
	   * \brief draw borders of spreadsheet.
	   */
	  void drawBorders();
  };


#endif //DEVDUINO_SPREADSHEET_H
