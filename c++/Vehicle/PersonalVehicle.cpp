
			/* PersonalVehicle.cpp */ 

#include "PersonalVehicle.hpp"
#include <iostream> 

using namespace std; 

PersonalVehicle::PersonalVehicle() : Vehicle(), _junk(22) { }  

PersonalVehicle::PersonalVehicle(const PersonalVehicle& v) 
   :  Vehicle(v), _junk(22) { } 

PersonalVehicle::~PersonalVehicle() { } 

void PersonalVehicle::drive() 
{
   cout << "We are driving a Personal Vehicle." << endl; 
} 

void PersonalVehicle::vDrive() 
{ 
    cout << "We are virtually driving a Personal Vehicle." << endl; 
}

Vehicle* PersonalVehicle::clone() 
{ 
    Vehicle* p = new PersonalVehicle(*this); 
    p->id_(_id); 
    return p; 
} 

