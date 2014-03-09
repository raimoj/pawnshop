// DlgUudistus.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "PanttiDoc.h"
#include "DlgUudistus.h"
#include "ObListLoanRows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUudistus dialog


extern CPanttiApp theApp;



CDlgUudistus::CDlgUudistus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUudistus::IDD, pParent)
{
	ASSERT(0);
}

CDlgUudistus::CDlgUudistus(long loanNr, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUudistus::IDD, pParent)
{
	CTime t = CTime::GetCurrentTime();
	CString date = t.Format("%d.%m.%Y");

	//{{AFX_DATA_INIT(CDlgUudistus)
	m_sLainaNr = _T("");
	m_sPv = _T("");
	m_sEraPv = _T("");
	m_sUudistusPv = date;//_T("");
	m_sLainasumma = _T("");
	m_dKorkoPr = 0.0;
	m_sLiitteet = _T("");
	m_sLainanNimi = _T("");
	m_bEiMuistutusta = FALSE;
	m_sHuom = _T("");
	m_sKorkopaivia = _T("");
	m_sKorkoYhteensa = _T("");
	m_sPaivakorko = _T("");
	m_sSHVPaivakorko = _T("");
	m_sLainaAjanSHVKorkoYht = _T("");
	m_sKorkoPvLainaAjanYli = _T("");
	m_sKorkoKKLainaAjanYli = _T("");
	m_sKKKorkoLainaAjanYli = _T("");
	m_sKKKorkoYhtLainaAjanYli = _T("");
	m_sSHVMaksutYhteensa = _T("");
	m_sPyoristys = _T("");
	m_sNimiHTun = _T("");
	m_dSHVMaksuPrKK = 0.0;
	m_sKorkopaivia_laina_ajalla = _T("");
	m_sVakuusarvo = _T("");
	m_sKorkoYht2 = _T("");
	m_sLyhennyksetYht = _T("");
	m_sSailVakMaksu = _T("");
	m_sYlimSailMaksu = _T("");
	m_sKuittimaksu = _T("");
	m_sKatoamismaksu = _T("");
	m_sMuistutusmaksu1 = _T("");
	m_sMuistutusmaksu2 = _T("");
	m_sVakuusvarmennus = _T("");
	m_sPostituskulut = _T("");
	m_sAlennus = _T("");
	m_sMaksettavaYht = _T("");
	m_sKorotus = _T("");
	m_sLoppusumma_mk = _T("");
	m_sLaHuom = _T("");
	m_sSeuraavaLyhennys = _T("");
	m_sYlimSailMaksuPerKk = _T("");
	//}}AFX_DATA_INIT

	m_dMaksettava = 0.0;
	m_iUudistusKerrat = 0;

	bDlgAlreadyExists = FALSE;
	m_bCanceled	= FALSE;

	m_lLoanNr = loanNr;
	m_pLoan = new CLoan(loanNr);
	m_pLoan->getRenewalLoanExpenses()->computeExpensesAtDate(CTime::GetCurrentTime());
	m_sVarmennus = "EiTark";
}


CDlgUudistus::~CDlgUudistus()
{
	if (m_pLoan) delete m_pLoan;
}


