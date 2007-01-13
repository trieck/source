Attribute VB_Name = "basDeclares"
#If Win32 Then
    Declare Function GetDiskFreeSpace _
    Lib "kernel32" Alias "GetDiskFreeSpaceA" _
    (ByVal lpRootPathName As String, _
    lpSectorsPerCluster As Long, _
    lpBytesPerSector As Long, _
    lpNumberOfFreeClusters As Long, _
    lpTotalNumberOfClusters As Long) As Long
#Else
    Declare Function DiskSpaceFree Lib _
    "STKIT416.DLL" () As Long
    Global Const gstrCOLON$ = ":"
#End If

    

Function GetDiskSpaceFree(ByVal strDrive As String) As Long
'Use Setup-API to find Free Space
'Use only for 16-bit Systems
#If Win16 Then
    Dim lDiskFree As Long
    
    'Change to the drive we want to check space for.  The DiskSpaceFree() API
    'works on the current drive only.
    '
    ChDrive strDrive

    '
    'If we couldn't change to the request drive, it's an error, otherwise return
    'the amount of disk space free
    '
    If Err <> 0 Then
        lDiskFree = -1
    Else
        lDiskFree = DiskSpaceFree()
        If Err <> 0 Then    'If Setup Toolkit's DLL couldn't be found
            lDiskFree = -1
        End If
    End If

    If lDiskFree = -1 Then
        MsgBox "Error retrieving Free Space", MB_ICONEXCLAMATION, "Disk Free Space"
    End If

    GetDiskSpaceFree = lDiskFree

    '
    'Cleanup by setting the current drive back to the original
    '
    ChDrive strCurDrive

    Err = 0
#End If
End Function



