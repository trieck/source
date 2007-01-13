VERSION 5.00
Begin VB.Form frmUsers 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   1530
   ClientLeft      =   2895
   ClientTop       =   2775
   ClientWidth     =   5535
   Icon            =   "frmUsers.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1530
   ScaleWidth      =   5535
   Begin VB.CommandButton cmdCancel 
      Caption         =   "C&ancel"
      Height          =   375
      Left            =   4560
      TabIndex        =   5
      Top             =   720
      Width           =   855
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   4560
      TabIndex        =   4
      Top             =   240
      Width           =   855
   End
   Begin VB.TextBox txtPassword 
      BackColor       =   &H00FFFFFF&
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   1080
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   840
      Width           =   3375
   End
   Begin VB.ComboBox cboUsers 
      BackColor       =   &H00FFFFFF&
      Height          =   315
      Left            =   1080
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   240
      Width           =   3375
   End
   Begin VB.Label lblUser 
      Caption         =   "User:"
      Height          =   255
      Left            =   480
      TabIndex        =   3
      Top             =   240
      Width           =   495
   End
   Begin VB.Label lblPassword 
      Caption         =   "Password:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   855
   End
End
Attribute VB_Name = "frmUsers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim MyUser() As Users



Private Sub cboUsers_Click()
    txtPassword.Text = ""
    txtPassword.SetFocus
End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()
    If cboUsers.Text <> "" Then
        If txtPassword.Text = MyUser(cboUsers.ListIndex).Password Then
            frmUsers.Icon = LoadPicture(App.Path & "\trffc10a.ico")
            frmPhoneBook2.Show
            Unload Me
        Else
            MsgBox "Password does not match!", vbInformation, "Tom's PhoneBook"
            txtPassword.SetFocus
        End If
    End If
    
End Sub

Private Sub Form_Load()
    Dim a As Variant, i As Integer
    a = GetAllSettings("Tom's Phone Book", "Users")
    ReDim MyUser(UBound(a, 1))
    For i = LBound(a, 1) To UBound(a, 1)
        MyUser(i).User = a(i, 0)
        MyUser(i).Password = a(i, 1)
        cboUsers.AddItem MyUser(i).User
    Next i
    Me.Caption = App.ProductName
End Sub


Private Sub txtPassword_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
        cmdOK_Click
        KeyAscii = 0
    End If
End Sub

