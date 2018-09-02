#include "devduino_MAX30102.h"
#include <Wire.h>

bool DevDuino_MAX30102::write_reg(uint8_t uch_addr, uint8_t uch_data)
{
  Wire.beginTransmission(I2C_WRITE_ADDR);
  Wire.write(uch_addr);
  Wire.write(uch_data);
  Wire.endTransmission();
  return true;
}

bool DevDuino_MAX30102::read_reg(uint8_t uch_addr, uint8_t *puch_data)
{
  Wire.beginTransmission(I2C_WRITE_ADDR);
  Wire.write(uch_addr);
  Wire.endTransmission();
  Wire.beginTransmission(I2C_READ_ADDR);
  Wire.requestFrom(I2C_READ_ADDR,1);
  *puch_data=Wire.read();
  Wire.endTransmission();
  return true;
}

bool DevDuino_MAX30102::ready()
{
  Wire.begin();
  if(!write_reg(REG_MODE_CONFIG,0x40)) //Reset
    return false;
  delay(100);
  if(!write_reg(REG_INTR_ENABLE_1,0xc0)) // INTR setting
    return false;
  if(!write_reg(REG_INTR_ENABLE_2,0x00))
    return false;
  if(!write_reg(REG_FIFO_WR_PTR,0x00))  //FIFO_WR_PTR[4:0]
    return false;
  if(!write_reg(REG_OVF_COUNTER,0x00))  //OVF_COUNTER[4:0]
    return false;
  if(!write_reg(REG_FIFO_RD_PTR,0x00))  //FIFO_RD_PTR[4:0]
    return false;
  if(!write_reg(REG_FIFO_CONFIG,0x4f))  //sample avg = 4, fifo rollover=false, fifo almost full = 17
    return false;
  if(!write_reg(REG_MODE_CONFIG,0x03))  //0x02 for Red only, 0x03 for SpO2 mode 0x07 multimode LED
    return false;
  if(!write_reg(REG_SPO2_CONFIG,0x27))  // SPO2_ADC range = 4096nA, SPO2 sample rate (100 Hz), LED pulseWidth (411uS)
    return false;  
  if(!write_reg(REG_LED1_PA,0x24))//0x24  //Choose value for ~ 7mA for LED1
    return false;
  if(!write_reg(REG_LED2_PA,0x24))//0x24 // Choose value for ~ 7mA for LED2
    return false;
  if(!write_reg(REG_PILOT_PA,0x7f))   // Choose value for ~ 25mA for Pilot LED
    return false;
  delay(100);
  return true;  
}

bool DevDuino_MAX30102::read_fifo(uint32_t *pun_red_led, uint32_t *pun_ir_led)
{
  uint32_t un_temp;
  //uint8_t uch_temp;
  *pun_ir_led=0;
  *pun_red_led=0;
  //maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_temp);
  //maxim_max30102_read_reg(REG_INTR_STATUS_2, &uch_temp);
  Wire.beginTransmission(I2C_WRITE_ADDR);
  Wire.write(REG_FIFO_DATA);
  Wire.endTransmission();
  Wire.beginTransmission(I2C_READ_ADDR);
  Wire.requestFrom(I2C_READ_ADDR,6);
  un_temp=Wire.read();
  un_temp<<=16;
  *pun_red_led+=un_temp;
  un_temp=Wire.read();
  un_temp<<=8;
  *pun_red_led+=un_temp;
  un_temp=Wire.read();
  *pun_red_led+=un_temp;
  un_temp=Wire.read();
  un_temp<<=16;
  *pun_ir_led+=un_temp;
  un_temp=Wire.read();
  un_temp<<=8;
  *pun_ir_led+=un_temp;
  un_temp=Wire.read();
  *pun_ir_led+=un_temp;
  Wire.endTransmission();
  *pun_red_led&=0x03FFFF;  //Mask MSB [23:18]
  *pun_ir_led&=0x03FFFF;  //Mask MSB [23:18]
  return true;
}
/*=============================================================================
                             CONSTRUCTOR
=============================================================================*/
DevDuino_MAX30102::DevDuino_MAX30102(){}