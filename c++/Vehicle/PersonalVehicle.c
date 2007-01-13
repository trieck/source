
			/* PersonalVehicle.c */ 

#include <stdio.h> 
#include "PersonalVehicle.h"

void* _vtbl_PersonalVehicle[2]; 
void* _vtbl_PersonalVehicle_Vehicle[2]; 

void PersonalVehicle_DefaultConstructor (PersonalVehicle* _this, Vehicle* vp) 
{ 
   if (vp==0) { 
      _this->pVehicle = (Vehicle*)((char*)_this+sizeof(PersonalVehicle)); 
      Vehicle_DefaultConstructor(_this->pVehicle); 
   } else 
      _this->pVehicle = vp; 
   _this->_vptr = _vtbl_PersonalVehicle; 
   _this->pVehicle->_vptr = _vtbl_PersonalVehicle_Vehicle; 
   _this->_junk = 22; 
} 

PersonalVehicle* PersonalVehicle_new_DefaultConstructor()
{ 
   PersonalVehicle* p; 
   p = (PersonalVehicle*) malloc(sizeof(PersonalVehicle) + sizeof(Vehicle)); 
   PersonalVehicle_DefaultConstructor(p, 0); 
   return p; 
} 

void PersonalVehicle_CopyConstructor
   (PersonalVehicle* _this, const PersonalVehicle* q, Vehicle* vp) 
{ 
   if (vp==0) { 
      _this->pVehicle = (Vehicle*)((char*)_this+sizeof(PersonalVehicle)); 
      Vehicle_CopyConstructor(_this->pVehicle, q->pVehicle); 
   } else 
      _this->pVehicle = vp; 
   _this->_vptr = _vtbl_PersonalVehicle; 
   _this->pVehicle->_vptr = _vtbl_PersonalVehicle_Vehicle; 
   _this->_junk = q->_junk; 
} 

PersonalVehicle* PersonalVehicle_new_CopyConstructor(const PersonalVehicle* q) 
{ 
   PersonalVehicle* p; 
   p = (PersonalVehicle*) malloc(sizeof(PersonalVehicle) + sizeof(Vehicle)); 
   PersonalVehicle_CopyConstructor(p, q, 0); 
   return p; 
} 

int PersonalVehicle_junk(PersonalVehicle* _this) 
{
   return _this->_junk;
} 

void PersonalVehicle_drive(PersonalVehicle* _this) 
{ 
   printf("We are driving a Personal Vehicle.\n"); 
} 

void PersonalVehicle_vDrive(PersonalVehicle* _this) 
{ 
   printf("We are virtually driving a Personal Vehicle.\n"); 
} 

Vehicle* PersonalVehicle_clone(PersonalVehicle* _this) 
{ 
    PersonalVehicle* p = PersonalVehicle_new_CopyConstructor(_this); 
    Vehicle_id_(p->pVehicle, _this->pVehicle->_id); 
    return p->pVehicle; 
}

void PersonalVehicle_Vehicle_thunk_vDrive(Vehicle* _this) 
{
    PersonalVehicle_vDrive
      ((PersonalVehicle*)((char*)_this - sizeof(PersonalVehicle))); 
}

Vehicle* PersonalVehicle_Vehicle_thunk_clone(Vehicle* _this) 
{
    return PersonalVehicle_clone
      ((PersonalVehicle*)((char*)_this - sizeof(PersonalVehicle))); 
}

void build_vtbl_PersonalVehicle() 
{ 
    _vtbl_PersonalVehicle[0] = (void*) & PersonalVehicle_vDrive; 
    _vtbl_PersonalVehicle[1] = (void*) & PersonalVehicle_clone; 
}

void build_vtbl_PersonalVehicle_Vehicle() 
{ 
    _vtbl_PersonalVehicle_Vehicle[0] = 
       (void*) & PersonalVehicle_Vehicle_thunk_vDrive; 
    _vtbl_PersonalVehicle_Vehicle[1] = 
       (void*) & PersonalVehicle_Vehicle_thunk_clone; 
}

