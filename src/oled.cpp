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

#include "oled.h"

//Include devduino default font if allowed. 
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_OLED_FONT)
#include "devduino.font.h"
#endif

//------------------------------------------------------------------------//
//---------------------------- Pre-processors ----------------------------//
//------------------------------------------------------------------------//
#define SSD1306_I2C_ADDRESS 0x3C

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

#define SSD1306_PIXELS_PER_BYTE 8

#define SSD1306_FONT_WIDTH 5

//The first ASCII code to be coded in font.
#define SSD_1306_FONT_FIRST_CODE 33

#define SSD1306_FONT_HEIGHT 7

//Size in uint8_t of buffer of boolean.
#define SSD1306_BUFFER_SIZE SSD1306_WIDTH * SSD1306_HEIGHT / SSD1306_PIXELS_PER_BYTE

#define SSD1306_MAX_BYTES_PER_TRANSMISSION 16

//Fundamental Commands
#define SSD1306_COMMAND_SET_CONTRAST_CONTROL 0x81
#define SSD1306_COMMAND_SET_ENTIRE_DISPLAY_ON 0xA4
#define SSD1306_COMMAND_SET_DISPLAY 0xA6

//Scrolling Commands
#define SSD1306_COMMAND_SET_HORIZONTAL_SCROLL 0x26
#define SSD1306_COMMAND_SET_PARAM_HORIZONTAL_SCROLL_RIGHT 0x00
#define SSD1306_COMMAND_SET_PARAM_HORIZONTAL_SCROLL_LEFT 0x01
#define SSD1306_COMMAND_SET_SCROLL_DEACTIVATE 0x2E
#define SSD1306_COMMAND_SET_SCROLL_ACTIVATE 0x2F
#define SSD1306_COMMAND_SET_VERTICAL_SCROLL_AREA 0xA3

//Addressing Setting Commands
#define SSD1306_COMMAND_SET_LOWER_COLUMN_START_ADDRESS 0x00
#define SSD1306_COMMAND_SET_HIGHER_COLUMN_START_ADDRESS 0x10

#define SSD1306_COMMAND_SET_MEMORY_MODE 0x20

#define SSD1306_COMMAND_SET_COLUMN 0x21
#define SSD1306_COMMAND_SET_PAGE 0x22
#define SSD1306_COMMAND_SET_PAGE_START 0xB0

//Hardware Configuration (Panel resolution & layout related) Commands
#define SSD1306_COMMAND_SET_DISPLAY_START_LINE 0x40

#define SSD1306_COMMAND_SET_SEGMENT_REMAP 0xA0

#define SSD1306_COMMAND_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_COMMAND_SET_COM_OUTPUT_SCAN_DIRECTION 0xC0
#define SSD1306_COMMAND_SET_DISPLAY_OFFSET 0xD3

#define SSD1306_COMMAND_SET_COM_PINS_HARDWARE_CONFIG 0xDA

//Timing & Driving Scheme Setting Commands
#define SSD1306_COMMAND_SET_DISPLAY_CLOCK_DIVIDE_RATIO 0xD5
#define SSD1306_COMMAND_SET_PRECHARGE_PERIOD 0xD9
#define SSD1306_COMMAND_SET_VCOMH_DESELECT_LEVEL 0xDB

//Charge Pump Commands
#define SSD1306_COMMAND_SET_CHARGE_PUMP_SETTING 0x8D

namespace devduino {
	//------------------------------------------------------------------------//
	//--------------------------- Static variables ---------------------------//
	//------------------------------------------------------------------------//

	uint8_t Oled::buffer[SSD1306_BUFFER_SIZE];

	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//
	uint8_t Oled::getWidth() {
		return SSD1306_WIDTH;
	}

	uint8_t Oled::getHeight() {
		return SSD1306_HEIGHT;
	}

