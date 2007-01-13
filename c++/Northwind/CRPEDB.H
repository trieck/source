&&
&& File:    CRPEDB.H
&&
&& Authors: Crystal Services and Instructions Etc., Inc.
&& Date:    17 Aug. 94
&&
&& Purpose: This file presents the API to the Crystal Reports
&&	Print Engine DLL.
&&
&& Copyright (c) 1994  Crystal Services
&&

#define PE_SF_MAX_NAME_LENGTH 50

#define PE_SF_DESCENDING 0
#define PE_SF_ASCENDING  1

#define PE_ERR_NOERROR              0

#define PE_ERR_NOTENOUGHMEMORY      500
#define PE_ERR_INVALIDJOBNO         501
#define PE_ERR_INVALIDHANDLE        502
#define PE_ERR_STRINGTOOLONG        503
#define PE_ERR_NOSUCHREPORT         504
#define PE_ERR_NODESTINATION        505
#define PE_ERR_BADFILENUMBER        506
#define PE_ERR_BADFILENAME          507
#define PE_ERR_BADFIELDNUMBER       508
#define PE_ERR_BADFIELDNAME         509
#define PE_ERR_BADFORMULANAME       510
#define PE_ERR_BADSORTDIRECTION     511
#define PE_ERR_ENGINENOTOPEN        512
#define PE_ERR_INVALIDPRINTER       513
#define PE_ERR_PRINTFILEEXISTS      514
#define PE_ERR_BADFORMULATEXT       515
#define PE_ERR_BADGROUPSECTION      516
#define PE_ERR_ENGINEBUSY           517
#define PE_ERR_BADSECTION           518
#define PE_ERR_NOPRINTWINDOW        519
#define PE_ERR_JOBALREADYSTARTED    520
#define PE_ERR_BADSUMMARYFIELD      521
#define PE_ERR_NOTENOUGHSYSRES      522
#define PE_ERR_BADGROUPCONDITION    523
#define PE_ERR_JOBBUSY              524
#define PE_ERR_BADREPORTFILE        525
#define PE_ERR_NODEFAULTPRINTER     526
#define PE_ERR_SQLSERVERERROR       527
#define PE_ERR_BADLINENUMBER        528
#define PE_ERR_DISKFULL             529
#define PE_ERR_FILEERROR            530
#define PE_ERR_INCORRECTPASSWORD    531
#define PE_ERR_BADDATABASEDLL       532
#define PE_ERR_BADDATABASEFILE      533
#define PE_ERR_ERRORINDATABASEDLL   534
#define PE_ERR_DATABASESESSION      535
#define PE_ERR_DATABASELOGON        536
#define PE_ERR_DATABASELOCATION     537
#define PE_ERR_BADSTRUCTSIZE        538
#define PE_ERR_BADDATE              539
#define PE_ERR_BADEXPORTDLL         540
#define PE_ERR_ERRORINEXPORTDLL     541
#define PE_ERR_PREVATFIRSTPAGE      542
#define PE_ERR_NEXTATLASTPAGE       543
#define PE_ERR_CANNOTACCESSREPORT   544
#define PE_ERR_USERCANCELLED        545
#define PE_ERR_OLE2NOTLOADED        546
#define PE_ERR_BADCROSSTABGROUP     547
#define PE_ERR_NOCTSUMMARIZEDFIELD  548
#define PE_ERR_DESTINATIONNOTEXPORT 549
#define PE_ERR_INVALIDPAGENUMBER 550
#define PE_ERR_BADLABELNUMBER 551
#define PE_ERR_NOTSTOREDPROCEDURE 552
#define PE_ERR_INVALIDPARAMETER 553
#define PE_ERR_GRAPHNOTFOUND 554
#define PE_ERR_INVALIDGRAPHTYPE 555
#define PE_ERR_INVALIDGRAPHDATA 556
#define PE_ERR_CANNOTMOVEGRAPH 557
#define PE_ERR_INVALIDGRAPHTEXT 558
#define PE_ERR_INVALIDGRAPHOPT 559

#define PE_ERR_NOTIMPLEMENTED       999

&& Open, print and close report (used when no changes needed to report)
&&

EXTERN CWORD PEPrintReport(CSTRING, CLOGICAL, CLOGICAL, CSTRING, CWORD,;
				CWORD, CWORD, CWORD, CLONG, CHANDLE) CRPE.DLL


&& Open and close print engine
&&

EXTERN CLOGICAL PEOpenEngine(CVOID) CRPE.DLL
EXTERN CVOID PECloseEngine(CVOID) CRPE.DLL


&& Get version info
&&

#define PE_GV_DLL     100
#define PE_GV_ENGINE  200

EXTERN CWORD PEGetVersion(CWORD) CRPE.DLL


&& Open and close print job (i.e. report)
&&

