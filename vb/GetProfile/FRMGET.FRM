VERSION 5.00
Begin VB.Form frmGetProfile 
   BackColor       =   &H00403200&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "System Profile"
   ClientHeight    =   3840
   ClientLeft      =   1215
   ClientTop       =   2040
   ClientWidth     =   8130
   ForeColor       =   &H00400000&
   Icon            =   "FRMGET.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   Picture         =   "FRMGET.frx":0442
   ScaleHeight     =   3840
   ScaleWidth      =   8130
   Begin VB.CommandButton cmdNewSection 
      Caption         =   "&New Section"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6720
      TabIndex        =   9
      Top             =   840
      Width           =   1335
   End
   Begin VB.CommandButton cmdDeleteSection 
      Caption         =   "&Delete Section"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6720
      TabIndex        =   8
      Top             =   1320
      Width           =   1335
   End
   Begin VB.CommandButton cmdDeleteKey 
      Caption         =   "D&elete Key"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6720
      TabIndex        =   7
      Top             =   2520
      Width           =   1335
   End
   Begin VB.CommandButton cmdNewKey 
      Caption         =   "Ne&w Key"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6720
      TabIndex        =   6
      Top             =   2040
      Width           =   1335
   End
   Begin VB.ListBox lstGetProfile 
      BackColor       =   &H00FFFFFF&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   3180
      Left            =   120
      Sorted          =   -1  'True
      TabIndex        =   5
      Top             =   360
      Width           =   3015
   End
   Begin VB.ListBox lstShowKeys 
      BackColor       =   &H00FFFFFF&
      ForeColor       =   &H00800000&
      Height          =   3180
      Left            =   3240
      Sorted          =   -1  'True
      TabIndex        =   4
      Top             =   360
      Width           =   3375
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   6720
      TabIndex        =   3
      Top             =   3360
      Width           =   1335
   End
   Begin VB.CommandButton cmdShowSections 
      Height          =   375
      Left            =   6720
      TabIndex        =   0
      Top             =   360
      Width           =   1335
   End
   Begin VB.Label lblFileName 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800080&
      Height          =   375
      Left            =   6600
      TabIndex        =   10
      Top             =   0
      Width           =   1575
   End
   Begin VB.Label lblSectionProfile 
      Alignment       =   2  'Center
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      Caption         =   "Profile"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   375
      Left            =   3240
      TabIndex        =   2
      Top             =   0
      Width           =   3375
   End
   Begin VB.Label lblSectionTitle 
      Alignment       =   2  'Center
      BackColor       =   &H00FFFFFF&
      BackStyle       =   0  'Transparent
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   0
      Width           =   3015
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuWIN_INI 
         Caption         =   "WIN.INI"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuSYSTEM_INI 
         Caption         =   "SYSTEM.INI"
      End
      Begin VB.Menu mnuSeparator 
         Caption         =   "-"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
      End
   End
End
Attribute VB_Name = "frmGetProfile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Function VbGetPrivateProfileString(Section$, Key$, File$)
    Dim MyString$
    Dim Characters As Integer
    Dim ReturnString As String
    Dim nSize As Integer
    ReturnString = String$(128, 0)
    nSize = 127
    Characters = GetPrivateProfileString(Section$, Key$, "", ReturnString, nSize, File$)
    MyString$ = Left$(ReturnString, Characters)
    VbGetPrivateProfileString = MyString$
End Function

Function VbGetProfileString(Section$, Key$)
    Dim Characters As Integer
    Dim MyString$
    Dim ReturnString As String
    Dim nSize As Integer
    ReturnString = String$(128, 0)
    nSize = 127
    Characters = GetProfileString(Section$, Key$, "", ReturnString, nSize)
    MyString$ = Left$(ReturnString, Characters)
    VbGetProfileString = MyString$
End Function

