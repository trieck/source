VERSION 5.00
Begin VB.Form frmDrives 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Select Drive"
   ClientHeight    =   975
   ClientLeft      =   3255
   ClientTop       =   2295
   ClientWidth     =   4290
   Icon            =   "Drives.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   ScaleHeight     =   975
   ScaleWidth      =   4290
   Begin VB.CommandButton cmdCancel 
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   3480
      TabIndex        =   2
      Top             =   540
      Width           =   735
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   3480
      TabIndex        =   1
      Top             =   120
      Width           =   735
   End
   Begin VB.ComboBox cboDrives 
      Height          =   315
      Left            =   120
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   120
      Width           =   3315
   End
End
Attribute VB_Name = "frmDrives"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim m_obj As CMiscellaneous
Private Function LoadDrives()
    
    Debug.Assert (Not m_obj Is Nothing)
    
    Dim strDrives As String
    
    strDrives = m_obj.EnumDrives
    
    Debug.Assert (Len(strDrives) > 0)
    
    Dim pos As Integer
    Dim nPos As Integer
    Dim strTemp As String
    
    pos = InStr(strDrives, "~~")
    
    nPos = 1
    
    While (pos > 0 And nPos < pos)
        strTemp = Mid$(strDrives, nPos, 3)
        cboDrives.AddItem strTemp
        nPos = nPos + 4
    Wend
    
    ' Default first item
    If (cboDrives.ListCount > 0) Then
        cboDrives.ListIndex = 0
    End If
    
End Function

Private Sub cmdCancel_Click()
    Unload Me
End Sub


Private Sub cmdOK_Click()
    If (cboDrives.ListIndex > -1) Then
        Dim lBytes As Long
        Dim strDrive As String
                        
        strDrive = cboDrives.List(cboDrives.ListIndex)
        
        Debug.Assert (Len(strDrive) > 0)
        Debug.Assert (Not m_obj Is Nothing)
        
        lBytes = m_obj.GetDriveSpace(strDrive)
        
        mdiMain.AddListItem ( _
            "Drive: " & strDrive & lBytes & " Bytes Free.")
     End If
End Sub

Private Sub Form_Load()

    Set m_obj = mdiMain.GetObject()
    
    LoadDrives

    FormCenter Me, mdiMain
End Sub


Private Sub Form_Unload(Cancel As Integer)
    Set m_obj = Nothing
End Sub


