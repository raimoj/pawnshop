// DlgYjKuittaus.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgYjKuittaus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgYjKuittaus dialog


CDlgYjKuittaus::CDlgYjKuittaus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgYjKuittaus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgYjKuittaus)
	m_sLimitTime = _T("");
	m_sOldLoans = _T("");
	m_sYlijMk = _T("");
	//}}AFX_DATA_INIT
	m_lYj = 0;
}


void CDlgYjKuittaus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgYjKuittaus)
	DDX_Control(pDX, IDC_KUITTI, m_ctlKuitti);
	DDX_Text(pDX, IDC_YLIJ_TILITYSAIKA_ASTIED, m_sLimitTime);
	DDX_Text(pDX, IDC_OLD_LOANS, m_sOldLoans);
	DDX_Text(pDX, IDC_YLIJMK, m_sYlijMk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgYjKuittaus, CDialog)
	//{{AFX_MSG_MAP(CDlgYjKuittaus)
	ON_BN_CLICKED(IDC_KUITTI, OnKuitti)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgYjKuittaus message handlers

void CDlgYjKuittaus::OnCancel()
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CDlgYjKuittaus::OnOK()
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}

BOOL CDlgYjKuittaus::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_lYj == 0)
		m_ctlKuitti.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgYjKuittaus::OnKuitti()
{
	this->m_pCAuctionCtrl->printBalSetOff();
	OnOK();
}
