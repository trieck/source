VERSION 5.00
Begin VB.Form frmRegisters 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Registers"
   ClientHeight    =   4575
   ClientLeft      =   435
   ClientTop       =   7560
   ClientWidth     =   2640
   Icon            =   "registers.frx":0000
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4575
   ScaleWidth      =   2640
   ShowInTaskbar   =   0   'False
   Begin VB.Frame fmeRegisters 
      Caption         =   "Registers"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   4335
      Left            =   120
      TabIndex        =   6
      Top             =   120
      Width           =   2415
      Begin VB.TextBox txtReg 
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Index           =   4
         Left            =   1920
         MaxLength       =   2
         TabIndex        =   23
         Tag             =   "PCL"
         Top             =   2280
         Width           =   375
      End
      Begin VB.CheckBox chkFlags 
         BackColor       =   &H00800000&
         Caption         =   "C"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00C0FFFF&
         Height          =   255
         Index           =   0
         Left            =   1920
         Style           =   1  'Graphical
         TabIndex        =   22
         ToolTipText     =   "Carry Flag"
         Top             =   3840
         Width           =   255
      End
      Begin VB.Frame fmeFlags 
         Caption         =   "Flags"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   615
         Left            =   120
         TabIndex        =   14
         Top             =   3600
         Width           =   2175
         Begin VB.CheckBox chkFlags 
            BackColor       =   &H00804000&
            Caption         =   "Z"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00C0FFFF&
            Height          =   255
            Index           =   1
            Left            =   1560
            Style           =   1  'Graphical
            TabIndex        =   21
            ToolTipText     =   "Zero Flag"
            Top             =   240
            Width           =   255
         End
         Begin VB.CheckBox chkFlags 
            BackColor       =   &H00808000&
            Caption         =   "I"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00C0FFFF&
            Height          =   255
            Index           =   2
            Left            =   1320
            Style           =   1  'Graphical
            TabIndex        =   20
            ToolTipText     =   "IRQ Disable Flag"
            Top             =   240
            Width           =   255
         End
         Begin VB.CheckBox chkFlags 
            BackColor       =   &H00C0C000&
            Caption         =   "D"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00C0FFFF&
            Height          =   255
            Index           =   3
            Left            =   1080
            Style           =   1  'Graphical
            TabIndex        =   19
            ToolTipText     =   "Decimal Flag"
            Top             =   240
            Width           =   255
         End
         Begin VB.CheckBox chkFlags 
            BackColor       =   &H00FFFF00&
            Caption         =   "B"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Index           =   4
            Left            =   840
            Style           =   1  'Graphical
            TabIndex        =   18
            ToolTipText     =   "Break Flag"
            Top             =   240
            Width           =   255
         End
         Begin VB.CheckBox chkFlags 
            BackColor       =   &H00FFFF40&
            Caption         =   "-"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Index           =   5
            Left            =   600
            Style           =   1  'Graphical
            TabIndex        =   17
            Top             =   240
            Width           =   255
         End
         Begin VB.CheckBox chkFlags 
            BackColor       =   &H00FFFF80&
            Caption         =   "V"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Index           =   6
            Left            =   360
            Style           =   1  'Graphical
            TabIndex        =   16
            ToolTipText     =   "Overflow Flag"
            Top             =   240
            Width           =   255
         End
         Begin VB.CheckBox chkFlags 
            BackColor       =   &H00FFFFC0&
            Caption         =   "N"
            BeginProperty Font 
               Name            =   "Courier New"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Index           =   7
            Left            =   120
            Style           =   1  'Graphical
            TabIndex        =   15
            ToolTipText     =   "Negative Flag"
            Top             =   240
            Width           =   255
         End
      End
      Begin VB.TextBox txtReg 
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Index           =   6
         Left            =   1920
         MaxLength       =   2
         TabIndex        =   5
         Tag             =   "P"
         Top             =   3240
         Width           =   375
      End
      Begin VB.TextBox txtReg 
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Index           =   5
         Left            =   1920
         MaxLength       =   2
         TabIndex        =   4
         Tag             =   "S"
         Top             =   2760
         Width           =   375
      End
      Begin VB.TextBox txtReg 
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Index           =   3
         Left            =   1920
         MaxLength       =   2
         TabIndex        =   3
         Tag             =   "PCL"
         Top             =   1800
         Width           =   375
      End
      Begin VB.TextBox txtReg 
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Index           =   2
         Left            =   1920
         MaxLength       =   2
         TabIndex        =   2
         Tag             =   "Y"
         Top             =   1320
         Width           =   375
      End
      Begin VB.TextBox txtReg 
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Index           =   1
         Left            =   1920
         MaxLength       =   2
         TabIndex        =   1
         Tag             =   "X"
         Top             =   840
         Width           =   375
      End
      Begin VB.TextBox txtReg 
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Index           =   0
         Left            =   1920
         MaxLength       =   2
         TabIndex        =   0
         Tag             =   "A"
         Top             =   360
         Width           =   375
      End
      Begin VB.Label lblP 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H00000040&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "P"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00C0FFFF&
         Height          =   255
         Left            =   120
         TabIndex        =   13
         ToolTipText     =   "Processor Status Register"
         Top             =   3240
         Width           =   1695
      End
      Begin VB.Label lblS 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H00004080&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "S"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00C0FFFF&
         Height          =   255
         Left            =   120
         TabIndex        =   12
         ToolTipText     =   "Stack Pointer"
         Top             =   2760
         Width           =   1695
      End
      Begin VB.Label lblPCH 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H000040C0&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "PCH"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00C0FFFF&
         Height          =   255
         Left            =   120
         TabIndex        =   11
         ToolTipText     =   "Program Counter High"
         Top             =   2280
         Width           =   1695
      End
      Begin VB.Label lblPCL 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H000080FF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "PCL"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000008&
         Height          =   255
         Left            =   120
         TabIndex        =   10
         ToolTipText     =   "Program Counter Low"
         Top             =   1800
         Width           =   1695
      End
      Begin VB.Label lblY 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H0080C0FF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "Y"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000008&
         Height          =   255
         Left            =   120
         TabIndex        =   9
         ToolTipText     =   "Y Index Register"
         Top             =   1320
         Width           =   1695
      End
      Begin VB.Label lblX 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H00C0E0FF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "X"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000008&
         Height          =   255
         Left            =   120
         TabIndex        =   8
         ToolTipText     =   "X Index Register"
         Top             =   840
         Width           =   1695
      End
      Begin VB.Label lblA 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H00C0FFFF&
         BorderStyle     =   1  'Fixed Single
         Caption         =   "A"
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   11.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000008&
         Height          =   255
         Left            =   120
         TabIndex        =   7
         ToolTipText     =   "Accumulator"
         Top             =   360
         Width           =   1695
      End
   End
