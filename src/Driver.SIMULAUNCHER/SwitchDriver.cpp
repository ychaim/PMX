//drivers...SIMU

#include "SwitchDriver.hpp"

using namespace std;

ASwitchDriver * ASwitchDriver::create()
{
	static SwitchDriver *instance = new SwitchDriver();
	return instance;
}

SwitchDriver::SwitchDriver()
{

}

SwitchDriver::~SwitchDriver()
{
}

int SwitchDriver::pressed()
{

 return 0;
}

int SwitchDriver::pressed(unsigned char pin)
{
	return 0;
}
