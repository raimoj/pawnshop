// DlgLunastus.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "PanttiDoc.h"
#include "DlgLunastus.h"

//#include "LainariviRS.h" // lisätty jo PanttiDoc.h:ssa
//#include "TapahtumaRS.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLunastus dialog


extern CPanttiApp theApp;



CDlgLunastus::CDlgLunastus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLunastus::IDD, pParent)
{
	ASSERT(0);
}


CDlgLunastus::CDlgLunastus(long loanNr, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLunastus::IDD, pParent)
{
	CTime t = CTime::GetCurrentTime();
	CString date = t.Format("%d.%m.%Y");
	//{{AFX_DATA_INIT(CDlgLunastus)
	m_sPv = _T("");
	m_sEraPv = _T("");
	m_sLiitteet = _T("");
	m_sLainanNimi = _T("");
	m_bEiMuistutusta = FALSE;
	m_sLainaNr = _T("");
	m_sKorkopaivia = _T("");
	m_sLunastuspv = date;//_T("");
	m_sLainasumma = _T("");
	m_sKorkokuukausia = _T("");
	m_sKuukausikorko = _T("");
	m_sKuukausikorkoYht = _T("");
	m_sYlitysaikaPv = _T("");
	m_sPaivakorko = _T("");
	m_sViivastyskorkoYht = _T("");
	m_sKorkoYhteensa = _T("");
	m_sLainasumma2 = _T("");
	m_sHuom = _T("");
	m_sPyoristys = _T("");
	m_sNimiHTun = _T("");
	m_sKorkoPrKK = _T("");
	m_sSHVMaksuPr = _T("");
	m_sSHVKorkokuukausia = _T("");
	m_sSHV_Mk_KK = _T("");
	m_sSHVMaksuYht = _T("");
	m_dMaksettavaYhtMk = 0.0;
	m_sKorkoYht2 = _T("");
	m_sSHVMaksuYht2 = _T("");
	m_sVakuusarvo = _T("");
	m_sKuittimaksu = _T("");
	m_sKuitinKatoaminen = _T("");
	m_sMuistutuskirjemaksu2 = _T("");
	m_sMuistutuskirjemaksu1 = _T("");
	m_sAlennus = _T("");
	m_sVakuusvarmennus = _T("");
	m_sPostituskulut = _T("");
	m_sMaksettavaYht = _T("");
	m_sYlimSailMaksu = _T("");
	m_sLoppusummaMk = _T("");
	m_sLaHuom = _T("");
	m_sPyoristys = "";
	m_sYlimSailMaksuPerKk = _T("");
	//}}AFX_DATA_INIT

	bDlgAlreadyExists = FALSE;
	pDoc = theApp.m_pDoc;
	m_bCanceled = FALSE;

	m_lLoanNr = loanNr;
	m_pLoan = new CLoan(loanNr);
	m_pLoan->getRedemptionLoanExpenses()->computeExpensesAtDate(CTime::GetCurrentTime());

	m_dMaksettava = 0;
	m_dKorkoYht2 = 0;
	m_dSHVMaksuYht2 = 0;
	m_dKuittimaksu = 0;
	m_dKuitinKatoaminen = 0;
	m_dMuistutuskirjemaksu1 = 0;
	m_dMuistutuskirjemaksu2 = 0;
	m_dVakuusvarmennus = 0;
	m_dPostituskulut = 0;
	m_dAlennus = 0;
	//m_dPyoristysMk = 0;
	
	m_brBack.CreateSolidBrush(RGB(255, 255, 0)); //kirkkaan keltainen
	//m_brBack.CreateSolidBrush(RGB(128, 128, 64)); // ruskeanvihreä :)
	m_brBack2.CreateSolidBrush(RGB(128, 255, 255)); // vaaleansininen
	m_brBack3.CreateSolidBrush(RGB(255, 255, 255)); // valk

	m_sVarmennus = "";
}


