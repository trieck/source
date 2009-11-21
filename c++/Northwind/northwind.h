//////////////////
/// northwind.h //
/// 9/8/96		//
//////////////////

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"
#include <sql.h>		// ODBC Core Functions
#include <sqlext.h>		// ODBC Extended Functions

#define ID_LISTBOX1 7   // Unique identifier for List Box

typedef VOID (*MYPROC)(void);	// Typedef for Open, Close Engine

///////////////////////
// WinMain prototype //
///////////////////////

int PASCAL WinMain (HANDLE hInstance, HANDLE hPrevInstance,
                    LPSTR lpCmdLine,  int nCmdShow);
//////////////////////////
// WindowProc prototype //
//////////////////////////

long pascal WindowProc(HWND hWnd, UINT message,
                       WPARAM wParam, LPARAM lParam);

////////////////////////
// AboutBox prototype //
////////////////////////

BOOL About (HWND hDlg,   unsigned message,
            WORD wParam, LONG lParam);
////////////////////////////
// ViewProc Prototype	  //
////////////////////////////

BOOL ViewProc (HWND hDlg, unsigned message,
               WORD wParam, LONG lParam);

///////////////////////////////////
// DisplayCategoryInfo Prototype //
///////////////////////////////////

void DisplayCategoryInfo();

///////////////////////////////////
// DisplayCustomerInfo prototype //
///////////////////////////////////

void DisplayCustomerInfo();

///////////////////////////////////
// DisplayEmployeeInfo prototype //
///////////////////////////////////

void DisplayEmployeeInfo();

///////////////////////////////////
// DisplayOrderDetails prototype //
///////////////////////////////////

void DisplayOrderDetails();

/////////////////////////////
// DisplayOrders prototype //
/////////////////////////////

void DisplayOrders();

///////////////////////////////
// DisplayProducts prototype //
///////////////////////////////

void DisplayProducts();

//////////////////////////////////
// DisplayShipperInfo prototype //
//////////////////////////////////

void DisplayShipperInfo();

///////////////////////////////////
// DisplaySupplierInfo prototype //
///////////////////////////////////

void DisplaySupplierInfo();

///////////////////////////
// GetErrorMsg Prototype //
///////////////////////////

void GetErrorMsg (LPSTR Cause);

////////////////////////////
// UncheckMenus Prototype //
////////////////////////////

void UncheckMenus ();

/////////////////////////
// DoNewView Prototype //
////////////////////////

void DoNewView(UINT MenuItem,char* NewView);

///////////////////////
// Reports prototype //
///////////////////////

void Reports (HINSTANCE hInstLib, unsigned int ReportID);
