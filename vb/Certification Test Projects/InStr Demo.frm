VERSION 4.00
Begin VB.Form frmInStrDemo 
   BackColor       =   &H00800000&
   Caption         =   "InStr Demo"
   ClientHeight    =   2115
   ClientLeft      =   3315
   ClientTop       =   1710
   ClientWidth     =   3615
   ForeColor       =   &H00800000&
   Height          =   2550
   Left            =   3255
   LinkTopic       =   "Form1"
   ScaleHeight     =   2115
   ScaleWidth      =   3615
   Top             =   1335
   Width           =   3735
   Begin VB.TextBox txtStartPos 
      Height          =   375
      Left            =   1800
      TabIndex        =   1
      Top             =   840
      Width           =   1215
   End
   Begin VB.Label lblOutput 
      BackColor       =   &H00808000&
      ForeColor       =   &H00FFFFFF&
      Height          =   495
      Left            =   480
      TabIndex        =   3
      Top             =   1440
      Width           =   2655
   End
   Begin VB.Label lblStartPos 
      BackColor       =   &H00800000&
      Caption         =   "Starting Position:"
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   600
      TabIndex        =   2
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label lblString 
      BackColor       =   &H00400000&
      Caption         =   "xxOxxxOxxOxOx"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   18
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   495
      Left            =   480
      TabIndex        =   0
      Top             =   120
      Width           =   2655
   End
End
Attribute VB_Name = "frmInStrDemo"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub Label1_Click()

End Sub


Private Sub txtStartPos_KeyPress(KeyAscii As Integer)
Dim SearchString As String, SoughtString As String, FoundPos _
    As Integer, StartPos As Integer
If KeyAscii = 13 Then
    If IsNumeric(txtStartPos.Text) Then
        If txtStartPos.Text < 14 And txtStartPos > 0 Then
            StartPos = Val(txtStartPos.Text)
            SearchString = lblString.Caption
            SoughtString = "O"
            FoundPos = InStr(StartPos, SearchString, SoughtString, 1)
            If FoundPos <> 0 Then
                lblOutput.Caption = "Found string at position: " & Str$(FoundPos)
            Else
                lblOutput.Caption = "String Not Found."
            End If
        Else
            MsgBox "Please enter a value between 1 and 13."
            txtStartPos.SetFocus
            Exit Sub
        End If
    Else
        MsgBox "Please enter something numeric."
        txtStartPos.SetFocus
        Exit Sub
    End If
End If
End Sub


