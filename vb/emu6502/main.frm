VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "Mscomctl.ocx"
Object = "{ECEDB943-AC41-11D2-AB20-000000000000}#2.0#0"; "cmax20.ocx"
Begin VB.Form frmMain 
   ClientHeight    =   4275
   ClientLeft      =   4245
   ClientTop       =   5955
   ClientWidth     =   7305
   Icon            =   "main.frx":0000
   ScaleHeight     =   4275
   ScaleWidth      =   7305
   Begin CodeMaxCtl.CodeMax txtCode 
      Height          =   1455
      Left            =   1080
      OleObjectBlob   =   "main.frx":014A
      TabIndex        =   2
      Top             =   1320
      Width           =   2895
   End
   Begin MSComctlLib.StatusBar sbarMain 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   0
      Top             =   3900
      Width           =   7305
      _ExtentX        =   12885
      _ExtentY        =   661
      Style           =   1
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin MSComDlg.CommonDialog dlgOpenFile 
      Left            =   120
      Top             =   480
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DefaultExt      =   "*.*"
      DialogTitle     =   "Load 6502 code"
      FileName        =   "*.*"
      Filter          =   "6502 Code (*.*)"
      InitDir         =   ".\"
   End
   Begin MSComctlLib.ImageList imgCode 
      Left            =   720
      Top             =   480
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   16777215
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   4
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "main.frx":02B0
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "main.frx":2FBA
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "main.frx":3354
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "main.frx":4652
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar tbarMain 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   7305
      _ExtentX        =   12885
      _ExtentY        =   741
      ButtonWidth     =   609
      ButtonHeight    =   582
      AllowCustomize  =   0   'False
      Wrappable       =   0   'False
      Appearance      =   1
      ImageList       =   "imgCode"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   7
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Load 6502 Code"
            Object.Tag             =   "Load"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Toggle Register View"
            Object.Tag             =   "Registers"
            ImageIndex      =   2
            Style           =   1
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Stop Debugging"
            Object.Tag             =   "Stop"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Stop Execution"
            Object.Tag             =   "StopE"
            ImageIndex      =   4
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuLoad 
         Caption         =   "&Load"
         Shortcut        =   ^L
      End
      Begin VB.Menu mnuExit 
         Caption         =   "E&xit"
         Shortcut        =   ^X
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "&View"
      Begin VB.Menu mnuRegisters 
         Caption         =   "&Registers"
         Shortcut        =   ^R
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "&About"
         Enabled         =   0   'False
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Sub Form_Load()
    Me.Caption = App.Title
    dlgOpenFile.Flags = cdlOFNFileMustExist Or cdlOFNHideReadOnly _
        Or cdlOFNPathMustExist
        
    
End Sub


Private Sub Form_Resize()
    txtCode.Left = Me.ScaleLeft
    txtCode.Top = Me.ScaleTop + tbarMain.Height
    txtCode.Width = Me.ScaleWidth
    txtCode.Height = Abs(Me.ScaleHeight - tbarMain.Height - _
        sbarMain.Height)
End Sub


Private Sub Form_Unload(Cancel As Integer)
    Call ExitApplication
End Sub

Private Sub mnuExit_Click()
    Unload Me
End Sub

Private Sub mnuLoad_Click()
'    Dim buf() As Byte
'    Dim nLen As Long
'    Dim FileNum As Integer
'
'    On Error GoTo CancelTrap ' Trap cancel
'
'    dlgOpenFile.ShowOpen
'
'    On Error GoTo FileErr
'
'    nLen = FileLen(dlgOpenFile.filename)
'    ReDim buf(nLen)
'
'    FileNum = FreeFile()
'
'    Open dlgOpenFile.filename For Binary Access Read As FileNum
'
'    Get FileNum, , buf
'
'    Close FileNum
'
'    On Error GoTo 0
'
'    Call UpdateTitle(dlgOpenFile.filename)
'    Call Disassemble(buf)
'
'    Exit Sub
'
'CancelTrap: ' Nothing to see here
'    Exit Sub
'
'FileErr:
'    MsgBox Err.Description, vbInformation
'    Exit Sub
'
End Sub

Public Sub mnuRegisters_Click()
    Dim btn As Button
    Call ToggleRegisterView
    
    Set btn = tbarMain.Buttons(4)
    btn.value = IIf(btn.value = tbrPressed, tbrUnpressed, tbrPressed)
    
End Sub

Private Sub UpdateTitle(ByVal filename As String)
    Me.Caption = App.Title & " - " & filename
End Sub


Private Sub tbarMain_ButtonClick(ByVal Button As MSComctlLib.Button)
    Select Case Button.Tag
    Case "Load"
        Call mnuLoad_Click
    Case "Registers"
        Call ToggleRegisterView
    End Select
End Sub


