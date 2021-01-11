#include "pcf8591.h"

PCF8591::PCF8591(uint8_t addr)
{
	_addr = addr;
	_refV = 5.0f;
}

/**
 * Before MS5837::init(), please bcm2835_init() in main.c!
 **/
bool PCF8591::init()
{
	printf("PCF8591 Init...\n");
	if(!bcm2835_i2c_begin())
	{
		printf("bcm2835_i2c_begin failed at %s%d\n",__FILE__,__LINE__);
		return false;
	}
	bcm2835_i2c_setSlaveAddress(_addr);
	bcm2835_i2c_set_baudrate(100000);
	return true;
}

void PCF8591::setRefV(float refV)
{
	_refV = refV;
}

/**
 * brief   Read the channel A/D
 * param   channel 0-3
 * return  0-255
 */
uint8_t PCF8591::readAD(uint8_t channel)
{
	bcm2835_i2c_setSlaveAddress(_addr);
	sendBuf[0] = 0x00 | channel;
	if((errCode = bcm2835_i2c_write(sendBuf,1)))
		printf("bcm2835_i2c_write failed at %s%d, errCode = 0x%x\n",__FILE__,__LINE__, errCode);
	char byte;
	if((errCode = bcm2835_i2c_read(&byte,1)))
		printf("bcm2835_i2c_read failed at %s%d, errCode = 0x%x\n",__FILE__,__LINE__, errCode);
	return byte;
}

/**
 * brief read the channel voltage
 * param channel 0-3
 * return 0-_refV
 */
float PCF8591::readVoltage(uint8_t channel)
{
	return readAD(channel)/255.0f*_refV;
}
