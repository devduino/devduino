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

#ifndef DEVDUINO_DISPLAY_H
#define DEVDUINO_DISPLAY_H

#include <stdint.h>
#include <arduino.h>

#include "Sprite.h"
#include "Font.h"

/**
 * Default namespace for devduino related code.
 */
  /** 
   * \brief High level driver for SSD1306 of devduino.
   * 
   * You must call "begin" method before being able to use it.
   * The coordinate x=0 and y=0 is the bottom left corner of the screen.
   * The coordinate x=127 and y=63 is the top right corner of the screen.
   * 
   * All coordinates greater than x=127 and y=63 are ignored.
   * 
   * For more information on internal behavior, the display screen datasheet is available <a href="http:\\www.datasheetspdf.com\datasheet\SSD1306" target="_blank">here</a>.
   */
  class Display {
  public:
	/**
	 * \brief Get the width of screen.
	 * 
	 * \return The width of screen in pixels.
	 */
	uint8_t getWidth();

	/**
	 * \brief Get the height of screen.
	 *
	 * \return The height of screen in pixels.
	 */
	uint8_t getHeight();

	/**
	 * \brief Initialize display screen on DevDuino.
	 *
	 * This method must be called before any other method of this class.
	 *
	 * \remark Default font can be disabled by setting the preprocessor NO_GLOBAL_DISPLAY_FONT.
	 */
	void begin();

    /** 
     * \brief Draw a white line on screen.
     * 
     * Draw the line from \p x0, \p y0 to \p x1, \p y1.
     * The line can be drawn in any direction.
     * If the line you plan to draw is horizontal or vertical,
     * please use methods drawHorizontalLine or drawVerticalLine which are more effective.
	 * 
	 * X and Y coordinates must be between 0 and 127 (included).
     * 
     * \remark the rendering will be effective after a call to method flush().
     * 
     * \see drawHorizontalLine().
     * \see drawVerticalLine().
     * \see flush().
     * 
     * \param x0 The start position in pixel on X axis of the line to draw.
     * \param y0 The start position in pixel on Y axis of the line to draw.
     * \param x1 The end position in pixel on X axis of the line to draw.
     * \param y1 The end position in pixel on Y axis of the line to draw.
     */
    void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

    /**
     * \brief Draw a white horizontal line on screen.
     * 
     * Draw the line from \p x0, \p y to \p x1, \p y.
	 * 
	 * X and Y coordinates must be between 0 and 127 (included).
     * 
     * \remark the rendering will be effective after a call to method flush().
     * 
     * \see flush().
     * 
     * \param x0 The start position in pixel on X axis of the line to draw.
     * \param x1 The end position in pixel on X axis of the line to draw.
     * \param y The position in pixel on Y axis of the line to draw.
     */
    void drawHorizontalLine(uint8_t x0, uint8_t x1, uint8_t y);

    /**
     * \brief Draw a white vertical line on screen.
     * 
     * Draw the line from \p x, \p y0 to \p x, \p y1.
	 * 
	 * X and Y coordinates must be between 0 and 127 (included).
     * 
     * \remark the rendering will be effective after a call to method flush().
     * 
     * \see flush().
     * 
     * \param x The position in pixel on X axis of the line to draw.
     * \param y0 The start position in pixel on Y axis of the line to draw.
     * \param y1 The end position in pixel on Y axis of the line to draw.
     */
    void drawVerticalLine(uint8_t x, uint8_t y0, uint8_t y1);

	/**
	 * \brief Draw a rectangle with white border.
	 *
	 * \remark the rendering will be effective after a call to method flush().
	 *
	 * \see flush().
	 *
	 * \param x The position in pixel on X axis of the top border to draw.
	 * \param y The position in pixel on Y axis of the left border to draw.
	* \param w The width in pixel of the rectangle to draw.
	* \param h The height in pixel of the rectangle to draw.
	 */
	void drawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

	/**
	* \brief Fill a rectangle with white.
	*
	* Rectangle is filled from \p x and \p y, a width \p w and a height \p h.
	*
	* \remark the rendering will be effective after a call to method flush().
	*
	* \see flush().
	*
	* \param x The position in pixel on X axis of the rectangle to draw.
	* \param y The position in pixel on Y axis of the rectangle to draw.
	* \param w The width in pixel of the rectangle to draw.
	* \param h The height in pixel of the rectangle to draw.
	*/
	void fillRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

	/**
	 * \brief Draw a circle with white border.
	 *
	 * \remark the rendering will be effective after a call to method flush().
	 *
	 * \see flush().
	 *
	 * \param centerX The position in pixel of the X center of the circle.
	 * \param centerY The position in pixel of the Y center of the circle.
	 * \param radius The radius in pixel of the circle.
	 */
	void drawCircle(uint8_t centerX, uint8_t centerY, int8_t radius);

	/**
	* \brief Fill a circle with white.
	*
	* \remark the rendering will be effective after a call to method flush().
	*
	* \see flush().
	*
	* \param centerX The position in pixel of the X center of the circle.
	* \param centerY The position in pixel of the Y center of the circle.
	* \param radius The radius in pixel of the circle.
	*/
	void fillCircle(uint8_t centerX, uint8_t centerY, int8_t radius);

	/**
	 * \brief Scrolls flush vertically.
	 *
	 * Negative pixels scroll to bottom of screen, positive ones scroll to top of screen.
	 *
	 * \param pixels The number of pixels to scroll.
	 * \param clear True if pixels out of bounds must be cleared, false if pixels must be wrapped.
	 */
	void verticalScroll(int8_t pixels, bool clear =true);

	/**
	 * \brief Reset vertical scroll to 0 (its original position).
	 */
	void resetVerticalScroll();

	/**
	 * Get the current vertical scroll offset.
	 *
	 * \attention Does not work with continuous scrolling function.
	 *
	 * \return the number of pixels scrolled.
	 */
	int8_t getVerticalScroll();

	/**
	* \brief Continuously scroll flush vertically.
	*
	* Negative speed scrolls bottom of screen, positive one scroll top of screen.
	*
	* \param speed The speed of scroll.
	*/
	void continuousVerticalScroll(uint8_t speed);

	/**
	 * \brief stop the continuous vertical scrolling of screen.
	 */
	void stopContinuousVerticalScroll();

	/**
	 * \brief Draws a buffer.
     * 
     * Buffer is drawn to \p x and \p y.
	 * \p w and \p h parameters are the width and height in pixels of the buffer. It does not affect the scale of the drawn image.
     * 
     * \remark \p buffer must be stored in flash memory (PROGMEM).
     * \remark The rendering will be effective after a call to method flush().
     * 
     * \see flush().
     * 
     * \param buffer The buffer to draw to display.
     * \param x The position in pixel on X axis of the buffer to draw.
     * \param y The position in pixel on Y axis of the buffer to draw.
     * \param w The width in pixel of the buffer.
     * \param h The height in bytes of the buffer.
     * \param wrapX True if pixel that are beyond/before width of screen must be wrapped to left/right of screen.
     * \param wrapY True if pixel that are beyond/before height of screen must be wrapped to top/bottom of screen.
	 */
	void drawBuffer(const uint8_t* buffer, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool wrapX = false, bool wrapY = false);

	/**
	* \brief Draws a sprite.
	*
	* Sprite is drawn to \p x and \p y.
	*
	* \remark \p sprite's buffer must be stored in flash memory (PROGMEM).
	* \remark the rendering will be effective after a call to method flush().
	*
	* \see flush().
	*
    * \param sprite The sprite to draw to display.
	* \param x The position in pixel on X axis of the sprite to draw.
	* \param y The position in pixel on Y axis of the sprite to draw.
	*/
	void drawSprite(const Sprite& sprite, uint8_t x, uint8_t y);

    /**
     * \brief Draws a white pixel.
     * 
     * \remark the rendering will be effective after a call to method flush().
     * 
     * \see flush().
     * 
     * \param x The position in pixel on X axis of the pixel to draw.
     * \param y The position in pixel on Y axis of the pixel to draw.
     */
    void drawPixel(uint8_t x, uint8_t y);

	/**
	* \brief Print a text.
	*
	* Text will be rendered at current position with current font size.
	* After this method call, the current position of text will be updated to be the next empty coordinates.
	* If there is not enough place on screen, the current drawings (texts, lines, etc.) will scroll until the appropriate place is available.
	*
	* \attention If you need to reduce memory usage, you should not use class "String" and prefer the method with 'C style' parameters (char*, size_t).
	*
	* \remark the rendering will be effective after a call to method flush().
	*
	* \see print(const char *buffer, size_t bufferSize).
	* \see setTextPosition().
	* \see setFontSize().
	* \see flush().
	*
	* \param text The text to print.
    * \param x The position in pixel on X axis of the text to draw.
    * \param y The position in pixel on Y axis of the text to draw.
    * \param font The font to use to draw text.
	*/
	void print(String text, uint8_t x, uint8_t y, Font* font);

	/**
	* \brief Print a text.
	*
	* \see print(string text) for a more detailled description.
	* This method should be prefered to the one with (string) parameter for memory consumption reason.
	*
	* \remark the rendering will be effective after a call to method flush().
	*
	* \see flush().
	*
	* \param buffer[] The characters to print to screen.
	* \param bufferSize The characters to print to screen.
    * \param x The position in pixel on X axis of the text to draw.
    * \param y The position in pixel on Y axis of the text to draw.
    * \param font The font to use to draw text.
	*/
	void print(const char *buffer, size_t bufferSize, uint8_t x, uint8_t y, Font* font);

	/**
	* \brief Print a single character.
	*
	* \remark the rendering will be effective after a call to method flush().
	*
	* \see flush().
	*
	* \param characterCode The character to print to screen.
    * \param x The position in pixel on X axis of the text to draw.
    * \param y The position in pixel on Y axis of the text to draw.
    * \param font The font to use to draw text.
	*/
	void print(uint8_t characterCode, uint8_t x, uint8_t y, Font* font);
    
    /**
     * \brief flush the current drawings and print to screen.
     *
     * Sends buffer to screen to flush the preceding orders.
     */
    void flush();
    
    /**
     * \brief Clears the screen.
     *
     * Clear buffer to discard all preceding orders.
     * The clearing of screen will be effective after the next flush command issued.
     * 
     * \see flush().
     */
    void clear();

	/**
	* \brief Clears a part of the screen.
	*
	* Clear buffer to discard all preceding orders on a specific part of the screen.
	* The clearing of area will be effective after the next flush command issued.
	*
	* \see flush().
	*/
	void clearArea(uint8_t x, uint8_t y, uint8_t width, uint8_t height);

	/**
	* \brief Clears a pixel on screen.
	*
	* The clearing of pixel will be effective after the next flush command issued.
	*
	* \see flush().
	*/
	void clearPixel(uint8_t x, uint8_t y);

	/**
	* \brief Set scale level of next operations.
	*/
	void setScale(uint8_t scale);

	/**
	* \brief Get current scale level.
	*/
	uint8_t getScale();
    
  private:
	/**
	 * \brief The line where scroll gets its origin.
	 */
	uint8_t displayStartLine = 0;
	/**
	* \brief The level of scale (multiplication factor).
	*/
	uint8_t scale = 1;

	/**
	* \brief The buffer that stores the pixel of screen.
	*/
	static uint8_t buffer[];

	/**
	 * Constants for memory adressing mode.
	 */
    enum class memoryAddressingMode_t : uint8_t {
      horizontal = 0x00,
      vertical = 0x01,
      page = 0x02
    };

	/**
	* Constants for segment remap.
	*/
    enum class segmentReMap_t : uint8_t {
      start = 0x00,
      end = 0x01
    };

	/**
	* Constants for entire display on.
	*/
    enum class entireDisplayOn_t : uint8_t {
      follow = 0x00,
      ignore = 0x01
    };

	/**
	* Constants for normal or inverse display.
	*/
    enum class normalOrInverseDisplay_t : uint8_t {
      normal = 0x00,
      inverse = 0x01
    };

	/**
	* Constants for display on/off.
	*/
    enum class displayOnOff_t : uint8_t {
      on = 0xAF,
      off = 0xAE
    };

	/**
	* Constants for output scan direction.
	*/
    enum class comOutputScanDirection_t : uint8_t {
      from = 0xC0,
      to = 0xC8
    };

	/**
	* Constants for hardware configuration pin.
	*/
    enum class comPinsHardwareConfigurationPin_t : uint8_t {
      sequential = 0x02,
      alternative = 0x12
    };

	/**
	* Constants for hardware configuration remap.
	*/
    enum class comPinsHardwareConfigurationRemap_t : uint8_t {
      disable = 0x02,
      enable = 0x22
    };

	/**
	* Constants for charge pump setting.
	*/
    enum class chargePumpSetting_t : uint8_t {
      disable = 0x10,
      enable = 0x14
    };

	/**
	* Constants for scroll activation.
	*/
	enum class activateScroll_t : uint8_t {
		activate = 0x2F,
		deactivate = 0x2E
	};
    
    /** 
     * \brief Set Memory Addressing Mode.
     *  
     * \see datasheet 10.1.3 Set Memory Addressing Mode (20h)
     *
     * \param mode either page, horizontal or vertical (Please see datasheet for description).
     *  
     */
    void setMemoryAddressingMode(memoryAddressingMode_t mode);
    
    /**
     * \brief Set Column Address.
     * 
     * \see datasheet 10.1.4 Set Column Address (21h)
     * 
     * \param startAddress The column start address from 0 to 127.
     * \param endAddress The column end address from 0 to 127.
     */
    void setColumnAddress(uint8_t startAddress, uint8_t endAddress);
    
    /**
     * \brief Set Page Address.
     * 
     * \see datasheet 10.1.5 Set Page Address (22h).
     * 
     * \param startAddress The page start address.
     * \param endAddress The page end address.
     */
    void setPageAddress(uint8_t startAddress, uint8_t endAddress);
    
    /**
     * \brief Set Dispay Start Line.
     *  
     * \see datasheet 10.1.6 Set Display Start Line (40h~7Fh).
     * 
     * \param line The line to set to start from 0 to 63.
     */
    void setDisplayStartLine(uint8_t line);
    
    /**
     * \brief Set the contrast setting.
     *
     * \see datasheet 10.1.7 Set Contrast Control for BANK0 (81h).
     *
     * \param The contrast value.
     */
    void setContrastControl(uint8_t contrast);
    
    /**
     * \brief Set Segment Re-map.
     *
     * \see datasheet 10.1.8 Set Segment Re-map (A0h/A1h).
     *
     * \param address start (0 is right) or end (0 is left).
     */
    void setSegmentReMap(segmentReMap_t address);
    
    /**
     * \brief Entire Display ON.
     *
     * \see datasheet 10.1.9 Entire Display ON (A4h/A5h).
     *
     * \param followIgnore follow (display content in GDDRAM) or ignore (All pixels are ON).
     */
    void setEntireDisplayOn(entireDisplayOn_t followIgnore);
    
    /**
     * \brief Set Normal/Inverse Display.
     *
     * \see datasheet 10.1.10 Set Normal/Inverse Display (A6h/A7h).
     *
     * \param normalInverse normal or inverse.
     */
    void setNormalOrInverseDisplay(normalOrInverseDisplay_t normalInverse);
    
    /**
     * \brief Set Multiplex Ratio.
     *
     * \see datasheet 10.1.11 Set Multiplex Ratio (A8h).
     *
     * \param ratio from 16 to 63.
     */
    void setMultiplexRatio(uint8_t ratio);
    
    /**
     *  \brief Set Display ON or OFF.
     *  
     *  \see datasheet 10.1.12 Set Display ON/OFF (AEh/AFh)
     *  
     *  \param onOff on or off.
     */
    void setDisplayOnOff(displayOnOff_t onOff);
    
    /**
     * \brief Set COM Output Scan Direction.
     *
     * \see datasheet 10.1.14 Set COM Output Scan Direction (C0h/C8h).
     *
     * \param direction from com0 (0 is bottom) or to com0 (0 is top).
     */
    void setComOutputScanDirection(comOutputScanDirection_t direction);
    
    /**
     * \brief Set Display Offset.
     *
     * \see datasheet 10.1.15 Set Display Offset (D3h).
     *
     * \param offset from 0 to 63.
     */
    void setDisplayOffset(uint8_t offset);
    
    /**
     * \brief Set Display Clock Divide Ratio/ Oscillator Frequency.
     *
     * \see datasheet 10.1.16 Set Display Clock Divide Ratio/ Oscillator Frequency (D5h).
     *
     * \param ratio from 1 to 16.
     * \param frequency from 1 to 16.
     */
    void setDisplayClockDivideRatioOscillatorFrequency(uint8_t ratio, uint8_t frequency);
    
    /**
     * \brief Set Pre-charge Period.
     *
     * \see datasheet 10.1.17 Set Pre-charge Period (D9h).
     *
     * \param phase1 fromm 1 to 15.
     * \param phase2 fromm 1 to 15.
     */
    void setPreChargePeriod(uint8_t phase1, uint8_t phase2);
    
    /**
     * \brief Set COM Pins Hardware Configuration.
     *
     * \see datasheet 10.1.18 Set COM Pins Hardware Configuration (DAh).
     *
     * \param pinConfiguration sequential or alternative.
     * \param remapConfiguration enable or disable.
     */
    void setComPinsHardwareConfiguration(comPinsHardwareConfigurationPin_t pinConfiguration, comPinsHardwareConfigurationRemap_t remapConfiguration);
    
    /**
     * \brief Set COM Pins Hardware Configuration.
     *
     * \see datasheet 10.1.18 Set COM Pins Hardware Configuration (DAh).
     *
     * \param setting enable or disable charge pump.
     */
    void setChargePumpSetting(chargePumpSetting_t setting);

	/**
	* \brief Set the COM signal deselected voltage level.
	*
	* \see datasheet 10.1.19 Set VCOMH Deselect Level (DBh).
	*
	* \param level Please refer to datasheet for level to voltage mapping.
	*/
	void setVComHDeselectLevel(uint8_t level);

	/**
	* \brief Set scroll activation or deactivation.
	*
	* \see datasheet 10.2.3 Deactivate Scroll (2Eh).
	* \see datasheet 10.2.4 Activate Scroll (2Fh).
	*
	* \param activateDeactivate activate or deactivate scroll.
	*/
	void setActivateScroll(activateScroll_t activateDeactivate);
    
    /**
     * \brief Send command to screen.
     *
     * Send a command to SSD1306.
     *
     * \param command The command to send.
     */
    void sendCommand(uint8_t command);
  };


#endif //DEVDUINO_DISPLAY_H