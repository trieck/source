Attribute VB_Name = "basDeviceInfo"
Option Explicit

#If Win32 Then
    Declare Function GetSysColor Lib "user32" _
    (ByVal nIndex As Long) As Long

    Declare Function GetDeviceCaps _
    Lib "gdi32" (ByVal hdc As Long, _
    ByVal nIndex As Long) As Long
#Else
    Declare Function GetSysColor Lib "User" _
    (ByVal nIndex As Integer) As Long

    Declare Function GetDeviceCaps _
    Lib "GDI" (ByVal hdc As Integer, _
    ByVal nIndex As Integer) As Integer
#End If
Public Const COLOR_BACKGROUND = 1
Public Const TECHNOLOGY = 2
Public Const DT_RASDISPLAY = 1
Public Const DT_RASPRINTER = 2
Public Const HORZRES = 8
Public Const VERTRES = 10
Public Const LOGPIXELSX = 88
Public Const LOGPIXELSY = 90
Public Const BITSPIXEL = 12
Public Const NUMCOLORS = 24

