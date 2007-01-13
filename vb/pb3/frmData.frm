VERSION 5.00
Begin VB.Form frmData 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Phone Book Data"
   ClientHeight    =   3675
   ClientLeft      =   2070
   ClientTop       =   1965
   ClientWidth     =   5160
   Icon            =   "frmData.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   ScaleHeight     =   3675
   ScaleWidth      =   5160
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   4320
      TabIndex        =   16
      Top             =   3240
      Width           =   735
   End
   Begin VB.TextBox txtData 
      Height          =   285
      Index           =   7
      Left            =   2640
      TabIndex        =   13
      Top             =   2880
      Width           =   2415
   End
   Begin VB.TextBox txtData 
      Height          =   285
      Index           =   6
      Left            =   120
      TabIndex        =   12
      Top             =   2880
      Width           =   2415
   End
   Begin VB.TextBox txtData 
      Height          =   285
      Index           =   5
      Left            =   3480
      TabIndex        =   11
      Top             =   2280
      Width           =   1575
   End
   Begin VB.TextBox txtData 
      Height          =   285
      Index           =   4
      Left            =   2640
      TabIndex        =   9
      Top             =   2280
      Width           =   735
   End
   Begin VB.TextBox txtData 
      Height          =   285
      Index           =   3
      Left            =   120
      TabIndex        =   8
      Top             =   2280
      Width           =   2415
   End
   Begin VB.TextBox txtData 
      Height          =   975
      Index           =   2
      Left            =   120
      MultiLine       =   -1  'True
      TabIndex        =   4
      Top             =   960
      Width           =   4935
   End
   Begin VB.TextBox txtData 
      Height          =   285
      Index           =   1
      Left            =   2640
      TabIndex        =   3
      Top             =   360
      Width           =   2415
   End
   Begin VB.TextBox txtData 
      Height          =   285
      Index           =   0
      Left            =   120
      TabIndex        =   1
      Top             =   360
      Width           =   2415
   End
   Begin VB.Label lblBusPhone 
      Caption         =   "Business Phone:"
      Height          =   255
      Left            =   2640
      TabIndex        =   15
      Top             =   2640
      Width           =   2415
   End
   Begin VB.Label lblHomePhone 
      Caption         =   "Home Phone:"
      Height          =   255
      Left            =   120
      TabIndex        =   14
      Top             =   2640
      Width           =   2415
   End
   Begin VB.Label lblZip 
      Caption         =   "Zip:"
      Height          =   255
      Left            =   3480
      TabIndex        =   10
      Top             =   2040
      Width           =   1335
   End
   Begin VB.Label lblState 
      Caption         =   "State:"
      Height          =   255
      Left            =   2640
      TabIndex        =   7
      Top             =   2040
      Width           =   615
   End
   Begin VB.Label lblCity 
      Caption         =   "City:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   2040
      Width           =   1935
   End
   Begin VB.Label lblAddress 
      Caption         =   "Address:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   720
      Width           =   2415
   End
   Begin VB.Label lblFirstName 
      Caption         =   "First Name:"
      Height          =   255
      Left            =   2640
      TabIndex        =   2
      Top             =   120
      Width           =   1575
   End
   Begin VB.Label lblLastName 
      Caption         =   "Last Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1575
   End
End
Attribute VB_Name = "frmData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim bDirty As Boolean
Public Sub ClearText()
    Dim i As Integer
    For i = 0 To txtData.UBound
        txtData(i).Text = ""
    Next
End Sub

Private Sub cmdExit_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    bDirty = False
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    If (bDirty) Then
        Dim msg$
        msg$ = "Record has changed." & vbCrLf
        msg$ = msg$ & "Do you wish to save your changes?"
        If (MsgBox(msg$, vbYesNo + vbQuestion, "Save Changes") = vbYes) Then
            Call glbPB.DoUpdate(Me.Tag, txtData)
        End If
    End If
End Sub

Private Sub txtData_KeyPress(Index As Integer, KeyAscii As Integer)
        bDirty = True
        If (KeyAscii = Asc("'")) Then
            KeyAscii = 0
        End If
End Sub


