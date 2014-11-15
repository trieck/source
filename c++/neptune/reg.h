///////////////////////////////////////////////////////////////////////////////// REG.H : Win32 registry class//#ifndef __REG_H__#define __REG_H__/////////////////////////////////////////////////////////////////////////////class RegKey {public:// Construction / Destruction    RegKey();    ~RegKey();// Interface    bool open(HKEY hOpenKey, LPCTSTR name, REGSAM mask);    bool queryValue(LPCTSTR name, LPTSTR data, LPDWORD size);    bool queryValue(LPCTSTR name, DWORD & value);    bool isOpen() const;// implementationprotected:    void close();    operator HKEY();private:    HKEY hKey;};/////////////////////////////////////////////////////////////////////////////inline RegKey::operator HKEY(){    return hKey;}inline bool RegKey::isOpen() const{    return hKey != 0;}#endif // __REG_H__