Private Sub cmdDeleteKey_Click()
    
    #If Win32 Then
        Dim Reply%, FindEqual%, Key$, Value$ _
        , Success%, Di%
        FindEqual% = InStr(lstShowKeys.Text, "=")
        Key$ = Left(lstShowKeys.Text, FindEqual% - 1)
    #Else
        Dim Success%, Di%
        Key$ = lstShowKeys.Text
    #End If
    Reply% = MsgBox("Are you sure you want to delete the Key named" _
            + vbCr + vbLf + Key$ + "?", vbQuestion + vbYesNo + vbDefaultButton2, "Delete Key")
    If Reply% = 6 Then
        If mnuWIN_INI.Checked Then  'If WIN.INI
            Success% = WriteProfileStringToDeleteKey(lstGetProfile.Text, Key$, vbNullString)
        Else    'If SYSTEM.INI
            Success% = WritePrivateProfileStringToDeleteKey(lstGetProfile.Text _
            , Key$, vbNullString, "SYSTEM.INI")
        End If
        If Success% = 0 Then
            MsgBox "Failure deleting Key."
            Exit Sub
        ElseIf mnuWIN_INI.Checked Then 'Post Message Re: Update to WIN.INI
            #If Win32 Then
                Di% = PostMessageByString(HWND_BROADCAST _
                , WM_WININICHANGE, 0, lstGetProfile.Text)
            #Else
                Di% = PostMessage(HWND_BROADCAST _
                , WM_WININICHANGE, 0, lstGetProfile.Text)
            #End If
            lstGetProfile_Click
        End If
    End If
End Sub


Private Sub cmdDeleteSection_Click()
    Dim Success%, Reply%
    
    Reply% = MsgBox("Are you sure you want to delete the Section named" _
        + vbCr + vbLf + lstGetProfile.Text + "?", vbQuestion + vbYesNo + vbDefaultButton2 _
        , "Delete Section")
    
    If Reply% = 6 Then
        If mnuWIN_INI.Checked Then  'if WIN.INI
            Success% = WriteProfileStringToDeleteSection( _
                lstGetProfile.Text, vbNullString, vbNullString)
        Else    'If SYSTEM.INI
            Success% = WritePrivateProfileStringToDeleteSection( _
                lstGetProfile.Text, vbNullString, vbNullString _
                , "SYSTEM.INI")
        End If
        If Success% = 0 Then
            MsgBox "Error Deleting Section."
        Else
            lstGetProfile.Clear
            lstShowKeys.Clear
            cmdShowSections_Click
        End If
    End If
    
End Sub

Private Sub cmdExit_Click()
    End
End Sub


Private Sub cmdNewKey_Click()
    Dim NewKey$, NewValue$, Success%
    
    NewKey$ = InputBox("Enter Key Name:", "New Key for " + lstGetProfile.Text)
    If NewKey$ = "" Then Exit Sub
    NewKey$ = Trim(NewKey$)
    
    NewValue$ = InputBox("Enter a Value:", "Value for " + NewKey$)
    If NewValue$ = "" Then Exit Sub
    If mnuWIN_INI.Checked Then  'if WIN.INI
        Success% = WriteProfileStringForNewKey(lstGetProfile.Text _
            , NewKey$, NewValue$)
    Else    'If SYSTEM.INI
        Success% = WritePrivateProfileStringForNewKey(lstGetProfile.Text _
            , NewKey$, NewValue$, "SYSTEM.INI")
    End If
    If Success% = 0 Then
        MsgBox "Error writing New Key."
        Exit Sub
    End If
    lstGetProfile_Click
End Sub

Private Sub cmdNewSection_Click()
    Dim Success%, NewName$, MyKeyArray() As String _
        , MyValueArray() As String, NumberOfKeys, i%, j%, k%
    NewName$ = InputBox("Enter a new Section Name:", "New Section")
    If NewName$ = "" Then    'User canceled
        Exit Sub
    Else
