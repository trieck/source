VERSION 5.00
Begin VB.Form frmOptions 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Component Client"
   ClientHeight    =   2970
   ClientLeft      =   -75
   ClientTop       =   2175
   ClientWidth     =   2055
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "Options.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2970
   ScaleWidth      =   2055
   ShowInTaskbar   =   0   'False
   Visible         =   0   'False
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   315
      Left            =   120
      TabIndex        =   7
      Top             =   2588
      Width           =   1815
   End
   Begin VB.CommandButton cmdFunctions 
      Caption         =   "Get Drive &Space"
      Enabled         =   0   'False
      Height          =   315
      Index           =   4
      Left            =   120
      TabIndex        =   6
      Top             =   2228
      Width           =   1815
   End
   Begin VB.CommandButton cmdFunctions 
      Caption         =   "E&numerate Drives"
      Enabled         =   0   'False
      Height          =   315
      Index           =   3
      Left            =   120
      TabIndex        =   5
      Top             =   1868
      Width           =   1815
   End
   Begin VB.CommandButton cmdFunctions 
      Caption         =   "Get &Time"
      Enabled         =   0   'False
      Height          =   315
      Index           =   1
      Left            =   120
      TabIndex        =   4
      Top             =   962
      Width           =   1815
   End
   Begin VB.CommandButton cmdFunctions 
      Caption         =   "Get D&ateTime"
      Enabled         =   0   'False
      Height          =   315
      Index           =   2
      Left            =   120
      TabIndex        =   3
      Top             =   1320
      Width           =   1815
   End
   Begin VB.CommandButton cmdFunctions 
      Caption         =   "Get &Date"
      Enabled         =   0   'False
      Height          =   315
      Index           =   0
      Left            =   120
      TabIndex        =   2
      Top             =   664
      Width           =   1815
   End
   Begin VB.CommandButton cmdDestroyObject 
      Caption         =   "D&estroy Object"
      Enabled         =   0   'False
      Height          =   315
      Left            =   120
      TabIndex        =   1
      Top             =   366
      Width           =   1815
   End
   Begin VB.CommandButton cmdCreateObject 
      Caption         =   "&Create Object"
      Height          =   315
      Left            =   120
      TabIndex        =   0
      Top             =   68
      Width           =   1815
   End
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public g_cMiscellaneous As Object
Public Function AddListItem(strItem As String)
    If (Len(strItem) > 0) Then
        frmList.lstMain.AddItem strItem
    End If
End Function

Private Sub cmdDestroyObject_Click()
    ' Destroy the object
    Set g_cMiscellaneous = Nothing
    
    Dim vArray As Variant
    Dim i As Integer
    
    vArray = Array(frmList, frmDrives)
    
    For i = 0 To UBound(vArray)
        Unload vArray(i)
        Set vArray(i) = Nothing
    Next i
    
    Dim b As Byte
    For b = 0 To cmdFunctions.UBound
        cmdFunctions(b).Enabled = False
    Next b
    
    cmdCreateObject.Enabled = True
    cmdDestroyObject.Enabled = False
    
    mdiMain.sbarMain.SimpleText = "Object Destroyed."
End Sub


Private Sub cmdExit_Click()
    Unload mdiMain
End Sub


Private Sub cmdFunctions_Click(Index As Integer)
    On Error GoTo ErrTrap
    
    If (Not g_cMiscellaneous Is Nothing) Then
        Select Case Index
            Case 0  ' Get Date
                AddListItem (g_cMiscellaneous.GetDate())
            Case 1  ' Get Time
                AddListItem (g_cMiscellaneous.GetTime())
            Case 2  ' Get Date Time
                AddListItem (g_cMiscellaneous.GetDateTime())
            Case 3  ' Enumerate Drives
                AddListItem (g_cMiscellaneous.EnumDrives())
            Case 4  ' Get Drive Space
                frmDrives.Show
        End Select
    End If
    
    Exit Sub
    
ErrTrap:
    MsgBox Err.Description, vbExclamation, Err.Source
    On Error GoTo 0
End Sub


Private Sub Form_Unload(Cancel As Integer)
    If (Not g_cMiscellaneous Is Nothing) Then
        Set g_cMiscellaneous = Nothing
    End If
End Sub