void CDlgLunastus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLunastus)
	DDX_Control(pDX, IDC_HENK_TARK, m_ctlHenkTark);
	DDX_Control(pDX, IDC_VAKUUSVARMENNUSMAKSU, m_ctlVakuusvarmennusmaksu);
	DDX_Control(pDX, IDC_LNR, m_ctlLainaNr);
	DDX_Control(pDX, IDC_NIMI_HTUN, m_ctlNimiHTun);
	DDX_Text(pDX, IDC_PVM, m_sPv);
	DDX_Text(pDX, IDC_ERAPV, m_sEraPv);
	DDX_Text(pDX, IDC_LIITTEET, m_sLiitteet);
	DDX_Text(pDX, IDC_LAINANNIMI, m_sLainanNimi);
	DDX_Check(pDX, IDC_EIMUISTUTUSTA, m_bEiMuistutusta);
	DDX_Text(pDX, IDC_LNR, m_sLainaNr);
	DDX_Text(pDX, IDC_KORKOPAIVIA, m_sKorkopaivia);
	DDX_Text(pDX, IDC_LUNASTUSPAIVA, m_sLunastuspv);
	DDX_Text(pDX, IDC_LAINASUMMA, m_sLainasumma);
	DDX_Text(pDX, IDC_KORKOKUUKAUSIA, m_sKorkokuukausia);
	DDX_Text(pDX, IDC_KUUKAUSIKORKO, m_sKuukausikorko);
	DDX_Text(pDX, IDC_KUUKAUSIKORKO_YHT, m_sKuukausikorkoYht);
	DDX_Text(pDX, IDC_YLITYSAIKA_PV, m_sYlitysaikaPv);
	DDX_Text(pDX, IDC_PAIVAKORKO, m_sPaivakorko);
	DDX_Text(pDX, IDC_VIIVASTYSKORKO_YHT, m_sViivastyskorkoYht);
	DDX_Text(pDX, IDC_KORKO_YHT, m_sKorkoYhteensa);
	DDX_Text(pDX, IDC_LAINASUMMA2, m_sLainasumma2);
	DDX_Text(pDX, IDC_HUOM, m_sHuom);
	DDX_Text(pDX, IDC_PYORISTYS, m_sPyoristys);
	DDX_Text(pDX, IDC_NIMI_HTUN, m_sNimiHTun);
	DDX_Text(pDX, IDC_KORKOPRKK, m_sKorkoPrKK);
	DDX_Text(pDX, IDC_SHV_PR, m_sSHVMaksuPr);
	DDX_Text(pDX, IDC_KORKO_KK, m_sSHVKorkokuukausia);
	DDX_Text(pDX, IDC_SHV_MK_KK, m_sSHV_Mk_KK);
	DDX_Text(pDX, IDC_SHV_MAKSU_YHT1, m_sSHVMaksuYht);
	DDX_Text(pDX, IDC_KORKO_YHT2, m_sKorkoYht2);
	DDX_Text(pDX, IDC_SHV_YHT2, m_sSHVMaksuYht2);
	DDX_Text(pDX, IDC_VAKUUSARVO, m_sVakuusarvo);
	DDX_Text(pDX, IDC_KUITTIMAKSU, m_sKuittimaksu);
	DDX_Text(pDX, IDC_KATOAMISMAKSU, m_sKuitinKatoaminen);
	DDX_Text(pDX, IDC_MUISTUTUSKIRJEMAKSU2, m_sMuistutuskirjemaksu2);
	DDX_Text(pDX, IDC_MUISTUTUSKIRJEMAKSU1, m_sMuistutuskirjemaksu1);
	DDX_Text(pDX, IDC_ALENNUS, m_sAlennus);
	DDX_Text(pDX, IDC_VAKUUSVARMENNUSMAKSU, m_sVakuusvarmennus);
	DDX_Text(pDX, IDC_POSTITUSKULUT, m_sPostituskulut);
	DDX_Text(pDX, IDC_MAKSETTAVAYHT, m_sMaksettavaYht);
	DDX_Text(pDX, IDC_YLIMSAILMAKSU, m_sYlimSailMaksu);
	DDX_Text(pDX, IDC_LOPPUSUMMA_MK, m_sLoppusummaMk);
	DDX_Text(pDX, IDC_LAHUOM, m_sLaHuom);
	DDX_Text(pDX, IDC_YLIMSAILMAKSUPERKUUKAUSI, m_sYlimSailMaksuPerKk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLunastus, CDialog)
	//{{AFX_MSG_MAP(CDlgLunastus)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_KUITTI, OnKuitti)
	ON_BN_CLICKED(IDC_LASKE, OnLaske)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PERU, OnPeru)
	ON_EN_CHANGE(IDC_YLIMSAILMAKSU, OnChangeYlimsailmaksu)
	ON_EN_CHANGE(IDC_VAKUUSVARMENNUSMAKSU, OnChangeVakuusvarmennusmaksu)
	ON_EN_CHANGE(IDC_POSTITUSKULUT, OnChangePostituskulut)
	ON_EN_CHANGE(IDC_ALENNUS, OnChangeAlennus)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_LUNASTA, OnLunasta)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_EN_CHANGE(IDC_YLIMSAILMAKSU, OnChangeYlimSailMaksu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLunastus message handlers

BOOL CDlgLunastus::OnInitDialog()
{
	char buf[25];
	CString msg = "";
	m_dMaksettava = 0;

	CDialog::OnInitDialog();

	//m_ctlKorkoYht2.EnableWindow(FALSE);
	//m_ctlSHVMaksuYht2.EnableWindow(FALSE);
	//m_ctlKuittimaksu.EnableWindow(FALSE);
	//m_ctlMuistutuskirjemaksu1.EnableWindow(FALSE);
	//m_ctlMuistutuskirjemaksu2.EnableWindow(FALSE);
	//m_ctlVakuusvarmennusmaksu.EnableWindow(FALSE);
	//m_ctlMaksettavaYht.EnableWindow(FALSE);

	CFont f1;
	CFont f2;
	f1.CreateFont(-300 /*-260*/, 0, 0, 0, FW_BOLD, FALSE, FALSE,
	                0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                DEFAULT_PITCH | FF_ROMAN,
	                "Courier New"); // TrueType
	f2.CreateFont(-500, 0, 0, 0, FW_HEAVY, FALSE, FALSE,
	                0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                DEFAULT_PITCH | FF_ROMAN,
	                "Courier New"); // TrueType

	/*f.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE,
	                0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                DEFAULT_PITCH | FF_SWISS,
	                "Arial");*/ // TrueType


	m_ctlNimiHTun.SetFont(&f1);
	m_ctlLainaNr.SetFont(&f2);
	m_ctlHenkTark.AddString("Ajokortti");
	m_ctlHenkTark.AddString("Passi");
	m_ctlHenkTark.AddString("Kela");
	m_ctlHenkTark.AddString("Henkilöllisyystod");
	m_ctlHenkTark.SetCurSel(-1);

	//TRACE("Varm=%s\n", this->m_sVarmennus);
	this->m_ctlHenkTark.SetWindowText(m_sVarmennus);

	//
	// --- paluu, kun vanha dialogi aktivoidaan ----
	if (bDlgAlreadyExists)
	{
		return TRUE;
	}

	//CWnd* pWnd = GetDlgItem(IDC_LNR);
	//CDC* pdc = pWnd->GetDC();
	//pdc->SetTextColor(RGB(255,0,0));
	//pdc->TextOut(0,0, "Tekstiä");


	//CTime ThisDay = CTime::GetCurrentTime();
	//CTime paiva((ThisDay.GetYear()), (ThisDay.GetMonth()), (ThisDay.GetDay()), 0,0,0);
	//ThisDay = paiva;
	//CTimeSpan Erotus;

	if (!m_pLoan->getCDBLoan()->m_LA_Kielto.IsEmpty())
	{
		msg = "Lainalla on kielto: " + m_pLoan->getCDBLoan()->m_LA_Kielto;
		MessageBeep(1);
		AfxMessageBox(msg);
	}

	if (m_pLoan->getCDBLoan()->m_LA_KuitinKatoaminen)
	{
		msg = "Kuitti merkitty kadonneeksi !";
		MessageBeep(1);
		AfxMessageBox(msg);
		//m_ctlKuitinKatoaminen.EnableWindow(TRUE);
	}
	//else
		//m_ctlKuitinKatoaminen.EnableWindow(FALSE);


	sprintf(buf,"%s",m_pLoan->getCDBLoan()->m_LA_AlkupPv.Format("%d.%m.%Y"));
	m_sPv = buf;
	sprintf(buf,"%s",m_pLoan->getCDBLoan()->m_LA_EraPv.Format("%d.%m.%Y"));
	m_sEraPv = buf;

	m_sLiitteet = m_pLoan->getCDBLoan()->m_LA_Liitteet;
	m_sLainanNimi = m_pLoan->getCDBLoan()->m_LA_LainanNimi;
	m_bEiMuistutusta = m_pLoan->getCDBLoan()->m_LA_EiMuistutusta;
	m_sHuom = "";
	m_sLaHuom = m_pLoan->getCDBLoan()->m_LA_Huom;

	m_sVakuusarvo.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_VakSumma);
	


	//
	// --------- korkolaskelma: korko --------------
	//m_sLunastuspv			// kts. ctor
	m_sLainasumma.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_Laina);
	m_sKorkopaivia.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getLainaPvYht());
	m_sKorkokuukausia.Format("%d",m_pLoan->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa());
	//m_pLoan->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa()
	m_sYlimSailMaksuPerKk.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getExtraStoringFeePerKk());

	m_sKorkoPrKK.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_Korko);
	m_sKuukausikorko.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkPerKk());
	m_sKuukausikorkoYht.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkEnnenErapaivaaYht());

	m_sYlitysaikaPv.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getLainaPvErapvnJalkeen());
	m_sPaivakorko.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkPerPv());
	m_sViivastyskorkoYht.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkErapvnJalkeenYht());
	//YHT
	m_sKorkoYhteensa.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT());
	//
	// --------- korkolaskelma: SHV-maksu --------------
	m_sSHVMaksuPr.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_SaVakMaksuPr);
	m_sSHVKorkokuukausia.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa()
									+ m_pLoan->getRedemptionLoanExpenses()->getSHVLainaKkErapvnJalkeen() );
	TRACE("getLainaKkEnnenErapaivaa: %d\n", m_pLoan->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa());
	TRACE("getSHVLainaKkErapvnJalkeen: %d\n", m_pLoan->getRedemptionLoanExpenses()->getSHVLainaKkErapvnJalkeen());


		// shv (ei raj eräp. jälk 4 kk niinkuin korkolaskennassa)
	
	m_sSHV_Mk_KK.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkPerKk());
	m_sSHVMaksuYht.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT());



	//
	// --------- yhteenveto maksuista -------
	m_sLainasumma2.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_Laina);
	m_dKorkoYht2 = m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT();  // euroina
	m_sKorkoYht2.Format("%7.2f", m_dKorkoYht2);
	m_dSHVMaksuYht2 = m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT(); // euroina
	m_sSHVMaksuYht2.Format("%7.2f", m_dSHVMaksuYht2);
	m_sYlimSailMaksu.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getExtraStoringFee());
	m_dKuittimaksu = theApp.GetAs()->m_AT_Kuittimaksu; // euroina
	m_sKuittimaksu.Format("%7.2f", m_dKuittimaksu);
	//
	if (m_pLoan->getCDBLoan()->m_LA_KuitinKatoaminen)
	{
		m_dKuitinKatoaminen = m_pLoan->getCDBLoan()->m_LA_KuitinKatoamisMaksu; // euroina
		m_dMaksettava = m_pLoan->getCDBLoan()->m_LA_KuitinKatoamisMaksu;
	}
	else
	{
		m_dKuitinKatoaminen = 0.0;
	}
	m_sKuitinKatoaminen.Format("%7.2f", m_dKuitinKatoaminen);
	//
	// ---- muistutuskirjeet ----
	if ( m_pLoan->getCDBLoan()->m_LA_MuistKirje1 != NULL)
	{
		m_dMuistutuskirjemaksu1 = m_pLoan->getCDBLoan()->m_LA_MuistKirjeMaksu1; // euroina
	}
	else
	{
		m_dMuistutuskirjemaksu1 = 0.0;
	}
	m_sMuistutuskirjemaksu1.Format("%7.2f", m_dMuistutuskirjemaksu1);
	//	
	if ( m_pLoan->getCDBLoan()->m_LA_MuistKirje2 != NULL)
	{
		m_dMuistutuskirjemaksu2 = m_pLoan->getCDBLoan()->m_LA_MuistKirjeMaksu2; // euroina
	}
	else
	{
		m_dMuistutuskirjemaksu2 = 0.0;
	}
	m_sMuistutuskirjemaksu2.Format("%7.2f", m_dMuistutuskirjemaksu2);
	//
	//
	if (m_pLoan->getCDBLoan()->m_LA_VakVarmMaksu != NULL)
	{
		m_dVakuusvarmennus = m_pLoan->getCDBLoan()->m_LA_VakVarmMaksu; // euroina
		if (m_dVakuusvarmennus > 0.01)
		{
			m_sVakuusvarmennus.Format("%7.2f", m_dVakuusvarmennus); 
		}
		else
		{
			m_sVakuusvarmennus = "";
		}
	}
	else
	{
		m_dVakuusvarmennus = 0;
		m_sVakuusvarmennus = "";
	}
	//
	//
	if (m_pLoan->getCDBLoan()->m_LA_PostitusMaksu != NULL)
	{
		m_dPostituskulut = m_pLoan->getCDBLoan()->m_LA_PostitusMaksu; // euroina
		if (m_dPostituskulut > 0.01)
		{
			m_sPostituskulut.Format("%7.2f", m_dPostituskulut); 
		}
		else
		{
			m_sPostituskulut = "";
		}
	}
	else
	{
		m_dPostituskulut =  0;
		m_sPostituskulut = "";
	}

	if (m_pLoan->getCDBLoan()->m_LA_Alennus != NULL)
	{
		m_dAlennus = m_pLoan->getCDBLoan()->m_LA_Alennus; // euroina
		if (m_dAlennus > 0.01)
		{
			m_sAlennus.Format("%7.2f", m_dAlennus);
		}
		else
		{
			m_sAlennus = "";
		}
	}
	else
	{
		m_dAlennus = 0;
		m_sAlennus = "";
	}
	//
	// ------  SHV-maksut ----
	//m_sSHVKorkokuukausia.Format("%d", theApp.GetLoanMonths(m_pLoan->getRedemptionLoanExpenses()->getLainaPvYht(), FALSE));
	m_sSHVKorkokuukausia.Format("%d", m_pLoan->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa()
									+ m_pLoan->getRedemptionLoanExpenses()->getSHVLainaKkErapvnJalkeen() ); // shv, ei raj 4 kk kuten korkolaskennassa
	m_sSHV_Mk_KK.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkPerKk());

	TRACE("--\n");
	//TRACE("Kuitin katoaminen    : %7.2f\n", m_dKuitinKatoaminen);
	TRACE("Laina                : %7.2f\n", m_pLoan->getCDBLoan()->m_LA_Laina);
	TRACE("SäilytysVakMaksuPr   : %7.2f\n", m_pLoan->getCDBLoan()->m_LA_SaVakMaksuPr);
	//TRACE("Kuittimaksu          : %7.2f\n", m_dKuittimaksu);
	//TRACE("Ylim säilytysmaksu   : %7.2f\n", m_dYlimSailMaksu);
	TRACE("Korko                : %7.2f\n", m_dKorkoYht);
	//TRACE("Muistutuskirjemaksu1 : %7.2f\n", m_dMuistutuskirjemaksu1);
	//TRACE("Muistutuskirjemaksu2 : %7.2f\n", m_dMuistutuskirjemaksu2);
	TRACE("Vakuusvarmennus      : %7.2f\n", m_dVakuusvarmennus);
	TRACE("Postituskulut        : %7.2f\n", m_dPostituskulut);
	TRACE("Alennus              : %s\n", theApp.dot(m_sAlennus));
	TRACE("--\n");
	
	/// 
	m_dMaksettava = 0;
	
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	bDlgAlreadyExists = TRUE;

	this->OnLaske();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLunastus::OnDestroy()
{
	CDialog::OnDestroy();
}

