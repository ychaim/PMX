#ifndef LegoEV3_ASSERVEXTENDED_HPP_
#define LegoEV3_ASSERVEXTENDED_HPP_

#include <string>

#include "../Asserv.Insa/AsservInsa.hpp"
#include "../Common/Asserv/Asserv.hpp"
#include "../Log/LoggerFactory.hpp"

class LegoEV3AsservExtended: public Asserv
{
private:
	/*!
	 * \brief Return \ref Logger linked to \ref LegoEV3AsservExtended.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("LegoEV3AsservExtended");
		return instance;
	}

	/*!
	 * \brief asservissement utilisé
	 */
	AsservInsa * pAsservInsa_;

	//dernière puissance pour chaque motor.
	int last_sens_left_; //1:AV 0:AR
	int last_sens_right_; //1:AV 0:AR
	float motorwheel_patch_m;
	float motorwheel_patch_rad;

public:
	LegoEV3AsservExtended(std::string botId, Robot * robot);

	~LegoEV3AsservExtended()
	{
	}

	AsservInsa * insa();

	void startMotionTimerAndOdo();
	void stopMotionTimerAndOdo();
	void freeMotion();
	void assistedHandling();

	TRAJ_STATE doLineAbs(float distance_mm); // if distance <0, move backward
	TRAJ_STATE doRotateAbs(float degrees);
	TRAJ_STATE doRotateLeft(float degrees);
	TRAJ_STATE doRotateRight(float degrees);

	//relative motion (depends on current position of the robot)
	TRAJ_STATE doRotateTo(float thetaInDegree);
	TRAJ_STATE doMoveForwardTo(float xMM, float yMM);
	TRAJ_STATE doMoveForwardAndRotateTo(float xMM, float yMM, float thetaInDegree);
	TRAJ_STATE doMoveBackwardTo(float xMM, float yMM);
	TRAJ_STATE doMoveBackwardAndRotateTo(float xMM, float yMM, float thetaInDegree);
	TRAJ_STATE doMoveArcRotate(int degrees, float radiusMM);

	void findPidAD(float degrees, int mm, int sec);
	void findPidLR(float posl, int posr, int sec);

	void configureAlphaPID(float Ap, float Ai, float Ad);
	void configureDeltaPID(float Dp, float Di, float Dd);

	/*!
	 * Attention startMotionTimerAndOdo() est necessaire auparavant pour configurer vTops et donc la position du robot
	 */
	void setPositionAndColor(float x_mm, float y_mm, float thetaInDegrees, bool matchColor);

	void setVmax(float vmax);
	void setAccel(float acc);
	void setDecel(float dec);

	void setFrontCollision();
	void setRearCollision();

	float pos_getX_mm();
	float pos_getY_mm();
	// angle in radian
	float pos_getTheta();
	// angle in degrees
	float pos_getThetaInDegree();

};

#endif

