
/* Van.h */


#ifndef __Van__
#define __Van__

#include "Vehicle.h"

extern void* _vtbl_Van[2];

typedef struct {

	Vehicle vehicle;
	int _number_seats;
	double _payload_capacity;
	void** _vptr;

} Van;

void Van_DefaultConstructor(Van* _this);
Van* Van_new_DefaultConstructor();
void Van_CopyConstructor(Van* _this, const Van* q);
Van* Van_new_CopyConstructor(const Van* q);

void Van_number_seats_(Van* _this, int n);
void payload_capacity_(Van* _this, double x);
int Van_number_seats(Van* _this);
double Van_payload_capacity(Van* _this);
void Van_drive(Van* _this);
void Van_vDrive(Van* _this);
Vehicle* Van_clone(Van* _this);

void build_vtbl_Van();

#endif

