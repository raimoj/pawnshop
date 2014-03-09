// DlgUusiLaina.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgUusiLaina.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgUusiLaina dialog


CDlgUusiLaina::CDlgUusiLaina(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUusiLaina::IDD, pParent)
{
	CTime t = CTime::GetCurrentTime();
	CString date = t.Format("%d.%m.%Y");
	//{{AFX_DATA_INIT(CDlgUusiLaina)
	m_sPv = date;
	m_sEraPv = _T("");
	m_sLiitteet = _T("");
	m_sHuom = _T("");
	m_bEiMuistutusta = FALSE;
	m_sLainanNimi = _T("");
	m_dKorkoPr = 0.0;
	m_dSHVMaksuPr = 0.0;
	m_sHtun_Nimi = _T("");
	m_sHuom2 = _T("");
	m_sVarasto = _T("");
	m_sVakuusarvo = _T("");
	m_sLainasumma = _T("");
	m_sYlimSailMaksu = _T("");
	m_sSeuraavaLyhennys = _T("");
	//}}AFX_DATA_INIT
	m_bCanceled = FALSE;
	m_pLainarivit = new CRGXUusiLainaRGrid(this);
	
	m_bDlgAlreadyExists = FALSE;
	m_lLNr = 0;
	m_rows = 0;
	m_pLoan = new CLoan(0); // 0 = uusi laina
	m_iSelectedProductGroup = -1;
	m_sSelectedProductGroup = "";
	m_sVarmennus = "";
	m_dYlimSailMaksu = 0;
	m_dVakuusarvo = 0;
	m_dLainasumma = 0;
	m_sSeuraavaLyhennys = "";
}


CDlgUusiLaina::~CDlgUusiLaina()
{
	delete m_pLainarivit;
	delete m_pLoan;
}

void CDlgUusiLaina::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUusiLaina)
	DDX_Control(pDX, IDC_LAINASUMMA, m_ctlLainasumma);
	DDX_Control(pDX, IDC_VAKUUSARVO, m_ctlVakuusarvo);
	DDX_Control(pDX, IDC_HENK_TARK, m_ctlHenkTark);
	DDX_Control(pDX, IDC_VARASTO, m_ctlVarasto);
	DDX_Control(pDX, IDC_LAINAN_TUOTERYHMA, m_ctlLainanTuoteryhma);
	DDX_Text(pDX, IDC_PVM, m_sPv);
	DDX_Text(pDX, IDC_ERAPV, m_sEraPv);
	DDX_Text(pDX, IDC_LIITTEET, m_sLiitteet);
	DDX_Text(pDX, IDC_HUOM, m_sHuom);
	DDX_Check(pDX, IDC_EIMUISTUTUSTA, m_bEiMuistutusta);
	DDX_Text(pDX, IDC_LAINANNIMI, m_sLainanNimi);
	DDX_Text(pDX, IDC_KORKOPR, m_dKorkoPr);
	DDX_Text(pDX, IDC_SAILVAKMAKSU_PR, m_dSHVMaksuPr);
	DDX_Text(pDX, IDC_HTUN_NIMI, m_sHtun_Nimi);
	DDX_Text(pDX, IDC_HUOM2, m_sHuom2);
	DDX_Text(pDX, IDC_VARASTO, m_sVarasto);
	DDX_Text(pDX, IDC_VAKUUSARVO, m_sVakuusarvo);
	DDX_Text(pDX, IDC_LAINASUMMA, m_sLainasumma);
	DDX_Text(pDX, IDC_YLIMSAILMAKSU, m_sYlimSailMaksu);
	DDX_Text(pDX, IDC_SEURAAVA_LYHENNYS, m_sSeuraavaLyhennys);
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX, m_pLainarivit);
}


