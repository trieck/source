
#include "stdafx.h"
#include "pefile.h"

/////////////////////////////////////////////////////////////////////////////
void Usage()
{
    tcerr << TEXT("usage: petool file") << endl;
    exit(1);
}

/////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
    if (argc < 2) {
        Usage();
    }

	try {
		PEFile::Dump(argv[1]);
    } catch (const _com_error &e) {
        tcerr << e.Description() << endl;
    } catch (const Exception &e) {
        tcerr << e.GetDescription() << endl;
        return 1;
    }

	return 0;
}

