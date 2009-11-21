vehicle/FourWheelDriveVehicle.cpp                                                                   0100644 0053363 0024461 00000001321 10136047052 020371  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
/* FourWheelDriveVehicle.cpp */

#include "FourWheelDriveVehicle.hpp"
#include <iostream>

using namespace std;

FourWheelDriveVehicle::FourWheelDriveVehicle() : Vehicle(), _junk(33) { }

FourWheelDriveVehicle::FourWheelDriveVehicle(const FourWheelDriveVehicle& v)
		: Vehicle(v), _junk(33) { }

FourWheelDriveVehicle::~FourWheelDriveVehicle() { }

void FourWheelDriveVehicle::drive()
{
	cout << "We are driving a Four Wheel Drive Vehicle." << endl;
}

void FourWheelDriveVehicle::vDrive()
{
	cout << "We are virtually driving a Four Wheel Drive Vehicle." << endl;
}

Vehicle* FourWheelDriveVehicle::clone()
{
	Vehicle* p = new FourWheelDriveVehicle(*this);
	p->id_(_id);
	return p;
}

                                                                                                                                                                                                                                                                                                               vehicle/FourWheelDriveVehicle.h                                                                     0100644 0053363 0024461 00000002303 10136011410 020024  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            

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

                                                                                                                                                                                                                                                                                                                             vehicle/FourWheelDriveVehicle.hpp                                                                   0100644 0053363 0024461 00000001411 10136044307 020376  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
/* FourWheelDriveVehicle.hpp */


#ifndef __FourWheelDriveVehicle__
#define __FourWheelDriveVehicle__

#include "Vehicle.hpp"

// The reason that Four... is "virtually" derived from Vehicle is to later
// avoid redundant data when SUV is multiply derived from Four... and Personal...
class FourWheelDriveVehicle : virtual public Vehicle {

protected:

	int _junk;
	/* Pretend some useful stuff is here */

public:

	FourWheelDriveVehicle();
	FourWheelDriveVehicle(const FourWheelDriveVehicle& v);
	virtual ~FourWheelDriveVehicle();
	void drive();
	virtual void vDrive();
	virtual Vehicle* clone();
	int junk() {
		return _junk;
	}
	/* Pretend more good stuff follows */
};

#endif



                                                                                                                                                                                                                                                       vehicle/Makefile                                                                                    0100666 0053363 0024461 00000002763 10136051726 015155  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            

#Definitions

OBJS1=main.oo Vehicle.oo Van.oo PersonalVehicle.oo FourWheelDriveVehicle.oo SUV.oo
      OBJS2=main.o Vehicle.o Van.o PersonalVehicle.o FourWheelDriveVehicle.o SUV.o


#Dependency rules

            drive1 :
            $ {OBJS1}
            g++ $ {OBJS1} -o drive1
            main.oo :
            main.cpp SUV.hpp PersonalVehicle.hpp FourWheelDriveVehicle.hpp Van.hpp Vehicle.hpp
            g++ -c main.cpp -o main.oo
            SUV.oo :
            SUV.cpp SUV.hpp PersonalVehicle.hpp FourWheelDriveVehicle.hpp Vehicle.hpp
            g++ -c SUV.cpp -o SUV.oo
            PersonalVehicle.oo :
            PersonalVehicle.cpp PersonalVehicle.hpp Vehicle.hpp
            g++ -c PersonalVehicle.cpp -o PersonalVehicle.oo
            FourWheelDriveVehicle.oo :
            FourWheelDriveVehicle.cpp FourWheelDriveVehicle.hpp Vehicle.hpp
            g++ -c FourWheelDriveVehicle.cpp -o FourWheelDriveVehicle.oo
            Van.oo :
            Van.cpp Van.h Vehicle.hpp
            g++ -c Van.cpp -o Van.oo
            Vehicle.oo :
            Vehicle.cpp Vehicle.hpp
            g++ -c Vehicle.cpp -o Vehicle.oo

            drive2 :
            $ {OBJS2}
            cc $ {OBJS2} -o drive2
            main.o :
            main.c SUV.h PersonalVehicle.h FourWheelDriveVehicle.h Van.h Vehicle.h
            cc -c main.c
            SUV.o :
            SUV.c SUV.h PersonalVehicle.h FourWheelDriveVehicle.h Vehicle.h
            cc -c SUV.c
            PersonalVehicle.o :
            PersonalVehicle.c PersonalVehicle.h Vehicle.h
            cc -c PersonalVehicle.c
            FourWheelDriveVehicle.o :
            FourWheelDriveVehicle.c FourWheelDriveVehicle.h Vehicle.h
            cc -c FourWheelDriveVehicle.c
            Van.o :
            Van.cpp Van.h Vehicle.h
            cc -c Van.c
            Vehicle.o :
            Vehicle.c Vehicle.h
            cc -c Vehicle.c

            clean:
            rm -f $ {OBJS1} $ {OBJS2} drive1 drive2

            all:
            drive1 drive2

                         vehicle/PersonalVehicle.c                                                                           0100644 0053363 0024461 00000005247 10136053653 016741  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
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

                                                                                                                                                                                                                                                                                                                                                         vehicle/PersonalVehicle.cpp                                                                         0100644 0053363 0024461 00000001170 10136047231 017263  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
/* PersonalVehicle.cpp */

