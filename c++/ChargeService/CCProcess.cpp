/////////////////////////////////////////////////////////////////////////////
//
// CCPROCESS.CPP : Credit Card Process Worker Thread
//
// Copyright(c) 2003 KnowX.com, All Rights Reserved
//

#include "stdafx.h"
#include "common.h"
#include "msg.h"
#include "connimpl.h"
#include "config.h"
#include "ccprocess.h"
#include "wthread.h"
#include "ChargeService.h"
#include "elog.h"
#include "payflow.h"

/////////////////////////////////////////////////////////////////////////////
CCProcess::CCProcess() : pconfig(0), port(0)
{
}

/////////////////////////////////////////////////////////////////////////////
CCProcess::~CCProcess()
{
}

/////////////////////////////////////////////////////////////////////////////
BOOL CCProcess::Initialize(void* pv)
{
	pconfig = static_cast<Configuration*>(pv);
	host = pconfig->getString("HostAddress", "Charge");
	port = pconfig->getInt("PortNumber", "Charge");
	timeout = pconfig->getInt("Timeout", "Charge");
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void CCProcess::Execute(RequestType pconn, void* pv, OVERLAPPED* pOverlapped)
{
	ConnectionImpl conn(pconn->release()); // take ownership of the socket

	Message request;
	if (!conn.receive(request)) {
		EventLog::logerr("CCProcess::Execute() unable to receive message : %s",
		                 lasterror().c_str());
		return;
	}

	Message response = Dispatch(request);
	if (!conn.send(response)) {
		EventLog::logerr("CCProcess::Execute() unable to send message : %s",
		                 lasterror().c_str());
	}
}

/////////////////////////////////////////////////////////////////////////////
void CCProcess::Terminate(void* pv)
{
}

/////////////////////////////////////////////////////////////////////////////
typedef struct tagMessagePkg {
	tagMessagePkg(string shost, int nport, int ntimeout,
	              const string &srequest, DWORD threadId)
			: host(shost), port(nport), timeout(ntimeout), request(srequest),
			parent(threadId) {}

	tagMessagePkg(const tagMessagePkg &rhs) {
		*this = rhs;
	}
	tagMessagePkg &operator=(const tagMessagePkg &rhs) {
		if (this != &rhs) {
			host = rhs.host;
			request = rhs.request;
			port = rhs.port;
			timeout = rhs.timeout;
			parent = rhs.parent;
		}
		return *this;
	}
	string host, request;
	int port, timeout;
	DWORD parent;

} MessagePkg, *LPMESSAGEPKG;

typedef struct {
	HANDLE hEvent, hEvent2;
} ThreadParam, *LPTHREADPARAM;

/////////////////////////////////////////////////////////////////////////////
Message CCProcess::Dispatch(Message &request)
{
	Message response;
	DWORD threadId;

	ThreadParam params;	// Parameter to worker thread.

	// This event object is used to signal that worker thread message queue
	// is set up.
	params.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// This event object is used to signal that the original thread is
	// no longer waiting on worker thread to complete work.
	params.hEvent2 = CreateEvent(NULL, TRUE, FALSE, NULL);

	// This is the worker thread that performs the call to Verisign.
	// It is passed handles to the above event objects.
	HANDLE hThread = CreateThread(NULL, 0, WorkerFunction, &params, 0, &threadId);

	// Wait forever for worker thread to set up a message queue.
	WaitForSingleObject(params.hEvent, INFINITE);

	// Package up message and post to worker thread.
	MessagePkg *pkg = new MessagePkg(host, port, timeout, request["paramlist"],
	                                 GetCurrentThreadId());
	PostThreadMessage(threadId, WM_USER, (WPARAM)pkg, 0);

	// Wait for timeout period for worker thread to complete.
	if (WaitForSingleObject(hThread, timeout * 2000) == WAIT_TIMEOUT) {
		response["RESULT"] = "-1";
		response["RESPMSG"] = "cc service timeout";
		EventLog::logerr("CCProcess::Dispatch() timeout waiting for response.");
	} else {	// Worker thread completed in alloted time.
		// Receive response message from worker thread.
		MSG msg;
		if (PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE)) {
			GetMessage(&msg, NULL, WM_USER, WM_USER);
			stringmap *presponse = (stringmap *)msg.wParam;
			stringmap::const_iterator it = presponse->begin();
			for ( ; it != presponse->end(); it++) {
				response[(*it).first] = (*it).second;
			}
			// Delete response object, assuming ownership.
			delete presponse;
		}
	}

	// Signal worker thread that we are no longer waiting.
	SetEvent(params.hEvent2);

	// Cleanup
	CloseHandle(hThread);
	CloseHandle(params.hEvent2);
	CloseHandle(params.hEvent);

	return response;
}

/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI CCProcess::WorkerFunction(LPVOID pv)
{
	MSG msg;
	ThreadParam params = *(LPTHREADPARAM)pv;

	// Set up message queue.
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	// Signal parent thread that we have set up the queue.
	SetEvent(params.hEvent);

	// Wait indefinately for the message to arrive.
	if (GetMessage(&msg, NULL, WM_USER, WM_USER)) {
		MessagePkg *pkg = (LPMESSAGEPKG)msg.wParam;
		PayFlow pf(pkg->host, pkg->port, pkg->timeout);

		// Call Verisgn -- this may block indefinately.
		stringmap *response = new stringmap(pf.SubmitTransaction(pkg->request));

		// Check whether parent thread is still waiting on us.
		DWORD rtn = WaitForSingleObject(params.hEvent2, 0);
		if (rtn == WAIT_OBJECT_0 || rtn == WAIT_FAILED) {
			// Parent thread not waiting any longer.
			// Delete response object, assuming ownership.
			delete response;
		} else {
			// Post response back to parent thread.
			PostThreadMessage(pkg->parent, WM_USER, (WPARAM)response, 0);
		}
		delete pkg;
	}

	return 0L;
}