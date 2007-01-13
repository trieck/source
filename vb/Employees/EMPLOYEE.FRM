VERSION 5.00
Begin VB.Form frmEmployees 
   Appearance      =   0  'Flat
   BackColor       =   &H00404000&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Vandelait Importer/Exporters"
   ClientHeight    =   4380
   ClientLeft      =   3780
   ClientTop       =   6315
   ClientWidth     =   5940
   BeginProperty Font 
      Name            =   "Times New Roman"
      Size            =   13.5
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00808080&
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4380
   ScaleWidth      =   5940
   Begin VB.CommandButton cmdCancel 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "&Cancel"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4440
      TabIndex        =   14
      TabStop         =   0   'False
      Top             =   1800
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.TextBox txtEmployeeInfo 
      Appearance      =   0  'Flat
      BackColor       =   &H00E0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   375
      Index           =   2
      Left            =   2400
      TabIndex        =   4
      Top             =   2280
      Width           =   615
   End
   Begin VB.PictureBox pnlEmployee 
      BackColor       =   &H00E0E0E0&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Index           =   2
      Left            =   2280
      ScaleHeight     =   555
      ScaleWidth      =   795
      TabIndex        =   15
      Top             =   2160
      Width           =   855
   End
   Begin VB.TextBox txtEmployeeInfo 
      Appearance      =   0  'Flat
      BackColor       =   &H00E0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   1
      Left            =   2400
      TabIndex        =   3
      Top             =   1560
      Width           =   1095
   End
   Begin VB.PictureBox pnlEmployee 
      BackColor       =   &H00E0E0E0&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Index           =   1
      Left            =   2280
      ScaleHeight     =   555
      ScaleWidth      =   1275
      TabIndex        =   16
      Top             =   1440
      Width           =   1335
   End
   Begin VB.TextBox txtEmployeeInfo 
      Appearance      =   0  'Flat
      BackColor       =   &H00E0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   0
      Left            =   2400
      TabIndex        =   2
      Top             =   840
      Width           =   1815
   End
   Begin VB.PictureBox pnlEmployee 
      BackColor       =   &H00E0E0E0&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   615
      Index           =   0
      Left            =   2280
      ScaleHeight     =   555
      ScaleWidth      =   1995
      TabIndex        =   17
      Top             =   720
      Width           =   2055
   End
   Begin VB.OptionButton optMarried 
      Appearance      =   0  'Flat
      BackColor       =   &H00E0E0E0&
      Caption         =   "Married"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   375
      Left            =   4560
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   1200
      Width           =   975
   End
   Begin VB.OptionButton optSingle 
      Appearance      =   0  'Flat
      BackColor       =   &H00E0E0E0&
      Caption         =   "Single"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   375
      Left            =   4560
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   840
      Width           =   855
   End
   Begin VB.PictureBox pnlOption 
      BackColor       =   &H00E0E0E0&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   4440
      ScaleHeight     =   915
      ScaleWidth      =   1155
      TabIndex        =   18
      Top             =   720
      Width           =   1215
   End
   Begin VB.ComboBox cboEmployeeName 
      Appearance      =   0  'Flat
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
      ForeColor       =   &H00000000&
      Height          =   315
      Left            =   2280
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   105
      Width           =   3375
   End
   Begin VB.TextBox txtEmployeeInfo 
      Appearance      =   0  'Flat
      BackColor       =   &H00E0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   3
      Left            =   2400
      TabIndex        =   5
      Top             =   3000
      Width           =   1095
   End
   Begin VB.TextBox txtEmployeeInfo 
      Appearance      =   0  'Flat
      BackColor       =   &H00E0FFFF&
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   4
      Left            =   2400
      TabIndex        =   6
      Top             =   3720
      Width           =   615
   End
   Begin VB.PictureBox pnlEmployee 
      BackColor       =   &H00E0E0E0&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Index           =   3
      Left            =   2280
      ScaleHeight     =   555
      ScaleWidth      =   1275
      TabIndex        =   19
      Top             =   2880
      Width           =   1335
   End
   Begin VB.PictureBox pnlEmployee 
      BackColor       =   &H00E0E0E0&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Index           =   4
      Left            =   2280
      ScaleHeight     =   555
      ScaleWidth      =   795
      TabIndex        =   20
      Top             =   3600
      Width           =   855
   End
   Begin VB.PictureBox pnlCombo 
      BackColor       =   &H00E0E0E0&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2205
      ScaleHeight     =   435
      ScaleWidth      =   3510
      TabIndex        =   21
      Top             =   0
      Width           =   3570
   End
   Begin VB.PictureBox ToolButton 
      Height          =   330
      Index           =   3
      Left            =   1440
      ScaleHeight     =   270
      ScaleWidth      =   300
      TabIndex        =   22
      Top             =   0
      Width           =   360
   End
   Begin VB.PictureBox ToolButton 
      BackColor       =   &H00004080&
      Enabled         =   0   'False
      Height          =   330
      Index           =   2
      Left            =   960
      ScaleHeight     =   270
      ScaleWidth      =   300
      TabIndex        =   23
      Top             =   0
      Width           =   360
   End
   Begin VB.PictureBox ToolButton 
      Enabled         =   0   'False
      Height          =   330
      Index           =   1
      Left            =   600
      ScaleHeight     =   270
      ScaleWidth      =   300
      TabIndex        =   24
      Top             =   0
      Width           =   360
   End
   Begin VB.PictureBox ToolButton 
      Height          =   330
      Index           =   0
      Left            =   120
      ScaleHeight     =   270
      ScaleWidth      =   300
      TabIndex        =   25
      Top             =   0
      Width           =   360
   End
   Begin VB.Label lblTitle 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H00404000&
      Caption         =   "Title:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00E0FFFF&
      Height          =   255
      Left            =   1680
      TabIndex        =   8
      Top             =   840
      Width           =   495
   End
   Begin VB.Label lblToolbar 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   555
      Left            =   -120
      TabIndex        =   13
      Top             =   0
      Width           =   12120
   End
   Begin VB.Label lblNumChildren 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H00404000&
      Caption         =   "Number of Children:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00E0FFFF&
      Height          =   495
      Left            =   1200
      TabIndex        =   12
      Top             =   3600
      Width           =   975
   End
   Begin VB.Label lblDOH 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H00404000&
      Caption         =   "Date of Hire:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00E0FFFF&
      Height          =   255
      Left            =   960
      TabIndex        =   11
      Top             =   2880
      Width           =   1215
   End
   Begin VB.Label lblAge 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H00404000&
      Caption         =   "Age:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00E0FFFF&
      Height          =   255
      Left            =   1680
      TabIndex        =   10
      Top             =   2160
      Width           =   495
   End
   Begin VB.Label lblSalary 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H00404000&
      Caption         =   "Salary:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00E0FFFF&
      Height          =   255
      Left            =   1560
      TabIndex        =   9
      Top             =   1440
      Width           =   615
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuPrint 
         Caption         =   "&Print"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuData 
      Caption         =   "&Data"
      Begin VB.Menu mnuNew 
         Caption         =   "&New Employee"
      End
      Begin VB.Menu mnuDelete 
         Caption         =   "&Delete Employee"
         Enabled         =   0   'False
      End
   End