#include "PersonalVehicle.hpp"
#include <iostream>

using namespace std;

PersonalVehicle::PersonalVehicle() : Vehicle(), _junk(22) { }

PersonalVehicle::PersonalVehicle(const PersonalVehicle& v)
		:  Vehicle(v), _junk(22) { }

PersonalVehicle::~PersonalVehicle() { }

void PersonalVehicle::drive()
{
	cout << "We are driving a Personal Vehicle." << endl;
}

void PersonalVehicle::vDrive()
{
	cout << "We are virtually driving a Personal Vehicle." << endl;
}

Vehicle* PersonalVehicle::clone()
{
	Vehicle* p = new PersonalVehicle(*this);
	p->id_(_id);
	return p;
}

                                                                                                                                                                                                                                                                                                                                                                                                        vehicle/PersonalVehicle.h                                                                           0100644 0053363 0024461 00000002052 10136005245 016727  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            

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

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      vehicle/PersonalVehicle.hpp                                                                         0100644 0053363 0024461 00000001325 10136044201 017264  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            

/* PersonalVehicle.hpp */


#ifndef __PersonalVehicle__
#define __PersonalVehicle__

#include "Vehicle.hpp"

// The reason that Personal... is "virtually" derived from Vehicle is to later
// avoid redundant data when SUV is multiply derived from Four... and Personal...
class PersonalVehicle : virtual public Vehicle {

protected:

	int _junk;
	/* Pretend some useful stuff is here */

public:

	PersonalVehicle();
	PersonalVehicle(const PersonalVehicle& v);
	virtual ~PersonalVehicle();
	void drive();
	virtual void vDrive();
	virtual Vehicle* clone();
	int junk() {
		return _junk;
	}
	/* Pretend more good stuff follows */
};

#endif

                                                                                                                                                                                                                                                                                                           vehicle/SUV.c                                                                                       0100644 0053363 0024461 00000006142 10136053653 014326  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
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

void SUV_drive(SUV* _this)
{

	printf("We are driving an SUV.\n");
}

void SUV_vDrive(SUV* _this)
{

	printf("We are virtually driving an SUV.\n");
}

