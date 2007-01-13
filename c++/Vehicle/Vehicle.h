	
				/* Vehicle.h */ 

#ifndef __Vehicle__ 
#define __Vehicle__ 

#include <string.h> 

extern int _Vehicle_count; 

extern void* _vtbl_Vehicle[2]; 

typedef struct {

        int _id; 
        char _make[16];
        char _model[16]; 
        char _color[16]; 
        void** _vptr; 

} Vehicle; 

void Vehicle_DefaultConstructor(Vehicle* _this);
Vehicle* Vehicle_new_DefaultConstructor();
void Vehicle_CopyConstructor(Vehicle* _this, const Vehicle* p); 
Vehicle* Vehicle_new_CopyConstructor(const Vehicle* p); 

void Vehicle_id_(Vehicle* _this, int i); 
void Vehicle_make_(Vehicle* _this, const char *s); 
void Vehicle_model_(Vehicle* _this, const char *s); 
void Vehicle_color_(Vehicle* _this, const char *s); 
int Vehicle_count();
int Vehicle_id(Vehicle* _this);
const char * Vehicle_make(Vehicle* _this);
const char * Vehicle_model(Vehicle* _this);
const char * Vehicle_color(Vehicle* _this);
void Vehicle_drive(Vehicle* _this); 
void Vehicle_vDrive(Vehicle* _this); 
Vehicle* Vehicle_clone(Vehicle* _this); 

void build_vtbl_Vehicle(); 

#endif 
