
				/* SUV.hpp */ 


#ifndef __SUV__
#define __SUV__ 

#include "PersonalVehicle.hpp"
#include "FourWheelDriveVehicle.hpp"

// SUV is derived from both PersonalVehicle and FourWheelDriveVehicle. 
// Since these were in turn "virtually" derived from Vehicle, only one 
// copy of Vehicle data will occur in each SUV object. 
class SUV : public PersonalVehicle, public FourWheelDriveVehicle { 

    protected: 

	/* Pretend some useful stuff is here */ 

    public: 

        SUV(); 
        SUV(const SUV& v); 
        virtual ~SUV(); 
        void drive();
        virtual void vDrive();
        virtual Vehicle* clone(); 
        /* Pretend more good stuff follows */
}; 

#endif 


