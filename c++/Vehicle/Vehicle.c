
/* Vehicle.c */

#include <stdio.h>
#include "Vehicle.h"

int _Vehicle_count = 0;

void* _vtbl_Vehicle[2];

void Vehicle_DefaultConstructor(Vehicle* _this)
{
	_this->_vptr = _vtbl_Vehicle;
	Vehicle_id_(_this, ++_Vehicle_count);
	Vehicle_make_(_this, "unknown");
	Vehicle_model_(_this, "unknown");
	Vehicle_color_(_this, "unknown");
}

Vehicle* Vehicle_new_DefaultConstructor()
{
	Vehicle* p = (Vehicle*) malloc(sizeof(Vehicle));
	Vehicle_DefaultConstructor(p);
	return p;
}


void Vehicle_CopyConstructor(Vehicle* _this, const Vehicle* q)
{
	_this->_vptr = _vtbl_Vehicle;
	Vehicle_id_(_this, ++_Vehicle_count);
	Vehicle_make_(_this, q->_make);
	Vehicle_model_(_this, q->_model);
	Vehicle_color_(_this, q->_color);
}

Vehicle* Vehicle_new_CopyConstructor(const Vehicle* q)
{
	Vehicle* p = (Vehicle*) malloc(sizeof(Vehicle));
	Vehicle_CopyConstructor(p,q);
	return p;
}

void Vehicle_id_(Vehicle* _this, int i)
{
	_this->_id = i;
}

void Vehicle_make_(Vehicle* _this, const char *s)
{
	strcpy(_this->_make, s);
}

void Vehicle_model_(Vehicle* _this, const char *s)
{
	strcpy(_this->_model, s);
}

void Vehicle_color_(Vehicle* _this, const char *s)
{
	strcpy(_this->_color, s);
}

int Vehicle_count()
{
	return _Vehicle_count;
}

int Vehicle_id(Vehicle* _this)
{
	return _this->_id;
}

const char * Vehicle_make(Vehicle* _this)
{
	return _this->_make;
}

const char * Vehicle_model(Vehicle* _this)
{
	return _this->_model;
}

const char * Vehicle_color(Vehicle* _this)
{
	return _this->_color;
}

void Vehicle_drive(Vehicle* _this)
{
	printf("We are driving a Vehicle.\n");
}

void Vehicle_vDrive(Vehicle* _this)
{
	printf("We are virtually driving a Vehicle.\n");
}

Vehicle* Vehicle_clone(Vehicle* _this)
{
	Vehicle* p = Vehicle_new_CopyConstructor(_this);
	Vehicle_id_(p, _this->_id);
	return p;
}

void build_vtbl_Vehicle()
{
	_vtbl_Vehicle[0] = (void*) & Vehicle_vDrive;
	_vtbl_Vehicle[1] = (void*) & Vehicle_clone;
}


