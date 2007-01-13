VERSION 4.00
Begin VB.Form frmFileTest 
   Caption         =   "File Test"
   ClientHeight    =   4020
   ClientLeft      =   2760
   ClientTop       =   1560
   ClientWidth     =   4905
   Height          =   4425
   Icon            =   "frmFileTest.frx":0000
   Left            =   2700
   LinkTopic       =   "Form1"
   ScaleHeight     =   4020
   ScaleWidth      =   4905
   Top             =   1215
   Width           =   5025
   Begin VB.FileListBox File1 
      Height          =   3180
      Left            =   2400
      TabIndex        =   2
      Top             =   600
      Width           =   2415
   End
   Begin VB.DirListBox Dir1 
      Height          =   3180
      Left            =   120
      TabIndex        =   1
      Top             =   600
      Width           =   2175
   End
   Begin VB.DriveListBox Drive1 
      Height          =   315
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4695
   End
End
Attribute VB_Name = "frmFileTest"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub Dir1_Change()
    File1.Path = Dir1.Path
End Sub


Private Sub Drive1_Change()
    On Error GoTo ErrHandler
    Dir1.Path = Drive1.Drive
    Exit Sub
ErrHandler:
    If Err = 68 Then
        MsgBox "Device is not available", 0, "Drive Not Ready."
        Drive1.Drive = Dir1.Path
    End If
End Sub


