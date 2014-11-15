/////////////////////////////////////////////////////////////////////////////
//
//	COMMAND.H : command line information
//	serves different needs than CCommandLineInfo
//
//	Copyright(c) 2000, UPS Logistics, All Rights Reserved
//

#ifndef __COMMAND_H__
#define __COMMAND_H__

/////////////////////////////////////////////////////////////////////////////
class CommandLine {
public:
// Construction / Destruction
    CommandLine();
    ~CommandLine();

// Interface
    LPCTSTR getArg(int N) const;
    int size() const;

// Implementation
protected:
private:
    int m_size;
};
/////////////////////////////////////////////////////////////////////////////

inline int CommandLine::size() const
{
    return m_size;
}

#endif // __COMMAND_H__