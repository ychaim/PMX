#ifndef OPOS6UL_ASSERVEXTENDED_HPP_
#define OPOS6UL_ASSERVEXTENDED_HPP_

#include <string>

#include "../Common/Asserv/Asserv.hpp"

class OPOS6UL_AsservExtended: public Asserv
{
private:

public:
	OPOS6UL_AsservExtended(std::string botId, Robot * robot)
			: Asserv(botId, robot) //on appelle le constructeur pere
	{

	}

	~OPOS6UL_AsservExtended()
	{
	}

	void startMotionTimerAndOdo();

};

#endif
