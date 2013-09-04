
//////////////////////////
//						//
//    NORTHWIND.CPP 	//
//       9/8/96			//
//						//
//////////////////////////

#include "northwind.h"

HANDLE ghInst;					// Instance Handle for dialogs
HINSTANCE hInstLib;				// Handle to Crystal Reports Library
HWND hWnd;		   				// Handle for main window
HWND hWndList;		   			// Handle for list box
HWND hDlg;						// Handle for Dialog;
HENV henv;						// Handle for an ODBC environment
HDBC hdbc;						// Handle for an ODBC connection
RETCODE retcode;				// Return code
HSTMT hStmt;					// Handle for a statement
SDWORD far* dwNameLength;		// Length of each entry
HFONT hFont;					// Handle for font
FARPROC lpDialogProc;			// Dialog Proc
MYPROC CloseEngineProc;			// CloseEngine Procedure

//////////////////////
// WinMain Function //
//////////////////////
int pascal WinMain(HINSTANCE hInstance, HINSTANCE hInstPrevious, LPSTR lpCmdLine,int nCmdShow)
{
	WNDCLASS WindowClass; 		// Structure to hold windows attributes
	MYPROC OpenEngineProc;		// OpenEngine Procedure;
	MSG msg;
	static char szAppName[] = "Tom";

	if (!hInstPrevious) {
		WindowClass.style = NULL;
		WindowClass.lpfnWndProc = WindowProc;
		WindowClass.cbClsExtra = 0;
		WindowClass.cbWndExtra = 0;
		WindowClass.hInstance = hInstance;
		WindowClass.hIcon = LoadIcon (hInstance, "PLANET");
		WindowClass.hCursor = LoadCursor (NULL, IDC_ARROW);
		WindowClass.hbrBackground = GetSysColorBrush(COLOR_MENU);
		WindowClass.lpszMenuName =  "MAINMENU";
		WindowClass.lpszClassName = szAppName;

		if (!RegisterClass (&WindowClass))
			return (FALSE);
	}
	// Create main window
	hWnd = CreateWindow(
	           szAppName,				// window class name
	           "Northwind Database",	// window title
	           WS_OVERLAPPED |			// window style
	           WS_CAPTION |
	           WS_SYSMENU |
	           WS_MINIMIZEBOX,
	           120,				 	// set screen position
	           25,
	           600,			        // set window size
	           520,
	           NULL,					// no parent window
	           NULL,        			// main menu
	           hInstance,				// program instance handle
	           NULL                    // no window creation data
	       );

	// Set up database connection

	// Allocate ODBC environment
	retcode = SQLAllocEnv(&henv);
	if (retcode)
		GetErrorMsg("Allocating Environment");

	// Allocate the connection
	retcode = SQLAllocConnect(henv, &hdbc);
	if (retcode)
		GetErrorMsg("Allocating Connection");
	// Connect
	retcode = SQLConnect(hdbc,(UCHAR far*)"NorthWind", SQL_NTS,NULL, SQL_NTS, NULL, SQL_NTS);
	if (retcode)
		GetErrorMsg("Connecting");

	// Link to Crystal Reports Library
	hInstLib = LoadLibrary("crpe32.dll");

	if (hInstLib) {
		// Get Procedure addresses
		OpenEngineProc = (MYPROC) GetProcAddress(hInstLib, "PEOpenEngine");
		CloseEngineProc = (MYPROC) GetProcAddress(hInstLib, "PECloseEngine");
	}
	// Open the Print Engine
	(OpenEngineProc)();


	// Find the client rectangle
	RECT ClientRect;
	GetClientRect(hWnd, &ClientRect);

	// Get DC
	HDC lbDC;
	lbDC = GetDC(hWndList);

	// Create a font for List Box
	hFont =  CreateFont(
	             -MulDiv(8, GetDeviceCaps(lbDC, LOGPIXELSY), 72),
	             0,
	             0,
	             0,
	             400,
	             FALSE,
	             FALSE,
	             FALSE,
	             DEFAULT_CHARSET,
	             OUT_DEFAULT_PRECIS,
	             CLIP_DEFAULT_PRECIS,
	             DEFAULT_QUALITY,
	             DEFAULT_PITCH,
	             "MS Sans Serif");

	// Release DC
	ReleaseDC(hWndList, lbDC);

	// Create the list box
	hWndList =	CreateWindowEx(
	                WS_EX_CLIENTEDGE,
	                "LISTBOX",
	                NULL,
	                WS_CHILD |
	                WS_VSCROLL |
	                WS_VISIBLE |
	                LBS_NOTIFY |
	                LBS_NOINTEGRALHEIGHT,
	                NULL,
	                NULL,
	                ((ClientRect.right - ClientRect.left)/2),
	                (ClientRect.bottom - ClientRect.top),
	                hWnd,
	                (HMENU)ID_LISTBOX1,
	                hInstance,
	                NULL);

	// Set font for list box
	SendMessage(hWndList, WM_SETFONT, (WPARAM)hFont,0);

	// Display the main window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	ghInst = hInstance;

	// the message loop
	while (GetMessage(&msg, 0,0,0)) { // get any messages
		TranslateMessage(&msg);		// translate message
		DispatchMessage(&msg);		// dispatch message
	}
	return msg.wParam;				// end so return to Windows
}

