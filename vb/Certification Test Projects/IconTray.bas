Attribute VB_Name = "basIconTray"
Public Declare Function Shell_NotifyIcon _
            Lib "Shell32.dll" _
            Alias "Shell_NotifyIconA" _
            (ByVal dwMessage As Long, _
            lpData As NOTIFYICONDATA) As Long

Public Type NOTIFYICONDATA
    cbSize As Long
    hWnd As Long
    uID As Long
    uFlags As Long
    uCallBackMessage As Long
    hIcon As Long
    szTip As String * 64
End Type

Global t As NOTIFYICONDATA

Global Const NIM_ADD = &H0
Global Const NIM_MODIFY = &H1
Global Const NIM_DELETE = &H2
Global Const NIF_MESSAGE = &H1
Global Const NIF_ICON = &H2
Global Const NIF_TIP = &H4
Global Const WM_MOUSEMOVE = &H200





    