KeyInfo:
        NumberOfKeys = InputBox("Enter # of Keys (must be a minimum of 1):", "Number of Keys")
        If NumberOfKeys = "" Then Exit Sub
        If Not IsNumeric(NumberOfKeys) Then
            i% = MsgBox("Please enter a Numeric value.", vbOKOnly, "Non Numeric")
            GoTo KeyInfo
        ElseIf NumberOfKeys < 1 Then
            i% = MsgBox("Please enter a value greater than zero.", vbOKOnly, "Zero value")
            GoTo KeyInfo
        End If
        
        ReDim MyKeyArray(NumberOfKeys)
        ReDim MyValueArray(NumberOfKeys)
        
        For j% = 1 To NumberOfKeys
            MyKeyArray(j%) = InputBox("Enter a Key Name:", "Key #" + Str$(j%))
            MyValueArray(j%) = InputBox("Enter a value:", "Value for " + MyKeyArray(j%))
        Next j%
        
        NewName$ = Trim(NewName$)
        
        For k% = 1 To NumberOfKeys
            If frmGetProfile!mnuWIN_INI.Checked Then    'if WIN.INI
                Success% = WriteProfileStringForNewSection( _
                    NewName$, MyKeyArray(k%), MyValueArray(k%))
            Else    'For SYSTEM.INI
                Success% = WritePrivateProfileStringForNewSection( _
                    NewName$, MyKeyArray(k%), MyValueArray(k%) _
                    , "SYSTEM.INI")
            End If
            If Success% = 0 Then GoTo ErrHandler
        Next k%
        
        lstGetProfile.Clear
        cmdShowSections_Click
        Exit Sub
    End If
ErrHandler:
    MsgBox "There was an error writing the current Section"
End Sub

Private Sub cmdShowSections_Click()
    #If Win32 Then
        Dim Rtn&
        Dim ReturnString As String, nSize As Long
        Dim NullOffset%
        Dim MsgString$
        
        ReturnString = String(512, 0)
        nSize = 512
        If mnuWIN_INI.Checked Then  'WIN.INI Selected
            Rtn& = GetProfileString(vbNullString, vbNullString, "", ReturnString, nSize)
        Else    'SYTEM.INI Selected
            Rtn& = GetPrivateProfileString(vbNullString, vbNullString, "", ReturnString, nSize _
            , "SYSTEM.INI")
        End If
        Do
            NullOffset% = InStr(ReturnString, Chr$(0))
            If NullOffset% > 1 Then
                MsgString$ = Mid$(ReturnString, 1, NullOffset% - 1)
                lstGetProfile.AddItem MsgString$
                ReturnString = Mid$(ReturnString, NullOffset% + 1)
            End If
        Loop While NullOffset% > 1
        cmdShowSections.Enabled = False
        cmdNewSection.Enabled = True
    #Else
        Dim Rtn%
        Dim SectionName$
        Dim ReturnString As String, nSize As Integer
        
        ReturnString = String(512, 0)
        nSize = 512
        SectionName$ = InputBox$("Enter Name of Section:", Me.Caption)
        If SectionName$ = "" Then Exit Sub
        If mnuWIN_INI.Checked Then  'WIN.INI
            Rtn% = GetProfileString(SectionName$, vbNullString, "", ReturnString, nSize)
        Else    'SYSTEM.INI
            Rtn% = GetPrivateProfileString(SectionName$, vbNullString, "", ReturnString _
                    , nSize, "SYSTEM.INI")
        End If
        If Rtn% = 0 Then
            MsgBox "Error reading Section.", vbInformation, Me.Caption
            Exit Sub
        Else
            lstGetProfile.AddItem SectionName$
        End If
    #End If
End Sub

Private Sub Form_Activate()
    lstGetProfile.SetFocus
End Sub

Private Sub Form_Load()
    #If Win32 Then
        cmdShowSections.Caption = "&Show Sections"
        lblSectionTitle.Caption = "Sections"
    #Else
        cmdShowSections.Caption = "&Show Section"
        lblSectionTitle.Caption = "Section"
    #End If
    lblFileName.Caption = "WIN.INI"
End Sub


