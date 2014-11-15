#include "stdafx.h"
#include "search.h"
#include "HiresTimer.h"
#include "RandStream.h"

/////////////////////////////////////////////////////////////////////////////
void displayResults(LPCSTR idxname, const DocVector &v)
{
    char filename[MAX_PATH];
    sprintf(filename, "%s%s.txt",
            dirname(idxname).c_str(),
            basename(idxname).c_str());

    RandomFileStreamPtr stream;
    stream.Attach(RandomFileStream::Create(filename,
                                           GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING,
                                           FILE_ATTRIBUTE_READONLY));
    if (stream == NULL)
        throw Exception(lasterror());	// can't open

    UINT word_pos, i;
    ULONG read;
    UINT64 loc;
    HRESULT hr;
    LARGE_INTEGER offset;
    ULARGE_INTEGER newPos;

    char buf[81];
    string x(78, '-');

    for (i = 0; i < v.size(); i++) {
        loc = v[i];
        word_pos = (loc & 0xFFFFFFFF00000000) >> 32;
        offset.QuadPart = (loc & 0xFFFFFFFF);
        if (offset.QuadPart > 40) offset.QuadPart -= 40;
        hr = stream->Seek(offset, STREAM_SEEK_SET, &newPos);
        if (FAILED(hr))
            throw Exception(lasterror());	// can't open

        hr = stream->Read(buf, sizeof(buf) - 1, &read);
        if (FAILED(hr))
            throw Exception(lasterror());	// can't open

        buf[read] = '\0';
        cout << "(" << i << ")  " << trim(buf) << "..." << endl
             << x << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////
void usage()
{
    cerr << "usage: search idxfile query" << endl;
    exit(1);
}

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    if (argc < 3) usage();

    HiresTimer timer;
    DocVector v;

    try {
        Search search(argv[1]);
        v = search.search(argv[2]);
        displayResults(argv[1], v);
    } catch (RCEXCEPTION e) {
        cerr << e.getDescription() << endl;
        return 1;
    }

    cout << "   " << comma(v.size()) << " hit(s)." << endl;
    cout << "   elapsed time " << timer << endl;

    return 0;
}

