/*-------------------------------
		   MERLIN.H			

	-	Protocol Specification			
		for Merlin Services	

	-	Created: 06/14/1997	
	-	Author:  Thomas A. Rieck

----------------------------------*/

#define	MAXMSGSPEC	80					// maximum size message specific data

// values for cType message field
#define	GET			1					// client sending request w/return data
#define	PUT			2					// client sending request w/o return data
#define	RSP			3					// response message from server

// values for cSubType message field
#define	DISK		1					// disk information

// values for cDetails message field
#define	ENUMDRIVES	1					// enumerate local drives
#define	DISKINFO	2					// byte size and free space

// error values for response message
#define	ERRORBADCMD	1
#define	ERROREXEC	2
#define	SUCCESS		3

// message structures
typedef struct 
{
	char	cType;
	char	cSubType;
	char	cDetails;
	char	cPad;						// align to even byte boundary
	char	cMsgSpec[MAXMSGSPEC];		// message specific data	
} REQUEST, *LPREQUEST;

typedef struct
{
	char			cType;
	char			cSubType;
	char			cDetails;
	char			cError;
	unsigned short	iMsgLen;
	char			cMsgSpec[MAXMSGSPEC];		// message specific data
} RESPONSE, *LPRESPONSE;

// message specific data structures

typedef struct
{
	unsigned long	lTotalBytes;
	unsigned long	lFreeBytes;
} DISKINFOSTRUCT, *LPDISKINFOSTRUCT;