
#include <windows.h>
#include <winioctl.h>

static const char hexish[] = "0123456789abcdef";
static char CharStr[17];

void WriteString(const char *s)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written;
	WriteFile(hConsole, s, strlen(s), &written, 0);
}

void WriteErr(const char *s)
{
	HANDLE hConsole = GetStdHandle(STD_ERROR_HANDLE);
	DWORD written;
	WriteFile(hConsole, s, strlen(s), &written, 0);
}

void PrintByte(BYTE b)
{
	char buf[3] = { 0 };

	BYTE hi = (b & 0xf0) >> 4;
	BYTE lo = (b & 0x0f);
	buf[0] = hexish[hi];
	buf[1] = hexish[lo];

	WriteString(buf);
}

void PrintWord(DWORD w)
{
	WriteString("0x");
	PrintByte(HIBYTE(w));
	PrintByte(LOBYTE(w));
}

void PrintDWord(DWORD dw)
{
	WriteString("0x");
	PrintByte(HIBYTE(HIWORD(dw)));
	PrintByte(LOBYTE(HIWORD(dw)));
	PrintByte(HIBYTE(LOWORD(dw)));
	PrintByte(LOBYTE(LOWORD(dw)));
}

void SetChar(BYTE b, int offset)
{
	if ((b >= 48 && b <= 90) || (b >=97 && b <= 122)) {
		CharStr[offset] = b;
	} else {
		CharStr[offset] = '.';
	} 
}

void PrintSector(HANDLE hFile, DISK_GEOMETRY *geom, __int64 track, DWORD sector)
{
	DWORD read, index;

	LPBYTE lpSector = (LPBYTE)VirtualAlloc (NULL, 
		geom->BytesPerSector,
		MEM_COMMIT|MEM_RESERVE, 
		PAGE_READWRITE);

	LARGE_INTEGER offset;
	offset.QuadPart = (geom->BytesPerSector * geom->SectorsPerTrack * track) +
		(sector * geom->BytesPerSector);

	offset.LowPart = SetFilePointer (hFile, offset.LowPart, &offset.HighPart, FILE_BEGIN);
	if (offset.LowPart == -1 && GetLastError() != NO_ERROR) { 
		WriteErr("unable to set file pointer.");
		VirtualFree(lpSector, 0, MEM_RELEASE);
		return;
	}

	if (!ReadFile (hFile, 
		lpSector, 
		geom->BytesPerSector, 
		&read, 
		NULL)) {
		WriteErr("unable to read file.");
		VirtualFree(lpSector, 0, MEM_RELEASE);
		return;
	}

	if (read == 0) {
		WriteErr("unable to read file.");
		VirtualFree(lpSector, 0, MEM_RELEASE);
	}

	for (DWORD i = 0; i <= read; i++) {
		index = i % 16;	
		
		if (i == read) {
			WriteString(CharStr);
			WriteString("\r\n");
			break;
		} else if (i > 0 && index == 0) {
			WriteString(CharStr);
			WriteString("\r\n");
		}
		
		if (index == 0) {
			PrintDWord(i);
			WriteString(": ");
		} 
		
		PrintByte(lpSector[i]);
		SetChar(lpSector[i], index);
		WriteString(" ");				
	}

	VirtualFree(lpSector, 0, MEM_RELEASE);
}

int ReadSector(char drive, __int64 track, DWORD sector)
{
	char buf[MAX_PATH];
	wsprintf(buf, "\\\\.\\%c:", drive);

	HANDLE hFile = CreateFile(
		buf, 
		GENERIC_READ,
        FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
        OPEN_EXISTING,
        0,
        NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		WriteErr("open failed.\r\n");
		return 1;
	}

	DISK_GEOMETRY geom;
	DWORD returned;
	DeviceIoControl(
		hFile,								/* device handle */
		IOCTL_DISK_GET_DRIVE_GEOMETRY,		/* control code */
		0,									/* input buffer ptr */
		0,									/* input buffer size */
		&geom,								/* output buffer ptr */
		sizeof(DISK_GEOMETRY),				/* output buffer size */
		&returned,							/* bytes returned ptr */
		0);									/* overlapped ptr */

	
	__int64 tracks = geom.Cylinders.QuadPart * geom.TracksPerCylinder;	

	// ensure valid track, sector
	if (track >= tracks ||
		sector >= geom.SectorsPerTrack) {
		wsprintf(buf, "invalid t/s#: %d,%d.\r\n", 
			track, sector);
		WriteErr(buf);
		CloseHandle(hFile);
		return 1;
	}

	PrintSector(hFile, &geom, track, sector);
	CloseHandle(hFile);

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc == 2) {
		;
	} else if (argc != 4) {
		WriteErr("usage: ts drive [track# sec#]\r\n");
		return 1;
	} else {
		return ReadSector(argv[1][0], _atoi64(argv[2]), atoi(argv[3]));
	}

	return 0;
}