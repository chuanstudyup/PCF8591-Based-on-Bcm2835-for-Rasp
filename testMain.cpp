#include "pcf8591.h"
#include <iostream>
using namespace std;

int main()
{
	bcm2835_init();
	PCF8591 pcf8591;
	if(pcf8591.init())
		cout << "PCF8591 init successfully" << endl;
	else
	{
		cout << "PCF8591 init failed" << endl;
		exit(-1);
	}
	int i = 10;
	while(i)
	{
		int byte = pcf8591.readAD(3);
		cout << byte << endl;
		bcm2835_delay(100);
	}
	return 0;
}

// g++ testMain.cpp pcf8591.cpp -lbcm2835 -o testMain
