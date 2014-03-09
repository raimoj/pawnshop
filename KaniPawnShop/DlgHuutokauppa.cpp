// DlgHuutokauppa.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgHuutokauppa.h"
#include "AuctionCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgHuutokauppa dialog


CDlgHuutokauppa::CDlgHuutokauppa(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHuutokauppa::IDD, pParent)
{
	ASSERT(0);
	/*//{{AFX_DATA_INIT(CDlgHuutokauppa)
	m_sLainanumeroLabel = _T("");
	//}}AFX_DATA_INIT
	TRACE("Default CDlgHuutokauppa-ctor\n");
	m_pHkLGrid = new CRGXHkLainaGrid;
	m_pHkLRGrid = new CRGXHkLainarivitGrid;
	*/
	m_brBack.CreateSolidBrush(RGB(255, 255, 0)); //kirkkaan keltainen
	//m_brBack.CreateSolidBrush(RGB(128, 128, 64)); // ruskeanvihreä :)
	m_brBack2.CreateSolidBrush(RGB(128, 255, 255)); // vaaleansininen
	m_brBack3.CreateSolidBrush(RGB(255, 255, 255)); // valk
	m_brBack4.CreateSolidBrush(RGB(255, 128, 128)); // vaalean pun

}
CDlgHuutokauppa::CDlgHuutokauppa(CMC* pMC, CAuctionCtrl* pACtrl, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHuutokauppa::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHuutokauppa)
	m_sLainanumeroLabel = _T("");
	m_sEtsiLainanumero = _T("");
	//}}AFX_DATA_INIT

	m_pMC = pMC;
	m_pACtrl = pACtrl;

	if (theApp.m_bAdminUser == TRUE)
		TRACE("AdminUser=TRUE\n");
	else
		TRACE("AdminUser=FALSE\n");

	m_pHkLGrid = new CRGXHkLainaGrid(m_pMC, m_pACtrl);
	m_pHkLRGrid = new CRGXHkLainarivitGrid(m_pMC, m_pACtrl);
	m_lCurrentLoanNbr = 0;

	m_brBack.CreateSolidBrush(RGB(255, 255, 0)); //kirkkaan keltainen
	//m_brBack.CreateSolidBrush(RGB(128, 128, 64)); // ruskeanvihreä :)
	m_brBack2.CreateSolidBrush(RGB(128, 255, 255)); // vaaleansininen
	m_brBack3.CreateSolidBrush(RGB(255, 255, 255)); // valk
	m_brBack4.CreateSolidBrush(RGB(255, 128, 128)); // vaalean pun

}


CDlgHuutokauppa::~CDlgHuutokauppa()
{
	delete m_pHkLGrid;
	delete m_pHkLRGrid;
}

void CDlgHuutokauppa::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHuutokauppa)
	DDX_Control(pDX, IDC_HKLISTA_BTN, m_ctlBtnHkLista);
	DDX_Control(pDX, IDC_KUVAUKSET_BTN, m_ctlBtnKuvaukset);
	DDX_Control(pDX, IDC_BTN_RAPORTTI, m_ctlBtnRaportti);
	DDX_Control(pDX, IDC_HUUTOKAUPPAN_VALINTA, m_ctlHuutokaupanValinta);
	DDX_Control(pDX, IDC_STATIC_TXT_TALLETUS_IND, m_ctlTalletusIndicator);
	DDX_Control(pDX, IDC_PALAUTA_BTN, m_ctlPalautaLainaBtn);
	DDX_Text(pDX, IDC_LAINANUMERO_LABEL, m_sLainanumeroLabel);
	DDX_Text(pDX, IDC_ETSI, m_sEtsiLainanumero);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHuutokauppa, CDialog)
	//{{AFX_MSG_MAP(CDlgHuutokauppa)
	ON_BN_CLICKED(IDC_PALAUTA_BTN, OnPalautaBtn)
	ON_BN_CLICKED(IDC_HKLISTA_BTN, OnHklistaBtn)
	ON_BN_CLICKED(IDC_KUVAUKSET_BTN, OnKuvauksetBtn)
	ON_CBN_SELCHANGE(IDC_HUUTOKAUPPAN_VALINTA, OnSelchangeHuutokauppanValinta)
	ON_BN_CLICKED(IDC_BTN_RAPORTTI, OnBtnRaportti)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_ETSI, OnBtnEtsi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHuutokauppa message handlers

