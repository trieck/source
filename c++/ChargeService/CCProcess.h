/////////////////////////////////////////////////////////////////////////////
//
// CCPROCESS.H : Credit Card Process Worker Thread
//
// Copyright(c) 2003 KnowX.com, All Rights Reserved
//

#ifndef __CCPROCESS_H__
#define __CCPROCESS_H__

/////////////////////////////////////////////////////////////////////////////
class CCProcess {
public:
	CCProcess();
	~CCProcess();
	typedef Connection * RequestType;
	BOOL Initialize(void* pv);
	void Execute(RequestType request, void* pv, OVERLAPPED* pOverlapped);
	void Terminate(void* pv);
private:
	static DWORD WINAPI WorkerFunction(LPVOID);

	const Configuration *pconfig;
	Message Dispatch(Message &request);
	string host;
	int port, timeout;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __CCPROCESS_H__