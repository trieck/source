VERSION 4.00
Begin VB.Form frmFile 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Files"
   ClientHeight    =   3630
   ClientLeft      =   2625
   ClientTop       =   2205
   ClientWidth     =   3870
   Height          =   4035
   Icon            =   "file.frx":0000
   Left            =   2565
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3630
   ScaleWidth      =   3870
   ShowInTaskbar   =   0   'False
   Top             =   1860
   Width           =   3990
   Begin VB.TextBox txtData 
      Height          =   3375
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   120
      Width           =   3615
   End
End
Attribute VB_Name = "frmFile"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    FileRead
End Sub


