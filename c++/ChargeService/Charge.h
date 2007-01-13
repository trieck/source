/////////////////////////////////////////////////////////////////////////////
//
// CHARGE.H : Credit Card Charger
//
// Copyright(c) 2003 KnowX.com, All Rights Reserved
//

#ifndef __CHARGE_H__
#define __CHARGE_H__

/////////////////////////////////////////////////////////////////////////////
class Charge 
{
	// Construction / Destruction
private:
	Charge();
public:
	virtual ~Charge();

	typedef auto_ptr<Charge> ChargePtr;

// Interface
	static ChargePtr instance();
	int Run(int argc, char **argv);

// Implementation
private:
	static ChargePtr This;
	Service *pservice;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __CHARGE_H__