void CDlgUudistus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUudistus)
	DDX_Control(pDX, IDC_HENK_TARK, m_ctlHenkTark);
	DDX_Control(pDX, IDC_LNR, m_ctlLainaNr);
	DDX_Control(pDX, IDC_NIMI_HTUN, m_ctlNimiHTun);
	DDX_Text(pDX, IDC_LNR, m_sLainaNr);
	DDX_Text(pDX, IDC_PVM, m_sPv);
	DDX_Text(pDX, IDC_ERAPV, m_sEraPv);
	DDX_Text(pDX, IDC_UUDISTUSPAIVA, m_sUudistusPv);
	DDX_Text(pDX, IDC_LAINASUMMA, m_sLainasumma);
	DDX_Text(pDX, IDC_KORKOPR, m_dKorkoPr);
	DDX_Text(pDX, IDC_LIITTEET, m_sLiitteet);
	DDX_Text(pDX, IDC_LAINANNIMI, m_sLainanNimi);
	DDX_Check(pDX, IDC_EIMUISTUTUSTA, m_bEiMuistutusta);
	DDX_Text(pDX, IDC_HUOM, m_sHuom);
	DDX_Text(pDX, IDC_KORKOPAIVIA, m_sKorkopaivia);
	DDX_Text(pDX, IDC_KORKO_YHT, m_sKorkoYhteensa);
	DDX_Text(pDX, IDC_PAIVAKORKO, m_sPaivakorko);
	DDX_Text(pDX, IDC_SHV_PAIVAKORKO, m_sSHVPaivakorko);
	DDX_Text(pDX, IDC_LAJAN_SHVKORKO_YHT, m_sLainaAjanSHVKorkoYht);
	DDX_Text(pDX, IDC_KORKOPAIVIA_LAINA_AJAN_YLI, m_sKorkoPvLainaAjanYli);
	DDX_Text(pDX, IDC_KORKOKK_LAINA_AJAN_YLI, m_sKorkoKKLainaAjanYli);
	DDX_Text(pDX, IDC_KKKORKO_LAINA_AJAN_YLI, m_sKKKorkoLainaAjanYli);
	DDX_Text(pDX, IDC_KKKORKO_YHT_LAINA_AJAN_YLI, m_sKKKorkoYhtLainaAjanYli);
	DDX_Text(pDX, IDC_SHVYHTEENSA, m_sSHVMaksutYhteensa);
	DDX_Text(pDX, IDC_PYORISTYS, m_sPyoristys);
	DDX_Text(pDX, IDC_NIMI_HTUN, m_sNimiHTun);
	DDX_Text(pDX, IDC_SHV_PR, m_dSHVMaksuPrKK);
	DDX_Text(pDX, IDC_KORKOPAIVIA_LAINA_AJALLA, m_sKorkopaivia_laina_ajalla);
	DDX_Text(pDX, IDC_VAKUUSARVO, m_sVakuusarvo);
	DDX_Text(pDX, IDC_KORKO_YHT_2, m_sKorkoYht2);
	DDX_Text(pDX, IDC_LAINAN_LYHENNYKSET, m_sLyhennyksetYht);
	DDX_Text(pDX, IDC_SAILVAKMAKSU, m_sSailVakMaksu);
	DDX_Text(pDX, IDC_YLIMSAILMAKSU, m_sYlimSailMaksu);
	DDX_Text(pDX, IDC_KUITTIMAKSU, m_sKuittimaksu);
	DDX_Text(pDX, IDC_KATOAMISMAKSU, m_sKatoamismaksu);
	DDX_Text(pDX, IDC_MUISTUTUSMAKSU1, m_sMuistutusmaksu1);
	DDX_Text(pDX, IDC_MUISTUTUSMAKSU2, m_sMuistutusmaksu2);
	DDX_Text(pDX, IDC_VAKUUSVARMENNUS, m_sVakuusvarmennus);
	DDX_Text(pDX, IDC_POSTITUSKULUT, m_sPostituskulut);
	DDX_Text(pDX, IDC_ALENNUS, m_sAlennus);
	DDX_Text(pDX, IDC_MAKSETTAVAYHT, m_sMaksettavaYht);
	DDX_Text(pDX, IDC_LAINAN_KOROTUS, m_sKorotus);
	DDX_Text(pDX, IDC_LOPPUSUMMA_MK, m_sLoppusumma_mk);
	DDX_Text(pDX, IDC_LAHUOM, m_sLaHuom);
	DDX_Text(pDX, IDC_SEURAAVA_LYHENNYS2, m_sSeuraavaLyhennys);
	DDX_Text(pDX, IDC_YLIMSAILMAKSUPERKK, m_sYlimSailMaksuPerKk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUudistus, CDialog)
	//{{AFX_MSG_MAP(CDlgUudistus)
	ON_BN_CLICKED(IDC_KUITTI, OnKuitti)
	ON_BN_CLICKED(IDC_LASKE, OnLaske)
	ON_BN_CLICKED(IDC_PERU, OnPeru)
	ON_EN_CHANGE(IDC_POSTITUSKULUT, OnChangePostituskulut)
	ON_EN_CHANGE(IDC_LAINAN_LYHENNYKSET, OnChangeLainanLyhennykset)
	ON_EN_CHANGE(IDC_ALENNUS, OnChangeAlennus)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_UUDISTA, OnUudista)
	ON_EN_CHANGE(IDC_LAINAN_KOROTUS, OnChangeLainanKorotus)
	ON_EN_CHANGE(IDC_YLIMSAILMAKSU, OnChangeYlimSailMaksu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUudistus message handlers

BOOL CDlgUudistus::OnInitDialog()
{
	char buf[25];
	CString msg = "";
	int iPvLkm = 0;

	CDialog::OnInitDialog();

	/*m_ctlKorkoYht2.EnableWindow(FALSE);
	m_ctlSHVMaksuYht2.EnableWindow(FALSE);
	m_ctlKuittimaksu.EnableWindow(FALSE);
	m_ctlMuistutuskirjemaksu1.EnableWindow(FALSE);
	m_ctlMuistutuskirjemaksu2.EnableWindow(FALSE);
	m_ctlVakuusvarmennusmaksu.EnableWindow(FALSE);
	m_ctlMaksettavaYht.EnableWindow(FALSE);*/
	
	
	m_ctlHenkTark.AddString("EiTark");
	m_ctlHenkTark.AddString("Ajokortti");
	m_ctlHenkTark.AddString("Passi");
	m_ctlHenkTark.AddString("Kela");
	m_ctlHenkTark.AddString("Henkilöllisyystod");
	m_ctlHenkTark.SetCurSel(1);


	//TRACE("Varm=%s\n", this->m_sVarmennus);
	this->m_ctlHenkTark.SetWindowText(m_sVarmennus);
		
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

	
	
	//
	// --- paluu, kun vanha dialogi aktivoidaan ----
	if (bDlgAlreadyExists)
	{

		return TRUE;
	}

	
	CTime ThisDay = CTime::GetCurrentTime();
	CTime paiva((ThisDay.GetYear()), (ThisDay.GetMonth()), (ThisDay.GetDay()), 0,0,0);
	ThisDay = paiva;
	CTimeSpan Erotus;
	//
	// --- käyttörajoitukset ---
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
	}
	//
	//
	sprintf(buf,"%s",m_pLoan->getCDBLoan()->m_LA_AlkupPv.Format("%d.%m.%Y"));
	m_sPv = buf;
	sprintf(buf,"%s",m_pLoan->getCDBLoan()->m_LA_EraPv.Format("%d.%m.%Y"));
	m_sEraPv = buf;

	m_sLiitteet = m_pLoan->getCDBLoan()->m_LA_Liitteet;
	m_sLainanNimi = m_pLoan->getCDBLoan()->m_LA_LainanNimi;
	m_sVakuusarvo.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_VakSumma);
	m_bEiMuistutusta = m_pLoan->getCDBLoan()->m_LA_EiMuistutusta;
	m_sSeuraavaLyhennys = "";
	m_sLaHuom = m_pLoan->getCDBLoan()->m_LA_Huom;

	//
	// --------- korkolaskelma: korko --------------
	//m_sUudistusPv			// kts. ctor
	m_sLainasumma.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_Laina);
	m_sKorkopaivia.Format("%d", m_pLoan->getRenewalLoanExpenses()->getLainaPvYht());
	//m_sYlimSailMaksuPerKk.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getExtraStoringFeePerKk());
	
	m_dKorkoPr = m_pLoan->getCDBLoan()->m_LA_Korko;
	m_sPaivakorko.Format("%7.4f", m_pLoan->getRenewalLoanExpenses()->getKorkoMkPerPv());
	m_sKorkoYhteensa.Format("%7.4f", m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT());

	//
	// --------- korkolaskelma: SHV-maksu --------------
	m_dSHVMaksuPrKK = m_pLoan->getRenewalLoanExpenses()->getSHVKorkoPrPerKk();
	m_sKorkopaivia_laina_ajalla.Format("%4d", m_pLoan->getRenewalLoanExpenses()->getLainaPvEnnenErapaivaa());
	m_sSHVPaivakorko.Format("%7.4f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkPerPv());
	m_sLainaAjanSHVKorkoYht.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkEnnenErapaivaaYht());
	//
	m_sKorkoPvLainaAjanYli.Format("%4d", m_pLoan->getRenewalLoanExpenses()->getLainaPvErapvnJalkeen());
	m_sKorkoKKLainaAjanYli.Format("%4d", m_pLoan->getRenewalLoanExpenses()->getSHVLainaKkErapvnJalkeen());
	m_sKKKorkoLainaAjanYli.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkPerKk());
	m_sKKKorkoYhtLainaAjanYli.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkErapvnJalkeenYht());
	m_sSHVMaksutYhteensa.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT());
	
	//---Ylim säilytysmaksu
	// Kaarina 15042004

	m_sYlimSailMaksuPerKk.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getExtraStoringFeePerKk());
	
	//
	// === yhteenvetosarake ====
	m_sKorkoYht2.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT());
	//
	// ---- Lainan lyhennykset ???? ------
	if (m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys > 0.01)
	{
		m_sLyhennyksetYht.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys);
	}
	else
	{
		m_sLyhennyksetYht = "";
	}
	m_sKorotus = "";

	m_sSailVakMaksu.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT());
	//m_sYlimSailMaksu.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_YlimSaMaksu);
	m_sYlimSailMaksu.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getExtraStoringFee());
	m_sKuittimaksu.Format("%7.2f", theApp.GetAs()->m_AT_Kuittimaksu);
		
	if (m_pLoan->getCDBLoan()->m_LA_KuitinKatoaminen)
	{
		m_sKatoamismaksu.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_KuitinKatoamisMaksu);
	}
	else
	{
		m_sKatoamismaksu = "0";
	}
	//
	// ---- muistutuskirjeet ----
	if ( m_pLoan->getCDBLoan()->m_LA_MuistKirje1 != NULL)
	{
		m_sMuistutusmaksu1.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_MuistKirjeMaksu1);
	}
	else
	{
		m_sMuistutusmaksu1 = "0";
	}
	if ( m_pLoan->getCDBLoan()->m_LA_MuistKirje2 != NULL)
	{
		m_sMuistutusmaksu2.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_MuistKirjeMaksu2);
	}
	else
	{
		m_sMuistutusmaksu2 = "0";
	}

	m_sVakuusvarmennus.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_VakVarmMaksu);
	if (m_pLoan->getCDBLoan()->m_LA_PostitusMaksu > 0.01)
	{
		m_sPostituskulut.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_PostitusMaksu);
	}
	else
	{
		m_sPostituskulut = "";
	}
	
	if (m_pLoan->getCDBLoan()->m_LA_Alennus > 0.01)
	{
		m_sAlennus.Format("%7.2f", m_pLoan->getCDBLoan()->m_LA_Alennus);
	}
	else
	{
		m_sAlennus = "";
	}

	
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	bDlgAlreadyExists = TRUE;
	
	this->OnLaske();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgUudistus::OnOK()
{
	//CDialog::OnOK();
}

