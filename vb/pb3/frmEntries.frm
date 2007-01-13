VERSION 5.00
Begin VB.Form frmEntries 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Matching Entries"
   ClientHeight    =   3810
   ClientLeft      =   2955
   ClientTop       =   2370
   ClientWidth     =   3345
   Icon            =   "frmEntries.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   3810
   ScaleWidth      =   3345
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdCancel 
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   2400
      TabIndex        =   2
      Top             =   3360
      Width           =   855
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   3360
      Width           =   855
   End
   Begin VB.ListBox lstEntries 
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3180
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3135
   End
End
Attribute VB_Name = "frmEntries"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub ColorButton1_Click()

End Sub


Private Sub cmdCancel_Click()
    Unload Me
End Sub


Private Sub cmdOK_Click()
    If lstEntries.ListIndex >= 0 Then
    '   Clear out text
        frmData.ClearText
                
        ' Get the data
        Dim vArray As Variant
        vArray = glbPB.GetData(lstEntries.ItemData(lstEntries.ListIndex))
        
        ' Populate the form
        If (IsArray(vArray)) Then
            Dim i As Integer
            frmData.Tag = vArray(0)
            For i = 0 To UBound(vArray) - 1
                frmData!txtData(i) = vArray(i + 1)
            Next i
        End If
        mdiMain.sbarMain.SimpleText = lstEntries
        frmData.WindowState = vbNormal
    End If
End Sub


Private Sub Form_Load()
    FormCenter Me, mdiMain
End Sub


Private Sub lstEntries_DblClick()
    cmdOK_Click
End Sub