/////////////////////////
// WindowProc Function //
/////////////////////////
long pascal WindowProc (HWND hWnd, UINT message,
                        WPARAM wParam, LPARAM lParam)
{
	HMENU hSubMnu;
	int count, i, rslt;

	switch (message) {		// process selected messages
	case WM_COMMAND:	// message to handle control commands
		switch (LOWORD(wParam)) {
		case ID_LISTBOX1:
			// Messages for LISTBOX1
			if (HIWORD(wParam) == LBN_SELCHANGE) {

				// How many items in menu
				hSubMnu = GetSubMenu(GetMenu(hWnd), 1);
				count = GetMenuItemCount(hSubMnu);
				// Determine which one is checked
				for (i=0; i<count-1; i++) {
					rslt = GetMenuState(hSubMnu,
					                    i,
					                    MF_BYPOSITION);
					if (rslt & MFS_CHECKED)
						break;
				}
				// Display appropriate information
				switch (i) {
				case 0:
					DisplayCategoryInfo();
					break;
				case 1:
					DisplayCustomerInfo();
					break;
				case 2:
					DisplayEmployeeInfo();
					break;
				case 3:
					DisplayOrderDetails();
					break;
				case 4:
					DisplayOrders();
					break;
				case 5:
					DisplayProducts();
					break;
				case 6:
					DisplayShipperInfo();
					break;
				case 7:
					DisplaySupplierInfo();
					break;
				default:
					break;
				}
			}
			return 0;
		case ID_VIEW_CATEGORIES: {
			UncheckMenus();
			DoNewView(ID_VIEW_CATEGORIES, (char*)ID_CATDLG);
		}
		return 0;
		case ID_VIEW_CUSTOMERS: {
			UncheckMenus();
			DoNewView(ID_VIEW_CUSTOMERS,(char*) ID_CUSTDLG);
		}
		return 0;
		case ID_VIEW_EMPLOYEES: {
			UncheckMenus();
			DoNewView(ID_VIEW_EMPLOYEES, (char*)ID_EMPDLG);
		}
		return 0;
		case ID_VIEW_ORDERDETAILS: {
			UncheckMenus();
			DoNewView(ID_VIEW_ORDERDETAILS, (char*)ID_ORDDETDLG);
		}
		return 0;
		case ID_VIEW_ORDERS: {
			UncheckMenus();
			DoNewView(ID_VIEW_ORDERS, (char*)ID_ORDERSDLG);
		}
		return 0;
		case ID_VIEW_PRODUCTS: {
			UncheckMenus();
			DoNewView(ID_VIEW_PRODUCTS, (char*)ID_PRODUCTSDLG);
		}
		return 0;
		case ID_VIEW_SHIPPERS: {
			UncheckMenus();
			DoNewView(ID_VIEW_SHIPPERS, (char*)ID_SHIPPERSDLG);
		}
		return 0;
		case ID_VIEW_SUPPLIERS: {
			UncheckMenus();
			DoNewView(ID_VIEW_SUPPLIERS, (char*)ID_SUPPLIERSDLG);
		}
		return 0;
		case ID_REPORTS_SALESBYCATEGORY: {

			Reports(hInstLib,1);
		}
		return 0;
		case ID_REPORTS_SALESBYYEAR: {
			Reports(hInstLib,2);
		}
		return 0;
		case ID_REPORTS_CUSTOMERSANDSUPPLIERSBYCITY: {
			Reports(hInstLib, 3);
		}
		return 0;
		case ID_REPORTS_EMPLOYEESALESBYCOUNTRY: {
			Reports(hInstLib, 4);
		}
		return 0;
		case ID_HELP_ABOUT:
			// user selected "About"
			lpDialogProc = MakeProcInstance ((FARPROC)About, ghInst);
			DialogBox (ghInst,
			           "AboutBox",
			           hWnd,
			           lpDialogProc);
			FreeProcInstance (lpDialogProc);
			return 0;
		case ID_FILE_EXIT:
			// Exit application
			SendMessage(hWnd, WM_CLOSE,0,0);
			return 0;
		default:
			return 0;
		};

	case WM_DESTROY:	// window is being destroyed
		// Free statement
		retcode = SQLFreeStmt(hStmt, SQL_DROP);
		// Disconnect from database
		SQLDisconnect(hdbc);
		// Free connection
		SQLFreeConnect(hdbc);
		// Free environment
		SQLFreeEnv(henv);
		// Close Print Engine
		if (hInstLib)
			(CloseEngineProc)();
		// Free the library
		FreeLibrary(hInstLib);
		// Delete the font object
		DeleteObject(hFont);
		// quit
		PostQuitMessage(0);
		return 0;
	default:	// Any other message - we don't want to know,
		// so call default message processing
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

///////////////////////
// ViewProc Function //
///////////////////////
BOOL ViewProc(HWND hDlg, unsigned message,
              WORD wParam, LONG lParam)
{
	switch (message) {
	case WM_INITDIALOG:
		RECT ClientRect;
		RECT dlgRect;
		GetClientRect(hWnd, &ClientRect);
		GetWindowRect(hDlg, &dlgRect);
		MoveWindow(hDlg,
		           (ClientRect.right - ClientRect.left)/2,
		           0,
		           dlgRect.right- dlgRect.left,
		           dlgRect.bottom - dlgRect.top,
		           TRUE);
		return (TRUE);
	}
	return DefWindowProc(hDlg, message, wParam, lParam);
}
////////////////////
// About Function //
////////////////////
BOOL About(HWND hDlg, unsigned message,
           WORD wParam, LONG lParam)
{

	switch (message) {
	case WM_INITDIALOG:
		// Center dialog box
		RECT aRect;
		RECT DlgRect;
		GetWindowRect(hWnd, &aRect);
		GetWindowRect(hDlg, &DlgRect);
		MoveWindow(hDlg,
		           (aRect.right - aRect.left)/2,
		           (aRect.bottom - aRect.top)/2,
		           (DlgRect.right - DlgRect.left),
		           (DlgRect.bottom - DlgRect.top),
		           FALSE);
		return (TRUE);
	case WM_COMMAND:
		switch (wParam) {
		case IDOK:
		case IDCANCEL:
			EndDialog (hDlg, TRUE);
			return (TRUE);
		default:
			break;
		}
	}
	return (FALSE);
}

///////////////////////////
// UncheckMenus Function //
///////////////////////////
void UncheckMenus()
{
	HMENU hSubMnu;
	int count;
	int i;
	hSubMnu = GetSubMenu(GetMenu(hWnd), 1);
	count = GetMenuItemCount(hSubMnu);
	for (i=0; i<count+1; i++) {
		CheckMenuItem(hSubMnu,
		              i,
		              MF_BYPOSITION |
		              MF_UNCHECKED
		             );
	}
}

////////////////////////
// DoNewView Function //
////////////////////////
void DoNewView(UINT MenuItem, char* NewView)
{
	HMENU hSubMnu;
	UCHAR szData[50]; // Storage for each Name

	// Check appropriate menu
	hSubMnu = GetSubMenu(GetMenu(hWnd), 1);
	CheckMenuItem(hSubMnu,
	              MenuItem,
	              MF_BYCOMMAND |
	              MF_CHECKED);

	// Clear the List Box
	SendMessage(hWndList, LB_RESETCONTENT, 0, 0);

	// Destroy the current view
	DestroyWindow(hDlg);

	// Show the New View
	lpDialogProc = MakeProcInstance ((FARPROC)ViewProc, ghInst);
	hDlg =  CreateDialog (ghInst,
	                      NewView,
	                      hWnd,
	                      lpDialogProc);
	FreeProcInstance (lpDialogProc);

	ShowWindow(hDlg, SW_SHOW);

	// Drop current statement
	if (hStmt) {
		retcode = SQLFreeStmt(hStmt, SQL_DROP);
		if (retcode)
			GetErrorMsg("Dropping statement");
	}

	// Allocate statement
	retcode = SQLAllocStmt(hdbc, &hStmt);
	if (retcode)
		GetErrorMsg("Allocating statement");

	// Execute the statement
	if (NewView ==(char*)ID_CATDLG) {
		retcode = SQLExecDirect(hStmt, (UCHAR far*)"SELECT CategoryName FROM CATEGORIES", SQL_NTS);
		if (retcode)
			GetErrorMsg("Executing statement");
	}
	if (NewView == (char*)ID_CUSTDLG) {
		retcode = SQLExecDirect(hStmt, (UCHAR far*)"SELECT CompanyName FROM CUSTOMERS", SQL_NTS);
		if (retcode)
			GetErrorMsg("Executing statement");
	}
	if (NewView == (char*)ID_EMPDLG) {
		retcode = SQLExecDirect(hStmt, (UCHAR far*)"SELECT LastName FROM EMPLOYEES ORDER BY LastName", SQL_NTS);
		if (retcode)
			GetErrorMsg("Executing statement");
	}
	if (NewView == (char*)ID_ORDDETDLG) {
		retcode = SQLExecDirect(hStmt, (UCHAR far*)"SELECT OrderId FROM [Order Details]", SQL_NTS);
		if (retcode)
			GetErrorMsg("Executing statement");
	}
	if (NewView == (char*)ID_ORDERSDLG) {
		retcode = SQLExecDirect(hStmt, (UCHAR far*)"SELECT OrderID FROM Orders", SQL_NTS);
		if (retcode)
			GetErrorMsg("Executing statement");
	}
	if (NewView == (char*)ID_PRODUCTSDLG) {
		retcode = SQLExecDirect(hStmt, (UCHAR far*)"SELECT ProductName FROM Products ORDER BY ProductName", SQL_NTS);
		if (retcode)
			GetErrorMsg("Executing statement");
	}
	if (NewView == (char*)ID_SHIPPERSDLG) {
		retcode = SQLExecDirect(hStmt, (UCHAR far*)"SELECT CompanyName FROM Shippers ORDER BY CompanyName", SQL_NTS);
		if (retcode)
			GetErrorMsg("Executing statement");
	}
	if (NewView == (char*)ID_SUPPLIERSDLG) {
		retcode = SQLExecDirect(hStmt, (UCHAR far*)"SELECT CompanyName FROM Suppliers ORDER BY CompanyName", SQL_NTS);
		if (retcode)
			GetErrorMsg("Executing statement");
	}

	// Fill the list box
	while (!retcode) {
		retcode=SQLFetch(hStmt); // move to next row
		retcode = SQLGetData(hStmt, 1, SQL_C_CHAR, &szData, 51, dwNameLength); //Get the data
		if (!retcode)
			SendMessage(hWndList, LB_ADDSTRING, 0 , (LPARAM)(LPCSTR)szData); // Fill the list box
	}

}

//////////////////////////
// GetErrorMsg Function //
//////////////////////////

// Use for ODBC Errors
void  GetErrorMsg(LPSTR Cause)
{

	UCHAR szSqlState[6];
// Note remember to allocate on the heap
	UCHAR *pszErrorMsg;
	if (!(pszErrorMsg = new UCHAR[SQL_MAX_MESSAGE_LENGTH]))
		return;

	SDWORD dwNativeError;
	SWORD wErrorMsg;

	SQLError(
	    henv, hdbc, hStmt, szSqlState,
	    &dwNativeError, pszErrorMsg,
	    SQL_MAX_MESSAGE_LENGTH-1, &wErrorMsg);
	MessageBox (hWnd,(const char*)pszErrorMsg, Cause, MB_ICONHAND);
	delete pszErrorMsg;
	DestroyWindow(hWnd);
}

/////////////////////////
// DisplayCategoryInfo //
/////////////////////////
void DisplayCategoryInfo()
{
	char szCategoryName[50];	// Storage for category name
	char szDescription[255];	// Storage for description
	int iIndex;

	// Free statement handle
	retcode = SQLFreeStmt(hStmt, SQL_CLOSE);
	// Prepare statement
	retcode = SQLPrepare(hStmt,
	                     (UCHAR*)"SELECT CategoryName, Description FROM Categories WHERE CategoryName = (?)",
	                     SQL_NTS);
	if (retcode)
		GetErrorMsg("Preparing statement");
	else {
		// Find out which item is selected
		iIndex = (int)SendMessage(hWndList, LB_GETCURSEL,0,0);
		// Get text for that item
		SendMessage(hWndList, LB_GETTEXT, iIndex,(LPARAM)(LPCSTR) szCategoryName);
		// Bind SQL Parameters
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT,
		                           SQL_C_CHAR, SQL_CHAR, lstrlen(szCategoryName),
		                           0, (PTR)&szCategoryName, sizeof(szCategoryName), NULL);
		if (retcode)
			GetErrorMsg("Binding parameter");
		else
			// Execute the statement
		{
			retcode = SQLExecute(hStmt);
			if (retcode)
				GetErrorMsg("Executing binded statement");
			else {
				// Get Record Information
				while (!retcode) {
					retcode=SQLFetch(hStmt);
					retcode = SQLGetData(hStmt, 1, SQL_C_CHAR, &szCategoryName, 51, dwNameLength);
					retcode = SQLGetData(hStmt, 2, SQL_C_CHAR, &szDescription, 256, dwNameLength);
				}
				// Set Record Information
				SetDlgItemText(hDlg, IDC_EDCATNAME, (LPCSTR)szCategoryName);
				SetDlgItemText(hDlg, IDC_EDCATDESC, (LPCSTR)szDescription);
			}
		}
	}
}

/////////////////////////
// DisplayCustomerInfo //
/////////////////////////
void DisplayCustomerInfo()
{
	char szCompanyName[50]; // Storage for company name
	char szContactName[50];	// Storage for contact name
	char szContactTitle[50];// Storage for contact title
	char szAddress[100];	// Storage for Address
	char szCity[50];		// Storage for City
	char szRegion[25];		// Storage for Region
	char szPostCode[20];	// Storage for Postal Code
	char szCountry[20];		// Storage for Country
	char szPhone[20];		// Storage for Phone
	char szFax[20];			// Storage for Fax
	int iIndex;				// Currently selected list item
	// Free statement handle
	retcode = SQLFreeStmt(hStmt, SQL_CLOSE);
	// Prepare statement
	retcode = SQLPrepare(hStmt,
	                     (UCHAR*)"SELECT * FROM CUSTOMERS WHERE CompanyName = (?)",
	                     SQL_NTS);
	if (retcode)
		GetErrorMsg("Preparing statement");
	else {
		// Find out which item is selected
		iIndex = (int)SendMessage(hWndList, LB_GETCURSEL,0,0);
		// Get text for that item
		SendMessage(hWndList, LB_GETTEXT, iIndex,(LPARAM)(LPCSTR) szCompanyName);
		// Bind SQL Parameters
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT,
		                           SQL_C_CHAR, SQL_CHAR, lstrlen(szCompanyName),
		                           0, (PTR)&szCompanyName, sizeof(szCompanyName), NULL);
		if (retcode)
			GetErrorMsg("Binding parameter");
		else
			// Execute the statement
		{
			retcode = SQLExecute(hStmt);
			if (retcode)
				GetErrorMsg("Executing binded statement");
			else {
				// Get Record Information
				while (!retcode) {
					retcode=SQLFetch(hStmt);
					retcode = SQLGetData(hStmt, 3, SQL_C_CHAR, &szContactName, 51, dwNameLength);
					retcode = SQLGetData(hStmt, 4, SQL_C_CHAR, &szContactTitle, 51, dwNameLength);
					retcode = SQLGetData(hStmt, 5, SQL_C_CHAR, &szAddress, 101, dwNameLength);
					retcode = SQLGetData(hStmt, 6, SQL_C_CHAR, &szCity, 51, dwNameLength);
					retcode = SQLGetData(hStmt, 7, SQL_C_CHAR, &szRegion, 26, dwNameLength);
					retcode = SQLGetData(hStmt, 8, SQL_C_CHAR, &szPostCode, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 9, SQL_C_CHAR, &szCountry, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 10, SQL_C_CHAR, &szPhone, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 11, SQL_C_CHAR, &szFax, 21, dwNameLength);
				}
				// Set Record Information
				SetDlgItemText(hDlg, IDC_EDCONNAME, (LPCSTR)szContactName);
				SetDlgItemText(hDlg, IDC_EDCONTITLE, (LPCSTR)szContactTitle);
				SetDlgItemText(hDlg, IDC_EDADDRESS, (LPCSTR)szAddress);
				SetDlgItemText(hDlg, IDC_EDCITY, (LPCSTR)szCity);
				SetDlgItemText(hDlg, IDC_EDREGION, (LPCSTR)szRegion);
				SetDlgItemText(hDlg, IDC_EDPOSTCODE, (LPCSTR)szPostCode);
				SetDlgItemText(hDlg, IDC_EDCOUNTRY, (LPCSTR)szCountry);
				SetDlgItemText(hDlg, IDC_EDPHONE, (LPCSTR)szPhone);
				SetDlgItemText(hDlg, IDC_EDFAX, (LPCSTR)szFax);
			}
		}
	}
}
/////////////////////////
// DisplayEmployeeInfo //
/////////////////////////
void DisplayEmployeeInfo()
{
	char szLastName[30];    // Storage for last name
	char szFirstName[30];	// Storage for first name
	char szTitle[50];		// Storage for title
	char szTOC[5];			// Storage for title of courtesy
	char szBirthDate[20];	// Storage for birth date
	char szHireDate[20];	// Storage for hire date
	char szAddress[30];		// Storage for address
	char szCity[20];		// Storage for city
	char szRegion[5];		// Storage for region
	char szPostalCode[20];	// Storage for postal code
	char szCountry[20];		// Storage for country
	char szHomePhone[20];	// Storage for home phone
	char szExtension[20];	// Storage for extension
	char szNotes[512];		// Storage for notes
	char szReportsTo[3];	// Storage for reports to


	int iIndex;				// Currently selected list item
	// Free statement handle
	retcode = SQLFreeStmt(hStmt, SQL_CLOSE);
	// Prepare statement
	retcode = SQLPrepare(hStmt,
	                     (UCHAR*)"SELECT * FROM Employees WHERE LastName = (?)",
	                     SQL_NTS);
	if (retcode)
		GetErrorMsg("Preparing statement");
	else {
		// Find out which item is selected
		iIndex = (int)SendMessage(hWndList, LB_GETCURSEL,0,0);
		// Get text for that item
		SendMessage(hWndList, LB_GETTEXT, iIndex,(LPARAM)(LPCSTR) szLastName);
		// Bind SQL Parameters
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT,
		                           SQL_C_CHAR, SQL_CHAR, lstrlen(szLastName),
		                           0, (PTR)&szLastName, sizeof(szLastName), NULL);
		if (retcode)
			GetErrorMsg("Binding parameter");
		else
			// Execute the statement
		{
			retcode = SQLExecute(hStmt);
			if (retcode)
				GetErrorMsg("Executing binded statement");
			else {
				// Get Record Information
				while (!retcode) {
					retcode=SQLFetch(hStmt);
					retcode = SQLGetData(hStmt, 2, SQL_C_CHAR, &szLastName, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 3, SQL_C_CHAR, &szFirstName, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 4, SQL_C_CHAR, &szTitle, 51, dwNameLength);
					retcode = SQLGetData(hStmt, 5, SQL_C_CHAR, &szTOC, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 6, SQL_C_CHAR, &szBirthDate, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 7, SQL_C_CHAR, &szHireDate, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 8, SQL_C_CHAR, &szAddress, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 9, SQL_C_CHAR, &szCity, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 10, SQL_C_CHAR, &szRegion, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 11, SQL_C_CHAR, &szPostalCode, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 12, SQL_C_CHAR, &szCountry, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 13, SQL_C_CHAR, &szHomePhone, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 14, SQL_C_CHAR, &szExtension, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 16, SQL_C_CHAR, &szNotes, 513, dwNameLength);
					retcode = SQLGetData(hStmt, 17, SQL_C_CHAR, &szReportsTo, 3, dwNameLength);
				}
				// Set Record Information
				SetDlgItemText(hDlg, IDC_EDLASTNAME, (LPCSTR)szLastName);
				SetDlgItemText(hDlg, IDC_EDFIRSTNAME, (LPCSTR)szFirstName);
				SetDlgItemText(hDlg, IDC_EDTITLE, (LPCSTR)szTitle);
				SetDlgItemText(hDlg, IDC_EDTOC, (LPCSTR)szTOC);
				SetDlgItemText(hDlg, IDC_EDBIRTHDATE, (LPCSTR)szBirthDate);
				SetDlgItemText(hDlg, IDC_EDHIREDATE, (LPCSTR)szHireDate);
				SetDlgItemText(hDlg, IDC_EDADDRESS, (LPCSTR)szAddress);
				SetDlgItemText(hDlg, IDC_EDCITY, (LPCSTR)szCity);
				SetDlgItemText(hDlg, IDC_EDREGION, (LPCSTR)szRegion);
				SetDlgItemText(hDlg, IDC_EDPOSTALCODE, (LPCSTR)szPostalCode);
				SetDlgItemText(hDlg, IDC_EDCOUNTRY, (LPCSTR)szCountry);
				SetDlgItemText(hDlg, IDC_EDHOMEPHONE, (LPCSTR)szHomePhone);
				SetDlgItemText(hDlg, IDC_EDEXTENSION, (LPCSTR)szExtension);
				SetDlgItemText(hDlg, IDC_EDNOTES, (LPCSTR)szNotes);
				SetDlgItemText(hDlg, IDC_EDREPORTSTO, (LPCSTR)szReportsTo);
			}
		}
	}
}

