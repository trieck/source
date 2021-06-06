#pragma once
#include <afxmt.h>

class LockGuard
{
public:
    explicit LockGuard(CSyncObject& syncObject) : m_object(syncObject)
    {
        m_object.Lock();
    }

    ~LockGuard()
    {
        m_object.Unlock();
    }

private:
    CSyncObject& m_object;
};
