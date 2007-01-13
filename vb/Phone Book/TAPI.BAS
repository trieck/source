Attribute VB_Name = "basTapi"
Option Explicit

Declare Function tapiRequestMakeCall& Lib "TAPI32.DLL" (ByVal Destaddress$, ByVal AppName$, ByVal CalledParty$, ByVal comment$)
Public Const TAPIERR_NOREQUESTRECIPIENT = -2&
Public Const TAPIERR_REQUESTQUEUEFULL = -3&

Public Sub DialNumber(sNumber As String, sAppName As String, sName As String)
    Dim nResult As Long
    Dim buff As String
    
    'Request that a number be dialed using
    'assisted Telphony
    
    nResult = tapiRequestMakeCall&(sNumber, sAppName, _
        sName, "")
        
    'The return value indicates the result.  A return value
    'of 0 indicates the request was accepted
    If nResult <> 0 Then
        buff = "Error dialing number : "
        Select Case nResult
            Case TAPIERR_NOREQUESTRECIPIENT
                buff = buff & "Could not find call control application."
            Case TAPIERR_REQUESTQUEUEFULL
                buff = buff & "Call control application is busy."
            Case Else
                buff = buff & "Error " & CStr(nResult) & "."
        End Select
        MsgBox buff
    End If
End Sub


