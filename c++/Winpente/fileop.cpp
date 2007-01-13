////////////////
// FILEOP.CPP //
////////////////

#include "winpente.h"

char szWorkingDirectory[_MAX_PATH];
static OPENFILENAME ofn;

/////////////////////////////
// FileInitialize Function //
/////////////////////////////
void FileInitialize(HWND hWnd)
{
	static char sz_filter[] = "Pente Files (*.PTE)\0*.pte\0";

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner			= hWnd;
	ofn.hInstance				  = NULL;
	ofn.lpstrFilter					= sz_filter;
	ofn.lpstrCustomFilter	= NULL;
	ofn.nMaxCustFilter	    = 0;
	ofn.nFilterIndex		     = 0;
	ofn.lpstrFile					 = NULL;
	ofn.nMaxFile				  = _MAX_PATH;
	ofn.lpstrFileTitle			  = NULL;
	ofn.nMaxFileTitle		   = _MAX_FNAME + _MAX_EXT;
	ofn.lpstrInitialDir			 = NULL;
	ofn.lpstrTitle				      = NULL;
	ofn.Flags					       = 0;
	ofn.nFileOffset				   = 0;
	ofn.nFileExtension		  = 0;
	ofn.lpstrDefExt			 	  = "pte";
	ofn.lCustData				  = 0L;
	ofn.lpfnHook				  = NULL;
	ofn.lpTemplateName	 = NULL;

	/* Get current working directory */
	_getcwd(szWorkingDirectory, _MAX_PATH);

	/* Check for slash at end */
	if (strncmp(&szWorkingDirectory[strlen(szWorkingDirectory) - 1], "\\", 1) == 0)
		strncpy(&szWorkingDirectory[strlen(szWorkingDirectory) - 1], "\0", 1);

}
//////////////////////////
// FileOpenDlg Function //
//////////////////////////
BOOL FileOpenDlg (HWND hWnd, PSTR pstrFileName, PSTR pstrTitleName)
{
	ofn.hwndOwner				= hWnd;
	ofn.lpstrFile				= pstrFileName;
	ofn.lpstrFileTitle			= pstrTitleName;
	ofn.Flags					= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

	return (GetOpenFileName (&ofn));
}

//////////////////////////
// FileSaveDlg Function //
//////////////////////////
BOOL FileSaveDlg (HWND hWnd, PSTR pstrFileName, PSTR pstrTitleName)
{
	ofn.hwndOwner	  = hWnd;
	ofn.lpstrFile			   = pstrFileName;
	ofn.lpstrFileTitle	   = pstrTitleName;
	ofn.Flags					= OFN_OVERWRITEPROMPT;

	return (GetSaveFileName(&ofn));
}

////////////////////////
// FileWrite Function //
////////////////////////
BOOL FileWrite(PSTR pstrFileName)
{
	FILE* file;
	int i,j;
	int iLength;
    GAMEFILE* SaveGame;
			
	iLength = sizeof(GAMEFILE);

	if (!(SaveGame = (GAMEFILE*)malloc( iLength)))
		return(FALSE);

	if (NULL == (file = fopen(pstrFileName, "wb")))
	{
		free(SaveGame);
		return(FALSE);
	}

	/*Copy Data from  existing structure */
	for (i=0, j=0;  i<19; j++)
	{
		SaveGame->piece[i][j] = p_Box[i][j]->piece;
		if (j == 18)
		{
			i++;
			j=-1;
		}
	}
	SaveGame->info[0] = p_Board->current_turn;
	SaveGame->info[1] = p_Board->p1_captures;
	SaveGame->info[2] = p_Board->p2_captures;
	SaveGame->info[3] = p_Board->game_option;

	if (iLength != (int)fwrite (SaveGame,1, iLength, file))
	{
		free(SaveGame);
		fclose(file);
		return(FALSE);
	}
	free(SaveGame);
	fclose(file);
	return(TRUE);
}

///////////////////////
// FileRead Function //
///////////////////////
BOOL FileRead(PSTR pstrFileName)
{
	FILE* file;
	int i,j;
	int iLength;
	GAMEFILE* OpenGame;
		
	iLength = sizeof(GAMEFILE);

	if (!(OpenGame = (GAMEFILE*)malloc( iLength)))
		return(FALSE);

	if (NULL == (file = fopen(pstrFileName, "rb")))
	{
		free(OpenGame);
		return (FALSE);
	}
		
	if (iLength != (int)fread(OpenGame, 1, iLength, file))
	{
		free(OpenGame);
		fclose(file);
		return (FALSE);
	}
	/*Copy Data into existing structure */
	for (i=0, j=0; i<19; j++)
	{
		p_Box[i][j]->piece =  OpenGame->piece[i][j];
		if (j == 18)
		{
			i++;
			j=-1;
		}
	}
	p_Board->current_turn = OpenGame->info[0];
	p_Board->p1_captures = OpenGame->info[1];
	p_Board->p2_captures = OpenGame->info[2];
	p_Board->game_option = OpenGame->info[3];
		
	free(OpenGame);
	fclose(file);
	return (TRUE);
}