	void Oled::begin(const Font* font) {
		if (font == nullptr) {
			//If no font is set but default font accepted, we set it.
#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED) && !defined(NO_GLOBAL_OLED_FONT)
			setFont(&devduinoFont);
#endif
		}
		else {
			setFont(font);
		}

		Wire.begin();

		setDisplayOnOff(displayOnOff_t::off);
		setMemoryAddressingMode(memoryAddressingMode_t::horizontal);
		setColumnAddress(0, SSD1306_HEIGHT - 1);
		setSegmentReMap(segmentReMap_t::end);
		setNormalOrInverseDisplay(normalOrInverseDisplay_t::normal);
		setMultiplexRatio(SSD1306_HEIGHT - 1);
		setComOutputScanDirection(comOutputScanDirection_t::from);
		setDisplayOffset(0x00);
		setDisplayClockDivideRatioOscillatorFrequency(0x8, 0x00);
		setPreChargePeriod(0x02, 0x02);
		setComPinsHardwareConfiguration(comPinsHardwareConfigurationPin_t::alternative, comPinsHardwareConfigurationRemap_t::disable);
		setEntireDisplayOn(entireDisplayOn_t::follow);
		setChargePumpSetting(chargePumpSetting_t::enable);
		setDisplayOnOff(displayOnOff_t::on);
	}
    
	void Oled::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
		uint8_t deltaX = (x1 > x0) ? (x1 - x0) : (x0 - x1);
		uint8_t deltaY = (y1 > y0) ? (y1 - y0) : (y0 - y1);

		int8_t directionX = x0 < x1 ? 1 : -1;
		int8_t directionY = y0 < y1 ? 1 : -1;

		int8_t error = (deltaX > deltaY ? deltaX : -deltaY) / 2;