CDlgLunastus::~CDlgLunastus()
{
	if (m_pLoan) delete m_pLoan;
}

void CDlgLunastus::OnOK()
{
	TRACE("OnOK\n");
	//CDialog::OnOK(); // poistettu ja lisätty OnLunasta() -> return ei sulje dialogia
	//CDialog::OnOK();
}



void CDlgLunastus::OnKuitti()
{
	//CString msg="";

	//char buf[25];
	//int iPvLkm = 0;
	//CDialog::OnInitDialog(); // ei saa tehdä kun dialogi on suljettu
	// ei saa tehdä kun dialogi on suljettu
	//UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	//CTime ThisDay = CTime::GetCurrentTime();
	//CTime paiva((ThisDay.GetYear()), (ThisDay.GetMonth()), (ThisDay.GetDay()), 0,0,0);
	//ThisDay = paiva;
	//CTimeSpan Erotus;
	
	// -- summat toimitetaan eteenpäin markkasummina ---
	m_pLoan->getRedemptionLoan()->buyOut(
						/*atof(m_sKorkoYht2)*/m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT(),  //tarvitaan lainatap + lokia varten
						/*atof(m_sSHVMaksuYht2)*/m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT(),	// tarvitaan lainatap + lokia varten
						atof(theApp.dot(m_sYlimSailMaksuPerKk)),
						atof(m_sKuittimaksu),
						m_dKuitinKatoaminen, // toimitetaan euroina = taas turha, poista parametri
						m_dMuistutuskirjemaksu1 + m_dMuistutuskirjemaksu2, // toimitetaan euroina
						atof(theApp.dot(m_sVakuusvarmennus)),
						atof(theApp.dot(m_sPostituskulut)),
						atof(theApp.dot(m_sAlennus)),	
						m_dPyoristysMk,
						atof(m_sMaksettavaYht),
						m_sHuom, this->m_sVarmennus);

	//CDialog::OnOK(); // sulkee dialogin // ei saa yrittää kun dialogi on jo suljettu
}



