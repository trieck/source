VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.MDIForm mdiMain 
   BackColor       =   &H80000001&
   Caption         =   "Component Automation Client"
   ClientHeight    =   4620
   ClientLeft      =   2295
   ClientTop       =   2280
   ClientWidth     =   6195
   Icon            =   "mdiMain.frx":0000
   LinkTopic       =   "MDIForm1"
   Begin ComctlLib.StatusBar sbarMain 
      Align           =   2  'Align Bottom
      Height          =   315
      Left            =   0
      TabIndex        =   0
      Top             =   4305
      Width           =   6195
      _ExtentX        =   10927
      _ExtentY        =   556
      Style           =   1
      SimpleText      =   ""
      _Version        =   327680
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      MouseIcon       =   "mdiMain.frx":0442
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
         Shortcut        =   ^X
      End
   End
   Begin VB.Menu mnuObject 
      Caption         =   "&Object"
      Begin VB.Menu mnuCreateObject 
         Caption         =   "Create Object"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuDestroyObject 
         Caption         =   "Destroy Object"
         Shortcut        =   ^D
      End
   End
   Begin VB.Menu mnuFunctions 
      Caption         =   "F&unctions"
      Begin VB.Menu mnuGetDate 
         Caption         =   "Get Date"
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuGetTime 
         Caption         =   "Get Time"
         Shortcut        =   ^T
      End
      Begin VB.Menu mnuGetDateTime 
         Caption         =   "Get DateTime"
         Shortcut        =   ^I
      End
      Begin VB.Menu mnuEnumDrives 
         Caption         =   "Enumerate Drives"
         Shortcut        =   ^E
      End
      Begin VB.Menu mnuDriveSpace 
         Caption         =   "Get Drive Space"
         Shortcut        =   ^S
      End
   End
End
Attribute VB_Name = "mdiMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private m_obj As CMiscellaneous
Private m_functionMenus As Variant

Private Sub EnableFunctionMenus(f As Boolean)
    Dim i As Integer
    
    For i = 0 To UBound(m_functionMenus)
        m_functionMenus(i).Enabled = f
    Next i
End Sub

Public Function GetObject() As CMiscellaneous
    Set GetObject = m_obj
End Function

Private Function IsFormLoaded(FormName As String) As Boolean
    Dim X As Form
    
    Dim f As Boolean
    
    f = False
    
    For Each X In Forms
        If X.Name = FormName Then
            f = True
            Exit For
        End If
    Next
    
    IsFormLoaded = f
    
End Function

Private Function IsNothing(p As Object) As Boolean
    IsNothing = (p Is Nothing)
End Function

Private Sub SetCreateMenus(f As Boolean)
    ' f represents whether to enable
    ' the creation of objects
    
    mnuCreateObject.Enabled = f
    mnuDestroyObject.Enabled = Not (f)
End Sub

Private Sub MDIForm_Load()
    ' Set the function menus
    
    m_functionMenus = Array(mnuGetDate, mnuGetTime, _
                        mnuGetDateTime, mnuEnumDrives, _
                        mnuDriveSpace)
                        
    ' Initially disable function menus
    EnableFunctionMenus (False)
    
    ' Set initial state of creation menus
    SetCreateMenus (True)
End Sub


Private Sub MDIForm_Resize()
    If (IsFormLoaded("frmList")) Then
        If frmList.WindowState = vbNormal Then
            With frmList
                .Left = 0
                .Top = 0
                .Width = Me.ScaleWidth
                .Height = Me.ScaleHeight
            End With
        End If
    End If
End Sub


Private Sub MDIForm_Unload(Cancel As Integer)
    If Not IsNothing(m_obj) Then
        Set m_obj = Nothing
    End If
End Sub

Private Sub mnuCreateObject_Click()
    ' Create an instance of the object
    Set m_obj = New CMiscellaneous
    
    Dim f As Boolean
    f = Not IsNothing(m_obj)
    
    EnableFunctionMenus (f)
    SetCreateMenus (Not f)
    
    If (f) Then
        With frmList
            .Show
            .Left = 0
            .Top = 0
            .Width = Me.ScaleWidth
            .Height = Me.ScaleHeight
        End With
        sbarMain.SimpleText = "Object Created."
    Else
        sbarMain.SimpleText = "Object not created."
    End If

End Sub


Private Sub mnuDestroyObject_Click()
    ' Destroy the object
    Set m_obj = Nothing
    
    EnableFunctionMenus (False)
    SetCreateMenus (True)
    
    Unload frmList
    Unload frmDrives
    
    sbarMain.SimpleText = "Object Destroyed."
End Sub

Private Sub mnuDriveSpace_Click()
    frmDrives.Show
End Sub

Private Sub mnuEnumDrives_Click()
    AddListItem (m_obj.EnumDrives())
End Sub

Private Sub mnuExit_Click()
    Unload Me
End Sub


Private Sub mnuGetDate_Click()
    AddListItem (m_obj.GetDate())
End Sub


Public Function AddListItem(strItem As String)
    If (Len(strItem) > 0) Then
        frmList.lstMain.AddItem strItem
    End If
End Function


Private Sub mnuGetDateTime_Click()
    AddListItem (m_obj.GetDateTime())
End Sub

Private Sub mnuGetTime_Click()
    AddListItem (m_obj.GetTime())
End Sub


