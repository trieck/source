VERSION 4.00
Begin VB.Form frmDataView 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Data View"
   ClientHeight    =   5805
   ClientLeft      =   1575
   ClientTop       =   1995
   ClientWidth     =   7575
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   0
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   Height          =   6495
   Icon            =   "frmDataView.frx":0000
   Left            =   1515
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5805
   ScaleWidth      =   7575
   Top             =   1365
   Width           =   7695
   Begin Threed.SSCommand cmdExit 
      Height          =   375
      Left            =   1320
      TabIndex        =   3
      Top             =   0
      Width           =   1215
      _Version        =   65536
      _ExtentX        =   2143
      _ExtentY        =   661
      _StockProps     =   78
      Caption         =   "E&xit"
      ForeColor       =   8388608
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "Book Antiqua"
         charset         =   0
         weight          =   400
         size            =   9.74
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   1
      Font3D          =   3
      MouseIcon       =   "frmDataView.frx":0442
      Picture         =   "frmDataView.frx":045E
   End
   Begin Threed.SSCommand cmdOpen 
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   0
      Width           =   1215
      _Version        =   65536
      _ExtentX        =   2143
      _ExtentY        =   661
      _StockProps     =   78
      Caption         =   "&Open"
      ForeColor       =   8388608
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "Book Antiqua"
         charset         =   0
         weight          =   400
         size            =   9.74
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      BevelWidth      =   1
      Font3D          =   3
      MouseIcon       =   "frmDataView.frx":047A
      Picture         =   "frmDataView.frx":0496
   End
   Begin VB.Label lblDBName 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   700
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00400000&
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   480
      Width           =   7335
   End
   Begin MSComDlg.CommonDialog cdlgFileOpen 
      Left            =   6960
      Top             =   4440
      _Version        =   65536
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
      CancelError     =   -1  'True
      DialogTitle     =   "Open File"
      Filter          =   "Access Databases (*.mdb) | *.mdb|"
      FontBold        =   -1  'True
      InitDir         =   "d:\temp"
   End
   Begin ComctlLib.ImageList imgDataViewTree 
      Left            =   6840
      Top             =   4920
      _Version        =   65536
      _ExtentX        =   1005
      _ExtentY        =   1005
      _StockProps     =   1
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      NumImages       =   8
      i1              =   "frmDataView.frx":04B2
      i2              =   "frmDataView.frx":0871
      i3              =   "frmDataView.frx":0D68
      i4              =   "frmDataView.frx":125F
      i5              =   "frmDataView.frx":1756
      i6              =   "frmDataView.frx":1C4D
      i7              =   "frmDataView.frx":200C
      i8              =   "frmDataView.frx":23CB
   End
   Begin ComctlLib.TreeView tvwDataView 
      Height          =   4575
      Left            =   120
      TabIndex        =   0
      Top             =   960
      Width           =   7335
      _Version        =   65536
      _ExtentX        =   12938
      _ExtentY        =   8070
      _StockProps     =   196
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Appearance      =   1
      BorderStyle     =   1
      HideSelection   =   0   'False
      ImageList       =   "imgDataViewTree"
      LabelEdit       =   1
      MouseIcon       =   "frmDataView.frx":278A
      PathSeparator   =   "\"
      Sorted          =   -1  'True
      Style           =   7
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuOpen 
         Caption         =   "&Open"
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuSeperator2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
         Shortcut        =   ^E
      End
   End
