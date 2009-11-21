/////////////////////////////////////////////////////////////////////////////
//
//	CHARGESERVICE.CPP : Credit Card Charger Service class
//
//	Copyright (c) 2003 KnowX.com, All Rights Reserved
//

#include "stdafx.h"
#include "common.h"
#include "config.h"
#include "conn.h"
#include "msg.h"
#include "ccprocess.h"
#include "wthread.h"
#include "ChargeService.h"
#include "registrar.h"
#include "elog.h"
#include "proto.h"
#include "payflow.h"

/////////////////////////////////////////////////////////////////////////////
ChargeService::ChargeService()
		: Service("Credit Card Charger Service"), config("backend.ini")
{
	Registrar::RegisterEventSource();
	pool.Initialize(&config, 0);
	PayFlow::init();
}

/////////////////////////////////////////////////////////////////////////////
ChargeService::~ChargeService()
{
}

/////////////////////////////////////////////////////////////////////////////
void ChargeService::OnStop()
{
	pool.Shutdown();
	PayFlow::cleanup();
	Service::OnStop();
}

/////////////////////////////////////////////////////////////////////////////
void ChargeService::Run()
{
	if (!conn.listen(DEFAULT_PORT, SOMAXCONN)) {
		EventLog::logerr("ChargeService::Run() listen error : %s",
		                 lasterror().c_str());
		return;
	}

	WorkerThread worker(this);
	worker.Start();

	// Call the base class implementation
	Service::Run();
}

/////////////////////////////////////////////////////////////////////////////
DWORD ChargeService::Execute(LPVOID pdata)
{
	for (;;) {
		Connection remote(conn.accept());
		remote.release();	// ownership in another thread
		pool.QueueRequest(&remote);
	}

	return 0;
}
