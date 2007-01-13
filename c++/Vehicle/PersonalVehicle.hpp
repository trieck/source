

			/* PersonalVehicle.hpp */ 


#ifndef __PersonalVehicle__
#define __PersonalVehicle__

#include "Vehicle.hpp"

// The reason that Personal... is "virtually" derived from Vehicle is to later 
// avoid redundant data when SUV is multiply derived from Four... and Personal...
class PersonalVehicle : virtual public Vehicle { 

    protected: 

        int _junk; 
	/* Pretend some useful stuff is here */ 

    public: 

        PersonalVehicle(); 
        PersonalVehicle(const PersonalVehicle& v); 
        virtual ~PersonalVehicle(); 
        void drive();
        virtual void vDrive();
        virtual Vehicle* clone(); 
        int junk() { return _junk; } 
        /* Pretend more good stuff follows */
}; 

#endif 

