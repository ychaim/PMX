#include "FunnyAction.hpp"

#include "../Action.Driver/AServoUsingMotorDriver.hpp"

using namespace std;

FunnyAction::FunnyAction(Actions & actions) :
		AActionsElement(actions)

{
	servomotordriver = AServoUsingMotorDriver::create();
}

FunnyAction::~FunnyAction()
{
}


void FunnyAction::reset()
{
	servomotordriver->resetEncoder(0);
}

void FunnyAction::activate(int pos)
{
	servomotordriver->setMotorPosition(60, pos, 0);
}

void FunnyAction::release()
{
	servomotordriver->stopMotor();
}
