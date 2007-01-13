VERSION 4.00
Begin VB.Form frmPhoneBook2 
   BackColor       =   &H00808000&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Tom's Phone Book"
   ClientHeight    =   4260
   ClientLeft      =   1125
   ClientTop       =   1740
   ClientWidth     =   7890
   ForeColor       =   &H00000000&
   Height          =   4950
   Left            =   1065
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4260
   ScaleWidth      =   7890
   Top             =   1110
   Width           =   8010
   Begin VB.CommandButton cmdLetter 
      Caption         =   "Z"
      Height          =   375
      Index           =   25
      Left            =   7455
      TabIndex        =   38
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "Y"
      Height          =   375
      Index           =   24
      Left            =   7095
      TabIndex        =   37
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "X"
      Height          =   375
      Index           =   23
      Left            =   6735
      TabIndex        =   36
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "W"
      Height          =   375
      Index           =   22
      Left            =   6375
      TabIndex        =   35
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "V"
      Height          =   375
      Index           =   21
      Left            =   6015
      TabIndex        =   34
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "U"
      Height          =   375
      Index           =   20
      Left            =   5655
      TabIndex        =   33
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "T"
      Height          =   375
      Index           =   19
      Left            =   5295
      TabIndex        =   32
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "S"
      Height          =   375
      Index           =   18
      Left            =   4935
      TabIndex        =   31
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "R"
      Height          =   375
      Index           =   17
      Left            =   4575
      TabIndex        =   30
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "Q"
      Height          =   375
      Index           =   16
      Left            =   4215
      TabIndex        =   29
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "P"
      Height          =   375
      Index           =   15
      Left            =   3855
      TabIndex        =   28
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "O"
      Height          =   375
      Index           =   14
      Left            =   3495
      TabIndex        =   27
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "N"
      Height          =   375
      Index           =   13
      Left            =   3135
      TabIndex        =   26
      Top             =   360
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "M"
      Height          =   375
      Index           =   12
      Left            =   7455
      TabIndex        =   25
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "L"
      Height          =   375
      Index           =   11
      Left            =   7095
      TabIndex        =   24
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "K"
      Height          =   375
      Index           =   10
      Left            =   6735
      TabIndex        =   23
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "J"
      Height          =   375
      Index           =   9
      Left            =   6375
      TabIndex        =   22
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "I"
      Height          =   375
      Index           =   8
      Left            =   6015
      TabIndex        =   21
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "H"
      Height          =   375
      Index           =   7
      Left            =   5655
      TabIndex        =   20
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "G"
      Height          =   375
      Index           =   6
      Left            =   5295
      TabIndex        =   19
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "F"
      Height          =   375
      Index           =   5
      Left            =   4935
      TabIndex        =   18
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "E"
      Height          =   375
      Index           =   4
      Left            =   4575
      TabIndex        =   17
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "D"
      Height          =   375
      Index           =   3
      Left            =   4215
      TabIndex        =   16
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "C"
      Height          =   375
      Index           =   2
      Left            =   3855
      TabIndex        =   15
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "B"
      Height          =   375
      Index           =   1
      Left            =   3495
      TabIndex        =   14
      Top             =   0
      Width           =   375
   End
   Begin VB.CommandButton cmdLetter 
      Caption         =   "A"
      Height          =   375
      Index           =   0
      Left            =   3135
      TabIndex        =   13
      Top             =   0
      Width           =   375
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   375
      Index           =   5
      Left            =   4800
      TabIndex        =   5
      Top             =   3480
      Width           =   2415
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   375
      Index           =   3
      Left            =   4800
      TabIndex        =   3
      Top             =   2520
      Width           =   1455
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   375
      Index           =   2
      Left            =   4800
      TabIndex        =   2
      Top             =   2040
      Width           =   2415
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   375
      Index           =   1
      Left            =   4800
      TabIndex        =   1
      Top             =   1560
      Width           =   2415
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   615
      Index           =   0
      Left            =   4800
      MultiLine       =   -1  'True
      TabIndex        =   0
      Top             =   840
      Width           =   2415
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H00C0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   375
      Index           =   4
      Left            =   4800
      TabIndex        =   4
      Top             =   3000
      Width           =   2415
   End
   Begin VB.ListBox lstOutputWindow 
      BackColor       =   &H00C0FFFF&
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   2400
      Left            =   120
      TabIndex        =   6
      Top             =   840
      Width           =   2895
   End
   Begin VB.PictureBox pctBackground 
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   765
      Left            =   -150
      ScaleHeight     =   765
      ScaleWidth      =   8175
      TabIndex        =   39
      Top             =   0
      Width           =   8175
   End
   Begin VB.PictureBox ImageList1 
      BackColor       =   &H80000005&
      Height          =   480
      Left            =   6360
      ScaleHeight     =   420
      ScaleWidth      =   1140
      TabIndex        =   42
      Top             =   2400
      Width           =   1200
   End
   Begin VB.PictureBox Toolbar1 
      Height          =   630
      Left            =   0
      ScaleHeight     =   570
      ScaleWidth      =   3075
      TabIndex        =   41
      Top             =   0
      Width           =   3135
   End
   Begin VB.PictureBox sbrOutputBar 
      Align           =   2  'Align Bottom
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   0
      ScaleHeight     =   240
      ScaleWidth      =   7830
      TabIndex        =   40
      Top             =   3960
      Width           =   7890
   End
   Begin VB.Label lblBusPhone 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "Business Phone:"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   8
      Top             =   3600
      Width           =   1575
   End
   Begin VB.Label lblAddress 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "Address:"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   12
      Top             =   840
      Width           =   1575
   End
   Begin VB.Label lblCity 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "City:"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   11
      Top             =   1680
      Width           =   1575
   End
   Begin VB.Label lblState 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "State:"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   10
      Top             =   2160
      Width           =   1575
   End
   Begin VB.Label lblZipCode 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "Zip Code:"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   9
      Top             =   2640
      Width           =   1575
   End
   Begin VB.Label lblHomePhone 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00808000&
      Caption         =   "Home Phone:"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   1
         weight          =   700
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   3120
      TabIndex        =   7
      Top             =   3120
      Width           =   1575
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuExit 
         Caption         =   "&Exit"
      End
   End
   Begin VB.Menu mnuData 
      Caption         =   "&Data"
      Begin VB.Menu mnuAddRecord 
         Caption         =   "&Add a New Record"
      End
      Begin VB.Menu mnuDeleteRecord 
         Caption         =   "&Delete Current Record"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuSaveCurrentRecord 
         Caption         =   "&Save Current Record"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "&About"
      End
   End
