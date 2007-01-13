VERSION 4.00
Begin VB.Form frmFieldAttributes 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Field Attributes"
   ClientHeight    =   4785
   ClientLeft      =   3000
   ClientTop       =   2670
   ClientWidth     =   4410
   ControlBox      =   0   'False
   Height          =   5190
   Icon            =   "frmFieldAttributes.frx":0000
   Left            =   2940
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4785
   ScaleWidth      =   4410
   Top             =   2325
   Width           =   4530
   Begin VB.CheckBox chkZeroLength 
      Height          =   255
      Left            =   3000
      TabIndex        =   20
      Top             =   1800
      Width           =   255
   End
   Begin VB.CheckBox chkRequired 
      Height          =   255
      Left            =   3000
      TabIndex        =   18
      Top             =   2160
      Width           =   255
   End
   Begin VB.CheckBox chkDescendingOrder 
      Height          =   255
      Left            =   3000
      TabIndex        =   14
      Top             =   3960
      Width           =   255
   End
   Begin VB.OptionButton optFixedField 
      Height          =   255
      Index           =   1
      Left            =   3000
      TabIndex        =   13
      Top             =   2880
      Width           =   255
   End
   Begin VB.OptionButton optFixedField 
      Height          =   255
      Index           =   0
      Left            =   3000
      TabIndex        =   12
      Top             =   2520
      Width           =   255
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   1680
      TabIndex        =   2
      Top             =   4320
      Width           =   1335
   End
   Begin VB.CheckBox chkAutoIncrement 
      Height          =   255
      Left            =   3000
      TabIndex        =   1
      Top             =   3240
      Width           =   255
   End
   Begin VB.CheckBox chkUpdatable 
      Height          =   255
      Left            =   3000
      TabIndex        =   0
      Top             =   3600
      Width           =   255
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Allow Zero Length:"
      Height          =   255
      Left            =   1320
      TabIndex        =   19
      Top             =   1800
      Width           =   1575
   End
   Begin VB.Label lblRequired 
      Alignment       =   1  'Right Justify
      Caption         =   "Required:"
      Height          =   255
      Left            =   1320
      TabIndex        =   17
      Top             =   2160
      Width           =   1575
   End
   Begin VB.Label lblFieldType 
      Alignment       =   1  'Right Justify
      Caption         =   "Field Type:"
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
      TabIndex        =   16
      Top             =   600
      Width           =   1215
   End
   Begin VB.Label lblFieldTypeOutput 
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
      Left            =   1560
      TabIndex        =   15
      Top             =   600
      Width           =   2055
   End
   Begin VB.Label lblFieldName 
      Alignment       =   1  'Right Justify
      Caption         =   "Field Name:"
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
      TabIndex        =   11
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label lblFieldNameOutput 
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
      TabIndex        =   10
      Top             =   120
      Width           =   2055
   End
   Begin VB.Label lblSize 
      Alignment       =   1  'Right Justify
      Caption         =   "Size:"
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
      TabIndex        =   9
      Top             =   1080
      Width           =   1215
   End
   Begin VB.Label lblSizeOutput 
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
      Top             =   1080
      Width           =   2055
   End
   Begin VB.Label lblVariableLength 
      Alignment       =   1  'Right Justify
      Caption         =   "Variable Length Field:"
      Height          =   255
      Left            =   1320
      TabIndex        =   7
      Top             =   2880
      Width           =   1575
   End
   Begin VB.Label lblAutoIncrement 
      Alignment       =   1  'Right Justify
      Caption         =   "Auto Increment:"
      Height          =   255
      Left            =   1320
      TabIndex        =   6
      Top             =   3240
      Width           =   1575
   End
   Begin VB.Label lblUpdatable 
      Alignment       =   1  'Right Justify
      Caption         =   "Updatable:"
      Height          =   255
      Left            =   1320
      TabIndex        =   5
      Top             =   3600
      Width           =   1575
   End
   Begin VB.Label lblDescendingOrder 
      Alignment       =   1  'Right Justify
      Caption         =   "Descending Order:"
      Height          =   255
      Left            =   1320
      TabIndex        =   4
      Top             =   3960
      Width           =   1575
   End
   Begin VB.Label lblFixedField 
      Alignment       =   1  'Right Justify
      Caption         =   "Fixed Field:"
      Height          =   255
      Left            =   1320
      TabIndex        =   3
      Top             =   2520
      Width           =   1575
   End
End
Attribute VB_Name = "frmFieldAttributes"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit


Public Function DisplayAttributes(ByVal Node As Node)
    Dim CurrentField As Field
    Set CurrentField = MyDB.TableDefs(Node.Parent.Parent.Text).Fields(Node.Text)
    
    'Get FieldName
    lblFieldNameOutput.Caption = CurrentField.Name
    'Get Field Type
    lblFieldTypeOutput.Caption = GetFieldType(CurrentField)
    'Get Size
    lblSizeOutput.Caption = CurrentField.Size
    'Get Allow Zero Length
    If CurrentField.AllowZeroLength Then
        chkZeroLength.Value = 1
    End If
    'Get Required
    If CurrentField.Required Then
        chkRequired.Value = 1
    End If
    'Check for Fixed Field
    If CurrentField.Attributes And dbFixedField Then
        optFixedField(0).Value = True
    Else
        optFixedField(1).Value = True
    End If
    'Check for Auto Increment
    If CurrentField.Attributes And dbAutoIncrField Then
        chkAutoIncrement.Value = 1
    End If
    'Check for Updatable
    If CurrentField.Attributes And dbUpdatableField Then
        chkUpdatable.Value = 1
    End If
    'Check for Descending
    If CurrentField.Attributes And dbDescending Then
        chkDescendingOrder.Value = 1
    End If
End Function

Private Sub cmdOK_Click()
    Unload Me
End Sub


Private Function GetFieldType(CurrentField As Field) As String
Select Case CurrentField.Type
        Case dbDate
            GetFieldType = "Date"
        Case dbText
            GetFieldType = "Text"
        Case dbMemo
            GetFieldType = "Memo"
        Case dbBoolean
            GetFieldType = "Boolean"
        Case dbInteger
            GetFieldType = "Integer"
        Case dbLong
            GetFieldType = "Long"
        Case dbCurrency
            GetFieldType = "Currency"
        Case dbSingle
            GetFieldType = "Single"
        Case dbDouble
            GetFieldType = "Double"
        Case dbByte
            GetFieldType = "Byte"
        Case dbLongBinary
            GetFieldType = "Long Binary"
    End Select
End Function