		while (x0 != x1 || y0 != y1) {
			drawPixel(x0, y0);

			int8_t currentError = error;

			if (currentError > -deltaX) {
				error -= deltaY;
				x0 += directionX;
			}

			if (currentError < deltaY) {
				error += deltaX;
				y0 += directionY;
			}
		}
		drawPixel(x0, y0);
	}
    
	void Oled::drawHorizontalLine(uint8_t x0, uint8_t x1, uint8_t y) {
		while (x0 != x1) {
			drawPixel(x0, y);
			x0 += (x1>x0) ? 1 : -1;
		}
		drawPixel(x0, y);
	}
    
	void Oled::drawVerticalLine(uint8_t x, uint8_t y0, uint8_t y1) {
		while (y0 != y1) {
			drawPixel(x, y0);
			y0 += (y1 > y0) ? 1 : -1;
		}
		drawPixel(x, y0);
	}

	void Oled::drawRectangle(uint8_t top, uint8_t left, uint8_t bottom, uint8_t right) {
		drawHorizontalLine(left, right, top);
		drawHorizontalLine(left, right, bottom);
		drawVerticalLine(left, top, bottom);
		drawVerticalLine(right, top, bottom);
	}
    
	void Oled::fillRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
		while(w > 0) {
			w--;
			drawVerticalLine(x + w, y, y + h - 1);
		}
	}

	void Oled::drawCircle(uint8_t centerX, uint8_t centerY, int8_t radius) {
		uint8_t x = 0;
		uint8_t y = radius;

		int8_t m = 5 - 4 * radius;

		while (x <= y) {
			drawPixel(centerX + x, centerY + y);
			drawPixel(centerX + y, centerY + x);
			drawPixel(centerX - x, centerY + y);
			drawPixel(centerX - y, centerY + x);
			drawPixel(centerX + x, centerY - y);
			drawPixel(centerX + y, centerY - x);
			drawPixel(centerX - x, centerY - y);
			drawPixel(centerX - y, centerY - x);

			if (m > 0) {
				y--;
				m -= 8 * y;
			}

			x++;
			m += 8 * x + 4;
		}
	}

	void Oled::fillCircle(uint8_t centerX, uint8_t centerY, int8_t radius) {
		uint8_t x = 0;
		uint8_t y = radius;

		int8_t m = 5 - 4 * radius;

		while (x <= y) {
			drawVerticalLine(centerX + x, centerY + y, centerY);
			drawVerticalLine(centerX + y, centerY + x, centerY);
			drawVerticalLine(centerX - x, centerY + y, centerY);
			drawVerticalLine(centerX - y, centerY + x, centerY);
			drawVerticalLine(centerX + x, centerY - y, centerY);
			drawVerticalLine(centerX + y, centerY - x, centerY);
			drawVerticalLine(centerX - x, centerY - y, centerY);
			drawVerticalLine(centerX - y, centerY - x, centerY);

			if (m > 0) {
				y--;
				m -= 8 * y;
			}

			x++;
			m += 8 * x + 4;
		}
	}

	void Oled::drawBuffer(const uint8_t* buffer, uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
		for (uint8_t currentX = 0; currentX < w; currentX++) {
			for (uint8_t currentY = 0; currentY < h; currentY++) {
				//Get the 8 pixels on byte.
				uint8_t pixels = pgm_read_byte(&buffer[((h - 1) - currentY) * w + currentX]);
				for (int pixelY = 1, i = 0; pixelY <= 128; pixelY <<= 1, i++) {
					if (pixels & pixelY) {
						drawPixel(x + currentX, y + currentY * 8 + i);
					}
				}
			}
		}
	}

	void Oled::drawSprite(const Sprite& sprite, uint8_t x, uint8_t y, uint8_t scale = 0) {
		//FIXME: Gérer le scale.
		drawBuffer(sprite.getBuffer(), x, y, sprite.getWidth(), sprite.getHeight());
	}

	void Oled::drawPixel(uint8_t x, uint8_t y) {
		if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
			return;
		}

		buffer[x + ((y / SSD1306_PIXELS_PER_BYTE) * SSD1306_WIDTH)] |= (1 << (y & (SSD1306_PIXELS_PER_BYTE - 1)));
	}
	
	void Oled::setTextPosition(uint8_t x, uint8_t y) {
		textX = x;
		textY = y;
	}

	void Oled::setFont(const Font* font) {
		this->font = font;
	}

	void Oled::setFontSize(uint8_t size) {
		fontSize = size;
	}

	void Oled::newLine() {
		textX = 0;
		textY -= fontSize * SSD1306_FONT_HEIGHT + 1;
	}

	void Oled::newLine(uint8_t pixels) {
		if (textX + fontSize * pixels > SSD1306_WIDTH) {
			newLine();
		}
	}

	void Oled::write(String text) {
		write(text.c_str(), text.length());		
	}

	void Oled::write(const char *buffer, size_t buffer_size) {
		while (buffer_size--) {
			write(*buffer++);
		}
	}
    
	void Oled::write(uint8_t characterCode, uint8_t previousCharacterCode) {
		if (characterCode == '\n') {
			newLine();
		} else {
			int8_t kerning = font->getGlyphKerning(characterCode, previousCharacterCode);
			uint8_t width = font->getGlyphWidth(characterCode);
			newLine(width + kerning);
			drawBuffer(font->getGlyphPixels(characterCode), textX + kerning, textY, width, font->getGlyphHeight(characterCode) / 8 + 1);
			incrementTextPosition(width + kerning);
		}
	}

	void Oled::display() {
		//Save previous clock configuration and set clock 400 KHz.
		uint8_t previousClock = TWBR;
		Wire.setClock(400000);

		setColumnAddress(0, SSD1306_WIDTH - 1);
		setPageAddress(0, 7);

		//Begin a transmission each SSD1306_MAX_BYTES_PER_TRANSMISSION bytes.
		for (uint16_t i = 0; i < SSD1306_BUFFER_SIZE; i += SSD1306_MAX_BYTES_PER_TRANSMISSION) {
			Wire.beginTransmission(SSD1306_I2C_ADDRESS);
			Wire.write(SSD1306_COMMAND_SET_DISPLAY_START_LINE | 0x00);

			for (uint16_t index = i; index < i + SSD1306_MAX_BYTES_PER_TRANSMISSION; index++) {
				Wire.write(buffer[index]);
			}

			Wire.endTransmission();
		}

		//Go back to previous clock configuration.
		TWBR = previousClock;
	}

	void Oled::clear() {
		memset(buffer, 0, SSD1306_BUFFER_SIZE);
	}

	void Oled::clearArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
		if (x + width >= SSD1306_WIDTH || y + height >= SSD1306_HEIGHT) {
			return;
		}
		for (uint8_t i = x; i <= x + width; i++) {
			for (uint8_t j = y; j <= y + height; j++) {
				clearPixel(i, j);
			}
		}
	}

	void Oled::clearPixel(uint8_t x, uint8_t y) {
		if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
			return;
		}

		buffer[x + ((y / SSD1306_PIXELS_PER_BYTE) * SSD1306_WIDTH)] &= ~(1 << (y & (SSD1306_PIXELS_PER_BYTE - 1)));
	}

	//------------------------------------------------------------------------//
	//--------------------------- Private methods ----------------------------//
	//------------------------------------------------------------------------//

	void Oled::incrementTextPosition(uint8_t pixels) {
		textX += fontSize * pixels + 1;
	}

	void Oled::setMemoryAddressingMode(memoryAddressingMode_t mode) {
		sendCommand(SSD1306_COMMAND_SET_MEMORY_MODE);
		sendCommand(static_cast<uint8_t>(mode));
	}

	void Oled::setColumnAddress(uint8_t startAddress, uint8_t endAddress) {
		sendCommand(SSD1306_COMMAND_SET_COLUMN);
		sendCommand(startAddress);
		sendCommand(endAddress);
	}

	void Oled::setPageAddress(uint8_t startAddress, uint8_t endAddress) {
		sendCommand(SSD1306_COMMAND_SET_PAGE);
		sendCommand(startAddress);
		sendCommand(endAddress);
	}

	void Oled::setDisplayStartLine(uint8_t line) {
		sendCommand(SSD1306_COMMAND_SET_DISPLAY_START_LINE | line);
	}

	void Oled::setContrastControl(uint8_t contrast) {
		sendCommand(SSD1306_COMMAND_SET_CONTRAST_CONTROL);
		sendCommand(contrast);
	}

	void Oled::setSegmentReMap(segmentReMap_t address) {
		sendCommand(SSD1306_COMMAND_SET_SEGMENT_REMAP | static_cast<uint8_t>(address));
	}

	void Oled::setEntireDisplayOn(entireDisplayOn_t followIgnore) {
		sendCommand(SSD1306_COMMAND_SET_ENTIRE_DISPLAY_ON | static_cast<uint8_t>(followIgnore));
	}

	void Oled::setNormalOrInverseDisplay(normalOrInverseDisplay_t normalInverse) {
		sendCommand(SSD1306_COMMAND_SET_DISPLAY | static_cast<uint8_t>(normalInverse));
	}

	void Oled::setMultiplexRatio(uint8_t ratio) {
		sendCommand(SSD1306_COMMAND_SET_MULTIPLEX_RATIO);
		sendCommand(ratio);
	}

	void Oled::setDisplayOnOff(displayOnOff_t onOff) {
		sendCommand(static_cast<uint8_t>(onOff));
	}

	void Oled::setComOutputScanDirection(comOutputScanDirection_t direction) {
		sendCommand(SSD1306_COMMAND_SET_COM_OUTPUT_SCAN_DIRECTION);
		sendCommand(static_cast<uint8_t>(direction));
	}

	void Oled::setDisplayOffset(uint8_t offset) {
		sendCommand(SSD1306_COMMAND_SET_DISPLAY_OFFSET);
		sendCommand(offset);
	}

	void Oled::setDisplayClockDivideRatioOscillatorFrequency(uint8_t ratio,
	uint8_t frequency) {
		sendCommand(SSD1306_COMMAND_SET_DISPLAY_CLOCK_DIVIDE_RATIO);
		sendCommand(ratio << 4 | frequency);
	}

	void Oled::setPreChargePeriod(uint8_t phase1, uint8_t phase2) {
		sendCommand(SSD1306_COMMAND_SET_PRECHARGE_PERIOD);
		sendCommand(phase1 << 4 | phase2);
	}

	void Oled::setComPinsHardwareConfiguration(comPinsHardwareConfigurationPin_t pinConfiguration, 
		comPinsHardwareConfigurationRemap_t remapConfiguration) {
		sendCommand(SSD1306_COMMAND_SET_COM_PINS_HARDWARE_CONFIG);
		sendCommand(static_cast<uint8_t>(pinConfiguration) | static_cast<uint8_t>(remapConfiguration));
	}

	void Oled::setChargePumpSetting(chargePumpSetting_t setting) {
		sendCommand(SSD1306_COMMAND_SET_CHARGE_PUMP_SETTING);
		sendCommand(static_cast<uint8_t>(setting));
	}

	void Oled::setVComHDeselectLevel(uint8_t level) {
		sendCommand(SSD1306_COMMAND_SET_VCOMH_DESELECT_LEVEL);
		sendCommand(static_cast<uint8_t>(level));
	}

	void Oled::setActivateScroll(activateScroll_t activateDeactivate) {
		sendCommand(static_cast<uint8_t>(activateDeactivate));
	}

	void Oled::sendCommand(uint8_t c) {
		Wire.beginTransmission(SSD1306_I2C_ADDRESS);
		Wire.write(0x00);
		Wire.write(c);
		Wire.endTransmission();
	}
} // namespace devduino

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_OLED)
devduino::Oled oled;
#endif