End
Attribute VB_Name = "frmPhoneBook2"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

Option Explicit
Dim PhoneRS As Recordset, ReturnRS As Recordset
Dim LetterQuery As QueryDef, FullNameQuery As QueryDef _
    , HalfNameQuery As QueryDef
Dim MyIndex() As IndexType
Dim LetterSQL As String, FullNameSQL As String _
    , NewLast As String, NewFirst As String _
    , NDXNum As Integer, MyID As Integer _
    , CurrentListIndex As Integer _
    , DirtyFlags As Boolean


    Private Sub Show_Record()
        Dim VarIndex(5), i As Integer
        VarIndex(0) = ReturnRS("HOME_STREET")
        VarIndex(1) = ReturnRS("HOME_CITY")
        VarIndex(2) = ReturnRS("HOME_STATE")
        VarIndex(3) = ReturnRS("HOME_POSTAL")
        VarIndex(4) = ReturnRS("HOME_PHONE")
        VarIndex(5) = ReturnRS("BUSINESS_PHONE")
        For i = 0 To 5
            If IsNull(VarIndex(i)) Then
                VarIndex(i) = ""
            End If
            txtOutput(i).Enabled = True
            txtOutput(i).Text = VarIndex(i)
        Next
        txtOutput(0).SetFocus
    End Sub

