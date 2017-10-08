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

#include "spreadsheet.h"

namespace devduino {
	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//
	Spreadsheet::Spreadsheet(const Oled& oled, uint8_t nbRows, uint8_t nbColumns, bool autoFlush) :
		oled(oled), 
		autoFlush(autoFlush)
	{
		setGrid(nbRows, nbColumns);
	}

	Spreadsheet& Spreadsheet::write(uint8_t cellId, const char* value, size_t buffer_size) {
		uint8_t row = cellId / nbColumns;
		uint8_t column = cellId - (row * nbColumns);

		if (row < nbRows && column < nbColumns) {
			uint8_t cellWidth = oled.getWidth() / nbColumns;
			uint8_t cellHeight = oled.getHeight() / nbRows;
			uint8_t cellX = column * cellWidth;
			uint8_t cellY = oled.getHeight() - ((row + 1) * cellHeight);
			oled.clearArea(cellX, cellY, cellWidth - 1, cellHeight - 1);
			oled.setTextPosition(cellX, cellY);
			oled.write(value, buffer_size);
			if (autoFlush) {
				flush();
			}
		}

		return *this;
	}

	Spreadsheet& Spreadsheet::write(uint8_t cellId, const String& value) {
		return write(cellId, value.c_str(), value.length());
	}

	Spreadsheet& Spreadsheet::setGrid(uint8_t nbRows, uint8_t nbColumns) {
		this->nbRows = nbRows;
		this->nbColumns = nbColumns;

		/*oled.clear();

		uint8_t cellWidth = oled.getWidth() / nbColumns;
		for (uint8_t column = 1; column < nbColumns; column++) {
			oled.drawVerticalLine(column * cellWidth, 0, oled.getHeight());
		}

		uint8_t cellHeight = oled.getHeight() / nbRows;
		for (uint8_t row = 1; row < nbRows; row++) {
			oled.drawVerticalLine(row * cellHeight, 0, oled.getWidth());
		}

		if (autoFlush) {
			flush();
		}*/
		return *this;
	}

	Spreadsheet& Spreadsheet::flush() {
		oled.display();
		return *this;
	}

	Spreadsheet& Spreadsheet::enableAutoFlush(bool autoFlush) {
		this->autoFlush = autoFlush;
		return *this;
	}

	//------------------------------------------------------------------------//
	//--------------------------- Private methods ----------------------------//
	//------------------------------------------------------------------------//
} // namespace devduino

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_SPREADSHEET)
	devduino::Spreadsheet spreadsheet(oled);
#endif