/////////////////////////
// DisplayOrderDetails //
/////////////////////////
void DisplayOrderDetails ()
{
	char szOrderID[7];		// Storage for Order ID
	char szProductID[5];	// Storage for Product ID
	char szUnitPrice[10];	// Storage for Unit price
	char szQuantity[5];		// Storage for Quantity
	char szDiscount[5];		// Storage for Discount


	int iIndex;				// Currently selected list item
	// Free statement handle
	retcode = SQLFreeStmt(hStmt, SQL_CLOSE);
	// Prepare statement
	retcode = SQLPrepare(hStmt,
	                     (UCHAR*)"SELECT * FROM [Order Details] WHERE OrderID = (?)",
	                     SQL_NTS);
	if (retcode)
		GetErrorMsg("Preparing statement");
	else {
		// Find out which item is selected
		iIndex = (int)SendMessage(hWndList, LB_GETCURSEL,0,0);
		// Get text for that item
		SendMessage(hWndList, LB_GETTEXT, iIndex,(LPARAM)(LPCSTR) szOrderID);
		// Bind SQL Parameters
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT,
		                           SQL_C_CHAR, SQL_INTEGER, lstrlen(szOrderID),
		                           0, (PTR)&szOrderID, sizeof(szOrderID), NULL);
		if (retcode)
			GetErrorMsg("Binding parameter");
		else
			// Execute the statement
		{
			retcode = SQLExecute(hStmt);
			if (retcode)
				GetErrorMsg("Executing binded statement");
			else {
				// Get Record Information
				while (!retcode) {
					retcode=SQLFetch(hStmt);
					retcode = SQLGetData(hStmt, 1, SQL_C_CHAR, &szOrderID, 8, dwNameLength);
					retcode = SQLGetData(hStmt, 2, SQL_C_CHAR, &szProductID, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 3, SQL_C_CHAR, &szUnitPrice, 11, dwNameLength);
					retcode = SQLGetData(hStmt, 4, SQL_C_CHAR, &szQuantity, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 5, SQL_C_CHAR, &szDiscount, 6, dwNameLength);
				}
				// Set Record Information
				SetDlgItemText(hDlg, IDC_EDORDERID, (LPCSTR)szOrderID);
				SetDlgItemText(hDlg, IDC_EDPRODUCTID, (LPCSTR)szProductID);
				SetDlgItemText(hDlg, IDC_EDUNITPRICE, (LPCSTR)szUnitPrice);
				SetDlgItemText(hDlg, IDC_EDQUANTITY, (LPCSTR)szQuantity);
				SetDlgItemText(hDlg, IDC_EDDISCOUNT, (LPCSTR)szDiscount);
			}
		}
	}
}