End
Attribute VB_Name = "frmEmployees"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit
Dim ActiveRec As Integer
Dim CurrName As String
Dim CurrRec As Integer
Dim NewName As String
Dim ReplaceFlags As Integer
Dim TotalRec As Integer
Dim crlf As String
Dim DirtyFlags As Integer
Dim NewMode As Integer

Private Sub cboEmployeeName_Click()
    Dim i As Integer, Reply As Integer
    'Set CurrName = selected name
    CurrName = cboEmployeeName.Text
    'Check for valid entry
    If CurrName <> "" Then
        i = 1
    'Iterate through Index til match
        Do Until MyIndex(i).FullName = CurrName
            i = i + 1
        Loop
        CurrRec = MyIndex(i).RecNum 'Set CurrRec matching index entry record number
        Get #1, CurrRec, MyEmployees 'Get the record info
        Show_Record    'Display entry based on CurrRec
    End If
    mnuDelete.Enabled = True
    mnuPrint.Enabled = True
    ToolButton(2).Enabled = True  'Enable Delete Employee
    ToolButton(3).Enabled = True 'Enable Printing
    txtEmployeeInfo(0).SetFocus
End Sub

Private Sub cboEmployeeName_DropDown()
    Check_EditMode
End Sub

Private Sub cboEmployeeName_KeyPress(KeyAscii As Integer)
'Don't allow typing in the Combo Box
    KeyAscii = 0
