// DlgHakulista.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgHakulista.h"
#include "PanttiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgHakulista dialog


CDlgHakulista::CDlgHakulista(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHakulista::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHakulista)
	m_sHakulistaInfoTxt = _T("");
	m_sInfo1 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgHakulista::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHakulista)
	DDX_Text(pDX, IDC_HL_INFO, m_sHakulistaInfoTxt);
	DDX_Text(pDX, IDC_INFO1, m_sInfo1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHakulista, CDialog)
	//{{AFX_MSG_MAP(CDlgHakulista)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHakulista message handlers

void CDlgHakulista::OnOK() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_sInfo1 = "Ohjelma laskee huutokaupan hakulistan! Kotvasen kestää vielä :-)";
	
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	theApp.m_pMC->startAuctionSearchList();
	theApp.m_pMC->m_pPView->SelchangeSnimi();

	CDialog::OnOK();
}
