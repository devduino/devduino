#ifndef DEVDUINO_TCS3472.H
#define DEVDUINO_TCS3472.H

#define TCS3472_DEVICE_ADDRESS        0x29

#define TCS3472_REGISTER_ADDRESS_DEVICE_ID                 0x12
#define TCS3472_REGISTER_ADDRESS_ENABLE                    0x00
#define TCS3472_REGISTER_ADDRESS_GAIN_CONTROL              0x0F
#define TCS3472_REGISTER_ADDRESS_INTEGRATION_TIME_CONTROL  0x01

#define TCS3472_REGISTER_VALUE_COMMAND_BIT      0b10000000
#define TCS3472_REGISTER_VALUE_POWER_ON         0b00000001
#define TCS3472_REGISTER_VALUE_RGBC_ENABLE      0b00000011

#define TCS3472_REGISTER_VALUE_INTEGRATION_TIME_2_4ms  0xFF
#define TCS3472_REGISTER_VALUE_INTEGRATION_TIME_24ms   0xF6
#define TCS3472_REGISTER_VALUE_INTEGRATION_TIME_101ms  0xD5 
#define TCS3472_REGISTER_VALUE_INTEGRATION_TIME_154ms  0xC0
#define TCS3472_REGISTER_VALUE_INTEGRATION_TIME_700ms  0x00 

#define TCS3472_REGISTER_VALUE_GAIN_1X        0b00000000 
#define TCS3472_REGISTER_VALUE_GAIN_4X        0b00000001
#define TCS3472_REGISTER_VALUE_GAIN_16X       0b00000010
#define TCS3472_REGISTER_VALUE_GAIN_60X       0b00000011

#define TCS3472_REGISTER_ADDRESS_CDATA        0x14
#define TCS3472_REGISTER_ADDRESS_CDATAH       0x15
#define TCS3472_REGISTER_ADDRESS_RDATA        0x16
#define TCS3472_REGISTER_ADDRESS_RDATAH       0x17
#define TCS3472_REGISTER_ADDRESS_GDATA        0x18
#define TCS3472_REGISTER_ADDRESS_GDATAH       0x19
#define TCS3472_REGISTER_ADDRESS_BDATA        0x1A
#define TCS3472_REGISTER_ADDRESS_BDATAH       0x1B

#define LED_PINOUT_WHITE    5
#define LED_PINOUT_BLUE     9    
#define LED_PINOUT_GREEN    10     
#define LED_PINOUT_RED      11   

#define OFFSET_RGB_LED_RED      0
#define OFFSET_RGB_LED_GREEN  121
#define OFFSET_RGB_LED_BLUE   142

#define IGNORING_COEFFICIENT   6


class DevDuino_TCS3472 
{
	 public: 
	 
		  DevDuino_TCS3472();
		  
			  unsigned int deviceID = 0;	  
			  
			  boolean ready();
			  
			  void setGain(unsigned int gain);
			  void setIntegrationTime(unsigned int integrationTime);
			  
			  unsigned int getCLEAR();
			  unsigned int getRED();
			  unsigned int getGREEN();
			  unsigned int getBLUE();
			  
			  void displayRGBC(unsigned int RED, unsigned int GREEN, unsigned int BLUE, unsigned int CLEAR, unsigned int integrationTime);
			  void displayChart(unsigned int RED, unsigned int GREEN, unsigned int BLUE, unsigned int CLEAR, unsigned int integrationTime);

	 private:
	 
			  unsigned int valueCLEAR=0;
			  unsigned int valueRED=0;
			  unsigned int valueGREEN=0;
			  unsigned int valueBLUE=0;
			  unsigned int LSB = 0;
			  unsigned int MSB = 0;	
			  
			  unsigned int maxResolution=1024;	  
};
#endif