VERSION 4.00
Begin VB.Form frmPrinters 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Printers"
   ClientHeight    =   4815
   ClientLeft      =   3330
   ClientTop       =   2145
   ClientWidth     =   4665
   Height          =   5220
   Icon            =   "frmPrinters.frx":0000
   Left            =   3270
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   4815
   ScaleWidth      =   4665
   Top             =   1800
   Width           =   4785
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   2880
      TabIndex        =   3
      Top             =   4320
      Width           =   1695
   End
   Begin VB.CommandButton cmdDocProperties 
      Caption         =   "Document Properties"
      Enabled         =   0   'False
      Height          =   375
      Left            =   2880
      TabIndex        =   2
      Top             =   600
      Width           =   1695
   End
   Begin VB.CommandButton cmdShowPrinters 
      Caption         =   "Show Printers"
      Height          =   375
      Left            =   2880
      TabIndex        =   1
      Top             =   120
      Width           =   1695
   End
   Begin VB.ListBox lstPrinters 
      BackColor       =   &H00C0E0FF&
      Height          =   840
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2655
   End
   Begin VB.Label lblResolution 
      BackColor       =   &H00C0E0FF&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   17
      Top             =   3360
      Width           =   2055
   End
   Begin VB.Label lblResolutionLabel 
      Caption         =   "Resolution:"
      Height          =   255
      Left            =   120
      TabIndex        =   16
      Top             =   3360
      Width           =   1215
   End
   Begin VB.Label lblCopies 
      BackColor       =   &H00C0E0FF&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   15
      Top             =   3000
      Width           =   2055
   End
   Begin VB.Label lblCopiesCaption 
      Caption         =   "Copies:"
      Height          =   255
      Left            =   120
      TabIndex        =   14
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label lblFieldMask 
      BackColor       =   &H00C0E0FF&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   13
      Top             =   2640
      Width           =   2055
   End
   Begin VB.Label lblFieldMaskLabel 
      Caption         =   "Field Mask:"
      Height          =   255
      Left            =   120
      TabIndex        =   12
      Top             =   2640
      Width           =   855
   End
   Begin VB.Label lblOrientation 
      BackColor       =   &H00C0E0FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   " "
      Height          =   255
      Left            =   1680
      TabIndex        =   11
      Top             =   2280
      Width           =   2055
   End
   Begin VB.Label lblOrientationLabel 
      Caption         =   "Orientation:"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   2280
      Width           =   855
   End
   Begin VB.Label lblDriverVersion 
      BackColor       =   &H00C0E0FF&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   9
      Top             =   1920
      Width           =   2055
   End
   Begin VB.Label lblDriverVersionLabel 
      Caption         =   "Spec Version:"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   1920
      Width           =   1575
   End
   Begin VB.Label lblDevModeVersion 
      BackColor       =   &H00C0E0FF&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   7
      Top             =   1560
      Width           =   2055
   End
   Begin VB.Label lblDevModeVersionLabel 
      Caption         =   "DevMode Version:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   1560
      Width           =   1455
   End
   Begin VB.Label lblDeviceName 
      BackColor       =   &H00C0E0FF&
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   5
      Top             =   1200
      Width           =   2055
   End
   Begin VB.Label lblDevNameLabel 
      Caption         =   "Device Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1200
      Width           =   1095
   End
End
Attribute VB_Name = "frmPrinters"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit


Private Sub cmdDocProperties_Click()
    Dim dm As DEVMODE, dmout As DEVMODE
    Dim bufsize&, res&
    Dim dmInBuf() As Byte
    Dim dmOutBuf() As Byte
    Dim hPrinter&
    Dim DeviceName$
    
    DeviceName$ = lstPrinters.Text

    hPrinter = OpenCurrPrinter(DeviceName$)
    
    If hPrinter = 0 Then
        MsgBox "Unable to open printer."
        Exit Sub
    End If
    
    '   The output DEVMODE structure will reflect any changes
    '   made by the printer dialog box.
    '   Note that no changes will be made to the default
    '   printer settings
    
    bufsize = DocumentProperties(hwnd, hPrinter, DeviceName$, 0, 0, 0)
    
    ReDim dmInBuf(bufsize)
    ReDim dmOutBuf(bufsize)
    
    res = DocumentProperties(hwnd, hPrinter, DeviceName$, _
     agGetAddressForObject(dmOutBuf(0)), agGetAddressForObject(dmInBuf(0)), _
     DM_OUT_BUFFER)
     
    ' Copy the data buffer into the DEVMODE structure
    agCopyData dmOutBuf(0), dmout, Len(dmout)
    ShowDevMode dmout

End Sub


Private Sub cmdExit_Click()
    End
End Sub

Private Sub cmdShowPrinters_Click()
    Dim rtn&, Buffer$, BufferLen&
    Dim nPos%, i%, cr%
    Buffer$ = String(255, 0)
    BufferLen& = Len(Buffer$)
    rtn& = GetProfileString("PrinterPorts", vbNullString, "", Buffer$, BufferLen&)
    Buffer$ = Left$(Buffer$, rtn&)
    nPos = 1
    lstPrinters.Clear
    Do
        cr = InStr(nPos, Buffer$, Chr$(0))
        lstPrinters.AddItem Mid$(Buffer$, nPos, (rtn& - (rtn& - cr)))
        nPos = cr + 1
        i = i + 1
    Loop While nPos < rtn&
    cmdShowPrinters.Enabled = False
End Sub



Private Sub lstPrinters_Click()
    cmdDocProperties.Enabled = True
    lblDeviceName.Caption = ""
    lblDevModeVersion.Caption = ""
    lblDriverVersion.Caption = ""
    lblOrientation.Caption = ""
    lblFieldMask.Caption = ""
    lblCopies.Caption = ""
    lblResolution.Caption = ""
End Sub


Private Sub lstPrinters_LostFocus()
    If Screen.ActiveControl.Name <> "cmdDocProperties" Then
        cmdDocProperties.Enabled = False
    End If
End Sub



Public Function OpenCurrPrinter(DeviceName$) As Long
    
    Dim hPrinter&, res&
    Dim pDefs As PRINTER_DEFAULTS
    
    pDefs.pDatatype = vbNullString
    pDefs.pDevMode = 0
    pDefs.DesiredAccess = 0
    
    ' Open the printer
    res& = OpenPrinter(DeviceName$, hPrinter&, pDefs)
    If res <> 0 Then OpenCurrPrinter = hPrinter
End Function




Private Function ShowDevMode(dm As DEVMODE)
    lblDeviceName.Caption = agGetStringFromLPSTR(dm.dmDeviceName)
    lblDevModeVersion.Caption = Hex$(dm.dmSpecVersion)
    lblDriverVersion.Caption = Hex$(dm.dmDriverVersion)
    If dm.dmOrientation = DMORIENT_PORTRAIT Then
        lblOrientation.Caption = "Portrait"
    Else
        lblOrientation.Caption = "Landscape"
    End If
    lblFieldMask.Caption = Hex$(dm.dmFields)
    lblCopies.Caption = dm.dmCopies
    If dm.dmFields And DM_YRESOLUTION <> 0 Then
        lblResolution.Caption = CStr(dm.dmPrintQuality) & "," & _
            dm.dmYResolution
    End If
    cmdDocProperties.Enabled = False
End Function
