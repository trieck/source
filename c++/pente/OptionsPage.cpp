// OptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "pente.h"
#include "OptionsPage.h"


// OptionsPage dialog

IMPLEMENT_DYNAMIC(OptionsPage, CPropertyPage)

OptionsPage::OptionsPage()
	: CPropertyPage(OptionsPage::IDD)
{

}

OptionsPage::~OptionsPage()
{
}

void OptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OptionsPage, CPropertyPage)
END_MESSAGE_MAP()


// OptionsPage message handlers
