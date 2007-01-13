Attribute VB_Name = "modPhoneModule"
Option Explicit
Declare Function GetSysColor Lib "user32" (ByVal nIndex As Long) As Long
Public Const COLOR_ACTIVEBORDER = 10
'User Defined type that represents an index of
'returned records from a query
Type IndexType
    LastName As Variant
    FirstName As Variant
End Type
Public PhoneDB As Database 'Use to identify current DB



