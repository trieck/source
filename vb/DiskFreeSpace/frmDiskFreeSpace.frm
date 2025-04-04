VERSION 5.00
Begin VB.Form frmDiskFreeSpace 
   BackColor       =   &H00400000&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Disk Free Space"
   ClientHeight    =   4200
   ClientLeft      =   2565
   ClientTop       =   1905
   ClientWidth     =   4575
   Icon            =   "frmDiskFreeSpace.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4200
   ScaleWidth      =   4575
   Begin VB.DriveListBox Drive1 
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   9
      Top             =   3240
      Width           =   4335
   End
   Begin VB.CommandButton cmdShowDiskFreeSpace 
      Caption         =   "Show Disk Free Space"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   3720
      Width           =   4335
   End
   Begin VB.Label lblTotalBytes 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2280
      TabIndex        =   13
      Top             =   2520
      Width           =   2175
   End
   Begin VB.Label lblTotalFreeBytes 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2280
      TabIndex        =   12
      Top             =   2040
      Width           =   2175
   End
   Begin VB.Label lblTotalBytesLabel 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00400000&
      Caption         =   "Total Bytes:"
      ForeColor       =   &H00C0FFFF&
      Height          =   375
      Left            =   0
      TabIndex        =   11
      Top             =   2520
      Width           =   2175
   End
   Begin VB.Label lblTotalFreeBytesLabel 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00400000&
      Caption         =   "Total Free Bytes:"
      ForeColor       =   &H00C0FFFF&
      Height          =   375
      Left            =   0
      TabIndex        =   10
      Top             =   2040
      Width           =   2175
   End
   Begin VB.Label lblNumberofClusters 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2280
      TabIndex        =   8
      Top             =   1560
      Width           =   2175
   End
   Begin VB.Label lblTotalNumberofClustersLabel 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00400000&
      Caption         =   "Total Number of Clusters:"
      ForeColor       =   &H00C0FFFF&
      Height          =   375
      Left            =   0
      TabIndex        =   7
      Top             =   1560
      Width           =   2175
   End
   Begin VB.Label lblNumberofFreeClusters 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2280
      TabIndex        =   6
      Top             =   1080
      Width           =   2175
   End
   Begin VB.Label lblNumberofFreeClustersLabel 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00400000&
      Caption         =   "Number of Free Clusters:"
      ForeColor       =   &H00C0FFFF&
      Height          =   375
      Left            =   0
      TabIndex        =   5
      Top             =   1080
      Width           =   2175
   End
   Begin VB.Label lblBytesPerSector 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2280
      TabIndex        =   4
      Top             =   600
      Width           =   2175
   End
   Begin VB.Label lblBytesPerSectorLabel 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00400000&
      Caption         =   "Bytes Per Sector:"
      ForeColor       =   &H00C0FFFF&
      Height          =   375
      Left            =   0
      TabIndex        =   3
      Top             =   600
      Width           =   2175
   End
   Begin VB.Label lblSectorsPerCluster 
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2280
      TabIndex        =   2
      Top             =   120
      Width           =   2175
   End
   Begin VB.Label lblSectorsPerClusterLabel 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00400000&
      Caption         =   "Sectors Per Cluster:"
      ForeColor       =   &H00C0FFFF&
      Height          =   375
      Left            =   0
      TabIndex        =   1
      Top             =   120
      Width           =   2175
   End
End
Attribute VB_Name = "frmDiskFreeSpace"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdShowDiskFreeSpace_Click()
    Dim SectorsPerCluster&, _
        BytesPerSector&, NumberFreeClusters&, _
        TotalNumberClusters&, _
        FreeBytes&, TotalBytes&, Rtn&, s$, SpaceLoc%
    
    s$ = Drive1.Drive
    SpaceLoc% = InStr(s$, " ")
    If SpaceLoc% > 0 Then
        s$ = Left$(s$, SpaceLoc% - 1)
    End If
    If Right$(s$, 1) <> "\" Then s$ = s$ & "\"
    
    Rtn& = GetDiskFreeSpace(s$, SectorsPerCluster&, _
        BytesPerSector&, NumberFreeClusters&, TotalNumberClusters&)
    
    lblSectorsPerCluster.Caption = Format(SectorsPerCluster&, "#,0")
    lblBytesPerSector.Caption = Format(BytesPerSector&, "#,0")
    lblNumberofFreeClusters.Caption = Format(NumberFreeClusters&, "#,0")
    lblNumberofClusters.Caption = Format(TotalNumberClusters&, "#,0")
    FreeBytes& = NumberFreeClusters& * SectorsPerCluster& * BytesPerSector&
    lblTotalFreeBytes.Caption = Format(FreeBytes&, "#,0")
    TotalBytes& = TotalNumberClusters& * SectorsPerCluster& * BytesPerSector&
    lblTotalBytes.Caption = Format(TotalBytes&, "#,0")
End Sub


Private Sub Drive1_Change()
    lblSectorsPerCluster.Caption = ""
    lblBytesPerSector.Caption = ""
    lblNumberofFreeClusters.Caption = ""
    lblNumberofClusters.Caption = ""
    lblTotalFreeBytes.Caption = ""
    lblTotalBytes.Caption = ""
End Sub


