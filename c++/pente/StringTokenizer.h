// StringTokenizer.h: interface for the StringTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGTOKENIZER_H__E845A57C_2B53_410B_9124_8D47D351EF06__INCLUDED_)
#define AFX_STRINGTOKENIZER_H__E845A57C_2B53_410B_9124_8D47D351EF06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class StringTokenizer {
public:
    StringTokenizer(LPCTSTR pinput, LPCTSTR pdelim);
    ~StringTokenizer();

// Interface
    CString next();

// Implementation
private:
    LPTSTR strtok(LPTSTR s);

    CString delim;			// delimiter
    TCHAR* input;				// input string
    TCHAR* nextoken;		// next token
    bool init;					// has been initialized
};

#endif // !defined(AFX_STRINGTOKENIZER_H__E845A57C_2B53_410B_9124_8D47D351EF06__INCLUDED_)