BEGIN_MESSAGE_MAP(CDlgUusiLaina, CDialog)
	//{{AFX_MSG_MAP(CDlgUusiLaina)
	ON_BN_CLICKED(IDKUITTI, OnKuitti)
	ON_BN_CLICKED(IDC_BTN_LASKE, OnBtnLaske)
	ON_BN_CLICKED(IDC_PERU, OnPeru)
	ON_CONTROL(RJ_OG_UUSI_LAINA_DLG_LASKE, IDC_UUDEN_LAINAN_RIVIT, OnBtnLaske)
	ON_BN_CLICKED(IDC_TEELAINA, OnTeelaina)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUusiLaina message handlers

void CDlgUusiLaina::OnOK()
{
	TRACE("OnOK\n");
	//CDialog::OnOK(); // poistettu ja lisätty OnKuitti() -> return ei sulje dialogia
}

CString CDlgUusiLaina::GetDlgString()
{
	//UpdateData(); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	// ei saa tehda kun dialogi on suljettu
	CString sL ="";
	sL.Format("%7.2f", -m_dLainasumma);
	//m_AsId
	return "Uusi  " + sL; // uusi laina
}

BOOL CDlgUusiLaina::OnInitDialog() // tehdään kun dialogi tulee näkyviin
{
	char buf[100];
	CDialog::OnInitDialog();
	m_ctlVarasto.LimitText(5);
	theApp.m_pMC->getProductGroupsOfLoan(&m_ctlLainanTuoteryhma);


	m_ctlHenkTark.AddString("Ajokortti");
	m_ctlHenkTark.AddString("Passi");
	m_ctlHenkTark.AddString("Kela");
	m_ctlHenkTark.AddString("Henkilöllisyystod");
	m_ctlHenkTark.SetCurSel(-1);

	m_pLainarivit->SubclassDlgItem(IDC_UUDEN_LAINAN_RIVIT, this);
	m_pLainarivit->Initialize();
	m_pLainarivit->initGrid();

	//TRACE("Varm=%s\n", this->m_sVarmennus);
	this->m_ctlHenkTark.SetWindowText(m_sVarmennus);
	
	m_sVakuusarvo.Format("%7.2f", m_dVakuusarvo);
	m_sLainasumma.Format("%7.2f", m_dLainasumma);
	m_sYlimSailMaksu.Format("%7.2f", m_dYlimSailMaksu); // = 0
	m_sSeuraavaLyhennys = "";
	
	//if (m_bDlgAlreadyExists)
	//{
		m_ctlLainanTuoteryhma.SetCurSel(m_iSelectedProductGroup);
	//	return TRUE;
	//}
	
	CTime paiva = theApp.getDueDate();
	m_dateEraPv = paiva;
	sprintf(buf,"%s",paiva.Format("%d.%m.%Y"));
	m_sEraPv = buf;

	m_dSHVMaksuPr = theApp.GetAs()->m_AT_SHVMaksuPr;
	m_dYlimSailMaksu = 0;
	m_dKorkoPr = theApp.GetAs()->m_AT_LKorkoPr1;  // korko on luokiteltu lainan määrän mukaan;
	
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	m_bDlgAlreadyExists = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgUusiLaina::OnKuitti()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	//int r=0;
	CString msg="";
	CString sBuf = "";
	//char szbuf[250];
	//UpdateData(); // data is being retrieved (TRUE = default) // ei saa tehdä kun dialogi on suljettu


	m_pLoan->getCDBLoan()->m_LA_LainanNimi = m_sLainanNimi;

	m_pLoan->getCDBLoan()->m_LA_LainanTuoteryhma = m_sSelectedProductGroup.Left(1);

	CTime ThisDay = CTime::GetCurrentTime();
	CTime paiva((ThisDay.GetYear()), (ThisDay.GetMonth()), (ThisDay.GetDay()), 0,0,0);
	m_pLoan->getCDBLoan()->m_LA_Pv = paiva;
	m_pLoan->getCDBLoan()->m_LA_AlkupPv = paiva;
	m_pLoan->getCDBLoan()->m_LA_EraPv = m_dateEraPv;
	m_pLoan->getCDBLoan()->m_LA_Tila = "A";  // uusi laina ?
	if (m_bEiMuistutusta == FALSE)
	{
		m_pLoan->getCDBLoan()->m_LA_EiMuistutusta = FALSE;
	}
	else
	{
		m_pLoan->getCDBLoan()->m_LA_EiMuistutusta = TRUE;
	}
	m_pLoan->getCDBLoan()->m_LA_Huom = m_sHuom;  // huom lainalle
	m_pLoan->getCDBLoan()->m_LA_VakSumma = m_dVakuusarvo;
	m_pLoan->getCDBLoan()->m_LA_Laina = m_dLainasumma;
	m_pLoan->getCDBLoan()->m_LA_Korko = m_dKorkoPr;
	m_pLoan->getCDBLoan()->m_LA_Kielto = "";
	m_pLoan->getCDBLoan()->m_LA_SaVakMaksuPr = m_dSHVMaksuPr;
	
	m_pLoan->getCDBLoan()->m_LA_YlimSaMaksu = m_dYlimSailMaksu;   // OnBtnLaske() asetetaan arvo 
	// ongelma, kertamaksu
	// pitäisi olla /kk
	// montako kuukautta?


	m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys = atof(theApp.dot(m_sSeuraavaLyhennys));

	m_pLoan->getCDBLoan()->m_LA_KuitinKatoaminen = FALSE;
	m_pLoan->getCDBLoan()->m_LA_KuitinKatoamisMaksu = 0;
	m_pLoan->getCDBLoan()->m_LA_MuistKirjeMaksu1 = 0;
	m_pLoan->getCDBLoan()->m_LA_MuistKirjeMaksu2 = 0;
	m_pLoan->getCDBLoan()->m_LA_VakVarmMaksu = 0;
	m_pLoan->getCDBLoan()->m_LA_PostitusMaksu = 0;
	m_pLoan->getCDBLoan()->m_LA_Alennus = 0;

	m_pLoan->getCDBLoan()->m_LA_Liitteet = m_sLiitteet;
	m_pLoan->getCDBLoan()->m_LA_MuistHuom = "";
	m_pLoan->getCDBLoan()->m_LA_Aika = CTime::GetCurrentTime();
	m_pLoan->getCDBLoan()->m_LA_Varasto = m_sVarasto;

	// tapahtuman huomautukset
	m_pLoan->getCDBLoan()->m_sTapHuom = m_sHuom2;
	m_pLoan->getCDBLoan()->m_sVarmennus = m_sVarmennus;

	m_pLoan->getCDBLoan()->setLoanRows(m_pLainarivit, m_rows); // asettaa CObListLoanRows-listalle lainarivien tiedot
	if (m_pLoan->getCDBLoan()->saveLoan() < 1)  // asettaa myös uuden lainanumeron DBLoan.m_LA_Nr
	{
		return; // lainaa ei talletettu eikä kannata tulostaa siis kuittiakaan
	}
	m_pLoan->getRedemptionLoanExpenses()->m_pCDBLoanRef = m_pLoan->getCDBLoan();
	m_pLoan->getRedemptionLoanExpenses()->computeExpensesAtDate(m_dateEraPv); // lasketaan eräpäivän tilanne

	m_pLoan->getCDBLoan()->m_LA_YlimSaMaksu = m_dYlimSailMaksu; // * m_pLoan->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa();
	m_pLoan->getRedemptionLoanExpenses()->computeExpensesAtDate(m_dateEraPv);

	m_pLoan->getCDBLoan()->printTicket();
}



