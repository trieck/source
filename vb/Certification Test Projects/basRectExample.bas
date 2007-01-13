Attribute VB_Name = "basRectExample"
Option Explicit
#If Win32 Then
Declare Function SetRect Lib "user32" _
(lpRect As RECT, ByVal X1 As Long, _
ByVal Y1 As Long, ByVal X2 As Long, _
ByVal Y2 As Long) As Long
Type RECT
    Left As Long
    Top As Long
    Right As Long
    Bottom As Long
End Type
Type POINTAPI
    X As Long
    Y As Long
End Type
#Else
Declare Sub SetRect Lib "user" _
(lpRect As RECT, _
ByVal X1 As Integer, _
ByVal Y1 As Integer, _
ByVal X2 As Integer, ByVal Y2 As Integer)
Type RECT
    Left As Integer
    Top As Integer
    Right As Integer
    Bottom As Integer
End Type
Type POINTAPI
    X As Integer
    Y As Integer
End Type
#End If
Public StartPoint As POINTAPI
Public EndPoint As POINTAPI
Public RECT1 As RECT