////////////////////////////
// DisplayOrders function //
////////////////////////////

void DisplayOrders()
{
	char szOrderID[7];	    // Storage for Order ID
	char szCustomerID[7];	// Storage for Customer ID
	char szEmployeeID[5];	// Storage for Employee ID
	char szOrderDate[20];	// Storage for Order date
	char szRequireDate[20];	// Storage for Require date
	char szShipDate[20];	// Storage for Ship date
	char szShipVia[3];		// Storage for Ship via
	char szFreight[10];		// Storage for Freight
	char szShipName[30];	// Storage for Ship Name
	char szShipAddress[30];	// Storage for Ship Address
	char szShipCity[20];	// Storage for Ship City
	char szShipRegion[20];	// Storage for Ship Region
	char szShipPostal[20];	// Storage for Ship Postal
	char szShipCountry[20]; // Storage for Ship Country

	int iIndex;				// Currently selected list item
	// Free statement handle
	retcode = SQLFreeStmt(hStmt, SQL_CLOSE);
	// Prepare statement
	retcode = SQLPrepare(hStmt,
	                     (UCHAR*)"SELECT * FROM Orders WHERE OrderID = (?)",
	                     SQL_NTS);
	if (retcode)
		GetErrorMsg("Preparing statement");
	else {
		// Find out which item is selected
		iIndex = (int)SendMessage(hWndList, LB_GETCURSEL,0,0);
		// Get text for that item
		SendMessage(hWndList, LB_GETTEXT, iIndex,(LPARAM)(LPCSTR) szOrderID);
		// Bind SQL Parameters
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT,
		                           SQL_C_CHAR, SQL_INTEGER, lstrlen(szOrderID),
		                           0, (PTR)&szOrderID, sizeof(szOrderID), NULL);
		if (retcode)
			GetErrorMsg("Binding parameter");
		else
			// Execute the statement
		{
			retcode = SQLExecute(hStmt);
			if (retcode)
				GetErrorMsg("Executing binded statement");
			else {
				// Get Record Information
				while (!retcode) {
					retcode=SQLFetch(hStmt);
					retcode = SQLGetData(hStmt, 1, SQL_C_CHAR, &szOrderID, 8, dwNameLength);
					retcode = SQLGetData(hStmt, 2, SQL_C_CHAR, &szCustomerID, 8, dwNameLength);
					retcode = SQLGetData(hStmt, 3, SQL_C_CHAR, &szEmployeeID, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 4, SQL_C_CHAR, &szOrderDate, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 5, SQL_C_CHAR, &szRequireDate, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 6, SQL_C_CHAR, &szShipDate, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 7, SQL_C_CHAR, &szShipVia, 4, dwNameLength);
					retcode = SQLGetData(hStmt, 8, SQL_C_CHAR, &szFreight, 11, dwNameLength);
					retcode = SQLGetData(hStmt, 9, SQL_C_CHAR, &szShipName, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 10, SQL_C_CHAR, &szShipAddress, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 11, SQL_C_CHAR, &szShipCity, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 12, SQL_C_CHAR, &szShipRegion, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 13, SQL_C_CHAR, &szShipPostal, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 14, SQL_C_CHAR, &szShipCountry, 21, dwNameLength);
				}
				// Set Record Information
				SetDlgItemText(hDlg, IDC_EDORDERID, (LPCSTR)szOrderID);
				SetDlgItemText(hDlg, IDC_EDCUSTID, (LPCSTR)szCustomerID);
				SetDlgItemText(hDlg, IDC_EDEMPID, (LPCSTR)szEmployeeID);
				SetDlgItemText(hDlg, IDC_EDORDDATE, (LPCSTR)szOrderDate);
				SetDlgItemText(hDlg, IDC_EDREQDATE, (LPCSTR)szRequireDate);
				SetDlgItemText(hDlg, IDC_EDSHIPDATE, (LPCSTR)szShipDate);
				SetDlgItemText(hDlg, IDC_EDSHIPVIA, (LPCSTR)szShipVia);
				SetDlgItemText(hDlg, IDC_EDFREIGHT, (LPCSTR)szFreight);
				SetDlgItemText(hDlg, IDC_EDSHIPNAME, (LPCSTR)szShipName);
				SetDlgItemText(hDlg, IDC_EDSHIPADDRESS, (LPCSTR)szShipAddress);
				SetDlgItemText(hDlg, IDC_EDSHIPCITY, (LPCSTR)szShipCity);
				SetDlgItemText(hDlg, IDC_EDSHIPREGION, (LPCSTR)szShipRegion);
				SetDlgItemText(hDlg, IDC_EDSHIPPOSTAL, (LPCSTR)szShipPostal);
				SetDlgItemText(hDlg, IDC_EDSHIPCOUNTRY, (LPCSTR)szShipCountry);
			}
		}
	}
}