Private Sub cmdLetter_Click(Index As Integer)
    Dim SearchString As String, MyPanel As Panel
    Dim i As Integer, j As Integer
    
    frmPhoneBook2.MousePointer = 11 'Show Hourglass
    
    NDXNum = Index 'No Bold on all buttons
        For i = 0 To 25
            cmdLetter(i).FontBold = False
        Next i
        For j = 0 To 5 'Clear Text Boxes
            txtOutput(j).Text = ""
        Next j
    For Each MyPanel In sbrOutputBar.Panels 'Clear Status
        MyPanel.Text = ""
    Next MyPanel
    
    SearchString = Chr$(65 + Index) + "*" 'Base Query on a function of the index
    LetterQuery.Parameters![Letter Wanted] = SearchString
    Set ReturnRS = LetterQuery.OpenRecordset() 'Get Return Set
    Show_Output
    cmdLetter(Index).FontBold = True 'Bold the active button
    mnuDeleteRecord.Enabled = False
    Toolbar1.Buttons(3).Enabled = False 'No Delete
    frmPhoneBook2.MousePointer = 0 'Back to Default pointer
End Sub

Private Sub Form_Load()
    pctBackground.BackColor = GetSysColor(COLOR_ACTIVEBORDER)
    Me.MousePointer = 11
    Set LetterQuery = PhoneDB.QueryDefs("Letter Query")
    Set FullNameQuery = PhoneDB.QueryDefs("FullName Query")
    Set HalfNameQuery = PhoneDB.QueryDefs("HalfName Query")
    DirtyFlags = False
    Me.MousePointer = 0
End Sub




Private Sub Show_Output()
    Dim TotalRec As Integer, RecText As String, i As Integer
    
    TotalRec = 0
    lstOutputWindow.Clear
    For i = 0 To 5
        txtOutput(i).Enabled = False
    Next i
    Do Until ReturnRS.EOF
        ReDim Preserve MyIndex(TotalRec)
        MyIndex(TotalRec).LastName = ReturnRS("LAST_NAME")
        MyIndex(TotalRec).FirstName = ReturnRS("FIRST_NAME")
        If MyIndex(TotalRec).FirstName <> "" Then
            lstOutputWindow.AddItem MyIndex(TotalRec).LastName + ", " + MyIndex(TotalRec).FirstName
        Else
            lstOutputWindow.AddItem MyIndex(TotalRec).LastName
        End If
        ReturnRS.MoveNext
        TotalRec = TotalRec + 1
    Loop
    If TotalRec <> 1 Then
        RecText = " Records"
    Else
        RecText = " Record"
    End If
    lstOutputWindow.SetFocus
    sbrOutputBar.Panels(3).Text = Str$(TotalRec) + RecText
End Sub


Private Sub lblAddress_Click()

End Sub

Private Sub lstOutputWindow_Click()
    Dim CurrRec As Integer, NLast As String, NFirst As String, _
        i As Integer
    
    On Error GoTo Errhandler
    
    If Not DirtyFlags Then
        CurrRec = lstOutputWindow.ListIndex 'Set Record# = ListIndex Property
    Else
        CurrRec = CurrentListIndex 'Set Record# = Last Record Selected
    End If
    NLast = MyIndex(CurrRec).LastName
    If IsNull(MyIndex(CurrRec).FirstName) Or _
    MyIndex(CurrRec).FirstName = "" Then  'No first Name (for Companies)
        NFirst = ""
        HalfNameQuery.Parameters![LastName Wanted] = NLast
        Set ReturnRS = HalfNameQuery.OpenRecordset()
    Else
        NFirst = MyIndex(CurrRec).FirstName 'Full Name
        FullNameQuery.Parameters![LastName Wanted] = NLast
        FullNameQuery.Parameters![FirstName Wanted] = NFirst
        Set ReturnRS = FullNameQuery.OpenRecordset()
    End If
    MyID = ReturnRS("ID")
    If ReturnRS.RecordCount > 0 Then
        Show_Record
    Else
        MsgBox "No Record Found."
        Exit Sub
    End If
    mnuDeleteRecord.Enabled = True
    Toolbar1.Buttons(3).Enabled = True 'Delete
    sbrOutputBar.Panels(1).Text = Str$(CurrRec + 1)
    sbrOutputBar.Panels(2).Text = "of"
    Exit Sub
Errhandler:
    MsgBox "Error Accessing this Record.", vbOKOnly, "Error#" + Str$(Err)
    For i = 0 To 5
        txtOutput(i).Text = ""
    Next i
