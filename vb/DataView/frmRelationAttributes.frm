VERSION 4.00
Begin VB.Form frmRelationAttributes 
   Caption         =   "Relation Attributes"
   ClientHeight    =   5415
   ClientLeft      =   3510
   ClientTop       =   1815
   ClientWidth     =   4410
   Height          =   5820
   Icon            =   "frmRelationAttributes.frx":0000
   Left            =   3450
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5415
   ScaleWidth      =   4410
   Top             =   1470
   Width           =   4530
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   1680
      TabIndex        =   14
      Top             =   4920
      Width           =   1335
   End
   Begin VB.CheckBox chkDeletionsCascade 
      Caption         =   "Deletions will cascade"
      Height          =   375
      Left            =   1680
      TabIndex        =   11
      Top             =   4320
      Width           =   2175
   End
   Begin VB.CheckBox chkUpdatesCascade 
      Caption         =   "Updates will cascade"
      Height          =   375
      Left            =   1680
      TabIndex        =   10
      Top             =   3840
      Width           =   2055
   End
   Begin VB.Frame fmeJoin 
      BackColor       =   &H00C0C0C0&
      Caption         =   "Join"
      Height          =   735
      Left            =   600
      TabIndex        =   9
      Top             =   1560
      Width           =   3135
      Begin VB.OptionButton optJoinType 
         Caption         =   "Right Join"
         Height          =   255
         Index           =   1
         Left            =   1920
         TabIndex        =   13
         Top             =   360
         Width           =   1095
      End
      Begin VB.OptionButton optJoinType 
         Caption         =   "Left Join"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   12
         Top             =   360
         Width           =   1095
      End
   End
   Begin VB.CheckBox chkRelationInherited 
      Caption         =   "Relation Inherited"
      Height          =   375
      Left            =   1680
      TabIndex        =   8
      Top             =   3360
      Width           =   1575
   End
   Begin VB.CheckBox chkNoRefInteg 
      Caption         =   "No Referential Integrity"
      Height          =   375
      Left            =   1680
      TabIndex        =   7
      Top             =   2880
      Width           =   2055
   End
   Begin VB.CheckBox chkUniqueRelation 
      Caption         =   "Unique Relation"
      Height          =   375
      Left            =   1680
      TabIndex        =   6
      Top             =   2400
      Width           =   1575
   End
   Begin VB.Label lblForeignTableOutput 
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
      Left            =   1680
      TabIndex        =   5
      Top             =   1080
      Width           =   2055
   End
   Begin VB.Label lblForeignTable 
      Alignment       =   1  'Right Justify
      Caption         =   "Foreign Table:"
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
      Left            =   0
      TabIndex        =   4
      Top             =   1080
      Width           =   1455
   End
   Begin VB.Label lblRelationNameOutput 
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
      Left            =   1680
      TabIndex        =   3
      Top             =   120
      Width           =   2055
   End
   Begin VB.Label lblRelationName 
      Alignment       =   1  'Right Justify
      Caption         =   "Relation Name:"
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
      Left            =   0
      TabIndex        =   2
      Top             =   120
      Width           =   1455
   End
   Begin VB.Label lblPrimaryTableOutput 
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
      TabIndex        =   1
      Top             =   600
      Width           =   2055
   End
   Begin VB.Label lblPrimaryTable 
      Alignment       =   1  'Right Justify
      Caption         =   "PrimaryTable:"
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
      TabIndex        =   0
      Top             =   600
      Width           =   1215
   End
End
Attribute VB_Name = "frmRelationAttributes"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Public Function DisplayAttributes(ByVal Node As Node)
    Dim CurrentRelation As Relation
    Set CurrentRelation = MyDB.Relations(Node.Text)

    'Get Relation Name
    lblRelationNameOutput.Caption = CurrentRelation.Name
    
    'Get Primary Table
    lblPrimaryTableOutput.Caption = CurrentRelation.Table
    
    'Get Foreign Table
    lblForeignTableOutput.Caption = CurrentRelation.ForeignTable
    
    'Get Join Type
    If CurrentRelation.Attributes And dbRelationLeft Then
        optJoinType(0).Value = True
    Else
        optJoinType(1).Value = True
    End If
    
    'Check for Unique relation
    If CurrentRelation.Attributes And dbRelationUnique Then
        chkUniqueRelation.Value = 1
    End If
    
    'Check for No Referential Integrity
    If CurrentRelation.Attributes And dbRelationDontEnforce Then
        chkNoRefInteg.Value = 1
    End If
    
    'Check for Inherited relation
    If CurrentRelation.Attributes And dbRelationInherited Then
        chkRelationInherited.Value = 1
    End If
    
    'Check for updates cascade
    If CurrentRelation.Attributes And dbRelationUpdateCascade Then
        chkUpdatesCascade.Value = 1
    End If
    
    'Check will deletes cascade
    If CurrentRelation.Attributes And dbRelationDeleteCascade Then
        chkDeletionsCascade.Value = 1
    End If
    
    
End Function

Private Sub lblFieldType_Click()

End Sub


Private Sub cmdOK_Click()
    Unload Me
End Sub


