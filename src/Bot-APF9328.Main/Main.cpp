#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "../Bot-APF9328/APF9328LedBarTest.hpp"
#include "../Bot-APF9328/APF9328RobotExtended.hpp"
#include "../Common/ConsoleKeyInput.hpp"
#include "../Common/ConsoleManager.hpp"
#include "../Common/Robot.hpp"
#include "../Log/Logger.hpp"

using namespace std;

int main(int argc, char** argv)
{
	cout << "!!! Hello BigPMX !!!" << endl;

	//Specific Robot BigPMX
	APF9328RobotExtended &robot = APF9328RobotExtended::instance();

	//add specific tests for this robot
	robot.getConsoleManager().add(new APF9328LedBarTest());

	robot.parseConsoleArgs(argc, argv);

	//start the Robot (functional tests or match)
	robot.begin(argc, argv);

	sleep(1); //TODO wait and verify end of logger ?
	//cout << "End BigPMX." << endl;
	return 0;
}
