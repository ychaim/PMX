#include "LegoEV3AsservInsaTest.hpp"

#include <string>

#include "../Common/Asserv/Asserv.hpp"
#include "../Common/Asserv/EncoderControl.hpp"
#include "../Common/Asserv/MovingBase.hpp"
#include "../Common/Utils/Chronometer.hpp"
#include "../Log/Logger.hpp"
#include "LegoEV3RobotExtended.hpp"

using namespace std;

//set max ACC VMAX DEC
void LegoEV3AsservInsaTest::configureConsoleArgs(int argc, char** argv) //surcharge
{
	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();

	robot.getArgs().addArgument("Acc", "Acceleration(float)");
	robot.getArgs().addArgument("Vmax", "MaxSpeed(float)");
	robot.getArgs().addArgument("Dec", "Deceleration(float)");

	robot.getArgs().addArgument("mm", "Distance (mm) for test", "0.0");

	robot.getArgs().addArgument("Dp", "value(float) of p for Delta", "0.0");
	robot.getArgs().addArgument("Dd", "value(float) of d for Delta", "0.0");

	robot.getArgs().addArgument("angle", "Angle (degrees) for test", "0.0");

	robot.getArgs().addArgument("Ap", "value(float) of p for Alpha", "0.0");
	robot.getArgs().addArgument("Ad", "value(float) of d for Alpha", "0.0");

	//reparse arguments
	robot.parseConsoleArgs(argc, argv);
}

void LegoEV3AsservInsaTest::run(int argc, char** argv)
{
	logger().info() << "Executing - " << this->desc() << logs::end;
	configureConsoleArgs(argc, argv);

	utils::Chronometer chrono;
	long left;
	long right;

	//PID values
	float Dp = 0.0;
	float Dd = 0.0;
	float Ap = 0.0;
	float Ad = 0.0;
	int distmm = 0;
	float angle = 0.0;

	float Acc = 0.0;
	float Vmax = 0.0;
	float Dec = 0.0;

	logger().debug()  << logs::end;logger().debug()  << logs::end;logger().debug()  << logs::end;
	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();
	Arguments args = robot.getArgs();
	if (args["mm"] != "0")
	{
		distmm = atoi(args["mm"].c_str());
		logger().debug() << "Arg mm set " << args["mm"] << ", distmm = " << distmm << logs::end;
	}
	if (args["Acc"] != "0")
	{
		Acc = atof(args["Acc"].c_str());
		logger().debug() << "Arg Acc set " << args["Acc"] << ", Acc = " << Acc << logs::end;
	}
	if (args["Vmax"] != "0")
	{
		Vmax = atof(args["Vmax"].c_str());
		logger().debug() << "Arg Vmax set " << args["Vmax"] << ", Vmax = " << Vmax << logs::end;
	}
	if (args["Dec"] != "0")
	{
		Dec = atof(args["Dec"].c_str());
		logger().debug() << "Arg Dec set " << args["Dec"] << ", Dec = " << Dec << logs::end;
	}

	if (args["Dp"] != "0")
	{
		Dp = atof(args["Dp"].c_str());
		logger().debug() << "Arg Dp set " << args["Dp"] << ", Dp = " << Dp << logs::end;
	}
	if (args["Dd"] != "0")
	{
		Dd = atof(args["Dd"].c_str());
		logger().debug() << "Arg Dd set " << args["Dd"] << ", Dd = " << Dd << logs::end;
	}
	if (args["angle"] != "0")
	{
		angle = atof(args["angle"].c_str());
		logger().debug() << "Arg angle set " << args["angle"] << ", angle = " << angle << logs::end;
	}
	if (args["Ap"] != "0")
	{
		Ap = atof(args["Ap"].c_str());
		logger().debug() << "Arg Ap set " << args["Ap"] << ", Ap = " << Ap << logs::end;
	}

	if (args["Ad"] != "0")
	{
		Ad = atof(args["Ad"].c_str());
		logger().debug() << "Arg Ad set " << args["Ad"] << ", Ad = " << Ad << logs::end;
	}

	robot.asserv().startMotionTimerAndOdo();
	//surcharge des valeurs
	robot.asserv().configureAlphaPID(Ap, 0.0, Ad);
	robot.asserv().configureDeltaPID(Dp, 0.0, Dd);
	robot.asserv().setPositionAndColor(0.0, 300.0, 0.0, (robot.getMyColor()==PMXGREEN));
	robot.asserv().setVmax(Vmax);
	robot.asserv().setAccel(Acc);
	robot.asserv().setDecel(Dec);

	robot.svg().writePosition(robot.asserv().pos_getX_mm(),
			robot.asserv().pos_getY_mm(),
			robot.asserv().pos_getTheta(),
			LEGOEV3_SVG_POS_ROBOT);

	chrono.start();
	if (distmm != 0)
		robot.asserv().doLineAbs(distmm);

	if (angle != 0)
		robot.asserv().doRotateAbs(angle);

	left = robot.asserv().base()->encoders().getLeftEncoder();
	right = robot.asserv().base()->encoders().getRightEncoder();
	logger().info() << "time= "
			<< chrono.getElapsedTimeInMilliSec()
			<< "ms ; left= "
			<< left
			<< " ; right= "
			<< right
			<< " x="
			<< robot.asserv().pos_getX_mm()
			<< " y="
			<< robot.asserv().pos_getY_mm()
			<< " a="
			<< robot.asserv().pos_getThetaInDegree()
			<< logs::end;

	robot.svg().writePosition(robot.asserv().pos_getX_mm(),
			robot.asserv().pos_getY_mm(),
			robot.asserv().pos_getTheta(),
			LEGOEV3_SVG_POS_ROBOT);
	robot.stop();
	logger().info() << "Happy End." << logs::end;
}

