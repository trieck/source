Attribute VB_Name = "basGetProfile"
#If Win32 Then
    Declare Function GetProfileString Lib "kernel32" Alias "GetProfileStringA" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long) As Long
    Declare Function GetProfileSection Lib "kernel32" Alias "GetProfileSectionA" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Long) As Long
    Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
    Declare Function GetPrivateProfileSection Lib "kernel32" Alias "GetPrivateProfileSectionA" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
    Declare Function WriteProfileString Lib "kernel32" Alias "WriteProfileStringA" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Long
    Declare Function WriteProfileStringForNewSection Lib "kernel32" Alias "WriteProfileStringA" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Long
    Declare Function WriteProfileStringForNewKey Lib "kernel32" Alias "WriteProfileStringA" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Long
    Declare Function WriteProfileStringToDeleteSection Lib "kernel32" Alias "WriteProfileStringA" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Long
    Declare Function WriteProfileStringToDeleteKey Lib "kernel32" Alias "WriteProfileStringA" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Long
    Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Long
    Declare Function WritePrivateProfileStringForNewSection Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Long
    Declare Function WritePrivateProfileStringForNewKey Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Long
    Declare Function WritePrivateProfileStringToDeleteSection Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Long
    Declare Function WritePrivateProfileStringToDeleteKey Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Long
    Declare Function PostMessageByString Lib "user32" Alias "PostMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As String) As Long
#ElseIf Win16 Then
    Declare Function GetProfileString Lib "kernel" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer) As Integer
    Declare Function GetProfileSection Lib "kernel" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Integer) As Integer
    Declare Function GetPrivateProfileString Lib "kernel" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Integer, ByVal lpFileName As String) As Integer
    Declare Function GetPrivateProfileSection Lib "kernel" (ByVal lpAppName As String, ByVal lpReturnedString As String, ByVal nSize As Integer, ByVal lpFileName As String) As Integer
    Declare Function WriteProfileString Lib "kernel" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Integer
    Declare Function WriteProfileStringForNewSection Lib "kernel" Alias "WriteProfileString" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Integer
    Declare Function WriteProfileStringForNewKey Lib "kernel" Alias "WriteProfileString" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Integer
    Declare Function WriteProfileStringToDeleteSection Lib "kernel" Alias "WriteProfileString" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Integer
    Declare Function WriteProfileStringToDeleteKey Lib "kernel" Alias "WriteProfileString" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Integer
    Declare Function WritePrivateProfileString Lib "kernel" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Integer
    Declare Function WritePrivateProfileStringForNewSection Lib "kernel" Alias "WritePrivateProfileString" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Integer
    Declare Function WritePrivateProfileStringForNewKey Lib "kernel" Alias "WritePrivateProfileString" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Integer
    Declare Function WritePrivateProfileStringToDeleteSection Lib "kernel" Alias "WritePrivateProfileString" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Integer
    Declare Function WritePrivateProfileStringToDeleteKey Lib "kernel" Alias "WritePrivateProfileString" (ByVal lpApplicationName As String, ByVal lpKeyName As String, ByVal lpString As Any, ByVal lpFileName As String) As Integer
    Declare Function PostMessage Lib "user" (ByVal hwnd As Integer, ByVal wMsg As Integer, ByVal wParam As Integer, ByVal lParam As Any) As Integer
#End If
Public Const HWND_BROADCAST = -1
Public Const WM_WININICHANGE = &H1A
Public Const COLOR_BACKGROUND = 1

