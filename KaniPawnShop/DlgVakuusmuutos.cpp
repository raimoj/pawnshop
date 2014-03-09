// DlgVakuusmuutos.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "PanttiDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CDlgVakuusmuutos dialog


CDlgVakuusmuutos::CDlgVakuusmuutos(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVakuusmuutos::IDD, pParent)
{
	ASSERT(0);
}


CDlgVakuusmuutos::CDlgVakuusmuutos(long loanNr, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVakuusmuutos::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVakuusmuutos)
	m_sEraPv = _T("");
	m_sLiitteet = _T("");
	m_sLainanNimi = _T("");
	m_bEiMuistutusta = FALSE;
	m_sHuom = _T("");
	m_sMaksettavaYht = _T("");
	m_sVarmennus = _T("");
	m_sLainanKielto = _T("");
	m_bKuitinKatoaminen = FALSE;
	m_sMuistutuskirjePvm1 = _T("");
	m_sMuistutuskirjePvm2 = _T("");
	m_sKorkopaivia_laina_ajalla = _T("");
	m_sKorkoPvLainaAjanYli = _T("");
	m_sVapaaehtoinenLyhennys = _T("");
	m_sYlimSailMaksu = _T("");
	m_sKatoamismaksu = _T("");
	m_sMuistutusmaksu1 = _T("");
	m_sMuistutusmaksu2 = _T("");
	m_sPostitus = _T("");
	m_sKorkoPr = _T("");
	m_sMuistHuom = _T("");
	m_sSailVakMaksuPr = _T("");
	m_sLnro_Pv_Epv = _T("");
	m_sPyoristys = _T("");
	m_sOdotusPvm = _T("");
	m_sVarasto = _T("");
	m_bKielto = FALSE;
	m_sToimenpidekieltoPv = _T("");
	m_sLunastetutPantit = _T("");
	m_sKorkoYht = _T("");
	m_sKuittimaksu = _T("");
	m_sSHVMaksutYht = _T("");
	m_sVakuusvarmennus = _T("");
	m_sAlennus = _T("");
	m_sKorotus = _T("");
	m_sKulutYht = _T("");
	m_sLoppusummaMk = _T("");
	m_sYlimSailMaksuPerKk = _T("");
	//}}AFX_DATA_INIT

	bDlgAlreadyExists = FALSE;
	m_sDlgActionString = "Muut:";

	m_bCanceled	= FALSE;
	//m_dLainamuutos = 0.0;
	m_dVanhaVakuussumma = 0.0;
	m_dUusiLainasumma = 0.0;
	//m_dPyoristys = 0.0;
	m_sLunastetutPantit = "";

	m_bActionToBeMade = FALSE;	// FALSE = Uudistus, TRUE = Lunastus

	m_lLoanNr = loanNr;
	m_pCChangeCtrl = new CChangeCtrl(this, loanNr);

	m_sSelectedProductGroup = "";
	m_bKielto = false;
}


CDlgVakuusmuutos::~CDlgVakuusmuutos()
{
	/*if (m_pLainaRS) delete m_pLainaRS;
	if (m_pLainariviRS) delete m_pLainariviRS;

	if (pTapRS) delete pTapRS;*/
	if (m_pCChangeCtrl) delete m_pCChangeCtrl;
}


