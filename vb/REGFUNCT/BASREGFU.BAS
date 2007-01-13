Attribute VB_Name = "basRegFunctions"
Public Const HKEY_CLASSES_ROOT = &H80000000

Declare Function RegOpenKey Lib "shell.dll" _
(ByVal hKey As Long, ByVal lpszSubKey As String, _
lpcb As Long) As Long


Declare Function RegQueryValue Lib "shell.dll" _
(ByVal hKey As Long, ByVal lpszSubKey As String, _
 ByVal lpszValue As String, lpcb As Long) As Long


