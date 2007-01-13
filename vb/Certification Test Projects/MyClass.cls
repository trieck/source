VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
END
Attribute VB_Name = "MyClass"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit
Public TitleBar As String
Public XPos As Integer
Public YPos As Integer
Dim NewForm As New Form1
Public Sub ShowForm()
    NewForm.Caption = TitleBar
    NewForm.Left = XPos
    NewForm.Top = YPos
    NewForm.Width = 2050
    NewForm.Height = 3500
    NewForm.Show
End Sub




Private Sub Class_Terminate()
   Unload NewForm
End Sub