void CDlgLunastus::OnLaske()
{
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	TRACE("--\n");
	TRACE("Laina                : %7.2f\n", atof(m_sLainasumma2));
	TRACE("KorkoYht             : %7.2f\n", m_dKorkoYht2);
	TRACE(" ( SäilytysVakMaksuPr   : %7.2f )\n", m_pLoan->getCDBLoan()->m_LA_SaVakMaksuPr);
	TRACE("Ylim säilytysmaksu   : %s\n", m_sYlimSailMaksu);
	TRACE("Kuittimaksu          : %7.2f\n", m_dKuittimaksu);
	TRACE("Kuittikatoaminen     : %7.2f\n", m_dKuitinKatoaminen);
	TRACE("Muistutuskirjemaksu1 : %7.2f\n", m_dMuistutuskirjemaksu1);
	TRACE("Muistutuskirjemaksu2 : %7.2f\n", m_dMuistutuskirjemaksu2);
	TRACE("Vakuusvarmennus      : %7.2f\n", m_dVakuusvarmennus);
	TRACE("Postituskulut        : %7.2f\n", m_dPostituskulut);
	TRACE("Muut kulut           : %7.2f\n", atof(theApp.dot(m_sAlennus)));
	TRACE("--\n");

	m_dMaksettava = atof(m_sLainasumma) + 
					/*atof(m_sKorkoYht2)*/m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT() + 
					/*atof(m_sSHVMaksuYht2)*/m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT() +
					atof(theApp.dot(m_sYlimSailMaksu)) +
					atof(m_sKuittimaksu) + 
					atof(m_sKuitinKatoaminen) +
					atof(m_sMuistutuskirjemaksu1) +
					atof(m_sMuistutuskirjemaksu2) +
					atof(theApp.dot(m_sVakuusvarmennus)) +
					atof(theApp.dot(m_sPostituskulut)) -
					atof(theApp.dot(m_sAlennus));

	TRACE("Yhteensä             : %7.2f\n", m_dMaksettava);
	TRACE("--\n");

	m_dPyoristysMk = theApp.makeRounding(m_dMaksettava) - m_dMaksettava; 
	m_sPyoristys.Format("Pyöristys =%7.2f", m_dPyoristysMk);	

	m_sMaksettavaYht.Format("%7.2f", theApp.makeRounding(m_dMaksettava + m_dPyoristysMk));
	m_sLoppusummaMk.Format("%7.2f", theApp.makeRounding(theApp.euroToMk(m_dMaksettava + m_dPyoristysMk)));
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}





