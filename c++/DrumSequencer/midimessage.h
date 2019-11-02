/////////////////////////////////////////////////////////////////////////////
//
//	MIDIMESSAGE.H : MIDI message module
//
//	Copyright(c) 2011, Thomas A. Rieck, All Rights Reserved
//

#ifndef __MIDIMESSAGE_H__
#define __MIDIMESSAGE_H__

/////////////////////////////////////////////////////////////////////////////
class MidiMessage
{
public:
    // Construction / Destruction
    MidiMessage();
    MidiMessage(DWORD);
    virtual ~MidiMessage();

    // Interface
    inline BYTE GetVelocity() const
    {
        return m_velocity;
    }
    inline BYTE GetData() const
    {
        return m_data;
    }
    inline BYTE GetStatus() const
    {
        return m_status;
    }

    inline void SetVelocity(BYTE b)
    {
        m_velocity = b;
    }
    inline void SetData(BYTE b)
    {
        m_data = b;
    }
    inline void SetStatus(BYTE b)
    {
        m_status = b;
    }

    operator DWORD() const;

protected:
    // Implementation
    BYTE m_velocity;
    BYTE m_data;
    BYTE m_status;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __MIDIMESSAGE_H__