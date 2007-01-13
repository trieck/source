/*
** File:    CRPE.h
**
** Authors: Crystal Services
** Date:    13 Nov 91
**
** Purpose: This file presents the API to the Crystal Reports
**          Print Engine DLL.
**
** Copyright (c) 1991-1994  Crystal Services
*/

#if !defined (CRPE_H)
#define CRPE_H

#if !defined (WIN32)
  #include <Print.h>
#endif

#if defined (__cplusplus)
extern "C"
{
#endif

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
#define PE_ERR_INVALIDPAGENUMBER    550
#define PE_ERR_BADLABELNUMBER       551
#define PE_ERR_NOTSTOREDPROCEDURE   552
#define PE_ERR_INVALIDPARAMETER     553
#define PE_ERR_GRAPHNOTFOUND        554
#define PE_ERR_INVALIDGRAPHTYPE     555
#define PE_ERR_INVALIDGRAPHDATA     556
#define PE_ERR_CANNOTMOVEGRAPH      557
#define PE_ERR_INVALIDGRAPHTEXT     558
#define PE_ERR_INVALIDGRAPHOPT      559

#define PE_ERR_NOTIMPLEMENTED       999

#if defined (WIN32)
  #define CRPE_API __cdecl
#else
  #define CRPE_API FAR PASCAL
#endif


// Open, print and close report (used when no changes needed to report)
// --------------------------------------------------------------------

short CRPE_API PEPrintReport (char FAR* reportFilePath,
                              BOOL  toDefaultPrinter,
                              BOOL  toWindow, char FAR* title,
                                              short left,
                                              short top,
                                              short width,
                                              short height,
                                              long  style,
                                              HWND parentWindow);


// Open and close print engine
// ---------------------------

BOOL CRPE_API PEOpenEngine (void);
void CRPE_API PECloseEngine (void);
BOOL CRPE_API PECanCloseEngine (void);


// Get version info
// ----------------

#define PE_GV_DLL     100
#define PE_GV_ENGINE  200

short CRPE_API PEGetVersion (short versionRequested);


// Open and close print job (i.e. report)
// --------------------------------------

short CRPE_API PEOpenPrintJob (char FAR *reportFilePath);
BOOL CRPE_API PEClosePrintJob (short printJob);


// Start and cancel print job (i.e. print the report, usually after changing report)
// ---------------------------------------------------------------------------------

BOOL CRPE_API PEStartPrintJob (short printJob,
                               BOOL waitUntilDone);
void CRPE_API PECancelPrintJob (short printJob);


// Print job status
// ----------------

BOOL CRPE_API PEIsPrintJobFinished (short printJob);

#define PE_JOBNOTSTARTED 1
#define PE_JOBINPROGRESS 2
#define PE_JOBCOMPLETED  3
#define PE_JOBFAILED     4
#define PE_JOBCANCELLED  5

struct PEJobInfo
{
    WORD StructSize;    // initialize to sizeof (PEJobInfo)

    DWORD NumRecordsRead,
          NumRecordsSelected,
          NumRecordsPrinted;
    WORD  DisplayPageN, // the page being displayed in window
          LatestPageN,  // the page being generated
          StartPageN;   // user opted, default to 1
    BOOL  printEnded;   // full report print completed?
};

short CRPE_API PEGetJobStatus (short printJob,
                               struct PEJobInfo FAR *jobInfo);


// Print job error codes and messages
// ----------------------------------

short CRPE_API PEGetErrorCode (short printJob);
BOOL  CRPE_API PEGetErrorText (short printJob,
                               HANDLE FAR *textHandle,
                               short  FAR *textLength);

BOOL  CRPE_API PEGetHandleString (HANDLE textHandle,
                                  char FAR *buffer,
                                  short bufferLength);


// Setting the print date
// ----------------------

BOOL CRPE_API PEGetPrintDate (short printJob,
                              short FAR *year,
                              short FAR *month,
                              short FAR *day);

BOOL CRPE_API PESetPrintDate (short printJob,
                              short year,
                              short month,
                              short day);


// Controlling group conditions (i.e. group breaks)
// ------------------------------------------------

// use PE_ANYCHANGE for all field types except Date and Boolean
#define PE_GC_ANYCHANGE    0

// use these constants for Date fields
#define PE_GC_DAILY        0
#define PE_GC_WEEKLY       1
#define PE_GC_BIWEEKLY     2
#define PE_GC_SEMIMONTHLY  3
#define PE_GC_MONTHLY      4
#define PE_GC_QUARTERLY    5
#define PE_GC_SEMIANNUALLY 6
#define PE_GC_ANNUALLY     7

// use these constants for Boolean fields
#define PE_GC_TOYES        1
#define PE_GC_TONO         2
#define PE_GC_EVERYYES     3
#define PE_GC_EVERYNO      4
#define PE_GC_NEXTISYES    5
#define PE_GC_NEXTISNO     6

BOOL CRPE_API PESetGroupCondition (short printJob,
                                   short sectionCode,
                                   char FAR *conditionField,
                                   short condition,       // a PE_GC_ constant
                                   short sortDirection);  // a PE_SF_ constant

short CRPE_API PEGetNGroups (short printJob);

// for PEGetGroupCondition, condition encodes both
// the condition and the type of the condition field
#define PE_GC_CONDITIONMASK   0x00ff
#define PE_GC_TYPEMASK        0x0f00

#define PE_GC_TYPEOTHER       0x0000
#define PE_GC_TYPEDATE        0x0200
#define PE_GC_TYPEBOOLEAN     0x0400

BOOL CRPE_API PEGetGroupCondition (short printJob,
                                   short sectionCode,
                                   HANDLE FAR *conditionFieldHandle,
                                   short  FAR *conditionFieldLength,
                                   short  FAR *condition,
                                   short  FAR *sortDirection);



// Controlling formulas, selection formulas and group selection formulas
// ---------------------------------------------------------------------

short CRPE_API PEGetNFormulas (short printJob);

BOOL CRPE_API PEGetNthFormula (short printJob,
                               short formulaN,
                               HANDLE FAR *nameHandle,
                               short  FAR *nameLength,
                               HANDLE FAR *textHandle,
                               short  FAR *textLength);

BOOL CRPE_API PEGetFormula (short printJob,
                              char FAR *formulaName,
                              HANDLE FAR *textHandle,
                              short  FAR *textLength);

BOOL CRPE_API PESetFormula (short printJob,
                            char FAR *formulaName,
                            char FAR *formulaString);

BOOL CRPE_API PECheckFormula (short printJob,
                              char FAR *formulaName);

BOOL CRPE_API PEGetSelectionFormula (short printJob,
                                     HANDLE FAR *textHandle,
                                     short  FAR *textLength);

BOOL CRPE_API PESetSelectionFormula (short printJob,
                                     char FAR *formulaString);

BOOL CRPE_API PECheckSelectionFormula (short printJob);

BOOL CRPE_API PEGetGroupSelectionFormula (short printJob,
                                          HANDLE FAR *textHandle,
                                          short  FAR *textLength);

BOOL CRPE_API PESetGroupSelectionFormula (short printJob,
                                          char FAR *formulaString);

BOOL CRPE_API PECheckGroupSelectionFormula (short printJob);


// Controlling sort order and group sort order
// -------------------------------------------

short CRPE_API PEGetNSortFields (short printJob);

BOOL CRPE_API PEGetNthSortField (short printJob,
                                 short sortFieldN,
                                 HANDLE FAR *nameHandle,
                                 short  FAR *nameLength,
                                 short  FAR *direction);

BOOL CRPE_API PESetNthSortField (short printJob,
                                 short sortFieldN,
                                 char FAR *name,
                                 short direction);

BOOL CRPE_API PEDeleteNthSortField (short printJob,
                                    short sortFieldN);

short CRPE_API PEGetNGroupSortFields (short printJob);

BOOL CRPE_API PEGetNthGroupSortField (short printJob,
                                      short sortFieldN,
                                      HANDLE FAR *nameHandle,
                                      short  FAR *nameLength,
                                      short  FAR *direction);

BOOL CRPE_API PESetNthGroupSortField (short printJob,
                                      short sortFieldN,
                                      char FAR *name,
                                      short direction);

BOOL CRPE_API PEDeleteNthGroupSortField (short printJob,
                                         short sortFieldN);


// Controlling databases
// ---------------------
//
// The following functions allow retrieving and updating database info
// in an opened report, so that a report can be printed using different
// session, server, database, user and/or table location settings.  Any
// changes made to the report via these functions are not permanent, and
// only last as long as the report is open.
//
// The following database functions (except for PELogOnServer and
// PELogOffServer) must be called after PEOpenPrintJob and before
// PEStartPrintJob.

// The function PEGetNTables is called to fetch the number of tables in
// the report.  This includes all PC databases (e.g. Paradox, xBase)
// as well as SQL databases (e.g. SQL Server, Oracle, Netware).

short CRPE_API PEGetNTables (short printJob);


// The function PEGetNthTableType allows the application to determine the
// type of each table.  The application can test DBType (equal to
// PE_DT_STANDARD or PE_DT_SQL), or test the database DLL name used to
// create the report.  DLL names have the following naming convention:
//     - PDB*.DLL for standard (non-SQL) databases,
//     - PDS*.DLL for SQL databases.
//
// In the case of ODBC (PDSODBC.DLL) the DescriptiveName includes the
// ODBC data source name.

#define PE_WORD_LEN          2
#define PE_DLL_NAME_LEN      64
#define PE_FULL_NAME_LEN     256

#define PE_SIZEOF_TABLE_TYPE PE_WORD_LEN + \
                             PE_DLL_NAME_LEN + \
                             PE_FULL_NAME_LEN + \
                             PE_WORD_LEN

#define PE_DT_STANDARD  1
#define PE_DT_SQL       2

struct PETableType
{
    // Initialize to PE_SIZEOF_TABLE_TYPE.
    WORD StructSize;

    // All strings are null-terminated.
    char DLLName [PE_DLL_NAME_LEN];
    char DescriptiveName [PE_FULL_NAME_LEN];

    WORD DBType;
};

BOOL  CRPE_API PEGetNthTableType (short printJob,
                                  short tableN,
                                  struct PETableType FAR *tableType);


// The functions PEGetNthTableSessionInfo and PESetNthTableSessionInfo
// are only used when connecting to MS Access databases (which require a
// session to be opened first)

#define PE_LONGPTR_LEN       4
#define PE_SESS_USERID_LEN   128
#define PE_SESS_PASSWORD_LEN 128

#define PE_SIZEOF_SESSION_INFO PE_WORD_LEN + \
                               PE_SESS_USERID_LEN + \
                               PE_SESS_PASSWORD_LEN + \
                               PE_LONGPTR_LEN

struct PESessionInfo
{
    // Initialize to PE_SIZEOF_SESSION_INFO.
    WORD StructSize;

    // All strings are null-terminated.
    char UserID [PE_SESS_PASSWORD_LEN];

    // Password is undefined when getting information from report.
    char Password [PE_SESS_PASSWORD_LEN];

    // SessionHandle is undefined when getting information from report.
    // When setting information, if it is = 0 the UserID and Password
    // settings are used, otherwise the SessionHandle is used.
    DWORD SessionHandle;
};

BOOL  CRPE_API PEGetNthTableSessionInfo (short printJob,
                                         short tableN,
                                         struct PESessionInfo FAR *sessionInfo);
BOOL  CRPE_API PESetNthTableSessionInfo (short printJob,
                                         short tableN,
                                         struct PESessionInfo FAR *sessionInfo,
                                         BOOL propagateAcrossTables);


// Logging on is performed when printing the report, but the correct
// log on information must first be set using PESetNthTableLogOnInfo.
// Only the password is required, but the server, database, and
// user names may optionally be overriden as well.
//
// If the parameter propagateAcrossTables is TRUE, the new log on info
// is also applied to any other tables in this report that had the
// same original server and database names as this table.  If FALSE
// only this table is updated.
//
// Logging off is performed automatically when the print job is closed.

#define PE_SERVERNAME_LEN    128
#define PE_DATABASENAME_LEN  128
#define PE_USERID_LEN        128
#define PE_PASSWORD_LEN      128

#define PE_SIZEOF_LOGON_INFO PE_WORD_LEN + \
                             PE_SERVERNAME_LEN + \
                             PE_DATABASENAME_LEN + \
                             PE_USERID_LEN + \
                             PE_PASSWORD_LEN

struct PELogOnInfo
{
    // Initialize to PE_SIZEOF_LOGON_INFO.
    WORD StructSize;

    // For any of the following values an empty string ("") means to use
    // the value already set in the report.  To override a value in the
    // report use a non-empty string (e.g. "Server A").  All strings are
    // null-terminated.
    //
    // For Netware SQL, pass the dictionary path name in ServerName and
    // data path name in DatabaseName.
    char ServerName [PE_SERVERNAME_LEN];
    char DatabaseName [PE_DATABASENAME_LEN];
    char UserID [PE_USERID_LEN];

    // Password is undefined when getting information from report.
    char Password [PE_PASSWORD_LEN];
};

BOOL  CRPE_API PEGetNthTableLogOnInfo (short printJob,
                                       short tableN,
                                       struct PELogOnInfo FAR *logOnInfo);
BOOL  CRPE_API PESetNthTableLogOnInfo (short printJob,
                                       short tableN,
                                       struct PELogOnInfo FAR *logOnInfo,
                                       BOOL propagateAcrossTables);


// A table's location is fetched and set using PEGetNthTableLocation and
// PESetNthTableLocation.  This name is database-dependent, and must be
// formatted correctly for the expected database.  For example:
//     - Paradox: "c:\crw\ORDERS.DB"
//     - SQL Server: "publications.dbo.authors"

#define PE_TABLE_LOCATION_LEN      256

#define PE_SIZEOF_TABLE_LOCATION PE_WORD_LEN + \
                                 PE_TABLE_LOCATION_LEN

struct PETableLocation
{
    // Initialize to PE_SIZEOF_TABLE_LOCATION.
    WORD StructSize;

    // String is null-terminated.
    char Location [PE_TABLE_LOCATION_LEN];
};

BOOL  CRPE_API PEGetNthTableLocation (short printJob,
                                      short tableN,
                                      struct PETableLocation FAR *location);
BOOL  CRPE_API PESetNthTableLocation (short printJob,
                                      short tableN,
                                      struct PETableLocation FAR *location);


// If report based on a SQL Stored Procedure, use PEGetNParams to fetch the
// number of parameters, and PEGetNthParam and PESetNthParam to fetch and
// set individual parameters.  All parameter values are encoded as strings.

short CRPE_API PEGetNParams (short printJob);         // Returns number of input parameters.

BOOL  CRPE_API PEGetNthParam (short printJob,
                              short paramN,           // 0 indexed parameter number.
                              HANDLE FAR *textHandle, // Address of a texthandle variable.
                              short  FAR *textLength);// Number of characters in string
                                                        // (not including null terminator).

BOOL  CRPE_API PESetNthParam (short printJob,
                              short paramN,           // 0 indexed parameter number.
                              LPCSTR szParamValue);   // String representation of parameter value.


// The function PETestNthTableConnectivity tests whether a database
// table's settings are valid and ready to be reported on.  It returns
// true if the database session, log on, and location info is all
// correct.
//
// This is useful, for example, in prompting the user and testing a
// server password before printing begins.
//
// This function may require a significant amount of time to complete,
// since it will first open a user session (if required), then log onto
// the database server (if required), and then open the appropriate
// database table (to test that it exists).  It does not read any data,
// and closes the table immediately once successful.  Logging off is
// performed when the print job is closed.
//
// If it fails in any of these steps, the error code set indicates
// which database info needs to be updated using functions above:
//    - If it is unable to begin a session, PE_ERR_DATABASESESSION is set,
//      and the application should update with PESetNthTableSessionInfo.
//    - If it is unable to log onto a server, PE_ERR_DATABASELOGON is set,
//      and the application should update with PESetNthTableLogOnInfo.
//    - If it is unable open the table, PE_ERR_DATABASELOCATION is set,
//      and the application should update with PESetNthTableLocation.

BOOL  CRPE_API PETestNthTableConnectivity (short printJob,
                                           short tableN);


// PELogOnServer and PELogOffServer can be called at any time to log on
// and off of a database server.  These functions are not required if
// function PESetNthTableLogOnInfo above was already used to set the
// password for a table.
//
// These functions require a database DLL name, which can be retrieved
// using PEGetNthTableType above.
//
// This function can also be used for non-SQL tables, such as password-
// protected Paradox tables.  Call this function to set the password
// for the Paradox DLL before beginning printing.
//
// Note: When printing using PEStartPrintJob the ServerName passed in
// PELogOnServer must agree exactly with the server name stored in the
// report.  If this is not true use PESetNthTableLogOnInfo to perform
// logging on instead.

BOOL CRPE_API PELogOnServer (char FAR *dllName,
                             struct PELogOnInfo FAR *logOnInfo);
BOOL CRPE_API PELogOffServer (char FAR *dllName,
                              struct PELogOnInfo FAR *logOnInfo);

BOOL CRPE_API PELogOnSQLServerWithPrivateInfo (char FAR *dllName,
                                               void FAR *privateInfo);

// Overriding SQL query in report
// ------------------------------
//
// PEGetSQLQuery () returns the same query as appears in the Show SQL Query
// dialog in CRW, in syntax specific to the database driver you are using.
//
// PESetSQLQuery () is mostly useful for reports with SQL queries that
// were explicitly edited in the Show SQL Query dialog in CRW, i.e. those
// reports that needed database-specific selection criteria or joins.
// (Otherwise it is usually best to continue using function calls such as
// PESetSelectionFormula () and let CRW build the SQL query automatically.)
//
// PESetSQLQuery () has the same restrictions as editing in the Show SQL
// Query dialog; in particular that changes are accepted in the FROM and
// WHERE clauses but ignored in the SELECT list of fields.

BOOL CRPE_API PEGetSQLQuery (short printJob,
                             HANDLE FAR *textHandle,
                             short  FAR *textLength);

BOOL CRPE_API PESetSQLQuery (short printJob,
                             char FAR *queryString);


// Saved data
// ----------
//
// Use PEHasSavedData() to find out if a report currently has saved data
// associated with it.  This may or may not be TRUE when a print job is
// first opened from a report file.  Since data is saved during a print,
// this will always be TRUE immediately after a report is printed.
//
// Use PEDiscardSavedData() to release the saved data associated with a
// report.  The next time the report is printed, it will get current data
// from the database.
//
// The default behavior is for a report to use its saved data, rather than
// refresh its data from the database when printing a report.

BOOL CRPE_API PEHasSavedData (short printJob,
                              BOOL FAR *hasSavedData);
BOOL CRPE_API PEDiscardSavedData (short printJob);


// Report title
// ------------

BOOL CRPE_API PEGetReportTitle (short printJob,
                                HANDLE FAR *titleHandle,
                                short  FAR *titleLength);
BOOL CRPE_API PESetReportTitle (short printJob,
                                char FAR *title);


// Controlling print to window
// ---------------------------

BOOL CRPE_API PEOutputToWindow (short printJob,
                                char FAR *title,
                                short left,
                                short top,
                                short width,
                                short height,
                                long  style,
                                HWND parentWindow);

HWND CRPE_API PEGetWindowHandle (short printJob);

void CRPE_API PECloseWindow (short printJob);


// Controlling printed pages
// -------------------------

BOOL CRPE_API PEShowNextPage (short printJob);
BOOL CRPE_API PEShowFirstPage (short printJob);
BOOL CRPE_API PEShowPreviousPage (short printJob);
BOOL CRPE_API PEShowLastPage (short printJob);

#define PE_ZOOM_FULL_SIZE           0
#define PE_ZOOM_SIZE_FIT_ONE_SIDE   1
#define PE_ZOOM_SIZE_FIT_BOTH_SIDES 2

BOOL CRPE_API PEZoomPreviewWindow (short printJob,
                                   short level);


// Controlling print window when print control buttons hidden
// ----------------------------------------------------------

BOOL CRPE_API PEShowPrintControls (short printJob,
                                   BOOL showPrintControls);
BOOL CRPE_API PEPrintControlsShowing (short printJob,
                                      BOOL FAR *controlsShowing);

BOOL CRPE_API PEPrintWindow (short printJob,
                             BOOL waitUntilDone);

BOOL CRPE_API PEExportPrintWindow (short printJob,
                                   BOOL toMail,
                                   BOOL waitUntilDone);

BOOL CRPE_API PENextPrintWindowMagnification (short printJob);


// Changing printer selection
// --------------------------

BOOL CRPE_API PESelectPrinter (short printJob,
                               char FAR *driverName,
                               char FAR *printerName,
                               char FAR *portName,
                               DEVMODE FAR *mode);

BOOL CRPE_API PEGetSelectedPrinter (short printJob,
                                    HANDLE  FAR *driverHandle,
                                    short   FAR *driverLength,
                                    HANDLE  FAR *printerHandle,
                                    short   FAR *printerLength,
                                    HANDLE  FAR *portHandle,
                                    short   FAR *portLength,
                                    DEVMODE FAR * FAR *mode);


// Controlling print to printer
// ----------------------------

BOOL CRPE_API PEOutputToPrinter (short printJob,
                                 short nCopies);

BOOL CRPE_API PESetNDetailCopies (short printJob,
                                  short nDetailCopies);

BOOL CRPE_API PEGetNDetailCopies (short printJob,
                                  short FAR *nDetailCopies);

// Extension to PESetPrintOptions function: If the 2nd parameter
// (pointer to PEPrintOptions) is set to 0 (null) the function prompts
// the user for these options.
//
// With this change, you can get the behaviour of the print-to-printer
// button in the print window by calling PESetPrintOptions with a
// null pointer and then calling PEPrintWindow.

#define PE_MAXPAGEN  65535

#define PE_UNCOLLATED       0
#define PE_COLLATED         1
#define PE_DEFAULTCOLLATION 2

struct PEPrintOptions
{
    WORD StructSize;            // initialize to sizeof (PEPrintOptions)

    // page and copy numbers are 1-origin
    // use 0 to preserve the existing settings
    unsigned short startPageN,
                   stopPageN;

    unsigned short nReportCopies;
    unsigned short collation;
};

BOOL CRPE_API PESetPrintOptions (short printJob,
                                 struct PEPrintOptions FAR *options);

BOOL CRPE_API PEGetPrintOptions (short printJob,
                                 struct PEPrintOptions FAR *options);


// Controlling print to file and export
// ------------------------------------

#define PE_FT_RECORD              0
#define PE_FT_TABSEPARATED        1
#define PE_FT_TEXT                2
#define PE_FT_DIF                 3
#define PE_FT_CSV                 4
#define PE_FT_CHARSEPARATED       5
#define PE_FT_TABFORMATTED        6

// Use for all types except PE_FT_CHARSEPARATED
struct PEPrintFileOptions
{
    WORD StructSize;        // initialize to sizeof (PEPrintFileOptions)
    BOOL UseReportNumberFmt,
         UseReportDateFormat;
};

#define PE_FIELDDELIMLEN  16

// Use for PE_FT_CHARSEPARATED
struct PECharSepFileOptions
{
    WORD StructSize;        // initialize to sizeof (PECharSepFileOptions)
    BOOL UseReportNumberFmt,
         UseReportDateFormat;
    char StringDelimiter;
    char FieldDelimiter [PE_FIELDDELIMLEN + 1];
};

BOOL CRPE_API PEOutputToFile (short printJob,
                              char FAR *outputFilePath,
                              short type,
                              void FAR *options);

struct PEExportOptions
{
    WORD StructSize;               // initialize to sizeof (PEExportOptions)

    char formatDLLName [PE_DLL_NAME_LEN];
    DWORD formatType;
    void FAR *formatOptions;
    char destinationDLLName [PE_DLL_NAME_LEN];
    DWORD destinationType;
    void FAR *destinationOptions;
    WORD nFormatOptionsBytes;      // Set by 'PEGetExportOptions',
                                   // ignored by 'PEExportTo'.
    WORD nDestinationOptionsBytes; // Set by 'PEGetExportOptions',
                                   // ignored by 'PEExportTo'.
};

#define PE_SIZEOF_EXPORT_OPTIONS sizeof (WORD) + \
                                 PE_DLL_NAME_LEN + \
                                 sizeof (DWORD) + \
                                 sizeof (void FAR *) + \
                                 PE_DLL_NAME_LEN + \
                                 sizeof (DWORD) + \
                                 sizeof (void FAR *) + \
                                 sizeof (WORD) + \
                                 sizeof (WORD)

BOOL CRPE_API PEGetExportOptions (short printJob,
                                  struct PEExportOptions FAR *options);

BOOL CRPE_API PEExportTo (short printJob,
                          struct PEExportOptions FAR *options);


// Setting page margins
// --------------------

#define PE_SM_DEFAULT  0x8000

BOOL CRPE_API PESetMargins (short printJob,
                            short left,
                            short right,
                            short top,
                            short bottom);

BOOL CRPE_API PEGetMargins (short printJob,
                            short FAR *  left,
                            short FAR *  right,
                            short FAR *  top,
                            short FAR *  bottom);


// Setting section height and format
// ---------------------------------

#define PE_ALLSECTIONS           0
#define PE_TITLESECTION       1000
#define PE_HEADERSECTION      2000
#define PE_GROUPHEADER        3000      // 3000 is outermost, 3001 is next, ...
#define PE_DETAILSECTION      4000
#define PE_GROUPFOOTER        5000
#define PE_GRANDTOTALSECTION  6000
#define PE_FOOTERSECTION      7000
#define PE_SUMMARYSECTION     8000

BOOL CRPE_API PESetMinimumSectionHeight (short printJob,
                                         short sectionCode,
                                         short minimumHeight);  // in twips

BOOL CRPE_API PEGetMinimumSectionHeight (short printJob,
                                         short sectionCode,
                                         short FAR *minimumHeight);

struct PESectionOptions
{
    WORD StructSize;            // initialize to sizeof (PESectionOptions)

    short visible,              // BOOLEAN values, except use PE_UNCHANGED
          newPageBefore,        // to preserve the existing settings
          newPageAfter,
          keepTogether,
          suppressBlankLines,
          resetPageNAfter,
          printAtBottomOfPage;
};

BOOL CRPE_API PESetSectionFormat (short printJob,
                                  short sectionCode,
                                  struct PESectionOptions FAR *options);

BOOL CRPE_API PEGetSectionFormat (short printJob,
                                  short sectionCode,
                                  struct PESectionOptions FAR *options);


// Setting line height
// -------------------

#define PE_ALLLINES  -1

BOOL CRPE_API PESetLineHeight (short printJob,
                               short sectionCode,
                               short lineN,      // use PE_ALLLINES for all lines
                               short height,     // in twips
                               short ascent);    // in twips

short CRPE_API PEGetNLinesInSection (short printJob,
                                       short sectionCode);

BOOL CRPE_API PEGetLineHeight (short printJob,
                               short sectionCode,
                               short lineN,
                               short FAR *height,
                               short FAR *ascent);


// Setting font info
// -----------------

#define PE_FIELDS    0x0001
#define PE_TEXT      0x0002

#define PE_UNCHANGED -1

BOOL CRPE_API PESetFont (short printJob,
                         short sectionCode,
                         short scopeCode,
                         char FAR *faceName,  // 0 for no change
                         short fontFamily,    // FF_DONTCARE for no change
                         short fontPitch,     // DEFAULT_PITCH for no change
                         short charSet,       // DEFAULT_CHARSET for no change
                         short pointSize,     // 0 for no change
                         short isItalic,      // PE_UNCHANGED for no change
                         short isUnderlined,  // ditto
                         short isStruckOut,   // ditto
                         short weight);       // 0 for no change


// Setting Graph/Chart info
// ------------------------
//
// Two parameters are passed to uniquely identify the graph:
//      - section code
//      - graph number in that section
//
// The section code includes whether it is a header or footer, and the
// graph number starts at 0, 1...  The graph number identifies the graph
// by its position in the section
//      - looking top down first,
//      - then left to right if they have the same top.

// Graph Types

#define PE_SIDE_BY_SIDE_BAR_GRAPH             0
#define PE_STACKED_BAR_GRAPH                  2
#define PE_PERCENT_BAR_GRAPH                  3
#define PE_FAKED_3D_SIDE_BY_SIDE_BAR_GRAPH    4
#define PE_FAKED_3D_STACKED_BAR_GRAPH         5
#define PE_FAKED_3D_PERCENT_BAR_GRAPH         6
#define PE_PIE_GRAPH                          40
#define PE_MULTIPLE_PIE_GRAPH                 42
#define PE_PROPORTIONAL_MULTI_PIE_GRAPH       43
#define PE_LINE_GRAPH                         80
#define PE_AREA_GRAPH                         120
#define PE_THREED_BAR_GRAPH                   160
#define PE_USER_DEFINED_GRAPH                 500
#define PE_UNKNOWN_TYPE_GRAPH                 1000

// Graph Directions.
#define PE_GRAPH_ROWS_ONLY                    0
#define PE_GRAPH_COLS_ONLY                    1
#define PE_GRAPH_MIXED_ROW_COL                2
#define PE_GRAPH_MIXED_COL_ROW                3
#define PE_GRAPH_UNKNOWN_DIRECTION            20

// Graph constant for rowGroupN, colGroupN, summarizedFieldN in PEGraphDataInfo
#define PE_GRAPH_DATA_NULL_SELECTION          -1

// Graph text max length
#define PE_GRAPH_TEXT_LEN                     128

struct PEGraphDataInfo
{
    WORD StructSize;            // initialize to sizeof (PEGraphDataInfo)

    short rowGroupN,            // group number in report.
          colGroupN,            // group number in report.
          summarizedFieldN,     // summarized field number for the group
                                // where the graph stays.
          graphDirection;       // For normal group/total report, the direction,
                                // is always GRAPH_COLS_ONLY.  For CrossTab
                                // report all four options will change the
                                // graph data.
};

struct PEGraphTextInfo
{
    WORD StructSize;            // initialize to sizeof (PEGraphTextInfo)

    // Strings are null-terminated.
    char graphTitle       [PE_GRAPH_TEXT_LEN];
    char graphSubTitle    [PE_GRAPH_TEXT_LEN];
    char graphFootNote    [PE_GRAPH_TEXT_LEN];
    char graphGroupsTitle [PE_GRAPH_TEXT_LEN];
    char graphSeriesTitle [PE_GRAPH_TEXT_LEN];
    char graphXAxisTitle  [PE_GRAPH_TEXT_LEN];
    char graphYAxisTitle  [PE_GRAPH_TEXT_LEN];
    char graphZAxisTitle  [PE_GRAPH_TEXT_LEN];
};

struct PEGraphOptions
{
    WORD StructSize;            // initialize to sizeof (PEGraphOptions)

    double graphMaxValue,
           graphMinValue;

    BOOL   showDataValue,       // Show data values on risers.
           showGridLine,
           verticalBars,
           showLegend;

    char   fontFaceName [PE_GRAPH_TEXT_LEN];
};

BOOL CRPE_API PEGetGraphType (short printJob,
                              short sectionCode,
                              short graphN,
                              short FAR *graphType);

BOOL CRPE_API PEGetGraphData (short printJob,
                              short sectionCode,
                              short graphN,
                              struct PEGraphDataInfo FAR *graphDataInfo);

BOOL CRPE_API PEGetGraphText (short printJob,
                              short sectionCode,
                              short graphN,
                              struct PEGraphTextInfo FAR *graphTextInfo);

BOOL CRPE_API PEGetGraphOptions (short printJob,
                                 short sectionCode,
                                 short graphN,
                                 struct PEGraphOptions FAR *graphOptions);

BOOL CRPE_API PESetGraphType (short printJob,
                              short sectionCode,
                              short graphN,
                              short FAR *graphType);

BOOL CRPE_API PESetGraphData (short printJob,
                              short sectionCode,
                              short graphN,
                              struct PEGraphDataInfo FAR *graphDataInfo);

BOOL CRPE_API PESetGraphText (short printJob,
                              short sectionCode,
                              short graphN,
                              struct PEGraphTextInfo FAR *graphTextInfo);

BOOL CRPE_API PESetGraphOptions (short printJob,
                                 short sectionCode,
                                 short graphN,
                                 struct PEGraphOptions FAR *graphOptions);

#if defined (__cplusplus)
}
#endif

#endif // CRPE_H