void CDlgUusiLaina::OnBtnLaske()
{
	CString msg = "";
	CString sBuf = "";
	CString sLBText = "";
	UpdateData(); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	m_rows = m_pLainarivit->RowCount();
	m_dVakuusarvo = 0;
	m_dLainasumma = 0;
	m_dYlimSailMaksu = atof(theApp.dot(m_sYlimSailMaksu)); // teksti muutetaan doubleksi
	for (int i=1; i <= m_rows; i++)
	{
		m_dVakuusarvo = m_dVakuusarvo + atof(theApp.dot(m_pLainarivit->GetValueRowCol(i,9)));
		m_dLainasumma = m_dLainasumma + atof(theApp.dot(m_pLainarivit->GetValueRowCol(i,10)));
	}

	m_dKorkoPr = theApp.GetInterestRate(m_dLainasumma);

	// --- Lainan nimi ---
	//if (m_sLainanNimi == "")
		m_sLainanNimi = m_pLainarivit->GetValueRowCol(1,7);

	if (m_ctlLainanTuoteryhma.GetCurSel() == LB_ERR)
	{
		bool bSel = false;
		sBuf = m_pLainarivit->GetValueRowCol(1, 1);
		for (int i = 0; i < m_ctlLainanTuoteryhma.GetCount(); i++)
		{
			m_ctlLainanTuoteryhma.GetLBText(i, sLBText);
			if (sBuf.Left(1) == sLBText.Left(1))
			{
				m_ctlLainanTuoteryhma.SetCurSel(i);
				bSel = true;
				break;
			}
		}
		if (bSel == false && m_ctlLainanTuoteryhma.GetCount() >= 1)
		{
			m_ctlLainanTuoteryhma.SetCurSel(0);
		}
	}

	if (m_dLainasumma > m_dVakuusarvo)
	{
		msg.Format("Lainasumma on liian suuri vakuusarvoon nähden !\nLainasumma pienennetään.");
		if (AfxMessageBox(msg) == IDYES /*IDNO*/)
		{
		}
		m_pLainarivit->DecreaseLoan(m_dLainasumma - m_dVakuusarvo);
		m_dLainasumma = m_dVakuusarvo;

	}
	m_sVakuusarvo.Format("%7.2f", m_dVakuusarvo);
	m_sLainasumma.Format("%7.2f", m_dLainasumma);
	m_sYlimSailMaksu.Format("%7.2f", m_dYlimSailMaksu);
	


	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}



