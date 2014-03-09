// DlgYjKuittaus.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgYjMaksu.h"
#include "RGXAuctBalSetOff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgYjMaksu dialog


CDlgYjMaksu::CDlgYjMaksu(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgYjMaksu::IDD, pParent)
{
	//{ { A FX_DATA_INIT(CDlgYjMaksu)
	m_sKirjeNr = _T("");
	m_sHenkTun = _T("");
	//} } A FX_DATA_INIT
	m_pCRGXAuctBalSetOff = new CRGXAuctBalSetOff();
}

CDlgYjMaksu::CDlgYjMaksu(CAuctionCtrl* pActl, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgYjMaksu::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgYjMaksu)
	m_sKirjeNr = _T("");
	m_sHenkTun = _T("");
	m_sValittuLaina = _T("");
	//}}AFX_DATA_INIT
	m_pCRGXAuctBalSetOff = new CRGXAuctBalSetOff(pActl);
	m_pActl = pActl;
}

CDlgYjMaksu::~CDlgYjMaksu()
{
	delete m_pCRGXAuctBalSetOff;
}


void CDlgYjMaksu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgYjMaksu)
	DDX_Control(pDX, IDC_VALITTU_LAINA, m_ctlValittuLaina);
	DDX_Control(pDX, IDC_KUITTI, m_ctlBtnKuitti);
	DDX_Control(pDX, IDC_KIRJENR, m_ctlKirjeNr);
	DDX_Control(pDX, IDC_HENKTUN, m_ctlHenkTun);
	DDX_CBString(pDX, IDC_KIRJENR, m_sKirjeNr);
	DDX_CBString(pDX, IDC_HENKTUN, m_sHenkTun);
	DDX_Text(pDX, IDC_VALITTU_LAINA, m_sValittuLaina);
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX, m_pCRGXAuctBalSetOff);
}


BEGIN_MESSAGE_MAP(CDlgYjMaksu, CDialog)
	//{{AFX_MSG_MAP(CDlgYjMaksu)
	ON_CBN_SELCHANGE(IDC_KIRJENR, OnSelchangeKirjenr)
	ON_CBN_SELCHANGE(IDC_HENKTUN, OnSelchangeHenktun)
	ON_BN_CLICKED(IDC_SULJE, OnSulje)
	ON_BN_CLICKED(IDC_ETSI, OnEtsi)
	ON_BN_CLICKED(IDC_KUITTI, OnKuitti)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgYjMaksu message handlers

BOOL CDlgYjMaksu::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->m_ctlBtnKuitti.EnableWindow(false);

	m_pCRGXAuctBalSetOff->SubclassDlgItem(IDC_YJKIRJEEN_LAINAT, this);
	m_pCRGXAuctBalSetOff->Initialize();

	m_pCRGXAuctBalSetOff->initColumns();

	m_pActl->getLetterNrs(&m_ctlKirjeNr, "");
	m_pActl->getIdentityNrs(&m_ctlHenkTun);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgYjMaksu::OnSelchangeKirjenr()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString sLnr = "";
	m_ctlHenkTun.SetCurSel(-1);
	//
	int iRow = m_ctlKirjeNr.GetCurSel();
	if (iRow == CB_ERR)
		return;
	TRACE("Valittu rivi %d\n", iRow);

	m_ctlKirjeNr.GetLBText(iRow, sLnr);
	TRACE("Valittu nr %s\n", sLnr);
	m_pCRGXAuctBalSetOff->showLetter(atol(sLnr));
}

void CDlgYjMaksu::OnSelchangeHenktun()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString sH = "";
	m_ctlKirjeNr.ResetContent();
	int iRow = m_ctlHenkTun.GetCurSel();
	if (iRow == CB_ERR)
		return;
	TRACE("Valittu rivi %d\n", iRow);
	m_ctlHenkTun.GetLBText(iRow, sH);
	TRACE("Valittu HT '%s'\n", sH);
	m_pCRGXAuctBalSetOff->clear();
	m_pActl->getLetterNrs(&m_ctlKirjeNr, sH);
}


void CDlgYjMaksu::OnOK()
{
	m_ctlHenkTun.SetCurSel(-1);
	m_ctlKirjeNr.SetCurSel(-1);
	m_pCRGXAuctBalSetOff->clear();
	setSelectedLoan(0, false);
	CDialog::OnOK();
}

void CDlgYjMaksu::OnCancel()
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CDlgYjMaksu::OnSulje()
{
	//CDialog::OnOK();
}

void CDlgYjMaksu::OnEtsi()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString stmp = "";
	m_ctlKirjeNr.GetWindowText(stmp);
	if (stmp.IsEmpty())
	{
		m_pCRGXAuctBalSetOff->clear();
		return;
	}
	m_ctlKirjeNr.ResetContent();
	m_pActl->getLetterNrs(&m_ctlKirjeNr, "");
	m_ctlHenkTun.SetCurSel(-1);
	int iRow = m_ctlKirjeNr.FindStringExact(-1, stmp);
	if (iRow == CB_ERR)
	{
		m_pCRGXAuctBalSetOff->clear();
		return;
	}
	else
	{
		m_ctlKirjeNr.SetCurSel(iRow);
		m_pCRGXAuctBalSetOff->showLetter(atol(stmp));
	}
}

void CDlgYjMaksu::setSelectedLoan(long lLNr, bool bLock)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_lSelectedLoan = lLNr;
	if (lLNr > 0 && bLock == false)
	{
		m_sValittuLaina.Format("Valittu laina: %ld", lLNr);
		this->m_ctlBtnKuitti.EnableWindow(true);
	}
	else
	{
		m_sValittuLaina = "";
		this->m_ctlBtnKuitti.EnableWindow(false);
	}
	m_ctlValittuLaina.SetWindowText(m_sValittuLaina);
	//UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}

void CDlgYjMaksu::OnKuitti()
{
	CString msg = "";
	msg.Format("Tulostetaanko kuitti ylijäämästä lainalle %ld ?", m_lSelectedLoan);
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return;
	}
	else
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		m_pActl->printAuctBalSetOff(m_lSelectedLoan);
	}
	OnOK();
}