void CDlgUudistus::OnKuitti()
{
	double dUusiKorkoPr = 0;
	double dOldLoan = 0;
	CString msg = "";
	BOOL bKorotus = FALSE;

	// ei saa tehdä kun dialogi on suljettu
	//UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	//
	//
	// -- Korotus ? ---
	TRACE("Vanha lainasumma = %fe\n", m_pLoan->getCDBLoan()->m_LA_Laina);
	TRACE("Uusi lainasumma	= %fe\n", m_pLoan->getCDBLoan()->m_LA_Laina
										- atof(theApp.dot(m_sLyhennyksetYht))
										+ atof(theApp.dot(m_sKorotus))
										);
	if (m_pLoan->getCDBLoan()->m_LA_Laina
								- atof(theApp.dot(m_sLyhennyksetYht))
								+ atof(theApp.dot(m_sKorotus)) 
								> m_pLoan->getCDBLoan()->m_LA_Laina)
	{
		bKorotus = TRUE;
		msg.Format("   Korotus !  ");
		//AfxMessageBox(msg);
	}
	else
	{
		bKorotus = FALSE;
	}


	TRACE("Lyh=%s/Kor=%s\n", theApp.dot(m_sLyhennyksetYht), theApp.dot(m_sKorotus));
	m_pLoan->getRenewalLoan()->buyOut(
										bKorotus,  // korotus / uudistus 
										/*atof(m_sKorkoYht2)*/m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT(),	// lainatap. + loki
										m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT(), // lainatap. + loki
										0,					// lunastuksetYht,
										atof(theApp.dot(m_sLyhennyksetYht)), // lyhennyksetYht
										atof(theApp.dot(m_sKorotus)), // korotus
										atof(m_sYlimSailMaksuPerKk),// 
										atof(m_sKuittimaksu),// ei tarvita, poista parametri
										atof(m_sKatoamismaksu), // ei tarvita, poista parametri
										atof(m_sMuistutusmaksu1) + atof(m_sMuistutusmaksu2),// ei tarvita, poista parametri
										atof(m_sVakuusvarmennus), // ei tarvita, poista parametri
										atof(theApp.dot(m_sPostituskulut)), 
										atof(theApp.dot(m_sAlennus)),	
										this->m_dPyoristys,	
										atof(m_sMaksettavaYht),
										m_sLiitteet,
										m_sLainanNimi,
										m_bEiMuistutusta,
										m_sHuom, this->m_sVarmennus);

	//CDialog::OnOK(); // sulkee dialogin // ei saa tehdä jos dialogi on suljettu kuten kuitin tulostusessa
}


