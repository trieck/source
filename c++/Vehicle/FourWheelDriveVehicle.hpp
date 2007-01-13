
			/* FourWheelDriveVehicle.hpp */ 


#ifndef __FourWheelDriveVehicle__
#define __FourWheelDriveVehicle__

#include "Vehicle.hpp"

// The reason that Four... is "virtually" derived from Vehicle is to later 
// avoid redundant data when SUV is multiply derived from Four... and Personal...
class FourWheelDriveVehicle : virtual public Vehicle { 

    protected: 

        int _junk; 
        /* Pretend some useful stuff is here */ 

    public: 

        FourWheelDriveVehicle(); 
        FourWheelDriveVehicle(const FourWheelDriveVehicle& v); 
        virtual ~FourWheelDriveVehicle(); 
        void drive();
        virtual void vDrive();
        virtual Vehicle* clone(); 
        int junk() { return _junk; } 
        /* Pretend more good stuff follows */
}; 

#endif 



