
			/* Van.cpp */ 

#include <iostream> 
#include "Van.hpp"

using namespace std; 

// Notice how Vehicle constructors are invoked in Van constructors 
Van::Van() : Vehicle() { 
    number_seats_(0); 
    payload_capacity_(0); 
} 

Van::Van(const Van& v) : Vehicle(v) { 
    number_seats_(v._number_seats); 
    payload_capacity_(v._payload_capacity); 
} 

Van::~Van() { } 

void Van::drive() { 

   cout << "We are driving a Van." << endl; 
} 

void Van::vDrive() { 

    cout << "We are virtually driving a Van." << endl; 
}

Vehicle* Van::clone() { 

    Vehicle* p = new Van(*this); 
    p->id_(_id); 
    return p; 
}

// Notice how Vehicle == operator is used when defining Van == operator 

bool operator==(Van const &v1, Van const &v2) { 

    return ( 
	(Vehicle)v1 == (Vehicle)v2 && 
	v1._number_seats == v2._number_seats && 
	v1._payload_capacity == v2._payload_capacity
    ); 
} 


