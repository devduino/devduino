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

#include "display.h"

//------------------------------------------------------------------------//
//---------------------------- Pre-processors ----------------------------//
//------------------------------------------------------------------------//
#define SSD1306_I2C_ADDRESS 0x3C

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

#define SSD1306_PIXELS_PER_BYTE 8

//Size in uint8_t of buffer of boolean.
#define SSD1306_BUFFER_SIZE SSD1306_WIDTH * SSD1306_HEIGHT / SSD1306_PIXELS_PER_BYTE

#define SSD1306_MAX_BYTES_PER_TRANSMISSION 16

//Fundamental Commands
#define SSD1306_COMMAND_SET_CONTRAST_CONTROL 0x81
#define SSD1306_COMMAND_SET_ENTIRE_DISPLAY_ON 0xA4
#define SSD1306_COMMAND_SET_DISPLAY 0xA6

//Scrolling Commands
#define SSD1306_COMMAND_SET_HORIZONTAL_SCROLL 0x26
#define SSD1306_COMMAND_SET_VERTICAL_RIGHT_SCROLL 0x29
#define SSD1306_COMMAND_SET_VERTICAL_LEFT_SCROLL 0x2A
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

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

	//------------------------------------------------------------------------//
	//--------------------------- Static variables ---------------------------//
	//------------------------------------------------------------------------//

	uint8_t Display::buffer[SSD1306_BUFFER_SIZE];

	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//
	uint8_t Display::getWidth() {
		return SSD1306_WIDTH;
	}

	uint8_t Display::getHeight() {
		return SSD1306_HEIGHT;
	}

	void Display::begin() {
		setDisplayOnOff(displayOnOff_t::off);
		setDisplayStartLine(0);
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
		stopContinuousVerticalScroll();
		setDisplayOnOff(displayOnOff_t::on);

		clear();
	}
    
	void Display::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
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
	

    
	void Display::drawHorizontalLine(uint8_t x0, uint8_t x1, uint8_t y) {
		while (x0 != x1) {
			drawPixel(x0, y);
			x0 += (x1>x0) ? 1 : -1;
		}
		drawPixel(x0, y);
	}
    
	void Display::drawVerticalLine(uint8_t x, uint8_t y0, uint8_t y1) {
		while (y0 != y1) {
			drawPixel(x, y0);
			y0 += (y1 > y0) ? 1 : -1;
		}
		drawPixel(x, y0);
	}

	void Display::drawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
		drawHorizontalLine(x, x + w - 1, y + h - 1);
		drawHorizontalLine(x, x + w - 1, y);
		drawVerticalLine(x, y, y + h - 1);
		drawVerticalLine(x + w - 1, y, y + h - 1);
	}
    
	void Display::fillRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
		while(w > 0) {
			w--;
			drawVerticalLine(x + w, y, y + h);
		}
	}

	void Display::drawCircle(uint8_t centerX, uint8_t centerY, int8_t radius) {
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

	void Display::fillCircle(uint8_t centerX, uint8_t centerY, int8_t radius) {
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

	void Display::verticalScroll(int8_t pixels, bool clear) {
		//Compute display start line and clear scrolled buffer.
		int8_t newStartLine = displayStartLine + pixels;
		if (newStartLine > SSD1306_HEIGHT - 1) {
			newStartLine %= SSD1306_HEIGHT;

			if (clear) {
				//Clear buffer from old start line to screen height.
				clearArea(0, displayStartLine, SSD1306_WIDTH, SSD1306_HEIGHT - displayStartLine);
				//Clear buffer from 0 to new start line.
				clearArea(0, 0, SSD1306_WIDTH, newStartLine);
			}
		}
		else if (newStartLine < 0) {
			newStartLine += SSD1306_HEIGHT;
			if (clear) {
				//Clear buffer from 0 to old start line.
				clearArea(0, 0, SSD1306_WIDTH, displayStartLine);
				//Clear buffer from new start line to screen height.
				clearArea(0, newStartLine, SSD1306_WIDTH, SSD1306_HEIGHT - newStartLine);
			}
		}
		else if (clear) {
			//Clear buffer from new start line to old start line.
			if (pixels > 0) {
				clearArea(0, displayStartLine, SSD1306_WIDTH, pixels);
			}
			else {
				clearArea(0, newStartLine, SSD1306_WIDTH, -pixels);
			}
		}

		setDisplayStartLine(newStartLine);
	}

	void Display::resetVerticalScroll() {
		setDisplayStartLine(0);
	}

	int8_t Display::getVerticalScroll() {
		return displayStartLine;
	}

	void Display::continuousVerticalScroll(uint8_t speed) {
		setActivateScroll(activateScroll_t::deactivate);

		sendCommand(SSD1306_COMMAND_SET_VERTICAL_SCROLL_AREA);
		sendCommand(0x00);
		sendCommand(SSD1306_HEIGHT);
		sendCommand(SSD1306_COMMAND_SET_VERTICAL_RIGHT_SCROLL);
		sendCommand(0x00);
		sendCommand(0x00);
		sendCommand(0x00);
		sendCommand(0x00);
		sendCommand(speed);

		setActivateScroll(activateScroll_t::activate);
	}

	void Display::stopContinuousVerticalScroll() {
		setActivateScroll(activateScroll_t::deactivate);
	}

	void Display::drawBuffer(const uint8_t* buffer, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool wrapX, bool wrapY) {
		for (uint8_t currentX = 0; currentX < w; currentX++) {
			uint8_t pixelX = x + currentX;
			if (pixelX >= SSD1306_WIDTH) {
				//Wrap X if greater than width or break.
				if (wrapX) {
					pixelX -= SSD1306_WIDTH;
				}
				else {
					break;
				}
			}
			if (pixelX < 0) {
				//Wrap X if lower than 0 or break.
				if (wrapY) {
					pixelX += SSD1306_WIDTH;
				}
				else {
					break;
				}
			}

			for (uint8_t currentY = 0; currentY < h; currentY++) {
				//Get the 8 pixels on byte.
				uint8_t pixels = pgm_read_byte(&buffer[((h - 1) - currentY) * w + currentX]);

				for (int pixelByteY = 1, i = 0; pixelByteY <= 128; pixelByteY <<= 1, i++) {
					uint8_t pixelY = y + currentY * 8 + i;
					if (pixelY >= SSD1306_HEIGHT) {
						//Wrap Y if greater than height or break.
						if (wrapY) {
							pixelY -= SSD1306_HEIGHT;
						}
						else {
							break;
						}
					}
					if (pixelY < 0) {
						//Wrap Y if lower than 0 or break.
						if (wrapY) {
							pixelY += SSD1306_HEIGHT;
						}
						else {
							break;
						}
					}

					if (pixels & pixelByteY) {
						drawPixel(pixelX, pixelY);
					}
				}
			}
		}
	}

	void Display::drawSprite(const Sprite& sprite, uint8_t x, uint8_t y) {
	  drawBuffer((uint8_t*)sprite.getBuffer(), x, y, sprite.getWidth(), sprite.getHeight());
	}

	void Display::drawPixel(uint8_t x, uint8_t y) {
		for (uint8_t i = 0; i < scale; i++) {
			for (uint8_t j = 0; j < scale; j++) {
				uint8_t posX = x * scale + i;
				uint8_t posY = y * scale + j;
				if (posX < SSD1306_WIDTH && posY < SSD1306_HEIGHT) {
					uint8_t bits = (1 << (posY & (SSD1306_PIXELS_PER_BYTE - 1)));
					buffer[posX + (((y * scale + j) / SSD1306_PIXELS_PER_BYTE) * SSD1306_WIDTH)] |= bits;
				}
			}
		}
	}

	void Display::print(String text, uint8_t x, uint8_t y, Font* font) {
		print(text.c_str(), text.length(), x, y, font);
	}

	void Display::print(const char *buffer, size_t bufferSize, uint8_t x, uint8_t y, Font* font) {
		uint8_t width = 0;
		while (bufferSize--) {
			uint8_t glyphWidth = font->getGlyphWidth(*buffer);
			uint8_t glyphHeight = font->getGlyphHeight(*buffer);
			drawBuffer(font->getGlyphPixels(*buffer), 
				x + width + font->getGlyphXOffset(*buffer), 
				y + font->getGlyphYOffset(*buffer), 
				glyphWidth, 
				glyphHeight / 8 + 1);
			buffer++;
			//Increment width from glyphWidth + 1 to not let glyphs touch themselves.
			width += font->getGlyphXAdvance(*buffer);
		}
	}

	void Display::print(uint8_t characterCode, uint8_t x, uint8_t y, Font* font) {
		uint8_t width = font->getGlyphWidth(characterCode);
		uint8_t height = font->getGlyphHeight(characterCode);
		drawBuffer(font->getGlyphPixels(characterCode), x, y, width, height / 8 + 1);
	}

	void Display::flush() {
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
		sendCommand(SSD1306_COMMAND_SET_DISPLAY_START_LINE | displayStartLine);

		//Go back to previous clock configuration.
		TWBR = previousClock;
	}

	void Display::clear() {
		memset(buffer, 0, SSD1306_BUFFER_SIZE);
	}

	void Display::clearArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
		if (x + width > SSD1306_WIDTH || y + height > SSD1306_HEIGHT) {
			return;
		}
		for (uint8_t i = x; i < x + width; i++) {
			for (uint8_t j = y; j < y + height; j++) {
				clearPixel(i, j);
			}
		}
	}

	void Display::clearPixel(uint8_t x, uint8_t y) {
		if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
			return;
		}

		buffer[x + ((y / SSD1306_PIXELS_PER_BYTE) * SSD1306_WIDTH)] &= ~(1 << (y & (SSD1306_PIXELS_PER_BYTE - 1)));
	}

	void Display::setScale(uint8_t scale) {
		this->scale = scale;
	}

	uint8_t Display::getScale() {
		return scale;
	}

	//------------------------------------------------------------------------//
	//--------------------------- Private methods ----------------------------//
	//------------------------------------------------------------------------//

	void Display::setMemoryAddressingMode(memoryAddressingMode_t mode) {
		sendCommand(SSD1306_COMMAND_SET_MEMORY_MODE);
		sendCommand(static_cast<uint8_t>(mode));
	}

	void Display::setColumnAddress(uint8_t startAddress, uint8_t endAddress) {
		sendCommand(SSD1306_COMMAND_SET_COLUMN);
		sendCommand(startAddress);
		sendCommand(endAddress);
	}

	void Display::setPageAddress(uint8_t startAddress, uint8_t endAddress) {
		sendCommand(SSD1306_COMMAND_SET_PAGE);
		sendCommand(startAddress);
		sendCommand(endAddress);
	}

	void Display::setDisplayStartLine(uint8_t line) {
		displayStartLine = line % SSD1306_HEIGHT;
	}

	void Display::setContrastControl(uint8_t contrast) {
		sendCommand(SSD1306_COMMAND_SET_CONTRAST_CONTROL);
		sendCommand(contrast);
	}

	void Display::setSegmentReMap(segmentReMap_t address) {
		sendCommand(SSD1306_COMMAND_SET_SEGMENT_REMAP | static_cast<uint8_t>(address));
	}

	void Display::setEntireDisplayOn(entireDisplayOn_t followIgnore) {
		sendCommand(SSD1306_COMMAND_SET_ENTIRE_DISPLAY_ON | static_cast<uint8_t>(followIgnore));
	}

	void Display::setNormalOrInverseDisplay(normalOrInverseDisplay_t normalInverse) {
		sendCommand(SSD1306_COMMAND_SET_DISPLAY | static_cast<uint8_t>(normalInverse));
	}

	void Display::setMultiplexRatio(uint8_t ratio) {
		sendCommand(SSD1306_COMMAND_SET_MULTIPLEX_RATIO);
		sendCommand(ratio);
	}

	void Display::setDisplayOnOff(displayOnOff_t onOff) {
		sendCommand(static_cast<uint8_t>(onOff));
	}

	void Display::setComOutputScanDirection(comOutputScanDirection_t direction) {
		sendCommand(SSD1306_COMMAND_SET_COM_OUTPUT_SCAN_DIRECTION);
		sendCommand(static_cast<uint8_t>(direction));
	}

	void Display::setDisplayOffset(uint8_t offset) {
		sendCommand(SSD1306_COMMAND_SET_DISPLAY_OFFSET);
		sendCommand(offset);
	}

	void Display::setDisplayClockDivideRatioOscillatorFrequency(uint8_t ratio,
	uint8_t frequency) {
		sendCommand(SSD1306_COMMAND_SET_DISPLAY_CLOCK_DIVIDE_RATIO);
		sendCommand(ratio << 4 | frequency);
	}

	void Display::setPreChargePeriod(uint8_t phase1, uint8_t phase2) {
		sendCommand(SSD1306_COMMAND_SET_PRECHARGE_PERIOD);
		sendCommand(phase1 << 4 | phase2);
	}

	void Display::setComPinsHardwareConfiguration(comPinsHardwareConfigurationPin_t pinConfiguration, 
		comPinsHardwareConfigurationRemap_t remapConfiguration) {
		sendCommand(SSD1306_COMMAND_SET_COM_PINS_HARDWARE_CONFIG);
		sendCommand(static_cast<uint8_t>(pinConfiguration) | static_cast<uint8_t>(remapConfiguration));
	}

	void Display::setChargePumpSetting(chargePumpSetting_t setting) {
		sendCommand(SSD1306_COMMAND_SET_CHARGE_PUMP_SETTING);
		sendCommand(static_cast<uint8_t>(setting));
	}

	void Display::setVComHDeselectLevel(uint8_t level) {
		sendCommand(SSD1306_COMMAND_SET_VCOMH_DESELECT_LEVEL);
		sendCommand(static_cast<uint8_t>(level));
	}

	void Display::setActivateScroll(activateScroll_t activateDeactivate) {
		sendCommand(static_cast<uint8_t>(activateDeactivate));
	}

	void Display::sendCommand(uint8_t c) {
		Wire.beginTransmission(SSD1306_I2C_ADDRESS);
		Wire.write(0x00);
		Wire.write(c);
		Wire.endTransmission();
	}
