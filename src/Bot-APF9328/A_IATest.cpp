/*!
 * \file
 * \brief Implémentation de la classe A_IATest.
 */

#include "A_IATest.hpp"

#include <string>

#include "../Common/Asserv.Insa/AsservInsa.hpp"
#include "../Common/IA/IAbyZone.hpp"
#include "../Common/Position.hpp"
#include "../Common/Robot.hpp"
#include "../Common/Utils/Chronometer.hpp"
#include "../Log/Logger.hpp"
#include "APF9328AsservExtended.hpp"
#include "APF9328IAExtended.hpp"
#include "APF9328RobotExtended.hpp"


using namespace std;

bool ATEST_action1()
{
	APF9328RobotExtended &robot = APF9328RobotExtended::instance();
	robot.logger().info() << "start action1." << logs::end;
	TRAJ_STATE ts = TRAJ_OK;
	RobotPosition path, zone;

	robot.ia().iAbyZone().goToZone("zone1", &path, &zone);
	ts = robot.asserv().doMoveForwardTo(path.x, path.y);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();
	ts = robot.asserv().doMoveForwardAndRotateTo(zone.x, zone.y, zone.theta);
	if (ts != TRAJ_OK)
		return false;

	robot.svgPrintPosition();

	robot.logger().info() << "action1 done." << logs::end;
	return true; //return true si ok sinon false si interruption
}

bool ATEST_action2()
{
	APF9328RobotExtended &robot = APF9328RobotExtended::instance();
	robot.logger().info() << "start action2." << logs::end;

	TRAJ_STATE ts = TRAJ_OK;
	RobotPosition path, zone;

	robot.ia().iAbyZone().goToZone("zone2", &path, &zone);
	ts = robot.asserv().doMoveForwardTo(path.x, path.y);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();
	ts = robot.asserv().doMoveForwardAndRotateTo(zone.x, zone.y, zone.theta);
	if (ts != TRAJ_OK)
		return false;

	robot.svgPrintPosition();

	robot.logger().info() << "action2 done." << logs::end;
	return true;
}

bool ATEST_action3()
{
	APF9328RobotExtended &robot = APF9328RobotExtended::instance();
	robot.logger().info() << "start action3." << logs::end;

	TRAJ_STATE ts = TRAJ_OK;
	RobotPosition path, zone;

	robot.ia().iAbyZone().goToZone("zone3", &path, &zone);
	ts = robot.asserv().doMoveForwardTo(path.x, path.y);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();
	ts = robot.asserv().doMoveForwardAndRotateTo(zone.x, zone.y, zone.theta);
	if (ts != TRAJ_OK)
		return false;

	robot.svgPrintPosition();

	robot.logger().info() << "action3 done." << logs::end;
	return true;
}

void A_IATest::run(int argc, char** argv)
{
	logger().info() << "Executing - " << this->desc() << logs::end;

	APF9328RobotExtended &robot = APF9328RobotExtended::instance();

	robot.asserv().startMotionTimerAndOdo();
	robot.asserv().setPositionAndColor(150, 1050, 0.0, (robot.getMyColor() == PMXGREEN));
	robot.svgPrintPosition();
	robot.chrono().start();
	IASetup();
	robot.ia().iAbyZone().ia_start(); //launch IA


	robot.stop();

	logger().info() << "Happy End - "
			<< robot.chrono().getElapsedTimeInSec()
			<< " sec"
			<< logs::end;
}

void A_IATest::IASetup()
{
	logger().debug() << "IASetup" << logs::end;

	APF9328RobotExtended &robot = APF9328RobotExtended::instance();

	robot.ia().iAbyZone().ia_createZone("depart", 0, 900, 300, 300, 400, 1050, 180);
	robot.ia().iAbyZone().ia_createZone("zone1", 500, 1000, 300, 200, 500, 1100, 0);
	robot.ia().iAbyZone().ia_createZone("zone2", 500, 1800, 200, 200, 600, 1800, 90);
	robot.ia().iAbyZone().ia_createZone("zone3", 500, 0, 300, 200, 400, 250, 0);

	robot.ia().iAbyZone().ia_setPath("depart", "zone1", 500, 1100);
	robot.ia().iAbyZone().ia_setPath("depart", "zone2", 600, 1500);
	robot.ia().iAbyZone().ia_setPath("depart", "zone3", 450, 500);
	robot.ia().iAbyZone().ia_setPath("zone1", "zone2", 600, 1500);
	robot.ia().iAbyZone().ia_setPath("zone1", "zone3", 450, 500);
	robot.ia().iAbyZone().ia_setPath("zone2", "zone3", 450, 500);

	robot.ia().iAbyZone().ia_addAction("action1", &ATEST_action1);
	robot.ia().iAbyZone().ia_addAction("action2", &ATEST_action2);
	robot.ia().iAbyZone().ia_addAction("action3", &ATEST_action3);

}