End Sub

Private Sub Check_EditMode()
    Dim Reply As Integer
    If ToolButton(1).Enabled = True Then
        Reply = MsgBox("Do you wish to your changes to" + crlf + Trim(MyEmployees.Name) + "?", 36, "Record has changed")
        If Reply = 6 Then
            Save_Record
        Else
            ToolButton(1).Enabled = False
        End If
    End If
End Sub

Private Sub cmdCancel_Click()
    Dim j As Integer
    NewMode = 0
    cboEmployeeName.Text = ""
    For j = 0 To 4  'Clear all text boxes
        txtEmployeeInfo(j).Text = ""
        txtEmployeeInfo(j).Enabled = False
    Next j
    optSingle.Value = False
    optSingle.Enabled = False
    optMarried.Value = False
    optMarried.Enabled = False
    cboEmployeeName.Enabled = True
    ToolButton(0).Enabled = True    'New Yes
    ToolButton(1).Enabled = False   'Save No
    ToolButton(2).Enabled = False   'Delete No
    ToolButton(3).Enabled = True    'Print Yes
    mnuPrint.Enabled = True
    mnuNew.Enabled = True
    mnuDelete.Enabled = True
    cmdCancel.Visible = False
End Sub

Private Sub Exit_Click()
    Close
    End
End Sub

Private Sub Form_Load()
    Dim i As Integer
    crlf = Chr$(13) + Chr$(10)
    Const Path = "employee.db"
    ' Use the WinAPI to find  the current border color and set the label to match it.
    lblToolbar.BackColor = getSysColor(COLOR_ACTIVEBORDER)
    ' find current window
    cboEmployeeName.BackColor = getSysColor(COLOR_WINDOW)
    cboEmployeeName.ForeColor = getSysColor(COLOR_WINDOWTEXT)
    pnlCombo.BackColor = lblToolbar.BackColor
    pnlOption.BackColor = pnlCombo.BackColor
    optSingle.BackColor = pnlOption.BackColor
    optMarried.BackColor = optSingle.BackColor
    For i = 0 To 4
        pnlEmployee(i).BackColor = lblToolbar.BackColor
        txtEmployeeInfo(i).BackColor = cboEmployeeName.BackColor
        txtEmployeeInfo(i).ForeColor = cboEmployeeName.ForeColor
    Next i
    'Open file, set length equal to User Defined Type.
    Open Path For Random As #1 Len = Len(MyEmployees)
    'Calculate number of records based on length of open file and size of type.
    TotalRec = LOF(1) / Len(MyEmployees)
    If TotalRec > 0 Then
        Index_Records 'Sort Records
    Else
        CurrRec = 1
    End If
    Show_Combo
End Sub

Private Sub Index_Records()
'Use Bubble sort to index
    Dim i As Integer, j As Integer, k As Integer, n As Integer, temp As IndexType
    n = 1
    For i = 1 To TotalRec
        Get #1, i, MyEmployees
        If MyEmployees.Attrib = 1 Then
            ReDim Preserve MyIndex(n)
            MyIndex(n).FullName = Make_Name(MyEmployees.Name)
            MyIndex(n).RecNum = i
            n = n + 1
        End If
    Next i
    ActiveRec = n - 1
    For k = 1 To ActiveRec - 1
        For j = k + 1 To ActiveRec
            If MyIndex(k).FullName > MyIndex(j).FullName Then
                temp = MyIndex(k)
                MyIndex(k) = MyIndex(j)
                MyIndex(j) = temp
            End If
         Next j
    Next k
End Sub

Private Function Make_Name(CurrName As String) As String
    Make_Name = Trim(UCase(CurrName))
End Function