//////////////////////////////
// DisplayProducts function //
//////////////////////////////

void DisplayProducts()
{
	char szProductName[30];		// Storage for Product Name
	char szSupplier[30];		// Storage for Customer ID
	char szCategory[20];		// Storage for Category
	char szQuantityPerUnit[20];	// Storage for Quantity Per Unit
	char szUnitPrice[10];		// Storage for Unit Price
	char szUnitsInStock[5];		// Storage for Units In Stock
	char szUnitsOnOrder[5];		// Storage for Units On Order
	char szReorderLevel[5];		// Storage for Reorder Level
	char szDiscontinued[3];		// Storage for Discontinued

	int iIndex;				// Currently selected list item
	// Free statement handle
	retcode = SQLFreeStmt(hStmt, SQL_CLOSE);
	// Prepare statement
	retcode = SQLPrepare(hStmt,
	                     (UCHAR*)"SELECT * FROM Products WHERE ProductName = (?)",
	                     SQL_NTS);
	if (retcode)
		GetErrorMsg("Preparing statement");
	else {
		// Find out which item is selected
		iIndex = (int)SendMessage(hWndList, LB_GETCURSEL,0,0);
		// Get text for that item
		SendMessage(hWndList, LB_GETTEXT, iIndex,(LPARAM)(LPCSTR) szProductName);
		// Bind SQL Parameters
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT,
		                           SQL_C_CHAR, SQL_CHAR, lstrlen(szProductName),
		                           0, (PTR)&szProductName, sizeof(szProductName), NULL);
		if (retcode)
			GetErrorMsg("Binding parameter");
		else
			// Execute the statement
		{
			retcode = SQLExecute(hStmt);
			if (retcode)
				GetErrorMsg("Executing binded statement");
			else {
				// Get Record Information
				while (!retcode) {
					retcode=SQLFetch(hStmt);
					retcode = SQLGetData(hStmt, 2, SQL_C_CHAR, &szProductName, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 3, SQL_C_CHAR, &szSupplier, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 4, SQL_C_CHAR, &szCategory, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 5, SQL_C_CHAR, &szQuantityPerUnit, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 6, SQL_C_CHAR, &szUnitPrice, 11, dwNameLength);
					retcode = SQLGetData(hStmt, 7, SQL_C_CHAR, &szUnitsInStock, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 8, SQL_C_CHAR, &szUnitsOnOrder, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 9, SQL_C_CHAR, &szReorderLevel, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 10, SQL_C_CHAR, &szDiscontinued, 4, dwNameLength);
				}
				// Set Record Information
				SetDlgItemText(hDlg, IDC_EDPRODUCTNAME, (LPCSTR)szProductName);
				SetDlgItemText(hDlg, IDC_EDSUPPLIER, (LPCSTR)szSupplier);
				SetDlgItemText(hDlg, IDC_EDCATEGORY, (LPCSTR)szCategory);
				SetDlgItemText(hDlg, IDC_EDQUANTITYPERUNIT, (LPCSTR)szQuantityPerUnit);
				SetDlgItemText(hDlg, IDC_EDUNITPRICE, (LPCSTR)szUnitPrice);
				SetDlgItemText(hDlg, IDC_EDUNITSINSTOCK, (LPCSTR)szUnitsInStock);
				SetDlgItemText(hDlg, IDC_EDUNITSONORDER, (LPCSTR)szUnitsOnOrder);
				SetDlgItemText(hDlg, IDC_EDREORDERLEVEL, (LPCSTR)szReorderLevel);
				SetDlgItemText(hDlg, IDC_EDDISCONTINUED, (LPCSTR)szDiscontinued);
			}
		}
	}
}