void CDlgUusiLaina::OnCancel()
{

	m_bCanceled = TRUE;
	CDialog::OnCancel();
}

bool CDlgUusiLaina::Kuitti()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	OnKuitti();
	return TRUE;
}

double CDlgUusiLaina::GetFee()
{
	//UpdateData(); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	// ei saa tehdä kun dialogi on suljettu
	//return -m_dLainasumma;
	CString sL ="";
	sL.Format("%7.2f", -m_dLainasumma);
	return atof(sL);
}

void CDlgUusiLaina::OnPeru()
{
	CDialog::OnCancel();
	//m_pQ->RemoveQItem(this);  // ei tietenkään saa kutsua näin !
	m_bCanceled = TRUE;
}




void CDlgUusiLaina::OnTeelaina() 
{
	CString msg = "";
	OnBtnLaske();
	UpdateData(); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	// ottaa talteen dislogin kontrollrreissa olevat tiedot: Esim 
	// ylim s-maksu talletetaan muuttujaan m_sYlimSailMaksu (tekstimuuttuja) ja jotenkin myös m_dYlimSailMaksu (double)

	m_ctlHenkTark.GetWindowText(m_sVarmennus);
	if (m_sVarmennus.IsEmpty())
	{
		AfxMessageBox("Henk.varmennus?");
		this->m_ctlHenkTark.SetFocus();
		return;
	}
	m_iSelectedProductGroup = m_ctlLainanTuoteryhma.GetCurSel();
	m_ctlLainanTuoteryhma.GetLBText(m_iSelectedProductGroup, m_sSelectedProductGroup);

	if (m_iSelectedProductGroup == LB_ERR)
	{
		msg.Format("Tarkasta lainan tuoteryhmä!");
		if (AfxMessageBox(msg) == IDYES /*IDNO*/)
		{
		}
		return;
	}
	if ((m_dLainasumma <= 0.1) || (m_dVakuusarvo < m_dLainasumma))
	{
		msg.Format("Tarkasta vakuusarvo/lainasumma tai peru lainan tekeminen!");
		if (AfxMessageBox(msg) == IDYES /*IDNO*/)
		{
		}
		return;
	}
	CDialog::OnCancel();
}



void CDlgUusiLaina::fromGrid()
{
	if (m_ctlHenkTark.GetCurSel() == -1)
	{
		m_ctlHenkTark.SetFocus();
		
	}
}