End Sub








Private Sub mnuAbout_Click()
    Load frmAbout
    frmAbout.Show vbModal 'vbModal for OLE Servers always
End Sub

Private Sub mnuAddRecord_Click()
    Dim i As Integer, j As Integer, MyPanel As Panel
    
    NewLast = InputBox("Enter a Last Name:", "Add a Record")
    NewLast = Trim(NewLast)
        If NewLast <> "" Then
            NewFirst = InputBox("Enter a First Name:", "Add a Record")
            NewFirst = Trim(NewFirst)
        Else
            txtOutput(0).SetFocus
            Exit Sub
        End If
    For i = 0 To 25 'Turn off buttons when you add
        cmdLetter(i).FontBold = False
        cmdLetter(i).Enabled = False
        
    Next
    For j = 0 To 5  'And clear Text for new entry
        txtOutput(j).Text = ""
    Next j
    For Each MyPanel In sbrOutputBar.Panels 'And also clear status bar
        MyPanel.Text = ""
    Next MyPanel
    lstOutputWindow.Clear
    If NewFirst <> "" Then
        lstOutputWindow.AddItem NewLast + ", " + NewFirst
    Else
        lstOutputWindow.AddItem NewLast + ""
    End If
    lstOutputWindow.Enabled = False 'Disable the list so user can't type in it
    Toolbar1.Buttons(2).Enabled = False 'No New
    Toolbar1.Buttons(3).Enabled = False 'No Delete
    Toolbar1.Buttons(5).Enabled = True  'No Exit
    mnuAddRecord.Enabled = False
    mnuDeleteRecord.Enabled = False
    mnuSaveCurrentRecord.Enabled = True
    For i = 0 To 5
        txtOutput(i).Enabled = True
    Next i
    txtOutput(0).SetFocus
    NewLast = Chr(34) + NewLast + Chr(34)
    NewFirst = Chr(34) + NewFirst + Chr(34)
End Sub

Private Sub mnuDeleteRecord_Click()
    Dim Reply As Integer
    If Not IsNull(MyIndex(lstOutputWindow.ListIndex).FirstName) Then
        Reply = MsgBox("Are you sure you want to delete" + Chr(13) _
            + MyIndex(lstOutputWindow.ListIndex).FirstName + Chr(32) _
            + MyIndex(lstOutputWindow.ListIndex).LastName + "?", vbQuestion _
            + vbYesNo, "Delete Record")
    Else
        Reply = MsgBox("Are you sure you want to delete" + Chr(13) _
            + MyIndex(lstOutputWindow.ListIndex).LastName _
            + "?", vbQuestion + vbYesNo, "Delete Record")
    End If
    If Reply <> 7 Then
        ReturnRS.Delete
        cmdLetter_Click (NDXNum)
    Else
        Exit Sub
    End If
End Sub

Private Sub mnuExit_Click()
    Unload frmPhoneBook2
End Sub


Private Sub mnuSaveCurrentRecord_Click()
    Dim NameString As String, OutputString As String, i As Integer _
        , MidString As String, IndexNum As Integer
    NameString = "INSERT INTO Names (LAST_NAME, FIRST_NAME, HOME_STREET, HOME_CITY, HOME_STATE, HOME_POSTAL, HOME_PHONE, BUSINESS_PHONE) VALUES "
    NameString = NameString + "(" + NewLast + ", " + NewFirst + ", "
        For i = 0 To 5
            If i < 5 Then
                OutputString = OutputString + Chr(34) + Trim(txtOutput(i).Text) + Chr(34) + ", "
            Else
                OutputString = OutputString + Chr(34) + Trim(txtOutput(i).Text) + Chr(34)
            End If
        Next i
    NameString = NameString + OutputString + ");"
    PhoneDB.Execute NameString, dbFailOnError
    For i = 0 To 25 'Enable buttons after save
        cmdLetter(i).Enabled = True
    Next
    lstOutputWindow.Enabled = True
    Toolbar1.Buttons(2).Enabled = True  'Enable New
    Toolbar1.Buttons(3).Enabled = True  'Enable delete
    Toolbar1.Buttons(5).Enabled = False 'Disable Save
    mnuAddRecord.Enabled = True
    mnuDeleteRecord.Enabled = True
    mnuSaveCurrentRecord.Enabled = False
    For i = 0 To 5
        txtOutput(i).Enabled = False
    Next i
    MidString = Mid(NewLast, 2, 1)
    IndexNum = Asc(UCase(MidString)) - 65 'Get The index Number of the key that matches LastName
    cmdLetter_Click (IndexNum) 'Hit it
