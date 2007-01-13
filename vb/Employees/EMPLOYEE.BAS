Attribute VB_Name = "basEmployees"
Option Explicit
Declare Function GetSysColor Lib "User32" (ByVal nIndex As Integer) As Long
Global Const COLOR_ACTIVEBORDER = 10
Global Const COLOR_WINDOW = 5
Global Const COLOR_WINDOWTEXT = 8
Type EmployeeType
    Name As String * 20
    Title As String * 20
    Status As Integer
    Salary As Currency
    Age As Integer
    DOH As String * 8
    NumChildren As Integer
    Attrib As Integer
End Type
Global MyEmployees As EmployeeType
Type IndexType
    FullName As String
    RecNum As Integer
End Type
Global MyIndex() As IndexType

    
    

