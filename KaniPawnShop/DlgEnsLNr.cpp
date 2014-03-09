// DlgEnsLNr.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgEnsLNr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnsLNr dialog


CDlgEnsLNr::CDlgEnsLNr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnsLNr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEnsLNr)
	m_lLNr = 0;
	//}}AFX_DATA_INIT
}


void CDlgEnsLNr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEnsLNr)
	DDX_Text(pDX, IDC_ENSLAINANNR, m_lLNr);
	DDV_MinMaxLong(pDX, m_lLNr, 0, 999999999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEnsLNr, CDialog)
	//{{AFX_MSG_MAP(CDlgEnsLNr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnsLNr message handlers

void CDlgEnsLNr::OnOK()
{
	UpdateData();
	CDialog::OnOK();
}
