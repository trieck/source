/////////////////////////////////////////////////////////////////////////////
//
// CHARGE.CPP : Credit Card Charger
//
// Copyright(c) 2003 KnowX.com, All Rights Reserved
//

#include "stdafx.h"
#include "common.h"
#include "config.h"
#include "conn.h"
#include "msg.h"
#include "ccprocess.h"
#include "wthread.h"
#include "ChargeService.h"
#include "Charge.h"

Charge::ChargePtr Charge::This;

/////////////////////////////////////////////////////////////////////////////
Charge::Charge()
{
	pservice = new ChargeService();
}

/////////////////////////////////////////////////////////////////////////////
Charge::~Charge()
{
	delete pservice;
}

/////////////////////////////////////////////////////////////////////////////
Charge::ChargePtr Charge::instance()
{
	if (This.get() == NULL) {
		This = ChargePtr(new Charge());
	}

	return This;
}

/////////////////////////////////////////////////////////////////////////////
int Charge::Run(int argc, char **argv)
{
	pservice->Execute(argc, argv);

	return pservice->GetExitCode();
}

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	Charge::ChargePtr charger =
	    Charge::instance();

	return charger->Run(argc, argv);
}