Vehicle* SUV_clone(SUV* _this)
{

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








                                                                                                                                                                                                                                                                                                                                                                                                                              vehicle/SUV.cpp                                                                                     0100644 0053363 0024461 00000000752 10136047257 014672  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
/* SUV.cpp */

#include "SUV.hpp"
#include <iostream>

using namespace std;

SUV::SUV() : PersonalVehicle(), FourWheelDriveVehicle() { }

SUV::SUV(const SUV& v) : PersonalVehicle(v), FourWheelDriveVehicle(v) { }

SUV::~SUV() { }

void SUV::drive()
{
	cout << "We are driving an SUV." << endl;
}

void SUV::vDrive()
{
	cout << "We are virtually driving an SUV." << endl;
}

Vehicle* SUV::clone()
{
	Vehicle* p = new SUV(*this);
	p->id_(_id);
	return p;
}
                      vehicle/SUV.h                                                                                       0100644 0053363 0024461 00000002031 10136003420 014307  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            

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

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       vehicle/SUV.hpp                                                                                     0100644 0053363 0024461 00000001256 10136044424 014670  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
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


                                                                                                                                                                                                                                                                                                                                                  vehicle/Van.c                                                                                       0100644 0053363 0024461 00000003173 10136053653 014376  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            

/* Van.c */

#include <stdio.h>
#include "Van.h"

void* _vtbl_Van[2];

void Van_DefaultConstructor(Van* _this)
{
	Vehicle_DefaultConstructor(&(_this->vehicle));
	_this->_vptr = _vtbl_Van;
	_this->vehicle._vptr = _vtbl_Van;
	_this->_number_seats = 0;
	_this->_payload_capacity = 0;
}

Van* Van_new_DefaultConstructor()
{
	Van* p = (Van*) malloc(sizeof(Van));
	Van_DefaultConstructor(p);
	return p;
}

void Van_CopyConstructor(Van* _this, const Van* q)
{
	Vehicle_CopyConstructor(&(_this->vehicle),&(q->vehicle));
	_this->_vptr = _vtbl_Van;
	_this->vehicle._vptr = _vtbl_Van;
	_this->_number_seats = q->_number_seats;
	_this->_payload_capacity = q->_payload_capacity;
}

Van* Van_new_CopyConstructor(const Van* q)
{
	Van* p = (Van*) malloc(sizeof(Van));
	Van_CopyConstructor(p,q);
	return p;
}

void Van_number_seats_(Van* _this, int n)
{
	_this->_number_seats = n;
}

void payload_capacity_(Van* _this, double x)
{
	_this->_payload_capacity = x;
}

int Van_number_seats(Van* _this)
{
	return _this->_number_seats;
}

double Van_payload_capacity(Van* _this)
{
	return _this->_payload_capacity;
}

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
                                                                                                                                                                                                                                                                                                                                                                                                     vehicle/Van.cpp                                                                                     0100644 0053363 0024461 00000001577 10136046225 014741  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
/* Van.cpp */

#include <iostream>
#include "Van.hpp"

using namespace std;

// Notice how Vehicle constructors are invoked in Van constructors
Van::Van() : Vehicle()
{
	number_seats_(0);
	payload_capacity_(0);
}

Van::Van(const Van& v) : Vehicle(v)
{
	number_seats_(v._number_seats);
	payload_capacity_(v._payload_capacity);
}

Van::~Van() { }

void Van::drive()
{

	cout << "We are driving a Van." << endl;
}

void Van::vDrive()
{

	cout << "We are virtually driving a Van." << endl;
}

Vehicle* Van::clone()
{

	Vehicle* p = new Van(*this);
	p->id_(_id);
	return p;
}

// Notice how Vehicle == operator is used when defining Van == operator

bool operator==(Van const &v1, Van const &v2)
{

	return (
	           (Vehicle)v1 == (Vehicle)v2 &&
	           v1._number_seats == v2._number_seats &&
	           v1._payload_capacity == v2._payload_capacity
	       );
}


                                                                                                                                 vehicle/Van.h                                                                                       0100644 0053363 0024461 00000001306 10135773166 014406  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
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

                                                                                                                                                                                                                                                                                                                          vehicle/Van.hpp                                                                                     0100644 0053363 0024461 00000002165 10136046316 014741  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
/* Van.hpp */


#ifndef __Van__
#define __Van__

#include "Vehicle.hpp"

// Van is derived from Vehicle, so a Van object is conceptually also a
// Vehicle object. At the implementation level, A Van object contains all the
// data for a Vehicle object, plus extra data.

class Van : public Vehicle {

protected:

	// More member data
	int _number_seats;
	double _payload_capacity;

	// more mutator methods
	void number_seats_(int n) {
		_number_seats = n;
	}
	void payload_capacity_(double x) {
		_payload_capacity = x;
	}

	// assignment operator
	Van& operator= (const Van& v);

public:

	// Declare the usual things and implement some of them
	Van();
	Van(const Van& v);
	virtual ~Van();
	int number_seats() {
		return _number_seats;
	}
	double payload_capacity() {
		return _payload_capacity;
	}
	void drive();
	virtual void vDrive();
	virtual Vehicle* clone();
	friend bool operator==(Van const &v1, Van const &v2);
};

#endif

                                                                                                                                                                                                                                                                                                                                                                                                           vehicle/Vehicle.c                                                                                   0100644 0053363 0024461 00000004107 10136053653 015227  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
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


                                                                                                                                                                                                                                                                                                                                                                                                                                                         vehicle/Vehicle.cpp                                                                                 0100644 0053363 0024461 00000003067 10136047426 015574  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
/* Vehicle.cpp */

#include <iostream>
#include "Vehicle.hpp"

// Needed to use iostream

using namespace std;

// Initialize static variable
int Vehicle::_count = 0;

// Define default constructor

Vehicle::Vehicle()
{
	id_(++_count);
	make_("unknown");
	model_("unknown");
	color_("unknown");
}

// Define copy constructor. All data of new object will be same as
// old object, except for the _id

Vehicle::Vehicle(const Vehicle& v)
{
	id_(++_count);
	make_(v.make());
	model_(v.model());
	color_(v.color());
}

// Define silly drive method
void Vehicle::drive()
{
	cout << "We are driving a Vehicle." << endl;
}

// Ditto, but for the virtual function version
void Vehicle::vDrive()
{
	cout << "We are virtually driving a Vehicle." << endl;
}

Vehicle* Vehicle::clone()
{
	Vehicle* p = new Vehicle(*this);
	p->id_(_id);
	return p;
}

// Trivially define the destructor
Vehicle::~Vehicle() { }

// Define the index operator is a silly way. It will return a
// character in the _color variable (for no good reason).

char Vehicle::operator[](int n)
{

	return _color[n];
}

// Define comparison operator. Originally it compared the two _id 's.
// Now it compares the other data instead. Get used to looking at Boolean
// data and Boolean operators in a computational way.

bool operator==(Vehicle const& v1, Vehicle const& v2)
{
//    return (v1._id == v2._id);
	return (
	           strcmp(v1._make,v2._make) == 0 &&
	           strcmp(v1._model,v2._model) == 0 &&
	           strcmp(v1._color,v2._color) == 0
	       );
}


                                                                                                                                                                                                                                                                                                                                                                                                                                                                         vehicle/Vehicle.h                                                                                   0100644 0053363 0024461 00000002035 10135773041 015231  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
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
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   vehicle/Vehicle.hpp                                                                                 0100644 0053363 0024461 00000004313 10136043717 015573  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            
/* Vehicle.hpp */

#ifndef __Vehicle__
#define __Vehicle__

#include <string.h>

class Vehicle {

	// There is only one _count variable, not one per object
	static int _count;

	// "protected" means "public" to any code inside the definition of any class derived from
	// Vehicle, but "private" to all other outside code.

protected:

	// Some member data (instance variables, attributes)
	int _id;
	char _make[16];
	char _model[16];
	char _color[16];

public:

	// Mutator methods
	void id_(int i) {
		_id = i;
	}
	void make_(const char *s) {
		strcpy(_make, s);
	}
	void model_(const char *s) {
		strcpy(_model, s);
	}
	void color_(const char *s) {
		strcpy(_color, s);
	}

	// Assignment operator. Similar to copy constructor, but doesn't create a new object, but
	// rather, changes the object stored in an existing Vehicle variable.
	Vehicle& operator= (Vehicle const& v);

	// Declare default constructor
	Vehicle();
	// Declare copy constructor
	Vehicle(const Vehicle& v);
	// Declare destructor as a virtual function to help select appropriate destructor at run-time
	virtual ~Vehicle();
	// Static function to get value of static variable
	static int count() {
		return _count;
	}
	// Accessor methods
	int id() {
		return _id;
	}
	const char * make() const {
		return _make;
	}
	const char * model() const {
		return _model;
	}
	const char * color() const {
		return _color;
	}
	// Silly method
	void drive();
	// A virtual function version of the same thing
	virtual void vDrive();
	// Will be defining the index operator for this class
	virtual Vehicle* clone();
	char operator[](int n);
	// Will be defining comparison operator to compare two Vehicle objects.
	// Note that this is not a member function (method). It is declared to be a
	// "friend" of the Vehicle class and so can access private and protected data.
	friend bool operator==(Vehicle const &v1, Vehicle const &v2);
};

#endif
                                                                                                                                                                                                                                                                                                                     vehicle/main.c                                                                                      0100644 0053363 0024461 00000002725 10136053653 014600  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            


/* main.c */


#include <stdio.h>
#include "Van.h"
#include "SUV.h"

main()
{

	build_vtbl_Vehicle();
	build_vtbl_Van();
	build_vtbl_PersonalVehicle();
	build_vtbl_PersonalVehicle();
	build_vtbl_PersonalVehicle_Vehicle();
	build_vtbl_FourWheelDriveVehicle();
	build_vtbl_FourWheelDriveVehicle_Vehicle();
	build_vtbl_SUV();
	build_vtbl_SUV_Vehicle();
	build_vtbl_SUV_FourWheelDriveVehicle();

	Van* van = Van_new_DefaultConstructor();
	SUV* suv = SUV_new_DefaultConstructor();
	SUV* suv2 = SUV_new_CopyConstructor(suv);
	printf("%d\n", Vehicle_count());
	printf("%d %s %d\n",
	       Vehicle_id(&(van->vehicle)),
	       Vehicle_make(&(van->vehicle)),
	       Van_number_seats(van)
	      );
	printf("%d %d %d\n",
	       Vehicle_id(suv->pVehicle),
	       PersonalVehicle_junk(&(suv->personalVehicle)),
	       FourWheelDriveVehicle_junk(&(suv->fourWheelDriveVehicle))
	      );
	Vehicle* v = (Vehicle*) van;
	Vehicle_drive(v);
	Van_drive(van);

	// virtually invoke vDrive and clone

	void (*fp1)(Vehicle*);
	fp1 = v->_vptr[0];
	(*fp1)(v);

	void (*fp2)(Van*);
	fp2 = van->_vptr[0];
	(*fp2)(van);

	void (*fp3)(SUV*);
	fp3 = suv->_vptr[0];
	(*fp3)(suv);

	v = suv->pVehicle;
	fp1 = v->_vptr[0];
	(*fp1)(v);

	v = suv2->pVehicle;
	fp1 = v->_vptr[0];
	(*fp1)(v);

	Vehicle* (*fp4)(Vehicle*);
	fp4 = v->_vptr[1];
	Vehicle* v2 = (*fp4)(v);
	fp1 = v2->_vptr[0];
	(*fp1)(v2);


}


                                           vehicle/main.cpp                                                                                    0100644 0053363 0024461 00000002455 10136052632 015134  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            



/* main.cpp */

#include <iostream>
#include "Van.hpp"
#include "SUV.hpp"

using namespace std;

main()
{

	// Create a van object with default construct, and store a pointer to it
	Van * van = new Van();
	// Create an SUV object with default construct, and store a pointer to it
	SUV * suv = new SUV();
	// Create an SUV object using copy construct, and store a pointer to it
	SUV * suv2 = new SUV(*suv);
	// How many Vehicle objects so far? 3.
	cout << Vehicle::count() << endl;
	// Display some of the attributes of the Van object
	cout << van->id() << " " << van->make() << " " <<
	     van->number_seats() << endl;
	// Ditto for one of the SUV objects. Note the need for "FourWheelDriveVehicle::junk()"
	// instead of simply "junk()". This is because SUV has two associated junk() methods. Why?
	cout << suv->id() << " " << suv->PersonalVehicle::junk() <<
	     " " << suv->FourWheelDriveVehicle::junk() << endl;
	// Set a pointer to Vehicle variable to point to one of the Vans.
	Vehicle *v = van;
	// The behavior of the next four instructions should no longer surprise you.
	v -> drive();
	van -> drive();
	v -> vDrive();
	van -> vDrive();
	suv -> vDrive();
	suv2 -> vDrive();
	Vehicle* v2 = v -> clone();
	v2 -> vDrive();
}


                                                                                                                                                                                                                   vehicle/vehicle_stuff.txt                                                                           0100666 0053363 0024461 00000101073 10136053465 017100  0                                                                                                    ustar   Mike Rieck                      mkgroup_l_d                                                                                                                                                                                                            

The makefile:


#Definitions

OBJS1=main.oo Vehicle.oo Van.oo PersonalVehicle.oo FourWheelDriveVehicle.oo SUV.oo
      OBJS2=main.o Vehicle.o Van.o PersonalVehicle.o FourWheelDriveVehicle.o SUV.o


#Dependency rules

            drive1 :
            $ {OBJS1}
            g++ $ {OBJS1} -o drive1
            main.oo :
            main.cpp SUV.hpp PersonalVehicle.hpp FourWheelDriveVehicle.hpp Van.hpp Vehicle.hpp
            g++ -c main.cpp -o main.oo
            SUV.oo :
            SUV.cpp SUV.hpp PersonalVehicle.hpp FourWheelDriveVehicle.hpp Vehicle.hpp
            g++ -c SUV.cpp -o SUV.oo
            PersonalVehicle.oo :
            PersonalVehicle.cpp PersonalVehicle.hpp Vehicle.hpp
            g++ -c PersonalVehicle.cpp -o PersonalVehicle.oo
            FourWheelDriveVehicle.oo :
            FourWheelDriveVehicle.cpp FourWheelDriveVehicle.hpp Vehicle.hpp
            g++ -c FourWheelDriveVehicle.cpp -o FourWheelDriveVehicle.oo
            Van.oo :
            Van.cpp Van.h Vehicle.hpp
            g++ -c Van.cpp -o Van.oo
            Vehicle.oo :
            Vehicle.cpp Vehicle.hpp
            g++ -c Vehicle.cpp -o Vehicle.oo

            drive2 :
            $ {OBJS2}
            cc $ {OBJS2} -o drive2
            main.o :
            main.c SUV.h PersonalVehicle.h FourWheelDriveVehicle.h Van.h Vehicle.h
            cc -c main.c
            SUV.o :
            SUV.c SUV.h PersonalVehicle.h FourWheelDriveVehicle.h Vehicle.h
            cc -c SUV.c
            PersonalVehicle.o :
            PersonalVehicle.c PersonalVehicle.h Vehicle.h
            cc -c PersonalVehicle.c
            FourWheelDriveVehicle.o :
            FourWheelDriveVehicle.c FourWheelDriveVehicle.h Vehicle.h
            cc -c FourWheelDriveVehicle.c
            Van.o :
            Van.cpp Van.h Vehicle.h
            cc -c Van.c
            Vehicle.o :
            Vehicle.c Vehicle.h
            cc -c Vehicle.c

            clean:
            rm -f $ {OBJS1} $ {OBJS2} drive1 drive2

            all:
            drive1 drive2





            /* main.cpp */

#include <iostream>
#include "Van.hpp"
#include "SUV.hpp"

            using namespace std;

main()
{

	// Create a van object with default construct, and store a pointer to it
	Van * van = new Van();
	// Create an SUV object with default construct, and store a pointer to it
	SUV * suv = new SUV();
	// Create an SUV object using copy construct, and store a pointer to it
	SUV * suv2 = new SUV(*suv);
	// How many Vehicle objects so far? 3.
	cout << Vehicle::count() << endl;
	// Display some of the attributes of the Van object
	cout << van->id() << " " << van->make() << " " <<
	     van->number_seats() << endl;
	// Ditto for one of the SUV objects. Note the need for "FourWheelDriveVehicle::junk()"
	// instead of simply "junk()". This is because SUV has two associated junk() methods. Why?
	cout << suv->id() << " " << suv->PersonalVehicle::junk() <<
	     " " << suv->FourWheelDriveVehicle::junk() << endl;
	// Set a pointer to Vehicle variable to point to one of the Vans.
	Vehicle *v = van;
	// The behavior of the next four instructions should no longer surprise you.
	v -> drive();
	van -> drive();
	v -> vDrive();
	van -> vDrive();
	suv -> vDrive();
	suv2 -> vDrive();
	Vehicle* v2 = v -> clone();
	v2 -> vDrive();
}



/* Vehicle.hpp */

#ifndef __Vehicle__
#define __Vehicle__

#include <string.h>

class Vehicle {

	// There is only one _count variable, not one per object
	static int _count;

	// "protected" means "public" to any code inside the definition of any class derived from
	// Vehicle, but "private" to all other outside code.

protected:

	// Some member data (instance variables, attributes)
	int _id;
	char _make[16];
	char _model[16];
	char _color[16];

public:

	// Mutator methods
	void id_(int i) {
		_id = i;
	}
	void make_(const char *s) {
		strcpy(_make, s);
	}
	void model_(const char *s) {
		strcpy(_model, s);
	}
	void color_(const char *s) {
		strcpy(_color, s);
	}

	// Assignment operator. Similar to copy constructor, but doesn't create a new object, but
	// rather, changes the object stored in an existing Vehicle variable.
	Vehicle& operator= (Vehicle const& v);

	// Declare default constructor
	Vehicle();
	// Declare copy constructor
	Vehicle(const Vehicle& v);
	// Declare destructor as a virtual function to help select appropriate destructor at run-time
	virtual ~Vehicle();
	// Static function to get value of static variable
	static int count() {
		return _count;
	}
	// Accessor methods
	int id() {
		return _id;
	}
	const char * make() const {
		return _make;
	}
	const char * model() const {
		return _model;
	}
	const char * color() const {
		return _color;
	}
	// Silly method
	void drive();
	// A virtual function version of the same thing
	virtual void vDrive();
	// Will be defining the index operator for this class
	virtual Vehicle* clone();
	char operator[](int n);
	// Will be defining comparison operator to compare two Vehicle objects.
	// Note that this is not a member function (method). It is declared to be a
	// "friend" of the Vehicle class and so can access private and protected data.
	friend bool operator==(Vehicle const &v1, Vehicle const &v2);
};

#endif

/* Vehicle.cpp */

#include <iostream>
#include "Vehicle.hpp"

// Needed to use iostream

using namespace std;

// Initialize static variable
int Vehicle::_count = 0;

// Define default constructor

Vehicle::Vehicle()
{
	id_(++_count);
	make_("unknown");
	model_("unknown");
	color_("unknown");
}

// Define copy constructor. All data of new object will be same as
// old object, except for the _id

Vehicle::Vehicle(const Vehicle& v)
{
	id_(++_count);
	make_(v.make());
	model_(v.model());
	color_(v.color());
}

// Define silly drive method
void Vehicle::drive()
{
	cout << "We are driving a Vehicle." << endl;
}

// Ditto, but for the virtual function version
void Vehicle::vDrive()
{
	cout << "We are virtually driving a Vehicle." << endl;
}

Vehicle* Vehicle::clone()
{
	Vehicle* p = new Vehicle(*this);
	p->id_(_id);
	return p;
}

// Trivially define the destructor
Vehicle::~Vehicle() { }

// Define the index operator is a silly way. It will return a
// character in the _color variable (for no good reason).

char Vehicle::operator[](int n)
{

	return _color[n];
}

// Define comparison operator. Originally it compared the two _id 's.
// Now it compares the other data instead. Get used to looking at Boolean
// data and Boolean operators in a computational way.

bool operator==(Vehicle const& v1, Vehicle const& v2)
{
//    return (v1._id == v2._id);
	return (
	           strcmp(v1._make,v2._make) == 0 &&
	           strcmp(v1._model,v2._model) == 0 &&
	           strcmp(v1._color,v2._color) == 0
	       );
}



/* Van.hpp */


#ifndef __Van__
#define __Van__

#include "Vehicle.hpp"

// Van is derived from Vehicle, so a Van object is conceptually also a
// Vehicle object. At the implementation level, A Van object contains all the
// data for a Vehicle object, plus extra data.

class Van : public Vehicle {

protected:

	// More member data
	int _number_seats;
	double _payload_capacity;

	// more mutator methods
	void number_seats_(int n) {
		_number_seats = n;
	}
	void payload_capacity_(double x) {
		_payload_capacity = x;
	}

	// assignment operator
	Van& operator= (const Van& v);

public:

	// Declare the usual things and implement some of them
	Van();
	Van(const Van& v);
	virtual ~Van();
	int number_seats() {
		return _number_seats;
	}
	double payload_capacity() {
		return _payload_capacity;
	}
	void drive();
	virtual void vDrive();
	virtual Vehicle* clone();
	friend bool operator==(Van const &v1, Van const &v2);
};

#endif


/* Van.cpp */

#include <iostream>
#include "Van.hpp"

using namespace std;

// Notice how Vehicle constructors are invoked in Van constructors
Van::Van() : Vehicle()
{
	number_seats_(0);
	payload_capacity_(0);
}

Van::Van(const Van& v) : Vehicle(v)
{
	number_seats_(v._number_seats);
	payload_capacity_(v._payload_capacity);
}

Van::~Van() { }

void Van::drive()
{

	cout << "We are driving a Van." << endl;
}

void Van::vDrive()
{

	cout << "We are virtually driving a Van." << endl;
}

Vehicle* Van::clone()
{

	Vehicle* p = new Van(*this);
	p->id_(_id);
	return p;
}

// Notice how Vehicle == operator is used when defining Van == operator

bool operator==(Van const &v1, Van const &v2)
{

	return (
	           (Vehicle)v1 == (Vehicle)v2 &&
	           v1._number_seats == v2._number_seats &&
	           v1._payload_capacity == v2._payload_capacity
	       );
}


/* PersonalVehicle.hpp */


#ifndef __PersonalVehicle__
#define __PersonalVehicle__

#include "Vehicle.hpp"

// The reason that Personal... is "virtually" derived from Vehicle is to later
// avoid redundant data when SUV is multiply derived from Four... and Personal...
class PersonalVehicle : virtual public Vehicle {

protected:

	int _junk;
	/* Pretend some useful stuff is here */

public:

	PersonalVehicle();
	PersonalVehicle(const PersonalVehicle& v);
	virtual ~PersonalVehicle();
	void drive();
	virtual void vDrive();
	virtual Vehicle* clone();
	int junk() {
		return _junk;
	}
	/* Pretend more good stuff follows */
};

#endif


/* PersonalVehicle.cpp */

#include "PersonalVehicle.hpp"
#include <iostream>

using namespace std;

PersonalVehicle::PersonalVehicle() : Vehicle(), _junk(22) { }

PersonalVehicle::PersonalVehicle(const PersonalVehicle& v)
		:  Vehicle(v), _junk(22) { }

PersonalVehicle::~PersonalVehicle() { }

void PersonalVehicle::drive()
{
	cout << "We are driving a Personal Vehicle." << endl;
}

void PersonalVehicle::vDrive()
{
	cout << "We are virtually driving a Personal Vehicle." << endl;
}

Vehicle* PersonalVehicle::clone()
{
	Vehicle* p = new PersonalVehicle(*this);
	p->id_(_id);
	return p;
}


/* FourWheelDriveVehicle.hpp */


#ifndef __FourWheelDriveVehicle__
#define __FourWheelDriveVehicle__

#include "Vehicle.hpp"

// The reason that Four... is "virtually" derived from Vehicle is to later
// avoid redundant data when SUV is multiply derived from Four... and Personal...
class FourWheelDriveVehicle : virtual public Vehicle {

protected:

	int _junk;
	/* Pretend some useful stuff is here */

public:

	FourWheelDriveVehicle();
	FourWheelDriveVehicle(const FourWheelDriveVehicle& v);
	virtual ~FourWheelDriveVehicle();
	void drive();
	virtual void vDrive();
	virtual Vehicle* clone();
	int junk() {
		return _junk;
	}
	/* Pretend more good stuff follows */
};

#endif



/* FourWheelDriveVehicle.cpp */

#include "FourWheelDriveVehicle.hpp"
#include <iostream>

using namespace std;

FourWheelDriveVehicle::FourWheelDriveVehicle() : Vehicle(), _junk(33) { }

FourWheelDriveVehicle::FourWheelDriveVehicle(const FourWheelDriveVehicle& v)
		: Vehicle(v), _junk(33) { }

FourWheelDriveVehicle::~FourWheelDriveVehicle() { }

void FourWheelDriveVehicle::drive()
{
	cout << "We are driving a Four Wheel Drive Vehicle." << endl;
}

void FourWheelDriveVehicle::vDrive()
{
	cout << "We are virtually driving a Four Wheel Drive Vehicle." << endl;
}

Vehicle* FourWheelDriveVehicle::clone()
{
	Vehicle* p = new FourWheelDriveVehicle(*this);
	p->id_(_id);
	return p;
}


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


/* SUV.cpp */

#include "SUV.hpp"
#include <iostream>

using namespace std;

SUV::SUV() : PersonalVehicle(), FourWheelDriveVehicle() { }

SUV::SUV(const SUV& v) : PersonalVehicle(v), FourWheelDriveVehicle(v) { }

SUV::~SUV() { }

void SUV::drive()
{
	cout << "We are driving an SUV." << endl;
}

void SUV::vDrive()
{
	cout << "We are virtually driving an SUV." << endl;
}

Vehicle* SUV::clone()
{
	Vehicle* p = new SUV(*this);
	p->id_(_id);
	return p;
}



/* main.c */


#include <stdio.h>
#include "Van.h"
#include "SUV.h"

main()
{

	build_vtbl_Vehicle();
	build_vtbl_Van();
	build_vtbl_PersonalVehicle();
	build_vtbl_PersonalVehicle();
	build_vtbl_PersonalVehicle_Vehicle();
	build_vtbl_FourWheelDriveVehicle();
	build_vtbl_FourWheelDriveVehicle_Vehicle();
	build_vtbl_SUV();
	build_vtbl_SUV_Vehicle();
	build_vtbl_SUV_FourWheelDriveVehicle();

	Van* van = Van_new_DefaultConstructor();
	SUV* suv = SUV_new_DefaultConstructor();
	SUV* suv2 = SUV_new_CopyConstructor(suv);
	printf("%d\n", Vehicle_count());
	printf("%d %s %d\n",
	       Vehicle_id(&(van->vehicle)),
	       Vehicle_make(&(van->vehicle)),
	       Van_number_seats(van)
	      );
	printf("%d %d %d\n",
	       Vehicle_id(suv->pVehicle),
	       PersonalVehicle_junk(&(suv->personalVehicle)),
	       FourWheelDriveVehicle_junk(&(suv->fourWheelDriveVehicle))
	      );
	Vehicle* v = (Vehicle*) van;
	Vehicle_drive(v);
	Van_drive(van);

	// virtually invoke vDrive and clone

	void (*fp1)(Vehicle*);
	fp1 = v->_vptr[0];
	(*fp1)(v);

	void (*fp2)(Van*);
	fp2 = van->_vptr[0];
	(*fp2)(van);

	void (*fp3)(SUV*);
	fp3 = suv->_vptr[0];
	(*fp3)(suv);

	v = suv->pVehicle;
	fp1 = v->_vptr[0];
	(*fp1)(v);

	v = suv2->pVehicle;
	fp1 = v->_vptr[0];
	(*fp1)(v);

	Vehicle* (*fp4)(Vehicle*);
	fp4 = v->_vptr[1];
	Vehicle* v2 = (*fp4)(v);
	fp1 = v2->_vptr[0];
	(*fp1)(v2);


}



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



/* Van.c */

#include <stdio.h>
#include "Van.h"

void* _vtbl_Van[2];

void Van_DefaultConstructor(Van* _this)
{
	Vehicle_DefaultConstructor(&(_this->vehicle));
	_this->_vptr = _vtbl_Van;
	_this->vehicle._vptr = _vtbl_Van;
	_this->_number_seats = 0;
	_this->_payload_capacity = 0;
}

Van* Van_new_DefaultConstructor()
{
	Van* p = (Van*) malloc(sizeof(Van));
	Van_DefaultConstructor(p);
	return p;
}

void Van_CopyConstructor(Van* _this, const Van* q)
{
	Vehicle_CopyConstructor(&(_this->vehicle),&(q->vehicle));
	_this->_vptr = _vtbl_Van;
	_this->vehicle._vptr = _vtbl_Van;
	_this->_number_seats = q->_number_seats;
	_this->_payload_capacity = q->_payload_capacity;
}

Van* Van_new_CopyConstructor(const Van* q)
{
	Van* p = (Van*) malloc(sizeof(Van));
	Van_CopyConstructor(p,q);
	return p;
}

void Van_number_seats_(Van* _this, int n)
{
	_this->_number_seats = n;
}

void payload_capacity_(Van* _this, double x)
{
	_this->_payload_capacity = x;
}

int Van_number_seats(Van* _this)
{
	return _this->_number_seats;
}

double Van_payload_capacity(Van* _this)
{
	return _this->_payload_capacity;
}

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


/* FourWheelDriveVehicle.c */

#include <stdio.h>
#include "FourWheelDriveVehicle.h"

void* _vtbl_FourWheelDriveVehicle[2];
void* _vtbl_FourWheelDriveVehicle_Vehicle[2];

void FourWheelDriveVehicle_DefaultConstructor (FourWheelDriveVehicle* _this, Vehicle* vp)
{
	if (vp==0) {
		_this->pVehicle = (Vehicle*)((char*)_this+sizeof(FourWheelDriveVehicle));
		Vehicle_DefaultConstructor(_this->pVehicle);
	} else
		_this->pVehicle = vp;
	_this->_vptr = _vtbl_FourWheelDriveVehicle;
	_this->pVehicle->_vptr = _vtbl_FourWheelDriveVehicle_Vehicle;
	_this->_junk = 23;
}

FourWheelDriveVehicle* FourWheelDriveVehicle_new_DefaultConstructor()
{
	FourWheelDriveVehicle* p;
	p = (FourWheelDriveVehicle*) malloc(sizeof(FourWheelDriveVehicle) + sizeof(Vehicle));
	FourWheelDriveVehicle_DefaultConstructor(p, 0);
	return p;
}

void FourWheelDriveVehicle_CopyConstructor
(FourWheelDriveVehicle* _this, const FourWheelDriveVehicle* q, Vehicle* vp)
{
	if (vp==0) {
		_this->pVehicle = (Vehicle*)((char*)_this+sizeof(FourWheelDriveVehicle));
		Vehicle_CopyConstructor(_this->pVehicle, q->pVehicle);
	} else
		_this->pVehicle = vp;
	_this->_vptr = _vtbl_FourWheelDriveVehicle;
	_this->pVehicle->_vptr = _vtbl_FourWheelDriveVehicle_Vehicle;
	_this->_junk = q->_junk;
}

FourWheelDriveVehicle* FourWheelDriveVehicle_new_CopyConstructor(const FourWheelDriveVehicle* q)
{
	FourWheelDriveVehicle* p;
	p = (FourWheelDriveVehicle*) malloc(sizeof(FourWheelDriveVehicle) + sizeof(Vehicle));
	FourWheelDriveVehicle_CopyConstructor(p, q, 0);
	return p;
}

int FourWheelDriveVehicle_junk(FourWheelDriveVehicle* _this)
{
	return _this->_junk;
}

void FourWheelDriveVehicle_drive(FourWheelDriveVehicle* _this)
{
	printf("We are driving a Four Wheel Drive Vehicle.\n");
}

void FourWheelDriveVehicle_vDrive(FourWheelDriveVehicle* _this)
{
	printf("We are virtually driving a Four Wheel Drive Vehicle.\n");
}

Vehicle* FourWheelDriveVehicle_clone(FourWheelDriveVehicle* _this)
{
	FourWheelDriveVehicle* p = FourWheelDriveVehicle_new_CopyConstructor(_this);
	Vehicle_id_(p->pVehicle, _this->pVehicle->_id);
	return p->pVehicle;
}

void FourWheelDriveVehicle_Vehicle_thunk_vDrive(Vehicle* _this)
{
	FourWheelDriveVehicle_vDrive
	((FourWheelDriveVehicle*)((char*)_this - sizeof(FourWheelDriveVehicle)));
}

Vehicle* FourWheelDriveVehicle_Vehicle_thunk_clone(Vehicle* _this)
{
	return FourWheelDriveVehicle_clone
	       ((FourWheelDriveVehicle*)((char*)_this - sizeof(FourWheelDriveVehicle)));
}

void build_vtbl_FourWheelDriveVehicle()
{
	_vtbl_FourWheelDriveVehicle[0] = (void*) & FourWheelDriveVehicle_vDrive;
	_vtbl_FourWheelDriveVehicle[1] = (void*) & FourWheelDriveVehicle_clone;
}

void build_vtbl_FourWheelDriveVehicle_Vehicle()
{
	_vtbl_FourWheelDriveVehicle_Vehicle[0] =
	    (void*) & FourWheelDriveVehicle_Vehicle_thunk_vDrive;
	_vtbl_FourWheelDriveVehicle_Vehicle[1] =
	    (void*) & FourWheelDriveVehicle_Vehicle_thunk_clone;
}



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

void SUV_drive(SUV* _this)
{

	printf("We are driving an SUV.\n");
}

void SUV_vDrive(SUV* _this)
{

	printf("We are virtually driving an SUV.\n");
}

Vehicle* SUV_clone(SUV* _this)
{

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

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     