void CDlgVakuusmuutos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVakuusmuutos)
	DDX_Control(pDX, IDC_KOROTUS, m_ctlKorotus);
	DDX_Control(pDX, IDC_VAPAAEHT_LYH, m_ctlVapaaehtoinenLyhennys);
	DDX_Control(pDX, IDC_KUITIN_KATOAMINEN, m_ctlKuitinKatoaminen);
	DDX_Control(pDX, IDC_TALLETA_LAINATIEDOT, m_ctlTalletaLainatiedot);
	DDX_Control(pDX, IDC_KATOAMISMAKSU, m_ctlKatoamismaksu);
	DDX_Control(pDX, IDC_HUOM, m_ctlHuom);
	DDX_Control(pDX, IDC_TOIMENPIDEKIELTOPVM, m_ctlToimenpidekieltoPv);
	DDX_Control(pDX, IDCANCEL, m_ctlOKCANCELBtn);
	DDX_Control(pDX, IDC_VARASTO, m_ctlVarasto);
	DDX_Control(pDX, IDC_LAINAN_TUOTERYHMA, m_ctlLainanTuoteryhma);
	DDX_Control(pDX, IDC_MUIST_HUOM, m_ctlMuistHuom);
	DDX_Control(pDX, IDC_LAINANNIMI, m_ctlLainanNimi);
	DDX_Control(pDX, IDC_LIITTEET, m_ctlLiitteet);
	DDX_Control(pDX, IDC_VARMENNUS, m_ctlVarmennus);
	DDX_Control(pDX, IDC_NIMI_HTUN, m_ctlNimi_Htun);
	DDX_Control(pDX, IDC_LAINAN_KIELTO, m_ctlLainanKielto);
	DDX_Text(pDX, IDC_ERAPV, m_sEraPv);
	DDX_Text(pDX, IDC_LIITTEET, m_sLiitteet);
	DDX_Text(pDX, IDC_LAINANNIMI, m_sLainanNimi);
	DDX_Check(pDX, IDC_EIMUISTUTUSTA, m_bEiMuistutusta);
	DDX_Text(pDX, IDC_HUOM, m_sHuom);
	DDX_Text(pDX, IDC_MAKSETTAVA_YHT, m_sMaksettavaYht);
	DDX_Text(pDX, IDC_VARMENNUS, m_sVarmennus);
	DDX_Text(pDX, IDC_LAINAN_KIELTO, m_sLainanKielto);
	DDX_Check(pDX, IDC_KUITIN_KATOAMINEN, m_bKuitinKatoaminen);
	DDX_Text(pDX, IDC_MUISTUTUSKIRJE1_PVM, m_sMuistutuskirjePvm1);
	DDX_Text(pDX, IDC_MUISTUTUSKIRJE2_PVM, m_sMuistutuskirjePvm2);
	DDX_Text(pDX, IDC_KORKOPAIVIA_LAINA_AJALLA, m_sKorkopaivia_laina_ajalla);
	DDX_Text(pDX, IDC_KORKOPAIVIA_LAINA_AJAN_YLI, m_sKorkoPvLainaAjanYli);
	DDX_Text(pDX, IDC_VAPAAEHT_LYH, m_sVapaaehtoinenLyhennys);
	DDX_Text(pDX, IDC_YLIMSAILMAKSU2, m_sYlimSailMaksu);
	DDX_Text(pDX, IDC_KATOAMISMAKSU, m_sKatoamismaksu);
	DDX_Text(pDX, IDC_MUISTUTUSKIRJEMAKSU1, m_sMuistutusmaksu1);
	DDX_Text(pDX, IDC_MUISTUTUSKIRJEMAKSU2, m_sMuistutusmaksu2);
	DDX_Text(pDX, IDC_POSTITUS, m_sPostitus);
	DDX_Text(pDX, IDC_KORKOPR, m_sKorkoPr);
	DDX_Text(pDX, IDC_MUIST_HUOM, m_sMuistHuom);
	DDX_Text(pDX, IDC_SAILVAKMAKSU_PR, m_sSailVakMaksuPr);
	DDX_Text(pDX, IDC_LNRO_PV_EPV, m_sLnro_Pv_Epv);
	DDX_Text(pDX, IDC_PYORISTYS, m_sPyoristys);
	DDX_Text(pDX, IDC_ODOTUSPVM, m_sOdotusPvm);
	DDX_Text(pDX, IDC_VARASTO, m_sVarasto);
	DDX_Check(pDX, IDC_LAINANKIELTO, m_bKielto);
	DDX_Text(pDX, IDC_TOIMENPIDEKIELTOPVM, m_sToimenpidekieltoPv);
	DDX_Text(pDX, IDC_LUNASTETUTPANTIT, m_sLunastetutPantit);
	DDX_Text(pDX, IDC_KORKO_YHT, m_sKorkoYht);
	DDX_Text(pDX, IDC_KUITTIMAKSU, m_sKuittimaksu);
	DDX_Text(pDX, IDC_SHV_MAKSUT_YHT, m_sSHVMaksutYht);
	DDX_Text(pDX, IDC_VAKUUSVARMENNUSMAKSU, m_sVakuusvarmennus);
	DDX_Text(pDX, IDC_ALENNUS, m_sAlennus);
	DDX_Text(pDX, IDC_KOROTUS, m_sKorotus);
	DDX_Text(pDX, IDC_KULUT_YHT, m_sKulutYht);
	DDX_Text(pDX, IDC_LOPPUSUMMA_MK, m_sLoppusummaMk);
	DDX_Text(pDX, IDC_YLIMSAILMAKSU3, m_sYlimSailMaksuPerKk);
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX, m_pCChangeCtrl->getCRGXMuutosLRivitGrid());
}