void CDlgUudistus::OnLaske()
{
	CString msg = "";
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys = atof(theApp.dot(m_sSeuraavaLyhennys));
	if (  m_pLoan->getCDBLoan()->m_LA_Laina
			+ atof(theApp.dot(m_sKorotus))
			- atof(theApp.dot(m_sLyhennyksetYht))
			- atof(m_sVakuusarvo) > 0.01)
	{
		msg = "Lainaa ei saa korottaa yli vakuusarvon!";
		//MessageBeep(1);
		//AfxMessageBox(msg);		
	}
	/*if (  m_pLoan->getCDBLoan()->m_LA_Laina
			+ atof(theApp.dot(m_sKorotus))
			- atof(theApp.dot(m_sLyhennyksetYht)) < 0.01)
	{
		//msg = "Lainan lyhennys on liian suuri! Tarkoitatko lainan lunastusta ?\nPeru lainan uudistus ja jatka työtä lunastus-ikkunassa :-)";
		//MessageBeep(1);
		//AfxMessageBox(msg);		
	}*/

	TRACE("--\n");
	TRACE("Kuitin katoaminen    : %s\n", m_sKatoamismaksu);
	TRACE("Laina                : %7.2f\n", m_pLoan->getCDBLoan()->m_LA_Laina);
	//TRACE("SäilytysVakMaksuPr   : %7.2f\n", m_dSHVMaksuPr);
	TRACE("Lyh=%s/Kor=%s\n", theApp.dot(m_sLyhennyksetYht), theApp.dot(m_sKorotus));
	TRACE("Kuittimaksu          : %s\n", m_sKuittimaksu);
	TRACE("Ylim säilytysmaksu   : %s\n", m_sYlimSailMaksu);
	TRACE("Ylim säilytysmaksuPeKk   : %s\n", m_sYlimSailMaksuPerKk);
	TRACE("Korko                : %s\n", m_sKorkoYht2);
	TRACE("Muistutuskirjemaksu1 : %s\n", m_sMuistutusmaksu1);
	TRACE("Muistutuskirjemaksu2 : %s\n", m_sMuistutusmaksu2);
	TRACE("Vakuusvarmennus      : %s\n", m_sVakuusvarmennus);
	TRACE("Postituskulut        : %s\n", theApp.dot(m_sPostituskulut));
	TRACE("Muut kulut           : %s\n", theApp.dot(m_sAlennus));
	TRACE("--\n");
	
	if (m_pLoan->getCDBLoan()->m_LA_KuitinKatoaminen)
	{
		m_dMaksettava = m_pLoan->getCDBLoan()->m_LA_KuitinKatoamisMaksu;
	}

	m_dMaksettava =  /*atof(m_sKorkoYht2)*/ m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT()	
						+ atof(theApp.dot(m_sLyhennyksetYht))
						- atof(theApp.dot(m_sKorotus))
						+ atof(m_sSailVakMaksu)
						+ atof(m_sYlimSailMaksu)
						+ atof(m_sKuittimaksu)
						+ atof(m_sMuistutusmaksu1)
						+ atof(m_sMuistutusmaksu2)
						+ atof(m_sVakuusvarmennus)
						+ atof(theApp.dot(m_sPostituskulut))
						- atof(theApp.dot(m_sAlennus));
	TRACE("Yhteensä             : %7.2f\n", m_dMaksettava);
	TRACE("--\n");

	m_dPyoristys = theApp.makeRounding(m_dMaksettava) - m_dMaksettava;
	TRACE("Pyoristys=%7.2f\n", m_dPyoristys);
	m_sPyoristys.Format("Pyöristys =%7.2f", m_dPyoristys);
	
	m_sMaksettavaYht.Format("%7.2f", theApp.makeRounding(m_dMaksettava + m_dPyoristys));
	m_sLoppusumma_mk.Format("%7.2f", theApp.makeRounding(theApp.euroToMk(m_dMaksettava + m_dPyoristys)));
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

}

