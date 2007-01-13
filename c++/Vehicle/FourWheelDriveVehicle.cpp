
			/* FourWheelDriveVehicle.cpp */ 

#include "FourWheelDriveVehicle.hpp"
#include <iostream>

using namespace std; 

FourWheelDriveVehicle::FourWheelDriveVehicle() : Vehicle(), _junk(33) { } 

FourWheelDriveVehicle::FourWheelDriveVehicle(const FourWheelDriveVehicle& v)
  : Vehicle(v), _junk(33) { } 

FourWheelDriveVehicle::~FourWheelDriveVehicle() { } 

void FourWheelDriveVehicle::drive() 
{
   cout << "We are driving a Four Wheel Drive Vehicle." << endl; 
} 

void FourWheelDriveVehicle::vDrive() 
{ 
    cout << "We are virtually driving a Four Wheel Drive Vehicle." << endl; 
}

Vehicle* FourWheelDriveVehicle::clone() 
{ 
    Vehicle* p = new FourWheelDriveVehicle(*this); 
    p->id_(_id); 
    return p; 
} 

