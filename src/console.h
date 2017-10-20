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
	 *
	 * \param oled The oled display to bind console to.
	 * \param nbAreasX The number of areas to define on X axis.
	 * \param nbAreasY The number of areas to define on Y axis.
	*/
	Console(const Oled& oled, const Font* font = nullptr, bool autoFlush = true);



	const Oled& getOled();


	/**
	* \brief Set the position of the next character to write.
	*
	* After this method call, the next character to write will be placed at this exact position.
	* It is important to notice that the position of a text is dynamic. The next character to write will be placed at this position
	* but the position will be incremented each time a character is written. Therefore, if few characters are displayed between
	* calls to this method, they will not overlap.
	*
	* The automatic incrementation of position of the text to write is done on both X and Y axes.
	*
	* Before calling this method, the X and Y positions defaults to 0.
	*
	* \see write().
	*
	* \param x The position in pixel on X axis of the pixel to draw.
	* \param y The position in pixel on Y axis of the pixel to draw.
	*/
	Console& setTextPosition(uint8_t x, uint8_t y);

	/**
	* \brief Set the font to use to display next characters.
	*
	* \param font The reference of the font to use for next writes.
	*/
	Console& setFont(const Font* font);

	/**
	* \brief Defines the size of the font used for next texts rendering.
	*
	* On this type of screen, the size usually used is from 1 to 3.
	* Before calling this method, the size of font defaults to 1.
	*
	* \param size The size of the font.
	*/
	Console& setFontSize(uint8_t size);

	/**
	* \brief Skip a line.
	*
	* The position of the new line is calculated from the current font size.
	*
	* \remark the rendering will be effective after a call to method display().
	*
	* \see setFontSize().
	* \see display().
	*/
	Console& newLine();

	/**
	* \brief Write a text.
	*
	* Text will be rendered at current position with current font size.
	* After this method call, the current position of text will be updated to be the next empty coordinates.
	* If there is not enough place on screen, the current drawings (texts, lines, etc.) will scroll until the appropriate place is available.
	*
	* \attention If you need to reduce memory usage, you should not use class "String" and prefer the method with 'C style' parameters (char*, size_t).
	*
	* \remark the rendering will be effective after a call to method display().
	*
	* \see write(const char *buffer, size_t buffer_size).
	* \see setTextPosition().
	* \see setFontSize().
	* \see display().
	*
	* \param text The text to write.
	*/
	Console& write(String text);

	Console& writeln(const char* value, size_t buffer_size);
	Console& writeln(const String& value);

	/**
	* \brief Write a text.
	*
	* \see write(string text) for a more detailled description.
	* This method should be prefered to the one with (string) parameter for memory consumption reason.
	*
	* \remark the rendering will be effective after a call to method display().
	*
	* \see display().
	*
	* \param buffer[in] The characters to write to screen.
	*/
	Console& write(const char *buffer, size_t buffer_size);







	/**
	* \brief Flush the console to display.
	*
	* \remark Console needs to be flushed if "write" methods are used.
	*/
	Console& flush();

	Console& enableAutoFlush(bool autoFlush);

  private:
	  //The oled to display console output.
	  const Oled& oled;

	  /**
	  * \brief The x position in  screen coordinates of next character to display.
	  */
	  uint8_t textX;
	  /**
	  * \brief The y position in  screen coordinates of next character to display.
	  */
	  int8_t textY;
	  /**
	  * \brief A reference to the font to use to render characters.
	  */
	  const Font* font;
	  /**
	  * \brief The size of text to display.
	  *
	  * 1 means normal size, other values multiply the size of text.
	  */
	  uint8_t fontSize = 1;

	  bool autoFlush;

	  /**
	  * \brief Write a character.
	  *
	  * This method draws a single character.
	  * The kerning is calculated from previous character code.
	  *
	  * \remark the rendering will be effective after a call to method display().
	  *
	  * \see write(string text) for a more detailled description.
	  * \see display().
	  *
	  * \param characterCode The code of the character to write to screen.
	  * \param previousCharacterCode The code of the previous character to writen to screen or 0 (default) if none.
	  */
	  void write(uint8_t characterCode, uint8_t previousCharacterCode = 0);

	  /**
	  * \brief Increment text position by width of one character.
	  *
	  * Text position is moved to next line if there is not enough space left on the line to display a supplementary character.
	  *
	  * \param pixels The number of pixels to increment position.
	  */
	  void incrementTextPosition(uint8_t pixels);

	  /**
	  * \brief Skip a line if necessary.
	  *
	  * A new line is created only if the text position + the pixels given as parameter exceed the width of screen.
	  * The position of the new line is calculated from the current font size.
	  *
	  * \param pixels The number of pixels used to compute if a new line must be created.
	  *
	  * \remark the rendering will be effective after a call to method display().
	  *
	  * \see setFontSize().
	  * \see display().
	  */
	  Console& newLine(uint8_t pixels);
  };
} // namespace devduino

#endif //DEVDUINO_CONSOLE_H