Attribute VB_Name = "basMain"
Option Explicit

' Global functions and declarations
Private Const Hexish = "0123456789abcdef"
Private register_form As frmRegisters
Private main_form As frmMain
Private CPU As cls6502

' Main entry point
'
Public Sub Main()
    Call Init
End Sub

' Initialization
'
Private Sub Init()
    Dim splash As frmSplash
    
    ' Initialize global objects
    Set CPU = New cls6502
    Set register_form = New frmRegisters
    Set main_form = New frmMain
    
    Set splash = New frmSplash
    splash.Show
                
    Load register_form
    Load main_form
    
    Do While (True)
        DoEvents
        If (splash.Complete) Then Exit Do
    Loop
    
    Unload splash

    main_form.Show
    
End Sub

Public Sub ExitApplication()
    Unload register_form
    Unload main_form
    
    Set register_form = Nothing
    Set main_form = Nothing
End Sub

Public Sub ToggleRegisterBtn()
    Call main_form.mnuRegisters_Click
End Sub

Public Sub ToggleRegisterView()
    register_form.Visible = Not register_form.Visible
End Sub

Public Function GetCPU() As cls6502
    Set GetCPU = CPU
End Function

' Convert byte to two-digit hex string
'
Public Function Byte2Hex(val As Byte) As String
    Dim lo As Byte, hi As Byte
    lo = val And &HF
    hi = (val And &HF0) / &H10
    Byte2Hex = Mid$(Hexish, hi + 1, 1) & _
        Mid(Hexish, lo + 1, 1)
End Function

' Convert one or two-digit hex string to byte
'
Public Function Hex2Byte(ByVal val As String) As Byte
   
    Dim b As Byte
    
    Dim lo As Integer, hi As Integer
    If (Len(val) = 1) Then  ' leading zero
        lo = Asc(Mid$(val, 1, 1))
    Else
        lo = Asc(Mid$(val, 2, 1))
        hi = Asc(Mid$(val, 1, 1))
    End If
    
    Dim i As Integer
    For i = 1 To Len(Hexish)
        If (Asc(Mid$(Hexish, i, 1)) = lo) Then
            b = b Or (i - 1)
            Exit For
        End If
    Next
    
    For i = 1 To Len(Hexish)
        If (Asc(Mid$(Hexish, i, 1)) = hi) Then
            b = b Or ((i - 1) * &H10)
            Exit For
        End If
    Next
    
    Hex2Byte = b
End Function


Public Function ValidateHexDigit(KeyAscii As Integer) As Integer
    Dim i As Integer
    For i = 1 To Len(Hexish)
        If (Asc(Mid$(Hexish, i, 1)) = KeyAscii) Then
            ValidateHexDigit = KeyAscii
            Exit Function
        End If
    Next
    
    ValidateHexDigit = 0
End Function




