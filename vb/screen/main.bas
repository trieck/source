Attribute VB_Name = "basMain"
Option Explicit

Private Color_Table(4) As Long
Private Type color
    red As Byte
    green As Byte
    blue As Byte
End Type

Private Colors(4) As color
Private screen As New frmScreen

Public Sub main()
    Call Init_Screen
    Call Refresh_Screen
End Sub

Private Sub Init_Screen()
    ' Initialize color table
    Color_Table(1) = &H0
    Color_Table(2) = &HFF0000
    Color_Table(3) = &HFF00
    Color_Table(4) = &HFFFFFF

    ' Initialize colors
    Dim i As Integer
    For i = 1 To 4
        Colors(i).red = 0
        Colors(i).green = 0
        Colors(i).blue = 0
    Next i
    
    screen.pctScreen.BackColor = 1
    screen.Show
    
End Sub

Private Sub Refresh_Screen()

End Sub

Private Sub Update_Screen()

End Sub
