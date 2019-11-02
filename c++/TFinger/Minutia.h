#pragma once

// types of minutia
#define MT_ISOLATED			(0)
#define MT_RIDGE_ENDING		(1)
#define MT_CONT_RIDGE		(2)
#define MT_RIDGE_BIFUR		(3)
#define MT_CROSSING			(4)

class Minutia
{
public:
    Minutia();
    Minutia(const Minutia &rhs);
    ~Minutia();

    Minutia &operator = (const Minutia &rhs);

    int type;	// type of minutia
    int x;		// location
    int y;
};
