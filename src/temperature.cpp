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

#include "temperature.h"

//------------------------------------------------------------------------//
//---------------------------- Pre-processors ----------------------------//
//------------------------------------------------------------------------//
//Address of temperature sensor.
#define MCP9808_I2C_ADDRESS (uint8_t) 0x18

//Number of bytes per message to sensor.
#define MCP_9808_BYTES_PER_MESSAGE (uint8_t) 2

//Address of ambient temperature register.
#define MCP9808_T_A_REGISTER_ADDRESS (uint8_t) 0x05
//Address of configuration register.
#define MCP9808_CONFIG_REGISTER_ADDRESS (uint8_t) 0x01
//Address of shutdown register.
#define MCP9808_CONFIG_REGISTER_SHUTDOWN (uint8_t) 0x01

	//------------------------------------------------------------------------//
	//---------------------------- Public methods ----------------------------//
	//------------------------------------------------------------------------//

	void Temperature::begin() {
	}
    
	float Temperature::read() {
		//Request ambient temperature register.
		Wire.beginTransmission(MCP9808_I2C_ADDRESS);
		Wire.write(MCP9808_T_A_REGISTER_ADDRESS);
		Wire.endTransmission();

		//Read upper byte of temperature.
		Wire.requestFrom(MCP9808_I2C_ADDRESS, MCP_9808_BYTES_PER_MESSAGE);
		uint8_t upperByte = Wire.read();
		//Clear flag bits
		upperByte &= 0x1F;

		//Read lower byte of temperature.
		uint8_t lowerByte = Wire.read();

		float temperature;

		//If temperature below 0°C.
		if ((upperByte & 0x10) == 0x10) {
			//Clear sign.
			upperByte &= 0x0F;

			temperature = (256 - (upperByte << 8 | lowerByte)) / 16.0f;
		}
		else {
			temperature = (upperByte << 8 | lowerByte) / 16.0f;
		}

		return temperature;
	}

	void Temperature::shutdown() {
		//Request configuration register.
		Wire.beginTransmission(MCP9808_I2C_ADDRESS);
		Wire.write(MCP9808_CONFIG_REGISTER_ADDRESS);
		Wire.endTransmission();

		//Read upper and lower bytes of configuration.
		Wire.requestFrom(MCP9808_I2C_ADDRESS, MCP_9808_BYTES_PER_MESSAGE);
		uint8_t configRegisterUpperByte = Wire.read();
		uint8_t configRegisterLowerByte  = Wire.read();

		//Set shut-down bit to upper byte.
		configRegisterUpperByte |= MCP9808_CONFIG_REGISTER_SHUTDOWN;

		//Write back configuration
		Wire.beginTransmission(MCP9808_I2C_ADDRESS);
		Wire.write(MCP9808_CONFIG_REGISTER_ADDRESS);
		Wire.write(configRegisterUpperByte);
		Wire.write(configRegisterLowerByte);
		Wire.endTransmission();
	}

	void Temperature::wakeup() {
		//Request configuration register.
		Wire.beginTransmission(MCP9808_I2C_ADDRESS);
		Wire.write(MCP9808_CONFIG_REGISTER_ADDRESS);
		Wire.endTransmission();

		//Read upper and lower bytes of configuration.
		Wire.requestFrom(MCP9808_I2C_ADDRESS, MCP_9808_BYTES_PER_MESSAGE);
		uint8_t configRegisterUpperByte = Wire.read();
		uint8_t configRegisterLowerByte = Wire.read();

		//Set wake-up bit to upper byte.
		configRegisterUpperByte &= ~MCP9808_CONFIG_REGISTER_SHUTDOWN;

		//Write back configuration
		Wire.beginTransmission(MCP9808_I2C_ADDRESS);
		Wire.write(MCP9808_CONFIG_REGISTER_ADDRESS);
		Wire.write(configRegisterUpperByte);
		Wire.write(configRegisterLowerByte);
		Wire.endTransmission();
	}

	//------------------------------------------------------------------------//
	//--------------------------- Private methods ----------------------------//
	//------------------------------------------------------------------------//

