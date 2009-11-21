/////////////////////////////////////////////////////////////////////////////
//
// MERGE.H : n-way file merge
//
// Merge sorted files into one large file, by recursively combining n files
// at a time into ever bigger files until only one file remains.
//
// Merge is an template class that operates on a user-defined
// record class.  The user must supply a record comparison function and
// the member functions: open, close, read, write and unlink.
//
// Copyright (C) 2008 Thomas A. Rieck, All rights reserved.
//

#ifndef __MERGE_H__
#define __MERGE_H__

/////////////////////////////////////////////////////////////////////////////
// Merge template class definition

template <class record>
class Merge {
// Construction
public:
	Merge();
	~Merge();

// Interface
public:
	string merge(const stringvec & argv, int delflag);

// Implementation
private:
	virtual int countpasses(int argc);
	virtual string mergemany(const stringvec &argv, int delflag);
	virtual string mergeonce(const stringvec &argv, int delflag);
	virtual record** least(record** recs);

	virtual int open(const char* name, int oflag, int pmode = 0) = 0;
	virtual int close(int fd) = 0;
	virtual int read(record** r) = 0;
	virtual int write(record** r) = 0;
	virtual int unlink(const char* name) = 0;

	enum { NWAY = 60 };         // number of ways to merge during one pass
	// between 2 and 200
	int pass;                   // count down of pass number
	record** array;             // array for least function
};

template <class record>
Merge<record>::Merge()
{
	array = new record*[nway + 1];
}

template <class record>
Merge<record>::~Merge()
{
	delete [] array;
}

template <class record>
int Merge<record>::countpasses(int argc)
{
	int i = 0;

	if (argc <= NWAY)
		return 1;

	while (argc > 0) {
		i++;
		argc -= min(argc, NWAY);
	}

	return i + countpasses(i);
}

template <class record>
string Merge<record>::merge(const stringvec &argv, int delflag)
{
	pass = countpasses(argv.size());

	return mergemany(argv, delflag);
}

#endif // __MERGE_H__