CString CDlgUudistus::GetDlgString()
{
	CString s = "";
	s.Format("Uud. %s E [%ld]", m_sMaksettavaYht, this->m_lLoanNr); // lunastus
	return s; // uudistus
}

double CDlgUudistus::GetFee()   // tulostusjono tarvii tätä
{
	return atof(m_sMaksettavaYht);
	//return m_dMaksettava;
}

void CDlgUudistus::OnCancel()
{
	m_bCanceled = TRUE;
	CDialog::OnCancel();
}

bool CDlgUudistus::Kuitti()
{
	OnKuitti();
	return TRUE;
}


void CDlgUudistus::OnPeru()
{
	m_bCanceled	= TRUE;
	CDialog::OnCancel();
}


void CDlgUudistus::OnChangePostituskulut() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	OnLaske();
}

void CDlgUudistus::OnChangeLainanLyhennykset() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	OnLaske();
}

void CDlgUudistus::OnChangeAlennus() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	OnLaske();
}

void CDlgUudistus::OnOk() 
{
	//CDialog::OnOK(); // poistettu ja lisätty OnKuitti() -> return ei sulje dialogia
	
}

void CDlgUudistus::OnUudista() 
{
	CString msg = "";
	OnLaske();
	UpdateData(); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	
	if (  m_pLoan->getCDBLoan()->m_LA_Laina
			+ atof(theApp.dot(m_sKorotus))
			- atof(theApp.dot(m_sLyhennyksetYht)) < 0.01)
	{
		msg.Format("Lyhennys on liian suuri.\n\nLunastus ?");
		if (AfxMessageBox(msg, MB_YESNO) == IDNO)
		{
			return;
		}
		else
		{
			m_sLyhennyksetYht = "";
			m_sKorotus = "";
			UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
		}
	}
	if ( (atof(theApp.dot(m_sKorotus)) > 0.01 || atof(theApp.dot(m_sKorotus)) < -0.01) ||
		 (atof(theApp.dot(m_sLyhennyksetYht)) > 0.01 || atof(theApp.dot(m_sLyhennyksetYht)) < -0.01)
		) 
	{
		//msg = "Lyhennykset/Korotukset on huomioitava lainarivien lainasummissa!\nOhjelma laskee lainariveille uudet lainasummat!";
		//AfxMessageBox(msg);
		m_pLoan->getLoanRowList()->divideLoanSumsAtRows( 
			// vapaaehtoinen lyhennys
			m_pLoan->getCDBLoan()->m_LA_Laina	// vanhalainasumma - uusilainasumma
					- (m_pLoan->getCDBLoan()->m_LA_Laina 
						+ atof(theApp.dot(m_sKorotus)) 
						- atof(theApp.dot(m_sLyhennyksetYht))), 
			0,
			0);
	}

	if (m_pLoan->getCDBLoan()->m_LA_Laina 
						+ atof(theApp.dot(m_sKorotus)) 
						- atof(theApp.dot(m_sLyhennyksetYht)) > m_pLoan->getCDBLoan()->m_LA_VakSumma)
	{
		msg.Format("Uusi laina ylittää vakuusarvon!");
		if (AfxMessageBox(msg, MB_YESNO) == IDNO)
		{
			return;
		}
	}

	m_ctlHenkTark.GetWindowText(m_sVarmennus);
	if (m_sVarmennus.IsEmpty())
	{
		AfxMessageBox("Henk.varmennus?");
		this->m_ctlHenkTark.SetFocus();
		return;
	}

	CDialog::OnCancel();
}

void CDlgUudistus::OnChangeLainanKorotus() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	OnLaske();
}


void CDlgUudistus::OnChangeYlimSailMaksu() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	OnLaske();
}
