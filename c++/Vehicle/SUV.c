
			/* SUV.c */ 

#include <stdio.h> 
#include "SUV.h"

void* _vtbl_SUV[2]; 
void* _vtbl_SUV_Vehicle[2]; 
void* _vtbl_SUV_FourWheelDriveVehicle[2]; 

void SUV_DefaultConstructor (SUV* _this, Vehicle* vp) 
{ 
   if (vp==0) { 
      _this->pVehicle = (Vehicle*)((char*)_this + sizeof(SUV)); 
      Vehicle_DefaultConstructor(_this->pVehicle); 
   } else 
      _this->pVehicle = vp; 
   PersonalVehicle_DefaultConstructor
     (&(_this->personalVehicle), _this->pVehicle); 
   FourWheelDriveVehicle_DefaultConstructor
     (&(_this->fourWheelDriveVehicle), _this->pVehicle); 
   _this->_vptr = _vtbl_SUV; 
   _this->pVehicle->_vptr = _vtbl_SUV_Vehicle; 
   _this->personalVehicle._vptr = _vtbl_SUV; 
   _this->fourWheelDriveVehicle._vptr = _vtbl_SUV_FourWheelDriveVehicle; 
} 

SUV* SUV_new_DefaultConstructor()
{ 
   SUV* p; 
   p = (SUV*) malloc(sizeof(SUV) + sizeof(Vehicle)); 
   SUV_DefaultConstructor(p, 0); 
   return p; 
} 

void SUV_CopyConstructor
   (SUV* _this, const SUV* q, Vehicle* vp) 
{ 
   if (vp==0) { 
      _this->pVehicle = (Vehicle*)((char*)_this+sizeof(SUV)); 
      Vehicle_CopyConstructor(_this->pVehicle, q->pVehicle); 
   } else 
      _this->pVehicle = vp; 
   PersonalVehicle_CopyConstructor
     (&(_this->personalVehicle), &(q->personalVehicle), _this->pVehicle); 
   FourWheelDriveVehicle_CopyConstructor
     (&(_this->fourWheelDriveVehicle), &(q->fourWheelDriveVehicle), _this->pVehicle); 
   _this->_vptr = _vtbl_SUV; 
   _this->pVehicle->_vptr = _vtbl_SUV_Vehicle; 
   _this->personalVehicle._vptr = _vtbl_SUV; 
   _this->fourWheelDriveVehicle._vptr = _vtbl_SUV_FourWheelDriveVehicle; 

} 

SUV* SUV_new_CopyConstructor(const SUV* q) 
{ 
   SUV* p; 
   p = (SUV*) malloc(sizeof(SUV) + sizeof(Vehicle)); 
   SUV_CopyConstructor(p, q, 0); 
   return p; 
} 

void SUV_drive(SUV* _this) { 

   printf("We are driving an SUV.\n"); 
} 

void SUV_vDrive(SUV* _this) { 

   printf("We are virtually driving an SUV.\n"); 
} 

Vehicle* SUV_clone(SUV* _this) { 

    SUV* p = SUV_new_CopyConstructor(_this); 
    Vehicle_id_(p->pVehicle, _this->pVehicle->_id); 
    return p->pVehicle; 
}

void SUV_Vehicle_thunk_vDrive(Vehicle* _this) 
{
    SUV_vDrive((SUV*)((char*)_this - sizeof(SUV))); 
} 

void SUV_FourWheelDriveVehicle_thunk_vDrive(FourWheelDriveVehicle* _this) 
{
    SUV_vDrive((SUV*)((char*)_this - sizeof(PersonalVehicle))); 
} 

Vehicle* SUV_Vehicle_thunk_clone(Vehicle* _this) 
{
    return SUV_clone((SUV*)((char*)_this - sizeof(SUV))); 
} 

Vehicle* SUV_FourWheelDriveVehicle_thunk_clone(FourWheelDriveVehicle* _this) 
{
    return SUV_clone((SUV*)((char*)_this - sizeof(PersonalVehicle))); 
}

void build_vtbl_SUV() 
{ 
    _vtbl_SUV[0] = (void*) & SUV_vDrive; 
    _vtbl_SUV[1] = (void*) & SUV_clone; 
}

void build_vtbl_SUV_Vehicle() 
{ 
    _vtbl_SUV_Vehicle[0] = (void*) & SUV_Vehicle_thunk_vDrive; 
    _vtbl_SUV_Vehicle[1] = (void*) & SUV_Vehicle_thunk_clone; 
}

void build_vtbl_SUV_FourWheelDriveVehicle() 
{ 
    _vtbl_SUV_FourWheelDriveVehicle[0] = 
        (void*) & SUV_FourWheelDriveVehicle_thunk_vDrive; 
    _vtbl_SUV_FourWheelDriveVehicle[1] = 
        (void*) & SUV_FourWheelDriveVehicle_thunk_clone; 
}