End Sub


Private Sub Toolbar1_ButtonClick(ByVal Button As Button)
    Select Case Button.Key
    Case "Add"
        mnuAddRecord_Click
    Case "Delete"
        mnuDeleteRecord_Click
    Case "Save"
        mnuSaveCurrentRecord_Click
    Case "Exit"
        mnuExit_Click
    End Select
End Sub


Private Sub txtOutput_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
    If lstOutputWindow.ListIndex >= 0 Then
        DirtyFlags = True
        CurrentListIndex = lstOutputWindow.ListIndex
        Toolbar1.Buttons(5).Enabled = True
        mnuSaveCurrentRecord.Enabled = True
    End If
End Sub


Private Sub txtOutput_LostFocus(Index As Integer)
    Dim Reply As Integer, NLast As String, NFirst As String _
        , i As Integer, MyButton As Button _
        , k As Integer
    
    If TypeOf Screen.ActiveControl Is TextBox Then  'Allow LostFocus between members of Control Array
        Exit Sub
    End If
    
    If DirtyFlags Then 'Check for Edit Mode
        NLast = MyIndex(CurrentListIndex).LastName
        If Not IsNull(MyIndex(CurrentListIndex).FirstName) Then
            NFirst = MyIndex(CurrentListIndex).FirstName
            Reply = MsgBox("Do you want to save your changes to" _
            + vbCrLf _
            + NFirst _
             + Chr(32) + NLast _
             + "?", (vbYesNo + vbQuestion + vbDefaultButton1), "Record has changed!")
        Else
            NFirst = ""
            Reply = MsgBox("Do you want to save your changes to" _
            + vbCrLf _
            + NLast _
             + "?", (vbYesNo + vbQuestion + vbDefaultButton1), "Record has changed!")
        End If
        
        Toolbar1.Buttons(5).Enabled = False
        mnuSaveCurrentRecord.Enabled = False
        
        On Error GoTo Errhandler
        
        If Reply = vbYes Then
        'Define a Recordset to Update Names in the Open Database
            Set PhoneRS = PhoneDB.OpenRecordset("NAMES", dbOpenTable)
            With PhoneRS
                .Index = "PrimaryKey"
                .Seek "=", MyID
                .Edit
                .Fields("HOME_STREET") = Trim(txtOutput(0).Text)
                .Fields("HOME_CITY") = Trim(txtOutput(1).Text)
                .Fields("HOME_STATE") = Trim(txtOutput(2).Text)
                .Fields("HOME_POSTAL") = Trim(txtOutput(3).Text)
                .Fields("HOME_PHONE") = Trim(txtOutput(4).Text)
                .Fields("BUSINESS_PHONE") = Trim(txtOutput(5).Text)
                .Update
            End With
        End If
        DirtyFlags = False
        If TypeOf Screen.ActiveControl Is CommandButton Then
            cmdLetter_Click (Screen.ActiveControl.Index)
        ElseIf TypeOf Screen.ActiveControl Is ListBox Then
            lstOutputWindow_Click
        Else
            For Each MyButton In Toolbar1.Buttons
                If MyButton.Style = 0 And MyButton.Value = 1 Then
                     MyButton.Value = 0
                     Select Case MyButton.Key
                        Case "Add"
                            mnuAddRecord_Click
                        Case "Delete"
                            mnuDeleteRecord_Click
                        Case "Save"
                            Exit For
                        Case "Exit"
                            mnuExit_Click
                        Exit For
                    End Select
                End If
            Next
        End If
    End If
    Exit Sub
Errhandler:
    MsgBox "There was an error writing to Tom's Database", 64, "Error"
End Sub