Private Sub mnuDelete_Click()
    Dim Stat As Integer, j As Integer, Reply As Integer
    Reply = MsgBox("Are you sure you want to delete" + crlf + Trim(MyEmployees.Name) + "?", 276, frmEmployees.Caption)
    If Reply = 7 Then
        txtEmployeeInfo(0).SetFocus
        Exit Sub
    End If
    If optSingle Then
            Stat = 0
    Else
            Stat = 1
    End If
    MyEmployees.Attrib = 0
    Put #1, CurrRec, MyEmployees
    cboEmployeeName.Clear
    Index_Records
    Show_Combo
    cboEmployeeName.Text = MyEmployees.Name
    cboEmployeeName.Enabled = True
    ToolButton(0).Enabled = True   'Enable New
    ToolButton(1).Enabled = False  'Disable Save
    ToolButton(2).Enabled = False  'Disable Delete
    ToolButton(3).Enabled = True   'Enable Print
    mnuPrint.Enabled = True
    mnuNew.Enabled = True
    mnuDelete.Enabled = False
    For j = 0 To 4
        txtEmployeeInfo(j).Text = ""
        txtEmployeeInfo(j).Enabled = False
    Next j
    cboEmployeeName.Text = ""
    optSingle.Value = False
    optSingle.Enabled = False
    optMarried.Value = False
    optMarried.Enabled = False
End Sub

Private Sub mnuExit_Click()
    Exit_Click
End Sub

Private Sub mnuNew_Click()
    Dim i As Integer, j As Integer, k As Integer, Reply As Integer
    Check_EditMode
    NewMode = 1
    NewName = InputBox("Enter 'LastName, FirstName'", "New Employee", "")
    If NewName = "" Then Exit Sub
    NewName = Make_Name(NewName) 'Format to All Caps
    For i = 1 To ActiveRec 'Search for existing record name
        If NewName = MyIndex(i).FullName Then
            Reply = MsgBox("You already  have an employee named " + MyIndex(i).FullName + "." + Chr(13) + "Do you wish to overwrite this record?", 276, "Record Exists")
            If Reply = 7 Then
                Exit Sub
            Else
                ReplaceFlags = 1
                GoTo Clear_Form
            End If
        End If
    Next i
Clear_Form:
    For i = 0 To 4
        txtEmployeeInfo(i).Enabled = True
    Next i
    optSingle.Enabled = True
    optMarried.Enabled = True
    cboEmployeeName.Text = NewName
    cboEmployeeName.Enabled = False
    ToolButton(0).Enabled = False
    ToolButton(1).Enabled = True
    ToolButton(2).Enabled = False
    ToolButton(3).Enabled = False
    cmdCancel.Visible = True
    mnuNew.Enabled = False
    mnuDelete.Enabled = False
    mnuPrint.Enabled = False
    optSingle.Value = True
    For j = 0 To 4
        txtEmployeeInfo(j).Text = ""
    Next j
    txtEmployeeInfo(0).SetFocus
End Sub

Private Sub mnuPrint_Click()
'Print List of Records
    Dim i As Integer, MyStatus As String, Children$
    For i = 1 To ActiveRec
        Get #1, MyIndex(i).RecNum, MyEmployees
        If MyEmployees.Status = 0 Then
            MyStatus = "Single"
        Else
            MyStatus = "Married"
        End If
        If MyEmployees.NumChildren = 1 Then
            Children$ = " Child"
        Else
            Children$ = " Children"
        End If
        Printer.Print MyEmployees.Name
        Printer.Print MyEmployees.Title
        Printer.Print MyStatus
        Printer.Print Format$(MyEmployees.Salary, "$###,###")
        Printer.Print "Age "; Trim(MyEmployees.Age)
        Printer.Print Format$(MyEmployees.DOH, "mm/dd/yy")
        Printer.Print Trim(MyEmployees.NumChildren); Children$
        Printer.Print crlf
    Next i
    Printer.EndDoc
End Sub

Private Sub optMarried_Click()
' If current status is single then
' set mode for editing
    If NewMode = 0 Then 'Make sure we are not editing a new employee
        If MyEmployees.Status = 0 Then
            ToolButton(1).Enabled = True
            ToolButton(3).Enabled = False
            mnuPrint.Enabled = False
            ReplaceFlags = 1
        End If
    End If
End Sub

Private Sub optSingle_Click()
' If current status is married then
' set mode for editing
    If NewMode = 0 Then 'Make sure we are not editing a new employee
        If MyEmployees.Status = 1 Then
            ToolButton(1).Enabled = True
            ToolButton(3).Enabled = False
            mnuPrint.Enabled = False
            ReplaceFlags = 1
        End If
    End If