EXTERN CWORD PEOpenPrintJob(CSTRING) CRPE.DLL
EXTERN CLOGICAL PEClosePrintJob(CWORD) CRPE.DLL


&& Start and cancel print job (i.e. print the report, usually after changing report)
&&

EXTERN CLOGICAL PEStartPrintJob(CWORD, CLOGICAL) CRPE.DLL
EXTERN CVOID PECancelPrintJob(CWORD) CRPE.DLL


&& Print job status
&&

EXTERN CLOGICAL PEIsPrintJobFinished(CWORD) CRPE.DLL

#define PE_JOBNOTSTARTED 1
#define PE_JOBINPROGRESS 2
#define PE_JOBCOMPLETED  3
#define PE_JOBFAILED     4
#define PE_JOBCANCELLED  5


&& Print job error codes
&&

EXTERN CWORD PEGetErrorCode(CWORD) CRPE.DLL


&& Setting the print date
&& ----------------------

EXTERN CLOGICAL PESetPrintDate(CWORD, CWORD, CWORD, CWORD) CRPE.DLL


&& Controlling formulas, selection formulas and group selection formulas
&& ---------------------------------------------------------------------

EXTERN CLOGICAL PESetFormula(CWORD, CSTRING, CSTRING) CRPE.DLL

EXTERN CLOGICAL PESetSelectionFormula(CWORD, CSTRING) CRPE.DLL

EXTERN CLOGICAL PESetGroupSelectionFormula(CWORD, CSTRING) CRPE.DLL


&& Controlling group conditions (i.e. group breaks)
&&

&& use PE_ANYCHANGE for all field types except Date and Boolean
#define PE_GC_ANYCHANGE    0

&& use these constants for Date fields
#define PE_GC_DAILY        0
#define PE_GC_WEEKLY       1
#define PE_GC_BIWEEKLY     2
#define PE_GC_SEMIMONTHLY  3
#define PE_GC_MONTHLY      4
#define PE_GC_QUARTERLY    5
#define PE_GC_SEMIANNUALLY 6
#define PE_GC_ANNUALLY     7

&& use these constants for Boolean fields
#define PE_GC_TOYES        1
#define PE_GC_TONO         2
#define PE_GC_EVERYYES     3
#define PE_GC_EVERYNO      4
#define PE_GC_NEXTISYES    5
#define PE_GC_NEXTISNO     6

EXTERN CLOGICAL PESetGroupCondition(CWORD, CWORD, CSTRING, CWORD, CWORD) CRPE.DLL


&& Controlling sort order and group sort order
&&

EXTERN CWORD PEGetNSortFields(CWORD) CRPE.DLL

EXTERN CLOGICAL PESetNthSortField(CWORD, CWORD, CSTRING, CWORD) CRPE.DLL

EXTERN CLOGICAL PEDeleteNthSortField(CWORD, CWORD) CRPE.DLL

EXTERN CWORD PEGetNGroupSortFields(CWORD) CRPE.DLL

EXTERN CLOGICAL PESetNthGroupSortField(CWORD, CWORD, CSTRING, CWORD) CRPE.DLL

EXTERN CLOGICAL PEDeleteNthGroupSortField(CWORD, CWORD) CRPE.DLL


&& The function PEGetNTables is called to fetch the number of tables in
&& the report.  This includes all PC databases (e.g. Paradox, xBase)
&& as well as SQL databases (e.g. SQL Server, Oracle, Netware).

EXTERN CWORD PEGetNTables(CWORD) CRPE.DLL


&& The function PETestNthTableConnectivity tests whether a database
&& table's settings are valid and ready to be reported on.  It returns
&& true if the database session, log on, and location info is all
&& correct.
&&
&& This is useful, for example, in prompting the user and testing a
&& server password before printing begins.
&&
&& This function may require a significant amount of time to complete,
&& since it will first open a user session (if required), then log onto
&& the database server (if required), and then open the appropriate
&& database table (to test that it exists).  It does not read any data,
&& and closes the table immediately once successful.  Logging off is
&& performed when the print job is closed.
&&
&& If it fails in any of these steps, the error code set indicates
&& which database info needs to be updated using functions above:
&&    - If it is unable to begin a session, PE_ERR_DATABASESESSION is set.
&&    - If it is unable to log onto a server, PE_ERR_DATABASELOGON is set.
&&    - If it is unable open the table, PE_ERR_DATABASELOCATION is set.

EXTERN CLOGICAL PETestNthTableConnectivity(CWORD, CWORD) CRPE.DLL


&& Report title
&&

EXTERN CLOGICAL PESetReportTitle(CWORD, CSTRING) CRPE.DLL


&& Controlling printed pages
&&

