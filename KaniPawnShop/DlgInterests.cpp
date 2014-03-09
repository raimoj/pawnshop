// DlgInterests.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgInterests.h"

#include "DBLoanRenewalExpenses.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgInterests dialog


CDlgInterests::CDlgInterests(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInterests::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInterests)
	m_sNimiHtun = _T("");
	m_sLainanPaivays = _T("");
	m_sLainanErapaiva = _T("");
	m_sLainanLunTaiUudPv = _T("");
	m_sLainasumma = _T("");
	m_sLainanKorkoPrKk = _T("");
	m_sLainanSHVKorkoPrKk = _T("");
	m_sKulutLunYht = _T("");
	m_sKulutUudYht = _T("");
	m_sMuistutus1 = _T("");
	m_sMuistutus2 = _T("");
	m_sYlimSailMaksu = _T("");
	//}}AFX_DATA_INIT
}

CDlgInterests::~CDlgInterests()
{
	if (m_pLoan) delete m_pLoan;
}

void CDlgInterests::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInterests)
	DDX_Text(pDX, IDC_NIMI_HTUN, m_sNimiHtun);
	DDX_Text(pDX, IDC_LAINAN_PV, m_sLainanPaivays);
	DDX_Text(pDX, IDC_LAINAN_ERAPV, m_sLainanErapaiva);
	DDX_Text(pDX, IDC_LAINAN_LUNUUD_PV, m_sLainanLunTaiUudPv);
	DDX_Text(pDX, IDC_LAINASUMMA, m_sLainasumma);
	DDX_Text(pDX, IDC_KORKOPRKK, m_sLainanKorkoPrKk);
	DDX_Text(pDX, IDC_SHVMAKSUKORKOPRKK, m_sLainanSHVKorkoPrKk);
	DDX_Text(pDX, IDC_KULUT_LUNYHT, m_sKulutLunYht);
	DDX_Text(pDX, IDC_KULUT_UUDYHT, m_sKulutUudYht);
	DDX_Text(pDX, IDC_MUISTUTUS1, m_sMuistutus1);
	DDX_Text(pDX, IDC_MUISTUTUS2, m_sMuistutus2);
	DDX_Text(pDX, IDC_YLIMSAILMAKSU, m_sYlimSailMaksu);
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX,&m_wndInterestGrid);
}


BEGIN_MESSAGE_MAP(CDlgInterests, CDialog)
	//{{AFX_MSG_MAP(CDlgInterests)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BTN_LASKE, OnBtnLaske)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInterests message handlers

BOOL CDlgInterests::OnInitDialog()
{
	CDialog::OnInitDialog();
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_wndInterestGrid.SubclassDlgItem(IDC_INTERESTGRID, this);
	m_wndInterestGrid.Initialize();

	m_pLoan = new CLoan(m_pMC->getLoanNumber());
	initGridCols();
	showLoanInfo();
	showLoanExpenses();

	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	m_wndInterestGrid.SetReadOnly();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInterests::OnCancelMode()
{
	CDialog::OnCancelMode();

	// TODO: Add your message handler code here

}

void CDlgInterests::OnBtnLaske()
{
	char buf[100];
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	CTime tTarget = theApp.GetDate(theApp.RemoveSpaces(m_sLainanLunTaiUudPv));
	TRACE("New date=%s\n",tTarget.Format("%d.%m.%Y"));
	m_pLoan->getRedemptionLoanExpenses()->computeExpensesAtDate(tTarget);
	m_pLoan->getRenewalLoanExpenses()->computeExpensesAtDate(tTarget);
	showLoanExpenses();

	//sprintf(buf, "%s", tTarget.Format("%d.%m.%Y"));
	//sprintf(buf, "%s", m_pLoan->getRedemptionLoanExpenses()->getExpensesTargetDate().Format("%d.%m.%Y"));
	sprintf(buf, "%s", m_pLoan->getRenewalLoanExpenses()->getExpensesTargetDate().Format("%d.%m.%Y"));
	m_sLainanLunTaiUudPv = buf;
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}

void CDlgInterests::showLoanInfo()
{
	char buf[100];
	m_sNimiHtun.Format("LainaNr: %ld  Htun: %s", m_pLoan->getRedemptionLoan()->m_LA_Nr, m_pLoan->getCustomerInfo().m_AS_HTun);
	sprintf(buf, "%s", m_pLoan->getRedemptionLoan()->m_LA_Pv.Format("%d.%m.%Y"));
	m_sLainanPaivays = buf;
	sprintf(buf, "%s", m_pLoan->getRedemptionLoan()->m_LA_EraPv.Format("%d.%m.%Y"));
	m_sLainanErapaiva = buf;

	CTime ThisDay = CTime::GetCurrentTime();
	CTime paiva((ThisDay.GetYear()), (ThisDay.GetMonth()), (ThisDay.GetDay()), 0,0,0);
	sprintf(buf, "%s", paiva.Format("%d.%m.%Y"));
	m_sLainanLunTaiUudPv = buf;

	m_sLainasumma.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_Laina);
	m_sLainanKorkoPrKk.Format("%7.1f", m_pLoan->getRedemptionLoan()->m_LA_Korko);
	m_sLainanSHVKorkoPrKk.Format("%7.1f", m_pLoan->getRedemptionLoan()->m_LA_SaVakMaksuPr);

	if (m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu1 > 0.01)
	{
		m_sMuistutus1.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu1);
	}
	else
	{
		m_sMuistutus1 = "-";
	}

	if (m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu2 > 0.01)
	{
		m_sMuistutus2.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu2);
	}
	else
	{
		m_sMuistutus2 = "-";
	}
}

