//////////////////
// GrabData.cpp //
//   10/4/96    //
//////////////////

#include "grabdata.h"

int LibMain(HANDLE hinst, WORD wDataSeg, 
					WORD cbHeapSize, LPSTR lpszCmdLine)
{   
	if (cbHeapSize>0)
		UnlockData(0);
		
	return (hinst ? 1 : 0);
}                    

extern int FAR PASCAL _export GrabData(LPSAFEARRAY FAR *ppsa)
{                               
	long Ubound;			// Upper bound of array
	long ix[255];   		// Array to hold names
	int i, retcode;			
	BSTR element = NULL;    // BSTR to place back into array
	char szData[50];        // Array to hold individual data
	SDWORD dwNameLength;	// length of returned field
	HENV henv;				// Handle to an ODBC environment
	HDBC hdbc;				// Handle to an ODBC connection
	HSTMT hStmt;			// Handle to an ODBC statement
	                
	// retrieve the number of elements passed in,
	// assume a one dimensional array.
	SafeArrayGetUBound (*ppsa, 1, &Ubound); 
	
	// Fill array with indexes
	for (i=0;i<Ubound;i++)
		ix[i] = i;
	
	// Allocate ODBC environment
	retcode = SQLAllocEnv(&henv);
	if (retcode)
		return (-1);

	// Allocate the connection
	retcode = SQLAllocConnect(henv, &hdbc);
	if (retcode)
		return (-1);  
		
	// Connect          
	retcode = SQLConnect(hdbc,(UCHAR far*)"Customers", SQL_NTS,NULL, SQL_NTS, NULL, SQL_NTS); 
	if (retcode)
		return (-1);
			        
	// Allocate statement
	retcode = SQLAllocStmt(hdbc, &hStmt);
	if (retcode)
		return (-1);

	// Execute the statement
	retcode = SQLExecDirect(hStmt, (UCHAR far*)"SELECT [CONTACT_NA] FROM Customer ORDER BY [CONTACT_NA]", SQL_NTS);
	if (retcode)
		return (-1);   
		
   	i = 0;       
   	// Bind The column
   	SQLBindCol(hStmt, 1, SQL_C_CHAR, &szData, 30, &dwNameLength);
   	// build the data into the array
   	while (!retcode)
	{    
		retcode=SQLFetch(hStmt); 
		element = SysAllocString((BSTR)szData);
		if (!retcode)
			SafeArrayPutElement(*ppsa, &ix[i], element);
		SysFreeString (element); 
		i++;
	}                         
	
	// Free statement
	SQLFreeStmt(hStmt, SQL_DROP);
	// Disconnect from database
	SQLDisconnect(hdbc);       
	// Free connection
	SQLFreeConnect(hdbc);
	// Free environment
	SQLFreeEnv(henv);                    
	
	return (1);
}