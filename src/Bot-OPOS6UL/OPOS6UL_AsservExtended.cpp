#include "OPOS6UL_AsservExtended.hpp"

OPOS6UL_AsservExtended::OPOS6UL_AsservExtended(std::string botId, Robot * robot) :
		Asserv(botId, robot) //on appelle le constructeur pere
{
	useInternalAsserv_ = false; //configuration par defaut
}