BEGIN_MESSAGE_MAP(CDlgVakuusmuutos, CDialog)
	//{{AFX_MSG_MAP(CDlgVakuusmuutos)
	ON_BN_CLICKED(IDC_KUITTI, OnKuitti)
	ON_BN_CLICKED(IDC_TALLETA_LAINATIEDOT, OnTalletaLainatiedot)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PERU, OnPeru)
	ON_BN_CLICKED(IDC_KUITIN_KATOAMINEN, OnKuitinKatoaminen)
	ON_BN_CLICKED(IDC_LAINANKIELTO, OnLainankielto)
	ON_BN_CLICKED(IDC_BTN_LASKE, OnBtnLaske)
	ON_EN_CHANGE(IDC_VAPAAEHT_LYH, OnChangeVapaaehtLyh)
	ON_EN_CHANGE(IDC_KOROTUS, OnChangeKorotus)
	ON_BN_CLICKED(IDC_UUDISTUS_TAI_LUNASTUS, OnUudistusTaiLunastus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVakuusmuutos message handlers

BOOL CDlgVakuusmuutos::OnInitDialog()
{
	TRACE("Init\n");
	//char buf[150];
	CTimeSpan Erotus;
	int iPvLkm = 0;
	CString msg = "";
	CString sLBText = "";
	int j = 0;
	CString s1 = "";
	CString s2 = "";
	CString s3 = "";

	CDialog::OnInitDialog();
	this->m_pCChangeCtrl->getCRGXMuutosLRivitGrid()->SubclassDlgItem(IDC_MUUTOS_LAINARIVIT, this);
	//
	// ---- komponenttikohtaiset söyttörajoitteet ---
	//
	m_ctlLainanKielto.LimitText(20);
	m_ctlVarmennus.LimitText(2);
	m_ctlLiitteet.LimitText(255);
	m_ctlLainanNimi.LimitText(255);
	m_ctlMuistHuom.LimitText(255);
	m_ctlVarasto.LimitText(5);
	m_ctlHuom.LimitText(255);
	//
	//
	m_pCChangeCtrl->initChangeDlg();
	m_pCChangeCtrl->initChangeLRGrid();
	m_sEraPv = m_pCChangeCtrl->m_sEraPv;
	m_pCChangeCtrl->showLoanRows();

	if (bDlgAlreadyExists)
	{
		//m_ctlLainanTuoteryhma.SetCurSel(-1);
		return TRUE;
	}

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


	this->m_ctlNimi_Htun.SetFont(&f1);
	
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	bDlgAlreadyExists = TRUE;
	//OnBtnLaske();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVakuusmuutos::OnOK()
{
	TRACE("OK\n");
	// TODO: Add extra validation here
	//CDialog::OnOK();// poistettu ja lisätty OnKuitti() -> return ei sulje dialogia
}

void CDlgVakuusmuutos::OnKuitti()
{
	TRACE("Kuitti\n");
	this->m_pCChangeCtrl->executeLoanAction();
	// tätä ei saa tehdä kun dialogi on suljettu
	//UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)


	// Tätä ei saa tehdä koska dialogi on jo suljettu kun kuitti tulostetaan (View->MC->Queue)
	//CDialog::OnOK(); // sulkee dialogin
}



void CDlgVakuusmuutos::OnTalletaLainatiedot()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	//OnBtnLaske();
	m_pCChangeCtrl->saveLoanInfo();
	
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	//m_pCChangeCtrl->checkLostTicketPrinting();
	//OnPeru();
}




HBRUSH CDlgVakuusmuutos::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here

	if (pWnd->GetDlgCtrlID() == IDC_LAINAN_KIELTO)
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(255,128,255));
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}


CString CDlgVakuusmuutos::GetDlgString()
{
	CString s = "";
	s.Format("%s %s E  [%ld]", m_sDlgActionString, m_sMaksettavaYht, this->m_lLoanNr);
	return s; // Muutos (lun/uud)
}

double CDlgVakuusmuutos::GetFee()
{
	return atof(m_sMaksettavaYht);
}



void CDlgVakuusmuutos::OnCancel() 
{
	TRACE("Can\n");
	CDialog::OnCancel();
	m_bCanceled	= TRUE;
}




bool CDlgVakuusmuutos::Kuitti()
{
	TRACE("Kui\n");
	//OnTalletaLainatiedot();
	OnKuitti();
	return TRUE;
}

void CDlgVakuusmuutos::OnPeru()
{
	TRACE("Peru\n");
	m_bCanceled	= TRUE;
	CDialog::OnCancel();
}


void CDlgVakuusmuutos::rowDeleteEvent(ROWCOL nRow, double dPoistetutYht)
{
	TRACE("Del\n");
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString msg = "";
	//TRACE("Rivi %ld poistetaan !\n", nRow);
	//msg.Format("Rivi %ld poistettu!\nPoistetut yht. %7.2f mk", nRow, dPoistetutYht);
	//AfxMessageBox(msg);
	m_ctlTalletaLainatiedot.EnableWindow(FALSE);
	msg.Format("%7.2f", dPoistetutYht);
	m_sLunastetutPantit = msg;
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	OnBtnLaske();
}


