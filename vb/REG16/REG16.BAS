Attribute VB_Name = "REG161"
Global Const HKEY_CLASSES_ROOT = 1

Declare Function RegOpenKey Lib "shell.dll" (ByVal hKey As Long, ByVal szSubKey As String, hNewKey As Long) As Long
Declare Function RegQueryValue Lib "shell.dll" (ByVal hKey As Long, ByVal szSubKey As String, ByVal szBuffer As String, lSize As Long) As Long
Declare Function RegEnumKey Lib "shell.dll" (ByVal hKey As Long, ByVal Index As Long, ByVal szBuffer As String, lSize As Long) As Long


