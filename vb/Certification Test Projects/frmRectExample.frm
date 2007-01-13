VERSION 4.00
Begin VB.Form frmRectExample 
   BackColor       =   &H00C0FFFF&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Rectangle Example"
   ClientHeight    =   3510
   ClientLeft      =   2385
   ClientTop       =   1965
   ClientWidth     =   4455
   Height          =   3915
   Icon            =   "frmRectExample.frx":0000
   Left            =   2325
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3510
   ScaleWidth      =   4455
   Top             =   1620
   Width           =   4575
End
Attribute VB_Name = "frmRectExample"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Dim HasCapture As Boolean
Private Sub Form_Load()
    HasCapture = False
End Sub

Private Sub Form_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    StartPoint.X = X
    StartPoint.Y = Y
    EndPoint.X = X
    EndPoint.Y = Y
    Me.DrawMode = vbNotXorPen
    HasCapture = True
End Sub


Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If HasCapture Then
        Me.Line (StartPoint.X, StartPoint.Y)- _
            (EndPoint.X, EndPoint.Y), , B
        Me.Line (StartPoint.X, StartPoint.Y)- _
            (X, Y), , B
        EndPoint.X = X
        EndPoint.Y = Y
    End If
End Sub


Private Sub Form_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Not HasCapture Then Exit Sub
    Me.Line (StartPoint.X, StartPoint.Y)- _
        (EndPoint.X, EndPoint.Y), , B
    EndPoint.X = X
    EndPoint.Y = Y
    SetRect RECT1, StartPoint.X, StartPoint.Y _
        , EndPoint.X, EndPoint.Y
    HasCapture = False
    Me.DrawMode = vbCopyPen
    Me.Refresh
End Sub


Private Sub Form_Paint()
    Me.Line (RECT1.Left, RECT1.Top)- _
        (RECT1.Right, RECT1.Bottom), , B
End Sub


