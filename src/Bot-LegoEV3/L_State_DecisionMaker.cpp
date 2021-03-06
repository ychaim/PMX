#include "L_State_DecisionMaker.hpp"

#include <unistd.h>

#include "../Common/Action/Sensors.hpp"
#include "../Common/Action/ServoObjectsSystem.hpp"
#include "../Common/Asserv/Asserv.hpp"
#include "../Common/IA/IAbyZone.hpp"
#include "../Common/Position.hpp"
#include "../Common/Robot.hpp"
#include "../Common/State/Data.hpp"
#include "../Log/Logger.hpp"
#include "LegoEV3ActionsExtended.hpp"
#include "LegoEV3AsservExtended.hpp"
#include "LegoEV3IAExtended.hpp"
#include "LegoEV3RobotExtended.hpp"

bool L_tour1()
{

	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();
	robot.logger().info() << "start L_tour1." << logs::end;
	TRAJ_STATE ts = TRAJ_OK;
	RobotPosition path, zone;

	robot.ia().iAbyZone().goToZone("tour1", &path, &zone);
	ts = robot.asserv().doMoveForwardTo(path.x, path.y);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();

	ts = robot.asserv().doMoveForwardAndRotateTo(zone.x, zone.y, zone.theta);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();

	robot.asserv().ignoreFrontCollision(true);
	robot.asserv().ignoreRearCollision(true);
	ts = robot.asserv().doMoveForwardTo(520, 1090);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();

	ts = robot.asserv().doMoveForwardTo(1200, 1080);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();

	ts = robot.asserv().doLineAbs(-150);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();

	robot.asserv().ignoreFrontCollision(false);
	robot.asserv().ignoreRearCollision(false);

	robot.logger().info() << "L_tour1 done." << logs::end;
	return true; //return true si ok sinon false si interruption
}

bool L_peche1()
{
	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();
	robot.logger().info() << "start L_peche1." << logs::end;
	TRAJ_STATE ts = TRAJ_OK;
	RobotPosition path, zone;

	robot.ia().iAbyZone().goToZone("peche1", &path, &zone);
	ts = robot.asserv().doMoveForwardTo(path.x, path.y);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();
	ts = robot.asserv().doMoveForwardAndRotateTo(zone.x, zone.y, zone.theta);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();

	//RECALAGE sur le devant
	ts = robot.asserv().doMoveForwardTo(500, 35);
	if (ts != TRAJ_OK)
		return false;
	//set pos
	robot.asserv().setPositionAndColor(robot.asserv().getRelativeX(robot.asserv().pos_getX_mm()),
			100,
			-90.0,
			(robot.getMyColor() == PMXGREEN));
	robot.svgPrintPosition();

	ts = robot.asserv().doLineAbs(-60);
	if (ts != TRAJ_OK)
		return false;
	robot.svgPrintPosition();

	for (int pp = 1; pp < 4; pp++)
	{
		//PECHE
		//rotation
		ts = robot.asserv().doRotateTo(0);
		if (ts != TRAJ_OK)
			return false;

		if (robot.sharedData->end90s())
			break;

		//on abaisse la canne
		if (robot.getMyColor() == PMXGREEN)
			robot.actions().servoObjects().centreDeploy(-65);
		if (robot.getMyColor() == PMXVIOLET)
			robot.actions().servoObjects().centreDeploy(85);

		if (robot.sharedData->end90s())
			break;

		ts = robot.asserv().doMoveForwardAndRotateTo(740, 85, 0);
		if (ts != TRAJ_OK)
			return false;
		robot.svgPrintPosition();

		if (robot.sharedData->end90s())
					break;

		//on remonte la canne à 45
		if (robot.getMyColor() == PMXGREEN)
			robot.actions().servoObjects().centreDeploy(-10);
		if (robot.getMyColor() == PMXVIOLET)
			robot.actions().servoObjects().centreDeploy(30);

		if (robot.sharedData->end90s())
			break;

		//on va sur le filet
		ts = robot.asserv().doMoveForwardAndRotateTo(950, 150, 0);
		if (ts != TRAJ_OK)
			return false;

		if (robot.sharedData->end90s())
			break;

		ts = robot.asserv().doMoveForwardAndRotateTo(1140, 35, -30);
		if (ts != TRAJ_OK)
			return false;

		if (robot.sharedData->end90s())
			break;

		//on abaisse la canne
		if (robot.getMyColor() == PMXGREEN)
			robot.actions().servoObjects().centreDeploy(-65);
		if (robot.getMyColor() == PMXVIOLET)
			robot.actions().servoObjects().centreDeploy(85);

		if (robot.sharedData->end90s())
			break;

		//on lache les poissons
		if (robot.getMyColor() == PMXGREEN)
			robot.actions().servoObjects().leftDeploy(-100);
		if (robot.getMyColor() == PMXVIOLET)
			robot.actions().servoObjects().rightDeploy(-100);

		if (robot.sharedData->end90s())
			break;

		//on délache les poissons
		if (robot.getMyColor() == PMXGREEN)
			robot.actions().servoObjects().leftDeploy(100);
		if (robot.getMyColor() == PMXVIOLET)
			robot.actions().servoObjects().rightDeploy(100);
		/*
		 //on lache les poissons
		 if (robot.getMyColor() == PMXGREEN)
		 robot.actions().servoObjects().leftDeploy(-100);
		 if (robot.getMyColor() == PMXVIOLET)
		 robot.actions().servoObjects().rightDeploy(-100);

		 //on délache les poissons
		 if (robot.getMyColor() == PMXGREEN)
		 robot.actions().servoObjects().leftDeploy(100);
		 if (robot.getMyColor() == PMXVIOLET)
		 robot.actions().servoObjects().rightDeploy(100);
		 */
		//on releve la canne
		if (robot.getMyColor() == PMXGREEN)
			robot.actions().servoObjects().centreDeploy(-10);
		if (robot.getMyColor() == PMXVIOLET)
			robot.actions().servoObjects().centreDeploy(30);

		if (robot.sharedData->end90s())
			break;

		//on recule
		ts = robot.asserv().doMoveBackwardAndRotateTo(950, 150, 0);
		if (ts != TRAJ_OK)
			return false;

		if (robot.sharedData->end90s())
			break;

		ts = robot.asserv().doMoveBackwardAndRotateTo(750, 120, 0);
		if (ts != TRAJ_OK)
			return false;

		//on abaisse la canne
		if (robot.getMyColor() == PMXGREEN)
			robot.actions().servoObjects().centreDeploy(-65);
		if (robot.getMyColor() == PMXVIOLET)
			robot.actions().servoObjects().centreDeploy(85);

		if (robot.sharedData->end90s())
			break;

		ts = robot.asserv().doMoveBackwardAndRotateTo(450, 85, 0);
		if (ts != TRAJ_OK)
			return false;

		robot.logger().info() << "L_peche1 done: nb=" << pp << logs::end;
	}

	robot.actions().servoObjects().releaseAll();
	return true; //return true si ok sinon false si interruption
}

