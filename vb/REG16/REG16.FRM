VERSION 4.00
Begin VB.Form frmReg16 
   Appearance      =   0  'Flat
   BackColor       =   &H0080C0FF&
   Caption         =   "Reg 16"
   ClientHeight    =   3435
   ClientLeft      =   1410
   ClientTop       =   1830
   ClientWidth     =   6360
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   1
      weight          =   700
      size            =   8.25
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   3840
   Icon            =   "REG16.frx":0000
   Left            =   1350
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   3435
   ScaleWidth      =   6360
   Top             =   1485
   Width           =   6480
   Begin VB.CommandButton cmdSave 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "&Save To File"
      Enabled         =   0   'False
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1440
      TabIndex        =   5
      Top             =   3000
      Width           =   1215
   End
   Begin VB.ListBox lstLicense 
      Appearance      =   0  'Flat
      BackColor       =   &H00C0E0FF&
      Height          =   1785
      Left            =   120
      MultiSelect     =   2  'Extended
      TabIndex        =   2
      Top             =   600
      Width           =   6135
   End
   Begin VB.CommandButton cmdExit 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "E&xit"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5040
      TabIndex        =   0
      Top             =   3000
      Width           =   1215
   End
   Begin VB.CommandButton cmdGetLicenses 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "&Get Licenses"
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label lblLicense 
      Appearance      =   0  'Flat
      BackColor       =   &H00C0E0FF&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   2520
      Width           =   6135
   End
   Begin VB.Label lblLicenseInfo 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H00C0E0FF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         name            =   "MS Sans Serif"
         charset         =   0
         weight          =   400
         size            =   8.25
         underline       =   0   'False
         italic          =   0   'False
         strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   6135
   End
End
Attribute VB_Name = "frmReg16"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Dim hKey&   ' Handle to a registry key

Private Sub cmdExit_Click()
    End
End Sub

Private Sub cmdGetLicenses_Click()
    Dim rtn&, Buffer$, BufferLen&
    Dim Lic$, LicLen&, lIndex As Long

    lIndex = 0
    Buffer$ = String(255, " ")
    BufferLen& = Len(Buffer$)
    Lic$ = String(255, 0)
    LicLen& = Len(Lic$)

    ' Clear the list box
    lstLicense.Clear

    ' Open Licenses Key
    rtn& = RegOpenKey(HKEY_CLASSES_ROOT, "Licenses", hKey&)

    ' Get the license agreement
    If Not (rtn&) Then
        rtn& = RegQueryValue(hKey&, Chr$(0), Buffer$, BufferLen&)
        lblLicenseInfo.Caption = Left$(Buffer$, BufferLen&)
    End If

    ' Enumerate Licenses
    While (rtn& = 0)
        rtn& = RegEnumKey(hKey&, lIndex, Lic$, LicLen&)
        If (rtn& = 0) Then
            lstLicense.AddItem Left$(Lic$, LicLen&)
        End If
        lIndex = lIndex + 1
    Wend

End Sub

Private Sub cmdSave_Click()
    Dim sString As String, File%
    Dim Path$, Ln%

    ' Build String
    If lstLicense.Text <> "" And lblLicense.Caption <> "" Then
        sString = lstLicense.Text & ";" & lblLicense.Caption + Chr(13) + Chr(10)
    Else
        MsgBox "Must select a valid key."
        Exit Sub
    End If
    ' Save to file
    File% = FreeFile
    Path$ = App.Path & "\" & App.EXEName & ".txt"
    Open Path$ For Binary As #File%
    Ln% = LOF(File%)
    Put #File%, Ln% + 1, sString
    Close File%
    MsgBox "Entry appended to file."
End Sub

Private Sub Form_Load()
    Me.Left = (screen.Width - Me.Width) / 2
    Me.Top = (screen.Height - Me.Height) / 2
End Sub

Private Sub lstLicense_Click()
    Dim rtn&, NewKey&, Buffer$, BufferLen&

    Buffer$ = String(255, " ")
    BufferLen = Len(Buffer$)

    ' Open chosen key
    rtn& = RegOpenKey(hKey&, lstLicense.Text, NewKey&)
    ' Query value
    If (rtn& = 0) Then
        rtn& = RegQueryValue(NewKey&, Chr$(0), Buffer$, BufferLen&)
    End If
    ' Display value
    lblLicense.Caption = Left$(Buffer$, BufferLen&)
    'Enable saving
    cmdSave.Enabled = True
End Sub

