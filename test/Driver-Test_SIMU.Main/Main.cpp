#include <iostream>

#include "../Suite/UnitTestSuite.hpp"
#include "AsservDriverTest.hpp"
#include "LedDriverTest.hpp"

using namespace std;

int main()
{
	cout << "!!!Driver-SIMU-Test!!!" << endl;

	UnitTestSuite suite;

	suite.addTest(new test::LedDriverTest());
	suite.addTest(new test::AsservDriverTest());

	suite.run();

	return 0;
}