End
Attribute VB_Name = "frmDataView"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Function OpenFile(FileName As Variant)
    Dim DataNode As Node, MyTable As TableDef, MyQuery As QueryDef _
    , MyRelation As Relation, MyField As Field, MyIndex As Index _
    , i As Integer, j As Integer, h As Integer
    
    'On Error GoTo OpenFile_Handler
    
    'Clear the TreeView
    tvwDataView.Nodes.Clear
    ' Set Mouse Pointer to hourglass
    Me.MousePointer = 11
    ' Set Database = Current File selected
    ' and open for READ_ONLY
    Set MyDB = OpenDatabase(FileName, , True)
    ' Show Root with DatabaseName
    Set DataNode = tvwDataView.Nodes.Add(, , "Database", FileName, 1)
    'Show Tables Node
    Set DataNode = tvwDataView.Nodes.Add("Database", tvwChild, "Tables", "Tables", 6)
    'Show Queries Node
    Set DataNode = tvwDataView.Nodes.Add("Database", tvwChild, "Queries", "Queries", 7)
    ' Show Relations Node
    Set DataNode = tvwDataView.Nodes.Add("Database", tvwChild, "Relations", "Relations", 8)
    
    ' Iterate through the TableDefs and add to tree
    i = 0: j = 0
    For Each MyTable In MyDB.TableDefs
        Set DataNode = tvwDataView.Nodes.Add("Tables", tvwChild, MyDB.Name & MyTable.Name, MyTable.Name, 2)
        ' Add the Fields branch
        Set DataNode = tvwDataView.Nodes.Add(MyDB.Name & MyTable.Name, tvwChild, "Fields" & CStr(h), "Fields", 4)
        ' Add the Indexes branch
        Set DataNode = tvwDataView.Nodes.Add(MyDB.Name & MyTable.Name, tvwChild, "Indexes" & CStr(h), "Indexes", 5)
        ' Add Fields below 'Fields' branch
            For Each MyField In MyTable.Fields
                Set DataNode = tvwDataView.Nodes.Add("Fields" & CStr(h), tvwChild, "Field" & CStr(i), MyField.Name, 4)
                i = i + 1
            Next MyField
        ' Add Indices of each Table as a branch below the Table
            If MyTable.Attributes And dbSystemObject Then
                'Don't Look for indices in System Tables
            Else
                For Each MyIndex In MyTable.Indexes
                    Set DataNode = tvwDataView.Nodes.Add("Indexes" & CStr(h), tvwChild, "Index" & CStr(j), MyIndex.Name, 5)
                    j = j + 1
                Next MyIndex
            End If
            h = h + 1
    Next MyTable
    ' Iterate through QueryDefs and add to tree
    For Each MyQuery In MyDB.QueryDefs
        Set DataNode = tvwDataView.Nodes.Add("Queries", tvwChild, MyDB.Name & MyQuery.Name, MyQuery.Name, 7)
    Next MyQuery
    ' Iterate through Relations and add to tree
    For Each MyRelation In MyDB.Relations
        Set DataNode = tvwDataView.Nodes.Add("Relations", tvwChild, MyDB.Name & MyRelation.Name, MyRelation.Name, 8)
    Next MyRelation
    Me.MousePointer = 0
    lblDBName.Caption = MyDB.Name
    Exit Function
OpenFile_Handler:
    Me.MousePointer = 0
    MsgBox Error$
    Exit Function
End Function

Private Sub cmdExit_Click()
    mnuExit_Click
End Sub

Private Sub cmdOpen_Click()
    mnuOpen_Click
    tvwDataView.SetFocus    'Set focus to TreeView
End Sub

Private Sub mnuExit_Click()
    End
End Sub

Private Sub mnuOpen_Click()
    ' Open common dialog control
    On Error GoTo ErrHandler
    cdlgFileOpen.ShowOpen
    OpenFile (cdlgFileOpen.FileTitle)
ErrHandler:
    'User pressed Cancel
    Exit Sub
End Sub












Private Sub tvwDataView_NodeClick(ByVal Node As Node)
    
    'Don't get attributes for Database
    'Tables, Queries, Relations
    'Fields, or Indexes Nodes
    If Node.Key = "Database" _
    Or Node.Key = "Tables" _
    Or Node.Key = "Queries" _
    Or Node.Key = "Relations" _
    Or Left$(Node.Key, 6) = "Fields" _
    Or Left$(Node.Key, 7) = "Indexes" Then
        Exit Sub
    End If
    
    'Table Attributes
    If Node.Parent.Key = "Tables" Then
        Load frmTableAttributes
        Call frmTableAttributes.DisplayAttributes(Node)
        frmTableAttributes.Show 1
    'Query Attributes
    ElseIf Node.Parent.Key = "Queries" Then
        Load frmQueryAttributes
        Call frmQueryAttributes.DisplayAttributes(Node)
        frmQueryAttributes.Show 1
    'Relation Attributes
    ElseIf Node.Parent.Key = "Relations" Then
        Load frmRelationAttributes
        Call frmRelationAttributes.DisplayAttributes(Node)
        frmRelationAttributes.Show 1
    'Field Attributes
    ElseIf Left$(Node.Key, 5) = "Field" Then
        Load frmFieldAttributes
        Call frmFieldAttributes.DisplayAttributes(Node)
        frmFieldAttributes.Show 1
    'Index Attributes
    Else
        Load frmIndexAttributes
        Call frmIndexAttributes.DisplayAttributes(Node)
        frmIndexAttributes.Show 1
    End If
End Sub



