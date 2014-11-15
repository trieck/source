/////////////////////////////////////////////////////////////////////////////
//
// FILE.H : Win32 file class abstraction
//

#ifndef __FILE_H__
#define __FILE_H__

/////////////////////////////////////////////////////////////////////////////
class File {
public:
    enum openMode {
        unknown = 0,
        readOnly,
        readWrite,
        create
    };
    enum Console {
        StdIn = 0,
        StdOut,
        StdErr
    };
    enum Type {
        unknownType = 0,
        diskType,
        charType,
        pipeType
    };
    enum moveMethod {
        begin = 0,
        current,
        end
    };
    typedef auto_ptr<File> FilePtr;

// Construction / Destruction
    File(LPCTSTR filename, openMode M);
    virtual ~File();
protected:
    File(HANDLE hfile);
public:
    static const _int64 seekFailure;

// operations
    static tstring getTempFileName();
    static bool remove(LPCTSTR filename);
    static FilePtr getConsole(File::Console c);

    void close();
    bool isOpen() const;
    DWORD read(LPVOID pbuff, DWORD size);
    bool readLine(LPTSTR line, DWORD maxsize);
    tstring gulp();
    DWORD write(LPCTSTR str);
    _int64 size() const;
    _int64 seek(_int64 pos, File::moveMethod m);
    File::Type getType() const;

protected:
// implementation
    bool open();
    operator HANDLE() const;
private:
    HANDLE hFile;
    tstring filename;
    openMode mode;
    enum { blocksize = 4096 };
};
/////////////////////////////////////////////////////////////////////////////

inline bool File::isOpen() const
{
    return hFile != NULL;
}
inline File::operator HANDLE () const
{
    return hFile;
}

#endif // __FILE_H__