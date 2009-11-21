

/* FourWheelDriveVehicle.h */


#ifndef __FourWheelDriveVehicle__
#define __FourWheelDriveVehicle__

#include "Vehicle.h"

extern void* _vtbl_FourWheelDriveVehicle[2];
extern void* _vtbl_FourWheelDriveVehicle_Vehicle[2];

typedef struct {

	Vehicle* pVehicle;
	int _junk;
	void** _vptr;

} FourWheelDriveVehicle;

// When vp==0 in the constructors, then they must build Vehicle part.

void FourWheelDriveVehicle_DefaultConstructor
(FourWheelDriveVehicle* _this, Vehicle* vp);
FourWheelDriveVehicle* FourWheelDriveVehicle_new_DefaultConstructor ();
void FourWheelDriveVehicle_CopyConstructor
(FourWheelDriveVehicle* _this, const FourWheelDriveVehicle* q, Vehicle* vp);
FourWheelDriveVehicle* FourWheelDriveVehicle_new_CopyConstructor (const FourWheelDriveVehicle* q);

int FourWheelDriveVehicle_junk(FourWheelDriveVehicle* _this);
void FourWheelDriveVehicle_drive(FourWheelDriveVehicle* _this);
void FourWheelDriveVehicle_vDrive(FourWheelDriveVehicle* _this);
Vehicle* FourWheelDriveVehicle_clone(FourWheelDriveVehicle* _this);

void FourWheelDriveVehicle_Vehicle_thunk_vDrive(Vehicle* _this);
Vehicle* FourWheelDriveVehicle_Vehicle_thunk_clone(Vehicle* _this);

#endif

