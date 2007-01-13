VERSION 4.00
Begin VB.Form frmQueryAttributes 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Query Attributes"
   ClientHeight    =   4785
   ClientLeft      =   2970
   ClientTop       =   2640
   ClientWidth     =   4410
   Height          =   5190
   Icon            =   "frmQueryAttributes.frx":0000
   Left            =   2910
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4785
   ScaleWidth      =   4410
   Top             =   2295
   Width           =   4530
   Begin VB.CommandButton cmdShowFields 
      Caption         =   "..."
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   700
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3360
      TabIndex        =   13
      Top             =   2160
      Width           =   375
   End
   Begin VB.CheckBox chkReturnsRecords 
      Caption         =   "Returns Records"
      Height          =   255
      Left            =   1680
      TabIndex        =   12
      Top             =   2520
      Width           =   1575
   End
   Begin VB.CheckBox chkUpdatable 
      Caption         =   "Updatable"
      Height          =   255
      Left            =   1680
      TabIndex        =   11
      Top             =   2160
      Width           =   1215
   End
   Begin VB.TextBox txtSQL 
      BackColor       =   &H00C0C0C0&
      Height          =   1215
      Left            =   720
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   4
      Top             =   3000
      Width           =   3015
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   1560
      TabIndex        =   0
      Top             =   4320
      Width           =   1335
   End
   Begin VB.Label lblType 
      Alignment       =   1  'Right Justify
      Caption         =   "Type:"
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   10
      Top             =   1680
      Width           =   1215
   End
   Begin VB.Label lblTypeOutput 
      Alignment       =   1  'Right Justify
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1680
      TabIndex        =   9
      Top             =   1680
      Width           =   2055
   End
   Begin VB.Label lblLastUpdatedOutput 
      Alignment       =   1  'Right Justify
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1680
      TabIndex        =   8
      Top             =   1200
      Width           =   2055
   End
   Begin VB.Label lblLastUpdated 
      Alignment       =   1  'Right Justify
      Caption         =   "Last Updated:"
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   1200
      Width           =   1215
   End
   Begin VB.Label lblDateCreated 
      Alignment       =   1  'Right Justify
      Caption         =   "Date Created:"
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   720
      Width           =   1215
   End
   Begin VB.Label lblDateCreatedOutput 
      Alignment       =   1  'Right Justify
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1680
      TabIndex        =   5
      Top             =   720
      Width           =   2055
   End
   Begin VB.Label lblQueryName 
      Alignment       =   1  'Right Justify
      Caption         =   "Query Name:"
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   240
      Width           =   1215
   End
   Begin VB.Label lblQueryNameOutput 
      Alignment       =   1  'Right Justify
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1680
      TabIndex        =   2
      Top             =   240
      Width           =   2055
   End
   Begin VB.Label lblSQL 
      Caption         =   "SQL:"
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   2880
      Width           =   495
   End
End
Attribute VB_Name = "frmQueryAttributes"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Dim CurrentQuery As QueryDef

Public Function DisplayAttributes(ByVal Node As Node)
    Set CurrentQuery = MyDB.QueryDefs(Node.Text)
    
    'Get Query Name
    lblQueryNameOutput.Caption = CurrentQuery.Name
    
    'Get Date Created
    lblDateCreatedOutput.Caption = CurrentQuery.DateCreated
    
    'Get Last Updated
    lblLastUpdatedOutput.Caption = CurrentQuery.LastUpdated
    
    'Get Query Type
    lblTypeOutput.Caption = GetQueryType(CurrentQuery)
    
    'Check for Updatable
    If CurrentQuery.Updatable Then
        chkUpdatable.Value = 1
    End If
    
    'Check for Returns Records
    If CurrentQuery.ReturnsRecords Then
        chkReturnsRecords.Value = 1
    End If
    
    'Fill in SQL
    txtSQL.Text = CurrentQuery.SQL
End Function

Private Sub cmdOK_Click()
    Unload Me
End Sub

Private Function GetQueryType(CurrentQuery As QueryDef) As String
    Select Case CurrentQuery.Type
        Case dbQSelect
            GetQueryType = "Select"
        Case dbQAction
            GetQueryType = "Action"
        Case dbQCrosstab
            GetQueryType = "Crosstab"
        Case dbQDelete
            GetQueryType = "Delete"
        Case dbQUpdate
            GetQueryType = "Update"
        Case dbQAppend
            GetQueryType = "Append"
        Case dbQMakeTable
            GetQueryType = "Make Table"
        Case dbQDDL
            GetQueryType = "DDL"
        Case dbQSQLPassThrough
            GetQueryType = "SQL Pass Through"
        Case dbQSetOperation
            GetQueryType = "Union"
        Case dbQSPTBulk
            GetQueryType = "SPT No Return"
    End Select
End Function

Private Sub cmdShowFields_Click()
    'Used to show Fields in CurrentQuery
    Dim Message$, MyField As Field
    For Each MyField In CurrentQuery.Fields
        Message$ = Message$ + MyField.Name + Chr(10) + Chr(13)
    Next
    MsgBox Message$, vbOKOnly, "Fields in " + CurrentQuery.Name
End Sub


