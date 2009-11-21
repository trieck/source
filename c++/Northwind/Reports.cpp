/////////////////
// Reports.cpp //
/////////////////

#include "northwind.h"

void Reports(HINSTANCE hInstLib, unsigned int ReportID)
{
	BOOL fRunTimeLinkSuccess = FALSE;
	char Path[75];

	// Typedef for Printing Procedure
	typedef short FAR (*PRINTPROC)
	(char far*,
	 BOOL,
	 BOOL,
	 char far*,
	 int,
	 int,
	 int,
	 int,
	 long,
	 HWND);

	PRINTPROC PrintReportProc;
	PrintReportProc = (PRINTPROC) GetProcAddress(hInstLib, "PEPrintReport");

	switch (ReportID) {
	case 1:	// Sales By Category
		if (fRunTimeLinkSuccess = (PrintReportProc != NULL)) {
			lstrcpy ((char*)Path,"d:\\Tom's Projects\\Northwind\\Sales By Category.rpt");
		}
		break;
	case 2:	// Sales By Year
		if (fRunTimeLinkSuccess = (PrintReportProc != NULL)) {
			lstrcpy ((char*)Path, "d:\\Tom's Projects\\Northwind\\Sales By Year.rpt");
		}
		break;
	case 3:	// Customers and Suppliers By City
		if (fRunTimeLinkSuccess = (PrintReportProc != NULL)) {
			lstrcpy ((char*)Path, "d:\\Tom's Projects\\Northwind\\Customers and Suppliers By City.rpt");
		}
		break;
	case 4:	// Employee Sales By Country
		if (fRunTimeLinkSuccess = (PrintReportProc != NULL)) {
			lstrcpy ((char*)Path, "d:\\Tom's Projects\\Northwind\\Employee Sales By Country.rpt");
		}
		break;
	};
	(PrintReportProc)(Path,
	                  FALSE,
	                  TRUE,
	                  "Northwind Reports",
	                  CW_USEDEFAULT,
	                  CW_USEDEFAULT,
	                  CW_USEDEFAULT,
	                  CW_USEDEFAULT,
	                  NULL,
	                  NULL);
}