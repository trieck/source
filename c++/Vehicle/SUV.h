

/* SUV.h */


#ifndef __SUV__
#define __SUV__

#include "PersonalVehicle.h"
#include "FourWheelDriveVehicle.h"

extern void* _vtbl_SUV[2];
extern void* _vtbl_SUV_Vehicle[2];
extern void* _vtbl_FourWheelDriveVehicleSUV[2];

typedef struct {

	PersonalVehicle personalVehicle;
	FourWheelDriveVehicle fourWheelDriveVehicle;
	Vehicle* pVehicle;
	void** _vptr;

} SUV;

// When vp==0 in the constructors, then they must build Vehicle part.

void SUV_DefaultConstructor
(SUV* _this, Vehicle* vp);
SUV* SUV_new_DefaultConstructor ();
void SUV_CopyConstructor
(SUV* _this, const SUV* q, Vehicle* vp);
SUV* SUV_new_CopyConstructor (const SUV* q);

void SUV_drive(SUV* _this);
void SUV_vDrive(SUV* _this);
Vehicle* SUV_clone(SUV* _this);

void SUV_Vehicle_thunk_vDrive(Vehicle* _this);
void SUV_FourWheelDriveVehicle_thunk_vDrive(FourWheelDriveVehicle* _this);
Vehicle* SUV_Vehicle_thunk_clone(Vehicle* _this);
Vehicle* SUV_FourWheelDriveVehicle_thunk_clone(FourWheelDriveVehicle* _this);


#endif

