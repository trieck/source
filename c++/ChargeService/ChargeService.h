/////////////////////////////////////////////////////////////////////////////
//
//	CHARGESERVICE.H : Credit Card Charger Service class
//
//	Copyright (c) 2003 KnowX.com, All Rights Reserved
//

#ifndef __CHARGESERVICE_H__
#define __CHARGESERVICE_H__

#include "service.h"

/////////////////////////////////////////////////////////////////////////////
class ChargeService : public Service, IRunnable {
// Construction
public:
	ChargeService();
	virtual ~ChargeService();

// Interface
	HANDLE GetEvent() const;
	const Configuration *GetConfig() const;

// Implementation
protected:
	virtual void OnStop();
	virtual void Run();

private:
	DWORD Execute(LPVOID pdata);
	Configuration config;
	Connection conn;
	CThreadPool<CCProcess> pool;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __CHARGESERVICE_H__
