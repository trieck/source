VERSION 5.00
Begin VB.Form frmFileInfo 
   BackColor       =   &H00808000&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "File Info"
   ClientHeight    =   4980
   ClientLeft      =   1755
   ClientTop       =   1890
   ClientWidth     =   6150
   FillStyle       =   0  'Solid
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "fileinfo.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4980
   ScaleWidth      =   6150
   ShowInTaskbar   =   0   'False
   Begin VB.DriveListBox Drive1 
      BackColor       =   &H00D2FDF8&
      Height          =   360
      Left            =   120
      TabIndex        =   4
      Top             =   3660
      Width           =   3255
   End
   Begin VB.DirListBox dirFiles 
      BackColor       =   &H00D2FDF8&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3390
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   3255
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "&Exit"
      Height          =   375
      Left            =   4800
      TabIndex        =   2
      Top             =   4560
      Width           =   1215
   End
   Begin VB.FileListBox flFiles 
      BackColor       =   &H00D2FDF8&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3690
      Hidden          =   -1  'True
      Left            =   3480
      System          =   -1  'True
      TabIndex        =   1
      Top             =   120
      Width           =   2535
   End
   Begin VB.CommandButton cmdFileInfo 
      Caption         =   "File Info"
      Height          =   375
      Left            =   4800
      TabIndex        =   0
      Top             =   4080
      Width           =   1215
   End
End
Attribute VB_Name = "frmFileInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Sub cmdExit_Click()
    Set X = Nothing
    Unload Me
End Sub


Private Sub cmdFileInfo_Click()
    Dim Message$
    
    If flFiles.ListIndex < 0 Then Exit Sub
    
    X.FilePath = dirFiles.Path & IIf(Right$(dirFiles.Path, 1) <> "\", "\", "") & flFiles.List(flFiles.ListIndex)
    
    Message$ = "Date Created: " & X.DateCreated & vbCrLf
    Message$ = Message$ & "File Path: " & X.FilePath & vbCrLf
    Message$ = Message$ & "File Size: " & Format(X.FileSize, "###,###,###") & " Bytes." & vbCrLf
    Message$ = Message$ & "File Attributes: " & X.Attributes
    
    MsgBox Message$, vbInformation, App.Title
    
End Sub



Private Sub dirFiles_Change()
    flFiles.Path = dirFiles.Path
End Sub

Private Sub Drive1_Change()
    On Error GoTo dError
    dirFiles.Path = Drive1.Drive
    Exit Sub
dError:
    MsgBox Error$, vbInformation, App.Title
    Exit Sub
    
End Sub

