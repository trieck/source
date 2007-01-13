VERSION 4.00
Begin VB.Form frmTableAttributes 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Table Attributes"
   ClientHeight    =   4785
   ClientLeft      =   3045
   ClientTop       =   2670
   ClientWidth     =   4410
   ControlBox      =   0   'False
   Height          =   5190
   Icon            =   "frmTableAttributes.frx":0000
   Left            =   2985
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4785
   ScaleWidth      =   4410
   Top             =   2325
   Width           =   4530
   Begin VB.CheckBox chkAttachedSavePWD 
      Height          =   255
      Left            =   3000
      TabIndex        =   20
      Top             =   2520
      Width           =   255
   End
   Begin VB.OptionButton optODBC 
      Height          =   255
      Index           =   1
      Left            =   3000
      TabIndex        =   19
      Top             =   3960
      Width           =   255
   End
   Begin VB.OptionButton optODBC 
      Height          =   255
      Index           =   0
      Left            =   3000
      TabIndex        =   18
      Top             =   3600
      Width           =   255
   End
   Begin VB.CheckBox chkHiddenTable 
      Height          =   255
      Left            =   3000
      TabIndex        =   11
      Top             =   3240
      Width           =   255
   End
   Begin VB.CheckBox chkSysTable 
      Height          =   255
      Left            =   3000
      TabIndex        =   10
      Top             =   2880
      Width           =   255
   End
   Begin VB.CheckBox chkExclusiveAttached 
      Height          =   255
      Left            =   3000
      TabIndex        =   9
      Top             =   2160
      Width           =   255
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   1680
      TabIndex        =   0
      Top             =   4320
      Width           =   1335
   End
   Begin VB.Label lblExclusiveAttached 
      Alignment       =   1  'Right Justify
      Caption         =   "Exclusive Attached:"
      Height          =   255
      Left            =   1320
      TabIndex        =   12
      Top             =   2160
      Width           =   1575
   End
   Begin VB.Label lblODBC 
      Alignment       =   1  'Right Justify
      Caption         =   "ODBC Attached:"
      Height          =   255
      Left            =   1320
      TabIndex        =   17
      Top             =   3960
      Width           =   1575
   End
   Begin VB.Label lblNonODBC 
      Alignment       =   1  'Right Justify
      Caption         =   "Non ODBC Attached:"
      Height          =   255
      Left            =   1320
      TabIndex        =   16
      Top             =   3600
      Width           =   1575
   End
   Begin VB.Label lblHiddenTable 
      Alignment       =   1  'Right Justify
      Caption         =   "Hidden Table:"
      Height          =   255
      Left            =   1320
      TabIndex        =   15
      Top             =   3240
      Width           =   1575
   End
   Begin VB.Label lblSysTable 
      Alignment       =   1  'Right Justify
      Caption         =   "System Table:"
      Height          =   255
      Left            =   1320
      TabIndex        =   14
      Top             =   2880
      Width           =   1575
   End
   Begin VB.Label lblAttachedSavePWD 
      Alignment       =   1  'Right Justify
      Caption         =   "Attached Save PWD:"
      Height          =   255
      Left            =   1320
      TabIndex        =   13
      Top             =   2520
      Width           =   1575
   End
   Begin VB.Label lblUpdateableOutput 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00C0C0C0&
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
      Left            =   1560
      TabIndex        =   8
      Top             =   1560
      Width           =   2055
   End
   Begin VB.Label lblUpdateable 
      Alignment       =   1  'Right Justify
      Caption         =   "Updateable:"
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
      TabIndex        =   7
      Top             =   1560
      Width           =   1215
   End
   Begin VB.Label lblLastUpdatedOutput 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00C0C0C0&
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
      Left            =   1560
      TabIndex        =   6
      Top             =   1080
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
      Left            =   120
      TabIndex        =   5
      Top             =   1080
      Width           =   1215
   End
   Begin VB.Label lblDateCreatedOutput 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00C0C0C0&
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
      Left            =   1560
      TabIndex        =   4
      Top             =   600
      Width           =   2055
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
      Left            =   120
      TabIndex        =   3
      Top             =   600
      Width           =   1215
   End
   Begin VB.Label lblTableNameOutput 
      Alignment       =   1  'Right Justify
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
      Height          =   375
      Left            =   1560
      TabIndex        =   2
      Top             =   120
      Width           =   2055
   End
   Begin VB.Label lblTableName 
      Alignment       =   1  'Right Justify
      Caption         =   "Table Name:"
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
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "frmTableAttributes"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Public Function DisplayAttributes(ByVal Node As Node)
    Dim CurrentTable As TableDef
    Set CurrentTable = MyDB.TableDefs(Node.Text)
    
    'Get Table name
    lblTableNameOutput = CurrentTable.Name
    'Get the Date Created
    lblDateCreatedOutput = CurrentTable.DateCreated
    'Get the Last Updated Date
    lblLastUpdatedOutput = CurrentTable.LastUpdated
    'Get Table Attributes
    If CurrentTable.Attributes And dbAttachExclusive Then
        chkExclusiveAttached.Value = 1
    End If
    If CurrentTable.Attributes And dbAttachSavePWD Then
        chkAttachedSavePWD.Value = 1
    End If
    If CurrentTable.Attributes And dbSystemObject Then
        chkSysTable.Value = 1
    End If
    If CurrentTable.Attributes And dbHiddenObject Then
        chkHiddenTable.Value = 1
    End If
    If CurrentTable.Attributes And dbAttachedTable Then
        optODBC(0).Value = True
    ElseIf CurrentTable.Attributes And dbAttachedODBC Then
        optODBC(1).Value = True
    Else
        optODBC(0).Value = False
        optODBC(1).Value = False
    End If
End Function

Private Sub cmdOK_Click()
    Unload Me
End Sub