BOOL CDlgHuutokauppa::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_ctlPalautaLainaBtn.EnableWindow(FALSE);

	m_pHkLGrid->SubclassDlgItem(IDC_HK_LAINA, this);
	m_pHkLGrid->Initialize();
	m_pHkLGrid->initColumns();

	m_pHkLRGrid->SubclassDlgItem(IDC_HK_LAINARIVIT, this);
	m_pHkLRGrid->Initialize();
	m_pHkLRGrid->initColumns();

	m_pACtrl->initAutionDatesList(&m_ctlHuutokaupanValinta);
	m_pHkLGrid->showAuctionLoans(m_pACtrl->getSelectedAuction()); //"HKL_PoistettuHKsta = NULL"); ???
	m_pHkLRGrid->clearList();

	if (theApp.m_bAdminUser)
	{
		m_ctlBtnRaportti.EnableWindow(TRUE);
		m_ctlBtnKuvaukset.EnableWindow(TRUE);
		m_ctlBtnHkLista.EnableWindow(TRUE);
	}
	else
	{
		m_ctlBtnRaportti.EnableWindow(FALSE);
		m_ctlBtnKuvaukset.EnableWindow(FALSE);
		m_ctlBtnHkLista.EnableWindow(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHuutokauppa::showLoanInfo(long lLoanNbr, bool bReturnIsPossible)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString sPawnTicketOwner = "";
	long lCustID = 0;
	sPawnTicketOwner = this->m_pMC->m_pDB->getCustomerName(this->m_pMC->m_pDB->GetPawnTicketOwner( lLoanNbr));
	if (lLoanNbr >= 1)
	{
		
		this->m_sLainanumeroLabel.Format("Laina: %ld %s", lLoanNbr, sPawnTicketOwner);
		m_lCurrentLoanNbr = lLoanNbr;
		if (bReturnIsPossible)
			m_ctlPalautaLainaBtn.EnableWindow(TRUE);
		else
			m_ctlPalautaLainaBtn.EnableWindow(FALSE);
		UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	}
	else
	{
		clearDlgFields();
	}
}

void CDlgHuutokauppa::OnPalautaBtn()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_pACtrl->returnSelectedLoanFromAuction(m_lCurrentLoanNbr);
	showLoanInfo(0, FALSE);

	m_pHkLGrid->showAuctionLoans(m_pACtrl->getSelectedAuction()); //"HKL_PoistettuHKsta = NULL"); ???
	m_pHkLRGrid->clearList();

}

/*void CDlgHuutokauppa::OnAsiakaslistaBtn()
{
	this->m_pACtrl->printAuctionList(true);
}

void CDlgHuutokauppa::OnMeklarilistaBtn()
{
	this->m_pACtrl->printAuctionList(false);// true = Asiakaslista, false = Meklarilista
}
*/
void CDlgHuutokauppa::OnOK()
{
	TRACE("Notify the LGrid...\n");
	m_pHkLGrid->dialogIsClosing();
	TRACE("Notify the LRGrid...\n");
	m_pHkLRGrid->dialogIsClosing();
	TRACE("...CDlgHuutokauppa:OnOK...\n");
	CDialog::OnOK();
}

void CDlgHuutokauppa::OnHklistaBtn()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	this->m_pACtrl->saveAuctionList();
}

void CDlgHuutokauppa::OnKuvauksetBtn()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	this->m_pACtrl->printDescriptions();
}

void CDlgHuutokauppa::setSavingFlag(bool bOn)
{
	if (bOn == true)
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		m_ctlTalletusIndicator.SetWindowText("Talletus...");
	}
	else
		m_ctlTalletusIndicator.SetWindowText("-");
}

void CDlgHuutokauppa::OnSelchangeHuutokauppanValinta()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	long lAindx = m_ctlHuutokaupanValinta.GetItemData(m_ctlHuutokaupanValinta.GetCurSel());
	//TRACE("HK=%ld\n", lAindx);
	this->m_pACtrl->setSelectedAuction(lAindx);
	m_pHkLGrid->showAuctionLoans(m_pACtrl->getSelectedAuction()); //"HKL_PoistettuHKsta = NULL"); ???
	m_pHkLRGrid->clearList();
}

void CDlgHuutokauppa::OnBtnRaportti()
{
	this->m_pACtrl->auctionReport(this);
}

void CDlgHuutokauppa::clearDlgFields()
{
	this->m_sLainanumeroLabel = "";
	m_lCurrentLoanNbr = 0;
	m_ctlPalautaLainaBtn.EnableWindow(FALSE);
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}

void CDlgHuutokauppa::selectAuction()
{
	OnSelchangeHuutokauppanValinta();
}

HBRUSH CDlgHuutokauppa::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		// TODO: Change any attributes of the DC here

		//if (nCtlColor == CTLCOLOR_STATIC)
		//	return m_brBack2;
		//else if (nCtlColor == CTLCOLOR_EDIT)
		//	return m_brBack3;
		//else
	//	return static_cast<HBRUSH>(m_brBack3.GetSafeHandle());
	switch(nCtlColor)
	{
		case CTLCOLOR_BTN:
		case CTLCOLOR_STATIC:
			pDC->SetBkMode( TRANSPARENT );
			// Fall through

		case CTLCOLOR_DLG:
			return static_cast<HBRUSH>(m_brBack4.GetSafeHandle());
	}
	//return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	//return hbr;
}

void CDlgHuutokauppa::OnBtnEtsi() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	TRACE("Etsitään lnro %s\n", m_sEtsiLainanumero);
	this->m_pHkLGrid->findLoan(atol(m_sEtsiLainanumero));
}
