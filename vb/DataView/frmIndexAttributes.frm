VERSION 4.00
Begin VB.Form frmIndexAttributes 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Index Attributes"
   ClientHeight    =   4785
   ClientLeft      =   2985
   ClientTop       =   2655
   ClientWidth     =   4410
   ControlBox      =   0   'False
   Height          =   5190
   Icon            =   "frmIndexAttributes.frx":0000
   Left            =   2925
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4785
   ScaleWidth      =   4410
   Top             =   2310
   Width           =   4530
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   1560
      TabIndex        =   7
      Top             =   4200
      Width           =   1335
   End
   Begin VB.CheckBox chkForeign 
      Alignment       =   1  'Right Justify
      Caption         =   "Foreign:"
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
      Left            =   1440
      TabIndex        =   6
      Top             =   2040
      Width           =   1215
   End
   Begin VB.CheckBox chkPrimary 
      Alignment       =   1  'Right Justify
      Caption         =   "Primary:"
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1440
      TabIndex        =   5
      Top             =   1560
      Width           =   1215
   End
   Begin VB.CheckBox chkRequired 
      Alignment       =   1  'Right Justify
      Caption         =   "Required:"
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1440
      TabIndex        =   4
      Top             =   1080
      Width           =   1215
   End
   Begin VB.CheckBox chkUnique 
      Alignment       =   1  'Right Justify
      Caption         =   "Unique:"
      BeginProperty Font 
         name            =   "Arial"
         charset         =   0
         weight          =   400
         size            =   9.75
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1440
      TabIndex        =   3
      Top             =   600
      Width           =   1215
   End
   Begin VB.ListBox lstIndexFields 
      BackColor       =   &H00C0C0C0&
      Height          =   1230
      Left            =   720
      TabIndex        =   2
      Top             =   2880
      Width           =   3015
   End
   Begin VB.Label lblIndexFields 
      Caption         =   "Fields in Index:"
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
      TabIndex        =   8
      Top             =   2520
      Width           =   1455
   End
   Begin VB.Label lblIndexNameOutput 
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
      TabIndex        =   1
      Top             =   120
      Width           =   2055
   End
   Begin VB.Label lblIndexName 
      Alignment       =   1  'Right Justify
      Caption         =   "Index Name:"
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
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "frmIndexAttributes"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Public Function DisplayAttributes(ByVal Node As Node)

    Dim CurrentIndex As Index, MyField As Field
    Set CurrentIndex = MyDB.TableDefs(Node.Parent.Parent.Text).Indexes(Node.Text)
    
    'Display IndexName
    lblIndexNameOutput.Caption = CurrentIndex.Name
    
    'Check for Unique Value
    If CurrentIndex.Unique Then
        chkUnique.Value = 1
    End If
    
    'Check for Required Value
    If CurrentIndex.Required Then
        chkRequired.Value = 1
    End If
    
    'Check for Primary Value
    If CurrentIndex.Primary Then
        chkPrimary.Value = 1
    End If
    
    'Check for Foreign value
    If CurrentIndex.Foreign Then
        chkForeign.Value = 1
    End If
    
    'Display Fields belonging to Current Index
    'in IndexFields List Box
    For Each MyField In CurrentIndex.Fields
        lstIndexFields.AddItem MyField.Name
    Next MyField
End Function


Private Sub cmdOK_Click()
    Unload Me
End Sub


Private Sub Form_Activate()
    cmdOK.SetFocus
End Sub