End Sub

Private Sub Save_Record()
    Dim BlankTitle As String, BlankSalary As String, BlankAge As String, BlankDOH As String, BlankNumChildren As String, Stat As Integer
    BlankTitle = (Trim(txtEmployeeInfo(0).Text))
    BlankSalary = (Trim(txtEmployeeInfo(1).Text))
    BlankAge = (Trim(txtEmployeeInfo(2).Text))
    BlankDOH = (Trim(txtEmployeeInfo(3).Text))
    BlankNumChildren = (Trim(txtEmployeeInfo(4).Text))
'Check for blank fields
    If BlankTitle = "" Or BlankSalary = "" Or BlankAge = "" Or BlankDOH = "" Or BlankNumChildren = "" Then
        MsgBox "You must complete all fields.", 16, "Employees"
        txtEmployeeInfo(0).SetFocus
        Exit Sub
    End If
    If optSingle Then
        Stat = 0
    Else
        Stat = 1
    End If
    MyEmployees.Name = Trim(cboEmployeeName.Text)
    MyEmployees.Title = Trim(txtEmployeeInfo(0).Text)
    MyEmployees.Salary = Trim(txtEmployeeInfo(1).Text)
    MyEmployees.Status = Stat
    MyEmployees.Age = Trim(txtEmployeeInfo(2).Text)
    MyEmployees.DOH = Trim(txtEmployeeInfo(3).Text)
    MyEmployees.NumChildren = Trim(txtEmployeeInfo(4).Text)
    MyEmployees.Attrib = 1
    If ReplaceFlags = 0 Then 'If we are NOT replacing move to new record.
        TotalRec = TotalRec + 1
        CurrRec = TotalRec
    End If
    Put #1, CurrRec, MyEmployees
    If ReplaceFlags = 0 Then
        cboEmployeeName.Clear
        Index_Records
        Show_Combo
        cboEmployeeName.Text = MyEmployees.Name
        Show_Record
        cboEmployeeName.Enabled = True
    Else
        Show_Record
    End If
    ToolButton(0).Enabled = True
    ToolButton(1).Enabled = False
    ToolButton(2).Enabled = True
    ToolButton(3).Enabled = True
    cmdCancel.Visible = False
    mnuPrint.Enabled = True
    mnuNew.Enabled = True
    mnuDelete.Enabled = True
    ReplaceFlags = 0
    NewMode = 0
End Sub

Private Sub Show_Combo()
    Dim i As Integer
    For i = 1 To ActiveRec
        cboEmployeeName.AddItem MyIndex(i).FullName
    Next i
End Sub

Private Sub Show_Record()
    Dim i As Integer
    For i = 0 To 4
        txtEmployeeInfo(i).Enabled = True
    Next i
    optSingle.Enabled = True
    optMarried.Enabled = True
    txtEmployeeInfo(0).Text = Trim(MyEmployees.Title)
    If MyEmployees.Status = 0 Then
        optSingle = True
    Else
        optMarried = True
    End If
    txtEmployeeInfo(1).Text = Trim(Format$(MyEmployees.Salary, "$###,###"))
    txtEmployeeInfo(2).Text = Trim(MyEmployees.Age)
    txtEmployeeInfo(3).Text = Trim(Format$(MyEmployees.DOH, "mm/dd/yy"))
    txtEmployeeInfo(4).Text = Trim(MyEmployees.NumChildren)
End Sub

Private Sub ToolButton_Click(index As Integer)
    Select Case index
    Case 0
        mnuNew_Click
    Case 1
        Save_Record
    Case 2
        mnuDelete_Click
    Case 3
        mnuPrint_Click
    End Select
End Sub

Private Sub txtEmployeeInfo_KeyDown(index As Integer, KeyCode As Integer, Shift As Integer)
'Set editing mode
    If NewMode = 0 Then 'Make sure we are not entering a new employee
        ToolButton(1).Enabled = True
        ToolButton(3).Enabled = False
        mnuPrint.Enabled = False
        ReplaceFlags = 1
    End If
End Sub

Private Sub txtEmployeeInfo_KeyPress(index As Integer, KeyAscii As Integer)
' Turn off beep
    If KeyAscii = 13 Then
        KeyAscii = 0
    End If
End Sub