void CDlgInterests::showLoanExpenses()
{
	CString s = "";
	double dKulutYht = 0;
	m_wndInterestGrid.SetReadOnly(FALSE);
	//
	// --- laina/korkopäivien lkm ----
	s.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getLainaPvEnnenErapaivaa());
	m_wndInterestGrid.SetStyleRange(CGXRange(4,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(14,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(25,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(35,2), CGXStyle().SetValue(s));
	s.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getLainaPvErapvnJalkeen());
	m_wndInterestGrid.SetStyleRange(CGXRange(4,4), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(14,4), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(25,4), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(35,4), CGXStyle().SetValue(s));
	s.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getLainaPvYht());
	m_wndInterestGrid.SetStyleRange(CGXRange(4,6), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(14,6), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(25,6), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(35,6), CGXStyle().SetValue(s));
	//
	// --- lainakuukausien määrä ---
	s.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa());
	m_wndInterestGrid.SetStyleRange(CGXRange(5,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(26,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(36,2), CGXStyle().SetValue(s));
	s.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getKorkoLainaKkErapvnJalkeen());
	m_wndInterestGrid.SetStyleRange(CGXRange(5,4), CGXStyle().SetValue(s));  // korko (raj max 4 kk)
	s.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getSHVLainaKkErapvnJalkeen());
	m_wndInterestGrid.SetStyleRange(CGXRange(26,4), CGXStyle().SetValue(s)); // shv (ei raj 4 kk)
	m_wndInterestGrid.SetStyleRange(CGXRange(36,4), CGXStyle().SetValue(s)); // shv (ei raj 4 kk)
	//
	// ---- korko% -----
	s.Format("%7.3f", m_pLoan->getRedemptionLoanExpenses()->getKorkoPrPerPv());
	//m_wndInterestGrid.SetStyleRange(CGXRange(6,2), CGXStyle().SetValue(s));
	//m_wndInterestGrid.SetStyleRange(CGXRange(6,4), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(16,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(16,4), CGXStyle().SetValue(s));
	s.Format("%7.1f", m_pLoan->getRedemptionLoanExpenses()->getKorkoPrPerKk());
	m_wndInterestGrid.SetStyleRange(CGXRange(7,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(7,4), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(17,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(17,4), CGXStyle().SetValue(s));
	//
	// ---- SHV-korko% -----
	s.Format("%7.3f", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoPrPerPv());
	m_wndInterestGrid.SetStyleRange(CGXRange(27,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(27,4), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(37,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(37,4), CGXStyle().SetValue(s));
	s.Format("%7.1f", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoPrPerKk());
	m_wndInterestGrid.SetStyleRange(CGXRange(28,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(28,4), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(38,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(38,4), CGXStyle().SetValue(s));
	//
	// ---- korko mk / pv / kk -----
	s.Format("%7.4f", m_pLoan->getRenewalLoanExpenses()->getKorkoMkPerPv());
	m_wndInterestGrid.SetStyleRange(CGXRange(18,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(18,4), CGXStyle().SetValue(s));
	s.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkPerKk());
	m_wndInterestGrid.SetStyleRange(CGXRange(9,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(9,4), CGXStyle().SetValue(s));
	//
	// ---- SHV-korko mk / pv / kk -----
	s.Format("%7.4f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkPerPv());
	m_wndInterestGrid.SetStyleRange(CGXRange(39,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(39,4), CGXStyle().SetValue(s));

	s.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkPerKk());
	m_wndInterestGrid.SetStyleRange(CGXRange(30,2), CGXStyle().SetValue(s));
	m_wndInterestGrid.SetStyleRange(CGXRange(30,4), CGXStyle().SetValue(s));
	//s.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkPerKk());
	//m_wndInterestGrid.SetStyleRange(CGXRange(40,4), CGXStyle().SetValue(s));
	//
	// ---- korko mk yht -----
	s.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkEnnenErapaivaaYht());
	m_wndInterestGrid.SetStyleRange(CGXRange(9,3), CGXStyle().SetValue(s));
	s.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getKorkoMkEnnenErapaivaaYht());
	m_wndInterestGrid.SetStyleRange(CGXRange(18,3), CGXStyle().SetValue(s));

	s.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkErapvnJalkeenYht()); // uusiksi
	m_wndInterestGrid.SetStyleRange(CGXRange(9,5), CGXStyle().SetValue(s));




	s.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getKorkoMkErapvnJalkeenYht());
	m_wndInterestGrid.SetStyleRange(CGXRange(18,5), CGXStyle().SetValue(s));

	s.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT());
	m_wndInterestGrid.SetStyleRange(CGXRange(10,6), CGXStyle().SetValue(s));
	s.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT());
	m_wndInterestGrid.SetStyleRange(CGXRange(20,6), CGXStyle().SetValue(s));

	//
	// ---- SHV-korko yht ---
	s.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkEnnenErapaivaaYht());
	m_wndInterestGrid.SetStyleRange(CGXRange(30,3), CGXStyle().SetValue(s));
	s.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkErapvnJalkeenYht());
	m_wndInterestGrid.SetStyleRange(CGXRange(30,5), CGXStyle().SetValue(s));
	s.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT());
	m_wndInterestGrid.SetStyleRange(CGXRange(31,6), CGXStyle().SetValue(s));
	//
	s.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkEnnenErapaivaaYht());
	m_wndInterestGrid.SetStyleRange(CGXRange(39,3), CGXStyle().SetValue(s));
	s.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkErapvnJalkeenYht());
	m_wndInterestGrid.SetStyleRange(CGXRange(39,5), CGXStyle().SetValue(s));
	
	//s.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkErapvnJalkeenYht());
	//m_wndInterestGrid.SetStyleRange(CGXRange(40,5), CGXStyle().SetValue(s));
	s.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT());
	m_wndInterestGrid.SetStyleRange(CGXRange(41,6), CGXStyle().SetValue(s));

	//
	// --- ylimSailMaksu ---
	//m_sYlimSailMaksu.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_YlimSaMaksu);
	m_sYlimSailMaksu.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getExtraStoringFee());
	
	//
	// --- kulut yht lunastuksessa ---
	//dKulutYht = m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT() // ei sisällä ylim sail maksun ?
	dKulutYht = m_pLoan->getRedemptionLoanExpenses()->/*getKorkoMkYHT()*/getKorkoMkYHTplusYlimSailMaksu() // sisältää ylim sail maksun ?
									  + m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT()
									  + theApp.GetAs()->m_AT_Kuittimaksu
									  + m_pLoan->getRedemptionLoan()->m_LA_Laina;
	if (m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu1 > 0.01)
	{
		dKulutYht = dKulutYht + m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu1;
	}
	if (m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu2 > 0.01)
	{
		dKulutYht = dKulutYht + m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu2;
	}
	m_sKulutLunYht.Format("%7.2f", dKulutYht);

	//
	// --- kulut yht uudistettaessa ---
	//dKulutYht = m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT()
	dKulutYht = m_pLoan->getRenewalLoanExpenses()->/*getKorkoMkYHT()*/getKorkoMkYHTplusYlimSailMaksu()
									  + m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT()
									  + theApp.GetAs()->m_AT_Kuittimaksu;

	if (m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu1 > 0.01)
	{
		dKulutYht = dKulutYht + m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu1;
	}
	if (m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu2 > 0.01)
	{
		dKulutYht = dKulutYht + m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu2;
	}
	m_sKulutUudYht.Format("%7.2f", dKulutYht);
	
	
	//
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	m_wndInterestGrid.SetReadOnly(TRUE);
}

void CDlgInterests::initGridCols()
{
	m_wndInterestGrid.initGridCols();

}