HBRUSH CDlgLunastus::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
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
			//return static_cast<HBRUSH>(m_brBack2.GetSafeHandle());
			return /*CFormView*/CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	return /*CFormView*/CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

CString CDlgLunastus::GetDlgString()
{
	CString s = "";
	s.Format("Lun. %s E  [%ld]", m_sMaksettavaYht, this->m_lLoanNr); // lunastus
	return s; // lunastus
}


double CDlgLunastus::GetFee()
{
	return atof(m_sMaksettavaYht);
}

void CDlgLunastus::OnCancel()
{
	CDialog::OnCancel();
	m_bCanceled = TRUE;
}

bool CDlgLunastus::Kuitti()
{
	OnKuitti();
	return TRUE;
}

void CDlgLunastus::OnPeru()
{
	m_bCanceled	= TRUE;
	CDialog::OnCancel();
}


void CDlgLunastus::OnChangeYlimsailmaksu() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	OnLaske();
}

void CDlgLunastus::OnChangeVakuusvarmennusmaksu() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	OnLaske();
}

void CDlgLunastus::OnChangePostituskulut() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	OnLaske();
}

void CDlgLunastus::OnChangeAlennus() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	TRACE("Muut kulut           : %7.2f\n", atof(theApp.dot(m_sAlennus)));
	OnLaske();
}

void CDlgLunastus::OnOk() 
{
	TRACE("OnOK\n");
	//CDialog::OnOK(); // poistettu ja lisätty OnKuitti() -> return ei sulje dialogia
}

void CDlgLunastus::OnLunasta() 
{
	OnLaske();

	UpdateData(); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	
	m_ctlHenkTark.GetWindowText(m_sVarmennus);
	if (m_sVarmennus.IsEmpty())
	{
		AfxMessageBox("Henk.varmennus?");
		this->m_ctlHenkTark.SetFocus();
		return;
	}
	CDialog::OnCancel();
}

void CDlgLunastus::OnChangeYlimSailMaksu() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnLaske();
}
