
/* SUV.cpp */

#include "SUV.hpp"
#include <iostream>

using namespace std;

SUV::SUV() : PersonalVehicle(), FourWheelDriveVehicle() { }

SUV::SUV(const SUV& v) : PersonalVehicle(v), FourWheelDriveVehicle(v) { }

SUV::~SUV() { }

void SUV::drive()
{
	cout << "We are driving an SUV." << endl;
}

void SUV::vDrive()
{
	cout << "We are virtually driving an SUV." << endl;
}

Vehicle* SUV::clone()
{
	Vehicle* p = new SUV(*this);
	p->id_(_id);
	return p;
}