EXTERN CLOGICAL PEShowNextPage(CWORD) CRPE.DLL
EXTERN CLOGICAL PEShowFirstPage(CWORD) CRPE.DLL
EXTERN CLOGICAL PEShowPreviousPage(CWORD) CRPE.DLL
EXTERN CLOGICAL PEShowLastPage(CWORD) CRPE.DLL
EXTERN CLOGICAL PEShowPrintControls(CWORD, CLOGICAL) CRPE.DLL


&& Controlling print to printer
&& ----------------------------

EXTERN CLOGICAL PEOutputToPrinter(CWORD, CWORD) CRPE.DLL

EXTERN CLOGICAL PESetNDetailCopies(CWORD, CWORD) CRPE.DLL

&& Controlling print to window
&& ---------------------------

EXTERN CLOGICAL PEOutputToWindow(CWORD, CSTRING, CWORD, CWORD,;
					CWORD, CWORD, CLONG, CHANDLE) CRPE.DLL

EXTERN CHANDLE PEGetWindowHandle(CWORD) CRPE.DLL

EXTERN CLOGICAL PEPrintWindow(CWORD, CLOGICAL) CRPE.DLL

EXTERN CVOID PECloseWindow(CWORD) CRPE.DLL


&& Setting page margins
&& --------------------

#define PE_SM_DEFAULT 32768

EXTERN CLOGICAL PESetMargins(CWORD, CWORD, CWORD, CWORD, CWORD) CRPE.DLL


&& Setting section height and format
&& ---------------------------------

#define PE_ALLSECTIONS           0
#define PE_TITLESECTION           1000
#define PE_HEADERSECTION      2000
#define PE_GROUPHEADER        3000
#define PE_DETAILSECTION      4000
#define PE_GROUPFOOTER        5000
#define PE_GRANDTOTALSECTION  6000
#define PE_FOOTERSECTION      7000
#define PE_SUMMARYSECTION      8000

EXTERN CLOGICAL PESetMinimumSectionHeight(CWORD, CWORD, CWORD) CRPE.DLL

&& Setting line height
&& -------------------

#define PE_ALLLINES  -1

EXTERN CLOGICAL PESetLineHeight(CWORD, CWORD, CWORD, CWORD, CWORD) CRPE.DLL


&& Setting font info
&& -----------------

#define PE_FIELDS    0x0001
#define PE_TEXT      0x0002

#define PE_UNCHANGED -1

EXTERN CLOGICAL PESetFont(CWORD, CWORD, CWORD, CSTRING, CWORD, CWORD,;
				CWORD, CWORD, CWORD, CWORD, CWORD, CWORD) CRPE.DLL


&& Checking formulas, selection formulas and group selection formulas
&& ---------------------------------------------------------------------

EXTERN CLOGICAL PECheckFormula (CWORD, CSTRING) CRPE.DLL

EXTERN CLOGICAL PECheckSelectionFormula (CWORD) CRPE.DLL

EXTERN CLOGICAL PECheckGroupSelectionFormula (CWORD) CRPE.DLL


&& Discarding data that was previously saved with the report.
&&-----------------------------------------------------------------------------

EXTERN CLOGICAL PEDiscardSavedData (CWORD) CRPE.DLL


&& Getting number of formulas in report
&&--------------------------------------------------------------

EXTERN CWORD PEGetNFormulas (CWORD) CRPE.DLL


&& Getting number of groups in report
&&-----------------------------------------------------

EXTERN CWORD PEGetNGroups (CWORD) CRPE.DLL


&& Getting  number of lines in section
&&----------------------------------------------------------

EXTERN CWORD PEGetNLinesInSection (CWORD, CWORD) CRPE.DLL


&& Controlling preview window magnification
&&---------------------------------------------------------

EXTERN CLOGICAL PENextPrintWindowMagnification (CWORD) CRPE.DLL

#define PE_ZOOM_FULL_SIZE                    0
#define PE_ZOOM_SIZE_FIT_ONE_SIDE    1
#define PE_ZOOM_SIZE_FIT_BOTH_SIDES    2

EXTERN CLOGICAL PEZoomPreviewWindow (CWORD, CWORD) CRPE.DLL


&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&& The following are Windows constants defined in Windows.h.
&& They are redefined here for use with PE functions in dBASE.

#define WS_MINIMIZE	536870912
#define WS_VISIBLE	268435456
#define WS_DISABLED	134217728
#define WS_CLIPSIBLINGS	67108864
#define WS_CLIPCHILDREN	33554432
#define WS_MAXIMIZE	16777216
#define WS_CAPTION	12582912
#define WS_BORDER	8388608
#define WS_DLGFRAME	4194304
#define WS_VSCROLL	2097152
#define WS_HSCROLL	1048576
#define WS_SYSMENU	524288
#define WS_THICKFRAME	262144
#define WS_MINIMIZEBOX	131072
#define WS_MAXIMIZEBOX	65536
#define CW_USEDEFAULT	-32768