/////////////////////////////////
// DisplayShipperInfo function //
/////////////////////////////////
void DisplayShipperInfo()
{
	char szCompanyName[30];		// Storage for Company Name
	char szPhone[20];			// Storage for Phone Number
	int iIndex;

	// Free statement handle
	retcode = SQLFreeStmt(hStmt, SQL_CLOSE);
	// Prepare statement
	retcode = SQLPrepare(hStmt,
	                     (UCHAR*)"SELECT * FROM Shippers WHERE CompanyName = (?)",
	                     SQL_NTS);
	if (retcode)
		GetErrorMsg("Preparing statement");
	else {
		// Find out which item is selected
		iIndex = (int)SendMessage(hWndList, LB_GETCURSEL,0,0);
		// Get text for that item
		SendMessage(hWndList, LB_GETTEXT, iIndex,(LPARAM)(LPCSTR) szCompanyName);
		// Bind SQL Parameters
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT,
		                           SQL_C_CHAR, SQL_CHAR, lstrlen(szCompanyName),
		                           0, (PTR)&szCompanyName, sizeof(szCompanyName), NULL);
		if (retcode)
			GetErrorMsg("Binding parameter");
		else
			// Execute the statement
		{
			retcode = SQLExecute(hStmt);
			if (retcode)
				GetErrorMsg("Executing binded statement");
			else {
				// Get Record Information
				while (!retcode) {
					retcode=SQLFetch(hStmt);
					retcode = SQLGetData(hStmt, 2, SQL_C_CHAR, &szCompanyName, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 3, SQL_C_CHAR, &szPhone, 21, dwNameLength);
				}
				// Set Record Information
				SetDlgItemText(hDlg, IDC_EDSHIPNAME, (LPCSTR)szCompanyName);
				SetDlgItemText(hDlg, IDC_EDPHONE, (LPCSTR)szPhone);
			}
		}
	}
}

