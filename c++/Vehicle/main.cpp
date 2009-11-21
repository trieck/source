



/* main.cpp */

#include <iostream>
#include "Van.hpp"
#include "SUV.hpp"

using namespace std;

main()
{

	// Create a van object with default construct, and store a pointer to it
	Van * van = new Van();
	// Create an SUV object with default construct, and store a pointer to it
	SUV * suv = new SUV();
	// Create an SUV object using copy construct, and store a pointer to it
	SUV * suv2 = new SUV(*suv);
	// How many Vehicle objects so far? 3.
	cout << Vehicle::count() << endl;
	// Display some of the attributes of the Van object
	cout << van->id() << " " << van->make() << " " <<
	     van->number_seats() << endl;
	// Ditto for one of the SUV objects. Note the need for "FourWheelDriveVehicle::junk()"
	// instead of simply "junk()". This is because SUV has two associated junk() methods. Why?
	cout << suv->id() << " " << suv->PersonalVehicle::junk() <<
	     " " << suv->FourWheelDriveVehicle::junk() << endl;
	// Set a pointer to Vehicle variable to point to one of the Vans.
	Vehicle *v = van;
	// The behavior of the next four instructions should no longer surprise you.
	v -> drive();
	van -> drive();
	v -> vDrive();
	van -> vDrive();
	suv -> vDrive();
	suv2 -> vDrive();
	Vehicle* v2 = v -> clone();
	v2 -> vDrive();
}


