
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
        void number_seats_(int n) 
            { _number_seats = n; } 
        void payload_capacity_(double x) 
            { _payload_capacity = x; } 

        // assignment operator 
        Van& operator= (const Van& v); 

    public: 

        // Declare the usual things and implement some of them
        Van(); 
        Van(const Van& v); 
        virtual ~Van(); 
        int number_seats() 
            { return _number_seats; }  
        double payload_capacity() 
            { return _payload_capacity; }  
        void drive(); 
        virtual void vDrive(); 
	virtual Vehicle* clone(); 
        friend bool operator==(Van const &v1, Van const &v2);         
}; 

#endif

