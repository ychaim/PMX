#include <string>

#include "../../src/Common/Action.Driver/AButtonDriver.hpp"
#include "../../src/Common/Action.Driver/ALcdShieldDriver.hpp"
#include "../../src/Common/Action.Driver/ALedDriver.hpp"
#include "../../src/Common/Action.Driver/ASensorsDriver.hpp"
#include "../../src/Common/Action.Driver/AServoDriver.hpp"
#include "../../src/Common/Action.Driver/AServoUsingMotorDriver.hpp"
#include "../../src/Common/Action.Driver/ASoundDriver.hpp"
#include "../../src/Common/Action.Driver/ASwitchDriver.hpp"
#include "../../src/Common/Asserv.Driver/AAsservDriver.hpp"


AAsservDriver * AAsservDriver::create(std::string botid)
{
	return 0;
}

ALedDriver * ALedDriver::create(std::string, int nb)
{
	return 0;
}


AButtonDriver * AButtonDriver::create()
{
	return 0;
}

ALcdShieldDriver * ALcdShieldDriver::create(std::string botId)
{
	return 0;
}

ASensorsDriver * ASensorsDriver::create()
{
	return 0;
}


AServoDriver * AServoDriver::create()
{
	return 0;
}

AServoUsingMotorDriver * AServoUsingMotorDriver::create()
{
	return 0;
}

ASoundDriver * ASoundDriver::create()
{
	return 0;
}

ASwitchDriver * ASwitchDriver::create()
{
	return 0;
}
