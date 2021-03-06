#ifndef SIMULAUNCHER_SENSORSDRIVER_HPP_
#define SIMULAUNCHER_SENSORSDRIVER_HPP_

#include "../Common/Action.Driver/ASensorsDriver.hpp"
#include "../Log/LoggerFactory.hpp"


using namespace std;


class SensorsDriver: public ASensorsDriver
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref SensorsDriver(SIMULAUNCHER).
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("SensorsDriver.SIMULAUNCHER");
		return instance;
	}

public:

	/*!
	 * \brief Constructor.
	 */
	SensorsDriver();

	/*!
	 * \brief Destructor.
	 */
	virtual ~SensorsDriver();

	virtual bool front();
	virtual bool rear();

};

#endif
