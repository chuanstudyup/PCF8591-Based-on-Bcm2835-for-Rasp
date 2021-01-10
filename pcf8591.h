#ifndef PCF8591_H
#define PCF8591_H

#include <bcm2835.h>
#include <cstdio>
#include <cstdint>

/**
 * A class to control the 8-bits A/D(D/A) device PCF8591
 */
class PCF8591{
	public:
		PCF8591(uint8_t addr = 0x48);
		bool init();
		void setRefV(float refV);
		uint8_t readAD(uint8_t channel);
		float readVoltage(uint8_t channel);
		
	private:
		uint8_t _addr;
		float _refV;
		char sendBuf[3];
		uint8_t errCode;
};

#endif
