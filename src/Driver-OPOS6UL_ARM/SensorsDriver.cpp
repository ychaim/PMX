//drivers...OPO

#include "SensorsDriver.hpp"

#include <cmath>
#include <string>

#include "../Log/Logger.hpp"

using namespace std;

ASensorsDriver * ASensorsDriver::create(std::string)
{
	return new SensorsDriver();
}

SensorsDriver::SensorsDriver() :
		i2c_gp2y0e02b_(1), connected_gp2y0e02b_(true), shift_(0)
{

	i2c_gp2y0e02b_.setSlaveAddr(ADDRESS_gp2y0e02b);

	//read shift
	shift_ = read_i2c(SHIFT_gp2y0e02b);
	logger().error() << "shift = " << shift_ << logs::end;
	if (shift_ < 0)
	{
		logger().error() << "setup() : GpioBoard NOT CONNECTED !" << logs::end;
		connected_gp2y0e02b_ = false;
	}
	else
		connected_gp2y0e02b_ = true;

}

SensorsDriver::~SensorsDriver()
{
}

bool SensorsDriver::front()
{
	if (!connected_gp2y0e02b_) return -1;

	//read distance
	int d = read_i2c_2bytes_optimised(DISTANCE_REG_gp2y0e02b);
	if (d < 0)
	{
		logger().error() << "ERROR : front() : read_i2c_2bytes neg!" << logs::end;
	}
	else
	{

		logger().error() << "init dist=" << d << logs::end;
	}

	return false;
}

bool SensorsDriver::rear()
{
	if (!connected_gp2y0e02b_) return -1;
	return false;
}

/*
 long SensorsDriver::write_i2c(unsigned char command, unsigned char value)
 {
 return i2c_gp2y0e02b_.writeRegByte(command, value);
 }*/

int SensorsDriver::read_i2c(unsigned char command)
{
	return i2c_gp2y0e02b_.readRegByte(command);
}

int SensorsDriver::read_i2c_2bytes_optimised(unsigned char command)
{
	unsigned char data[2];
	long r = i2c_gp2y0e02b_.readReg(command, data, 2);
	if (r < 0) logger().error() << "ERROR read_i2c_2bytes_optimised() " << logs::end;
	unsigned char high = data[0];
	unsigned char low = data[1];

	logger().error() << "high: " << (int) high << " \tlow: " << (int) low << logs::end;
	int distance = ((high * 16 + low) / 16) * 10 / (int) std::pow(2, shift_); // Calculate the range in CM

	return distance;
}

int SensorsDriver::read_i2c_2bytes(unsigned char command)
{
	if (!connected_gp2y0e02b_) return -1;
	unsigned char low = 0;
	unsigned char high = 0;

	high = read_i2c(command);
	low = read_i2c(command + 1);

	logger().error() << "low: " << (int) low << " \thigh: " << (int) high << logs::end;
	int distance = ((high * 16 + low) / 16) / (int) std::pow(2, shift_); // Calculate the range in CM
	logger().error() << "dist: " << distance << logs::end;
	return distance;
}

