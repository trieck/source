/////////////////////////////////////////////////////////////////////////////
//
//	WTHREAD.H : Worker thread
//
//	Copyright(c) 2003, KnowX.com, All Rights Reserved
//

#ifndef __WTHREAD_H__
#define __WTHREAD_H__

/////////////////////////////////////////////////////////////////////////////
// WorkerThread class
class WorkerThread {
// Construction / Destruction
public:
	WorkerThread(IRunnable* pworker, LPVOID pparam = 0)
			: worker(pworker), param(pparam) {
		hThread = CreateThread(NULL, 0, ThreadProc, this,
		                       CREATE_SUSPENDED, 0);
	}

	virtual ~WorkerThread() {
		CloseHandle(hThread);
	}

// Interface
	DWORD Start() {
		return ResumeThread(hThread);
	}
	HANDLE GetThread() const {
		return hThread;
	}

// Implementation
private:
	static DWORD WINAPI ThreadProc(LPVOID instance) {
		WorkerThread *pthis = static_cast<WorkerThread*>(instance);
		return pthis->worker->Execute(pthis->param);
	}

	IRunnable *worker;
	LPVOID param;
	HANDLE hThread;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __WTHREAD_H__