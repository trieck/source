
/* Vehicle.cpp */

#include <iostream>
#include "Vehicle.hpp"

// Needed to use iostream

using namespace std;

// Initialize static variable
int Vehicle::_count = 0;

// Define default constructor

Vehicle::Vehicle()
{
	id_(++_count);
	make_("unknown");
	model_("unknown");
	color_("unknown");
}

// Define copy constructor. All data of new object will be same as
// old object, except for the _id

Vehicle::Vehicle(const Vehicle& v)
{
	id_(++_count);
	make_(v.make());
	model_(v.model());
	color_(v.color());
}

// Define silly drive method
void Vehicle::drive()
{
	cout << "We are driving a Vehicle." << endl;
}

// Ditto, but for the virtual function version
void Vehicle::vDrive()
{
	cout << "We are virtually driving a Vehicle." << endl;
}

Vehicle* Vehicle::clone()
{
	Vehicle* p = new Vehicle(*this);
	p->id_(_id);
	return p;
}

// Trivially define the destructor
Vehicle::~Vehicle() { }

// Define the index operator is a silly way. It will return a
// character in the _color variable (for no good reason).

char Vehicle::operator[](int n)
{

	return _color[n];
}

// Define comparison operator. Originally it compared the two _id 's.
// Now it compares the other data instead. Get used to looking at Boolean
// data and Boolean operators in a computational way.

bool operator==(Vehicle const& v1, Vehicle const& v2)
{
//    return (v1._id == v2._id);
	return (
	           strcmp(v1._make,v2._make) == 0 &&
	           strcmp(v1._model,v2._model) == 0 &&
	           strcmp(v1._color,v2._color) == 0
	       );
}