bool L_action1()
{
	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();
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

bool L_action2()
{
	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();
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

bool L_action3()
{
	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();
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

void L_State_DecisionMaker::IASetupDemo()
{
	logger().debug() << "IASetup" << logs::end;

	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();

	robot.ia().iAbyZone().ia_createZone("depart", 0, 900, 200, 200, 300, 1000, 180);
	robot.ia().iAbyZone().ia_createZone("zone1", 500, 1000, 300, 200, 500, 1100, 0);
	robot.ia().iAbyZone().ia_createZone("zone2", 500, 1800, 200, 200, 600, 1800, 90);
	robot.ia().iAbyZone().ia_createZone("zone3", 500, 0, 300, 200, 400, 250, 0);

	robot.ia().iAbyZone().ia_setPath("depart", "zone1", 500, 1100);
	robot.ia().iAbyZone().ia_setPath("depart", "zone2", 600, 1500);
	robot.ia().iAbyZone().ia_setPath("depart", "zone3", 450, 500);
	robot.ia().iAbyZone().ia_setPath("zone1", "zone2", 600, 1500);
	robot.ia().iAbyZone().ia_setPath("zone1", "zone3", 450, 500);
	robot.ia().iAbyZone().ia_setPath("zone2", "zone3", 450, 500);

	robot.ia().iAbyZone().ia_addAction("action1", &L_action1);
	robot.ia().iAbyZone().ia_addAction("action2", &L_action2);
	robot.ia().iAbyZone().ia_addAction("action3", &L_action3);

}

void L_State_DecisionMaker::IASetupHomologation()
{
	logger().debug() << "IAHomologation" << logs::end;

	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();
	robot.ia().iAbyZone().ia_createZone("depart", 0, 900, 200, 200, 300, 1000, 180);
	robot.ia().iAbyZone().ia_createZone("tour1", 600, 1100, 20, 20, 400, 1100, 0);
	robot.ia().iAbyZone().ia_createZone("peche1", 500, 0, 400, 200, 500, 200, -90);

	robot.ia().iAbyZone().ia_setPath("depart", "tour1", 300, 1000);
	robot.ia().iAbyZone().ia_setPath("depart", "peche1", 400, 1100);
	robot.ia().iAbyZone().ia_setPath("tour1", "peche1", 1150, 550);

	robot.ia().iAbyZone().ia_addAction("tour1", &L_tour1);
	robot.ia().iAbyZone().ia_addAction("peche1", &L_peche1);
}

IAutomateState*
L_State_DecisionMaker::execute(Robot &, void * data)
{
	logger().info() << "L_State_DecisionMaker" << logs::end;
	LegoEV3RobotExtended &robot = LegoEV3RobotExtended::instance();
	Data* sharedData = (Data*) data;

	robot.sharedData = (Data*) data;

	//IASetupDemo();
	IASetupHomologation();

	robot.svgPrintPosition();

	sleep(5);

	robot.actions().sensors().startSensors();
	robot.ia().iAbyZone().ia_start(); //launch IA

	//wait the execution Wait90
	while (!sharedData->end90s()) //&& robot.chronometerRobot().getElapsedTimeInSec() < 35)
	{
		//			logger().info() << "sharedData->end90s=" << sharedData->end90s() << " time="
		//					<< robot.chronometerRobot().getElapsedTimeInSec() << utils::end;
		//			robot.base().stop();
		usleep(5000000);
	}

	//robot.stop();
	return NULL; //finish all state
}
