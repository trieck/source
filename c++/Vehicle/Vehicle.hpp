	
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
        void id_(int i) 
            { _id = i; } 
        void make_(const char *s) 
            { strcpy(_make, s); }
        void model_(const char *s) 
            { strcpy(_model, s); }
        void color_(const char *s) 
            { strcpy(_color, s); }

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
        static int count() { return _count; } 
        // Accessor methods 
        int id() { return _id; } 
        const char * make() const { return _make; }
        const char * model() const { return _model; }
        const char * color() const { return _color; }
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