void CDlgVakuusmuutos::OnKuitinKatoaminen()
{
	TRACE("OnKat\n");
	CTimeSpan kieltoaika(theApp.GetAs()->m_AT_ToimenpideKieltoPv,0,0,0);
	CTime KieltoPvm = CTime::GetCurrentTime();
	KieltoPvm = KieltoPvm + kieltoaika;

	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	if (atof(m_sKatoamismaksu) <= 0)
	{
		m_sKatoamismaksu.Format("%7.2f", theApp.GetAs()->m_AT_KuitinKatoaminen);
		m_ctlKatoamismaksu.SetWindowText(m_sKatoamismaksu);
	}
	if (m_bKuitinKatoaminen == TRUE)
	{
		m_ctlToimenpidekieltoPv.EnableWindow(TRUE);
		m_sToimenpidekieltoPv.Format("%s", KieltoPvm.Format("%d.%m.%Y"));
		m_ctlToimenpidekieltoPv.SetWindowText(m_sToimenpidekieltoPv);
		m_sLainanKielto = "Katoaminen";
		m_ctlOKCANCELBtn.EnableWindow(FALSE);
	}
	else
	{
		m_ctlToimenpidekieltoPv.EnableWindow(FALSE);
		m_ctlToimenpidekieltoPv.SetWindowText(m_sToimenpidekieltoPv);
		m_ctlOKCANCELBtn.EnableWindow(TRUE);
	}

	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}


void CDlgVakuusmuutos::OnLainankielto()
{
	TRACE("OnKiel\n");
	CTimeSpan kieltoaika(theApp.GetAs()->m_AT_ToimenpideKieltoPv,0,0,0);
	CTime KieltoPvm = CTime::GetCurrentTime();
	KieltoPvm = KieltoPvm + kieltoaika;

	if (m_bKielto == TRUE)
	{
		//TRACE("Kielto pois (Päiväystä ei tyhjennetä)\n");
		m_bKielto = FALSE;

		m_sToimenpidekieltoPv = "";
		m_sKatoamismaksu = "";
		this->m_sLainanKielto = "";

		m_ctlToimenpidekieltoPv.SetWindowText("");
		m_ctlKatoamismaksu.SetWindowText("");
		m_ctlLainanKielto.SetWindowText("");

		m_ctlToimenpidekieltoPv.EnableWindow(TRUE);
		m_ctlOKCANCELBtn.EnableWindow(TRUE);
		m_ctlKuitinKatoaminen.EnableWindow(TRUE);
		m_ctlKatoamismaksu.EnableWindow(TRUE);
	}
	else
	{
		//TRACE("Kielto päälle (Jos tyhjä päiväys niin olet.arvo)\n");
		m_bKielto = TRUE;
		m_ctlToimenpidekieltoPv.EnableWindow(TRUE);
		m_sToimenpidekieltoPv.Format("%s", KieltoPvm.Format("%d.%m.%Y"));
		m_ctlToimenpidekieltoPv.SetWindowText(m_sToimenpidekieltoPv);
		m_ctlOKCANCELBtn.EnableWindow(FALSE);
		m_ctlKuitinKatoaminen.EnableWindow(FALSE);
		m_ctlKatoamismaksu.EnableWindow(FALSE);
	}
}


void CDlgVakuusmuutos::OnBtnLaske()
{
	TRACE("OnLaske\n");
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	UpdateData(); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	m_pCChangeCtrl->setLoanProductGroup();
	double d = atof(theApp.dot(m_sVapaaehtoinenLyhennys));
	double dKorotus = atof(theApp.dot(m_sKorotus));
	TRACE("vLyh=%7.2f\n", d);
	m_pCChangeCtrl->calculate(d, dKorotus);
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	TRACE("Pyör,%f\n", this->m_sPyoristys);
}


void CDlgVakuusmuutos::OnChangeVapaaehtLyh() 
{
	TRACE("OnCha\n");
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	

}

void CDlgVakuusmuutos::OnChangeKorotus() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	TRACE("OnCha\n");
	
}


void CDlgVakuusmuutos::OnUudistusTaiLunastus() 
{
	TRACE("OnUud\n");
	CString msg = "";
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	OnBtnLaske();

	// --- tarkastetaan, että tuoteryhmä on valittu ----
	m_pCChangeCtrl->m_iSelectedProductGroup = m_ctlLainanTuoteryhma.GetCurSel();
	if (m_pCChangeCtrl->m_iSelectedProductGroup == LB_ERR)
	{
		msg.Format("Tarkasta lainan tuoteryhmä");
		if (AfxMessageBox(msg) == IDYES /*IDNO*/)
		{
		}
		return;
	}
	else
		m_ctlLainanTuoteryhma.GetLBText(m_pCChangeCtrl->m_iSelectedProductGroup, m_sSelectedProductGroup);
	CDialog::OnCancel();
}

