Attribute VB_Name = "basTimer"
Option Explicit

' Windows API declarations
Public Declare Function SetTimer Lib "user32" _
    (ByVal hWnd As Long, _
    ByVal nIDEvent As Long, _
    ByVal uElapse As Long, _
    ByVal lpTimerFunc As Long) As Long

Public Declare Function KillTimer Lib "user32" _
    (ByVal hWnd As Long, _
    ByVal nIDEvent As Long) As Long
    
Private map As New Dictionary

Public Sub TimerProc(ByVal hWnd As Long, ByVal umsg As Long, _
    ByVal idEvent As Long, ByVal dwtime As Long)
    Call KillTimer(hWnd, idEvent)
    map.Item(hWnd) = True  ' elapsed
End Sub

Public Function TimerHasCompleted(ByVal hWnd As Long) As Boolean
    TimerHasCompleted = map.Item(hWnd)
End Function

Public Function CreateTimer(ByVal hWnd As Long, ByVal ID As Long, _
    ByVal elapse As Long)
    
    CreateTimer = SetTimer(hWnd, ID, elapse, AddressOf TimerProc)
    map.Add hWnd, False
    
End Function