//////////////////////////////////
// DisplaySupplierInfo function //
//////////////////////////////////
void DisplaySupplierInfo()
{
	char szCompanyName[30];	// Storage for Company Name
	char szContactName[30];	// Storage for Contact Name
	char szContactTitle[20];// Storage for Contact Title
	char szAddress[30];		// Storage for address
	char szCity[20];		// Storage for city
	char szRegion[5];		// Storage for region
	char szPostalCode[20];	// Storage for postal code
	char szCountry[20];		// Storage for country
	char szPhone[20];		// Storage for phone
	char szFax[20];			// Storage for fax

	int iIndex;				// Currently selected list item
	// Free statement handle
	retcode = SQLFreeStmt(hStmt, SQL_CLOSE);
	// Prepare statement
	retcode = SQLPrepare(hStmt,
	                     (UCHAR*)"SELECT * FROM Suppliers WHERE CompanyName = (?)",
	                     SQL_NTS);
	if (retcode)
		GetErrorMsg("Preparing statement");
	else {
		// Find out which item is selected
		iIndex = (int)SendMessage(hWndList, LB_GETCURSEL,0,0);
		// Get text for that item
		SendMessage(hWndList, LB_GETTEXT, iIndex,(LPARAM)(LPCSTR) szCompanyName);
		// Bind SQL Parameters
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT,
		                           SQL_C_CHAR, SQL_CHAR, lstrlen(szCompanyName),
		                           0, (PTR)&szCompanyName,sizeof(szCompanyName), NULL);
		if (retcode)
			GetErrorMsg("Binding parameter");
		else
			// Execute the statement
		{
			retcode = SQLExecute(hStmt);
			if (retcode)
				GetErrorMsg("Executing binded statement");
			else {
				// Get Record Information
				while (!retcode) {
					retcode=SQLFetch(hStmt);
					retcode = SQLGetData(hStmt, 2, SQL_C_CHAR, &szCompanyName, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 3, SQL_C_CHAR, &szContactName, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 4, SQL_C_CHAR, &szContactTitle, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 5, SQL_C_CHAR, &szAddress, 31, dwNameLength);
					retcode = SQLGetData(hStmt, 6, SQL_C_CHAR, &szCity, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 7, SQL_C_CHAR, &szRegion, 6, dwNameLength);
					retcode = SQLGetData(hStmt, 8, SQL_C_CHAR, &szPostalCode, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 9, SQL_C_CHAR, &szCountry, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 10, SQL_C_CHAR, &szPhone, 21, dwNameLength);
					retcode = SQLGetData(hStmt, 11, SQL_C_CHAR, &szFax, 21, dwNameLength);
				}
				// Set Record Information
				SetDlgItemText(hDlg, IDC_EDCOMPNAME, (LPCSTR)szCompanyName);
				SetDlgItemText(hDlg, IDC_EDCONNAME, (LPCSTR)szContactName);
				SetDlgItemText(hDlg, IDC_EDCONTITLE, (LPCSTR)szContactTitle);
				SetDlgItemText(hDlg, IDC_EDADDRESS, (LPCSTR)szAddress);
				SetDlgItemText(hDlg, IDC_EDCITY, (LPCSTR)szCity);
				SetDlgItemText(hDlg, IDC_EDREGION, (LPCSTR)szRegion);
				SetDlgItemText(hDlg, IDC_EDPOSTALCODE, (LPCSTR)szPostalCode);
				SetDlgItemText(hDlg, IDC_EDCOUNTRY, (LPCSTR)szCountry);
				SetDlgItemText(hDlg, IDC_EDPHONE, (LPCSTR)szPhone);
				SetDlgItemText(hDlg, IDC_EDFAX, (LPCSTR)szFax);
			}
		}
	}
}
