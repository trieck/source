

			/* PersonalVehicle.h */ 


#ifndef __PersonalVehicle__
#define __PersonalVehicle__

#include "Vehicle.h"

extern void* _vtbl_PersonalVehicle[2]; 
extern void* _vtbl_PersonalVehicle_Vehicle[2]; 

typedef struct { 

        Vehicle* pVehicle; 
        int _junk; 
        void** _vptr;

} PersonalVehicle; 

// When vp==0 in the constructors, then they must build Vehicle part.

void PersonalVehicle_DefaultConstructor
   (PersonalVehicle* _this, Vehicle* vp); 
PersonalVehicle* PersonalVehicle_new_DefaultConstructor (); 
void PersonalVehicle_CopyConstructor
   (PersonalVehicle* _this, const PersonalVehicle* q, Vehicle* vp); 
PersonalVehicle* PersonalVehicle_new_CopyConstructor (const PersonalVehicle* q); 

int PersonalVehicle_junk(PersonalVehicle* _this); 

void PersonalVehicle_drive(PersonalVehicle* _this); 
void PersonalVehicle_vDrive(PersonalVehicle* _this); 
Vehicle* PersonalVehicle_clone(PersonalVehicle* _this); 

void PersonalVehicle_Vehicle_thunk_vDrive(Vehicle* _this); 
Vehicle* PersonalVehicle_Vehicle_thunk_clone(Vehicle* _this); 


#endif 

