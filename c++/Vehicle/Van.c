

			/* Van.c */ 

#include <stdio.h> 
#include "Van.h"

void* _vtbl_Van[2]; 

void Van_DefaultConstructor(Van* _this) { 
    Vehicle_DefaultConstructor(&(_this->vehicle));
    _this->_vptr = _vtbl_Van; 
    _this->vehicle._vptr = _vtbl_Van; 
    _this->_number_seats = 0; 
    _this->_payload_capacity = 0; 
} 

Van* Van_new_DefaultConstructor() { 
    Van* p = (Van*) malloc(sizeof(Van)); 
    Van_DefaultConstructor(p); 
    return p; 
} 

void Van_CopyConstructor(Van* _this, const Van* q) {
    Vehicle_CopyConstructor(&(_this->vehicle),&(q->vehicle)); 
    _this->_vptr = _vtbl_Van; 
    _this->vehicle._vptr = _vtbl_Van; 
    _this->_number_seats = q->_number_seats; 
    _this->_payload_capacity = q->_payload_capacity; 
} 

Van* Van_new_CopyConstructor(const Van* q) {
    Van* p = (Van*) malloc(sizeof(Van)); 
    Van_CopyConstructor(p,q); 
    return p; 
} 

void Van_number_seats_(Van* _this, int n) 
            { _this->_number_seats = n; } 

void payload_capacity_(Van* _this, double x) 
            { _this->_payload_capacity = x; } 

int Van_number_seats(Van* _this) 
            { return _this->_number_seats; }  

double Van_payload_capacity(Van* _this) 
            { return _this->_payload_capacity; }  

void Van_drive(Van* _this) 
{ 
   printf("We are driving a Van.\n"); 
} 

void Van_vDrive(Van* _this) 
{ 
   printf("We are virtually driving a Van.\n"); 
} 

Vehicle* Van_clone(Van* _this) 
{ 
    Van* p = Van_new_CopyConstructor(_this); 
    Vehicle_id_(&(p->vehicle), _this->vehicle._id); 
    return (Vehicle*) p; 
}

void build_vtbl_Van() 
{ 
    _vtbl_Van[0] = (void*) & Van_vDrive; 
    _vtbl_Van[1] = (void*) & Van_clone; 
}