End
Attribute VB_Name = "frmRegisters"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private CPU As cls6502
Private Dirty(6) As Boolean

Private Sub RefreshFlags()
    Dim i As Integer
        
    For i = 0 To chkFlags.UBound
        If (CPU.RegP And (2 ^ i)) Then
            chkFlags(i).value = 1
        Else
            chkFlags(i).value = 0
        End If
    Next
    
End Sub

Private Sub RefreshRegister(ByVal index As Integer)
            
    Select Case index
    Case 0
        txtReg(index).Text = Byte2Hex(CPU.RegA)
    Case 1
        txtReg(index).Text = Byte2Hex(CPU.RegX)
    Case 2
        txtReg(index).Text = Byte2Hex(CPU.RegY)
    Case 3
        txtReg(index).Text = Byte2Hex(CPU.RegPCL)
    Case 4
        txtReg(index).Text = Byte2Hex(CPU.RegPCH)
    Case 5
        txtReg(index).Text = Byte2Hex(CPU.RegS)
    Case 6
        txtReg(index).Text = Byte2Hex(CPU.RegP)
        RefreshFlags
    End Select
    
    Dirty(index) = False
    
End Sub

Private Sub chkFlags_Click(index As Integer)
    Dim value As Integer
    
    value = chkFlags(index).value
    
    If (value) Then
        CPU.RegP = CPU.RegP Or (2 ^ index)
    Else
        CPU.RegP = CPU.RegP And Not (2 ^ index)
    End If
    
    RefreshRegister (6)
    
End Sub

Private Sub RefreshRegisters()
    
    Call RefreshRegister(0)
    Call RefreshRegister(1)
    Call RefreshRegister(2)
    Call RefreshRegister(3)
    Call RefreshRegister(4)
    Call RefreshRegister(5)
    Call RefreshRegister(6)
    
End Sub


Private Sub UpdateRegister(ByVal index As Integer)
    
    Dim b As Byte
    b = Hex2Byte(txtReg(index).Text)
    txtReg(index).Text = Byte2Hex(b) ' ensure we store leading zeros
    
    Select Case index
        Case 0
            CPU.RegA = b
        Case 1
            CPU.RegX = b
        Case 2
            CPU.RegY = b
        Case 3
            CPU.RegPCL = b
        Case 4
            CPU.RegPCH = b
        Case 5
            CPU.RegS = b
        Case 6
            CPU.RegP = b
            RefreshFlags
        Case Default
    End Select
    
    Dirty(index) = False

End Sub

Private Sub Form_Load()
    Set CPU = GetCPU()
    Call RefreshRegisters
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set CPU = Nothing
    Call ToggleRegisterBtn
End Sub

Private Sub txtReg_Change(index As Integer)
    Dirty(index) = True
End Sub

Private Sub txtReg_KeyDown(index As Integer, KeyCode As Integer, Shift As Integer)
    If (KeyCode = vbKeyDelete) Then ' disable delete
        KeyCode = 0
    End If
End Sub

Private Sub txtReg_KeyPress(index As Integer, KeyAscii As Integer)
    If (KeyAscii <> Asc(vbCr)) Then
        KeyAscii = ValidateHexDigit(KeyAscii)
        Dirty(index) = True
    Else
        Call UpdateRegister(index)
    End If
End Sub

Private Sub txtReg_LostFocus(index As Integer)
    If (Dirty(index)) Then
        Call UpdateRegister(index)
    End If
End Sub