Public Sub lstGetProfile_Click()
    Dim DevString As String, List$
    Dim StartPos%, EndPos%
    Dim Res$
    
    #If Win32 Then
    Dim Di As Long
    #Else
    Dim Di As Integer
    #End If
    
    cmdDeleteSection.Enabled = True
    cmdNewKey.Enabled = True
    cmdDeleteKey.Enabled = False
    
    DevString = String(4096, 0)
    lstShowKeys.Clear
    List$ = lstGetProfile.Text
    If mnuWIN_INI.Checked Then  'For WIN.INI
        #If Win32 Then
            Di = GetProfileSection(List$, DevString, 4095)
        #Else
            Di = GetProfileString(List$, vbNullString, "", DevString, 4095)
        #End If
    Else    'For SYSTEM.INI
        #If Win32 Then
            Di = GetPrivateProfileSection(List$, DevString, 4095, "SYSTEM.INI")
        #Else
            Di = GetPrivateProfileString(List$, vbNullString, "", DevString, 4095, "SYSTEM.INI")
        #End If
    End If
    If Di = 0 Then
        MsgBox "This section appears to be empty.", vbInformation, "No Info!"
        Exit Sub
    End If
    StartPos% = 1
    Res$ = ""
    Do While Asc(Mid$(DevString, StartPos%, 1)) <> 0
        EndPos% = InStr(StartPos%, DevString, Chr(0))
        Res$ = Res$ + Mid$(DevString, StartPos%, EndPos% - StartPos%)
        StartPos% = EndPos% + 1
        lstShowKeys.AddItem Res$
        Res$ = ""
    Loop
End Sub


Private Sub lstShowKeys_Click()
    cmdDeleteKey.Enabled = True
End Sub

Private Sub lstShowKeys_DblClick()
    #If Win32 Then
        Dim FindEqual%, Key$, Value$
        FindEqual% = InStr(lstShowKeys.Text, "=")
        If FindEqual% <> 0 Then
            Key$ = Left(lstShowKeys.Text, FindEqual% - 1)
            Value$ = Right(lstShowKeys.Text, Len(lstShowKeys.Text) - Len(Key$) - 1)
            Load frmBreakdown
            frmBreakdown.Show vbModal
            frmBreakdown!txtKey.Text = Key$
            frmBreakdown!txtValue.Text = Value$
        End If
    #Else
        Dim Value$
        If mnuWIN_INI.Checked Then
            Value$ = VbGetProfileString(lstGetProfile.Text, lstShowKeys.Text)
        Else
            Value$ = VbGetPrivateProfileString(lstGetProfile.Text, lstShowKeys.Text, "SYSTEM.INI")
        End If
        Load frmBreakdown
        frmBreakdown.Show vbModal
        frmBreakdown!txtKey.Text = lstShowKeys.Text
        frmBreakdown!txtValue.Text = Value$
    #End If
End Sub

Private Sub mnuExit_Click()
    End
End Sub


Private Sub mnuSYSTEM_INI_Click()
    If Not mnuSYSTEM_INI.Checked Then
        mnuSYSTEM_INI.Checked = True
        mnuWIN_INI.Checked = False
        lblFileName.Caption = "SYSTEM.INI"
        If cmdShowSections.Enabled = False Then
            cmdShowSections.Enabled = True
        End If
        lstGetProfile.Clear
        lstShowKeys.Clear
        cmdNewSection.Enabled = False
        cmdDeleteSection.Enabled = False
        cmdNewKey.Enabled = False
        cmdDeleteKey.Enabled = False
    End If
End Sub




Private Sub mnuWIN_INI_Click()
    If Not mnuWIN_INI.Checked Then
        mnuWIN_INI.Checked = True
        mnuSYSTEM_INI.Checked = False
        lblFileName.Caption = "WIN.INI"
        If cmdShowSections.Enabled = False Then
            cmdShowSections.Enabled = True
        End If
        lstGetProfile.Clear
        lstShowKeys.Clear
        cmdNewSection.Enabled = False
        cmdDeleteSection.Enabled = False
        cmdNewKey.Enabled = False
        cmdDeleteKey.Enabled = False
    End If
End Sub
