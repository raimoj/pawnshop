// Pantti.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Pantti.h"

#include "MainFrm.h"
#include "PanttiDoc.h"
#include "PanttiView.h"
#include "DlgArviomies.h"
#include "DlgAsetus.h"
//#include "DlgKassa.h"

#include "DlgHakulista.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanttiApp

BEGIN_MESSAGE_MAP(CPanttiApp, CWinApp)
	//{{AFX_MSG_MAP(CPanttiApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HALLINTA_ASETUKSET, OnHallintaAsetukset)
	ON_COMMAND(ID_HALLINTA_ARVIOMIEHET, OnHallintaArviomiehet)
	ON_COMMAND(ID_HALLINTA_KASSAT, OnHallintaKassat)
	ON_COMMAND(ID_HALLINTA_TUOTTEET, OnHallintaTuotteet)
	ON_COMMAND(ID_HALLINTA_KASSANSALDO, OnHallintaKassansaldo)
	ON_COMMAND(ID_RAPORTIT_KASSAPIVKIRJA, OnRaportitKassapivkirja)
	ON_COMMAND(ID_RAPORTIT_MUISTUTUSKIRJEET, OnRaportitMuistutuskirjeet)
	ON_COMMAND(ID_HUUTOKAUPPA_HAKULISTA, OnHuutokauppaHakulista)
	ON_COMMAND(ID_HUUTOKAUPPA_SIIRTOHUUTOKAUPPAAN, OnHuutokauppaSiirtohuutokauppaan)
	ON_COMMAND(ID_RAPORTIT_ODOTUSLISTA, OnRaportitOdotuslista)
	ON_COMMAND(ID_HUUTOKAUPPA_LAINANSIIRTOHUUTOKAUPPAAN, OnHuutokauppaLainansiirtohuutokauppaan)
	ON_UPDATE_COMMAND_UI(ID_HUUTOKAUPPA_LAINANSIIRTOHUUTOKAUPPAAN, OnUpdateHuutokauppaLainansiirtohuutokauppaan)
	ON_COMMAND(ID_HUUTOKAUPPA_YLIJMKIRJEET, OnHuutokauppaYlijmkirjeet)
	ON_COMMAND(ID_HUUTOKAUPPA_YLIJMNKUITTAUSASIAKKAALLE, OnHuutokauppaYlijmnkuittausasiakkaalle)
	ON_COMMAND(ID_HUUTOKAUPPA_YLIJMNKUITTLAINAAMOLLE, OnHuutokauppaYlijmnkuittlainaamolle)
	ON_COMMAND(ID_HUUTOKAUPPA_VAPAAEHTALIJPERIMINENASIAKKAALTA, OnHuutokauppaAlijPeriminenAsiakkaalta)
	ON_UPDATE_COMMAND_UI(ID_HUUTOKAUPPA_VAPAAEHTALIJPERIMINENASIAKKAALTA, OnUpdateHuutokauppaAlijPeriminenAsiakkaalta)
	ON_COMMAND(ID_LAINAT_LAINALUOTTOTAPPIOIHIN, OnLainatLainaluottotappioihin)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_LAINALUOTTOTAPPIOIHIN, OnUpdateLainatLainaluottotappioihin)
	ON_COMMAND(ID_LAINAT_HALTIJANMUUTOS, OnLainatHaltijanmuutos)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_HALTIJANMUUTOS, OnUpdateLainatHaltijanmuutos)
	ON_COMMAND(ID_RAPORTIT_KASSALOKI, OnRaportitKassaloki)
	ON_COMMAND(ID_HUUTOKAUPPA_HUUTOKAUPPA, OnHuutokauppaHuutokauppa)
	ON_COMMAND(ID_RAPORTIT_KIRJE1, OnRaportitKirje1)
	ON_COMMAND(ID_RAPORTIT_KIRJE2, OnRaportitKirje2)
	ON_COMMAND(ID_RAPORTIT_UUSIKUITTI, OnRaportitUusikuitti)
	ON_UPDATE_COMMAND_UI(ID_RAPORTIT_UUSIKUITTI, OnUpdateRaportitUusikuitti)
	ON_UPDATE_COMMAND_UI(ID_HALLINTA_ARVIOMIEHET, OnUpdateHallintaArviomiehet)
	ON_UPDATE_COMMAND_UI(ID_HALLINTA_TUOTTEET, OnUpdateHallintaTuotteet)
	ON_UPDATE_COMMAND_UI(ID_HALLINTA_KASSAT, OnUpdateHallintaKassat)
	ON_UPDATE_COMMAND_UI(ID_HALLINTA_KASSANSALDO, OnUpdateHallintaKassansaldo)
	ON_UPDATE_COMMAND_UI(ID_HALLINTA_ASETUKSET, OnUpdateHallintaAsetukset)
	ON_UPDATE_COMMAND_UI(ID_RAPORTIT_MUISTUTUSKIRJEET, OnUpdateRaportitMuistutuskirjeet)
	ON_UPDATE_COMMAND_UI(ID_RAPORTIT_KIRJE1, OnUpdateRaportitKirje1)
	ON_UPDATE_COMMAND_UI(ID_RAPORTIT_KIRJE2, OnUpdateRaportitKirje2)
	ON_UPDATE_COMMAND_UI(ID_HUUTOKAUPPA_HAKULISTA, OnUpdateHuutokauppaHakulista)
	ON_UPDATE_COMMAND_UI(ID_HUUTOKAUPPA_SIIRTOHUUTOKAUPPAAN, OnUpdateHuutokauppaSiirtohuutokauppaan)
	ON_UPDATE_COMMAND_UI(ID_HUUTOKAUPPA_YLIJMKIRJEET, OnUpdateHuutokauppaYlijmkirjeet)
	ON_UPDATE_COMMAND_UI(ID_HUUTOKAUPPA_YLIJMNKUITTLAINAAMOLLE, OnUpdateHuutokauppaYlijmnkuittlainaamolle)
	ON_COMMAND(ID_ASIAKKAAT_HENKTUNNUS, OnAsiakkaatHenktunnus)
	ON_COMMAND(ID_HUUTOKAUPPA_ALLEVUODENVANHATYLIJMT, OnHuutokauppaAllevuodenvanhatylijmt)
	ON_UPDATE_COMMAND_UI(ID_HUUTOKAUPPA_ALLEVUODENVANHATYLIJMT, OnUpdateHuutokauppaAllevuodenvanhatylijmt)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanttiApp construction

CPanttiApp::CPanttiApp()
{
	m_pMC = NULL;

	m_sUser = "?";
	m_sDesk = "?";
	m_lDeskId = -1;
	m_sODBCDataSource = "Panttitietokanta";

	m_bAsetusOK = TRUE;

	m_pPrintRes = new CPrintResource;

	//setDBConnection();
}

CPanttiApp::~CPanttiApp()
{
	delete m_pAsetusRS;
	delete m_pPrintRes;
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CPanttiApp object

CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPanttiApp initialization

BOOL CPanttiApp::InitInstance()
{
	GXInit();
	GXInitODBC();


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPanttiDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPanttiView));
	AddDocTemplate(pDocTemplate);
	
	// Parse command line for standard shell commands, DDE, file open
	//CCommandLineInfo cmdInfo;
	CPanttiCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}

	CString s = cmdInfo.GetParameter("-U");
	TRACE("CmdlineParam-U ='%s'\n", s);
	CString k = cmdInfo.GetParameter("-K");
	TRACE("CmdlineParam-K ='%s'\n", k);
	//
	// --- ODBC ---
	CString odbc = cmdInfo.GetParameter("-ODBC");
	TRACE("CmdlineParam-ODBC ='%s'\n", odbc);
	if (!odbc.IsEmpty())
		m_sODBCDataSource = odbc;
	setDBConnection();
	//
	//
	cmdInfo.IsValidDesk(k);
	if (cmdInfo.IsValidUser(s) && cmdInfo.IsValidDesk(k))
	{
	}
	else
	{
		TRACE("Invalid UserName/Deskname as command line parameter\n");
		if ( ! cmdInfo.AskUserName(k))
		{
			MessageBeep(1);
			TRACE("Invalid UserName !\n");
			//return FALSE;
		}
	}
	TRACE("Käyttäjän nimikirjaimet: '%s'\n", m_sUser);
	TRACE("Käyttäjän kassa: '%s'", m_sDesk);
	TRACE(" (KassaID= '%ld')\n", m_lDeskId);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;



	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	if (!m_bAsetusOK)   // asetustietoja ei ole vielä talletettu !
	{
		CDlgAsetus* pdlgAs = new CDlgAsetus;

		// oletusarvot
		pdlgAs->m_sToimisto		= "Oulun Panttilainakonttori Oy";
		pdlgAs->m_sKatuOs		= "    Pakkahuoneenkatu 26";
		pdlgAs->m_sPtp			= "       90100 Oulu";
		pdlgAs->m_sPuh			= "        08 374239";
		pdlgAs->m_sFax			= "        08 374654";

		pdlgAs->m_iLaina_aika = 4;
		//
		pdlgAs->m_dKorko1 = 2.6;
		pdlgAs->setRaja1(100);
		pdlgAs->m_dKorko2 = 2.4;
		pdlgAs->setRaja2(500);
		pdlgAs->m_dKorko3 = 2.2;
		pdlgAs->setRaja3(1000);
		pdlgAs->m_dKorko4 = 2.0;

		pdlgAs->setKuittimaksu(5);
		pdlgAs->m_sSeurHKPv = "";
		pdlgAs->m_sHkEraPvRaja = "";

		pdlgAs->setKuitinkatoaminen(5);
		pdlgAs->m_iToimenpidekieltoraja = 30;
		pdlgAs->setMuistutuskirjemaksu(5);
		pdlgAs->setVakuusvarmennusmaksu(5);
		pdlgAs->setPostitusmaksu(5);
		pdlgAs->m_dSHVMaksuPr = 1.5;

		pdlgAs->setMuistutuskirjeraja(20);
		pdlgAs->m_iMuistutuskirje1raja_pv = 15;
		pdlgAs->m_iMuistutuskirje2raja_pv = 25;

		pdlgAs->m_dHkMaksuProsentti = 15;

		pdlgAs->setHkPoistoMaksu(5);
		pdlgAs->m_dMyValmMaksuPr = 2;
		pdlgAs->setMyValmMaksuMin(5);
		pdlgAs->m_dArvopapValMaksuPr = 5;

		pdlgAs->m_iYlijaamanTilitysaika = 365;
		pdlgAs->setYlijaamanIlmMaksu(10);
		pdlgAs->setYlijaamanAlaraja(50);

		if (pdlgAs->DoModal() == IDOK) // talletus
		{
		}

		delete pdlgAs;
		HaeUudetAsetukset();
	}
	else
	{
		HaeUudetAsetukset();
	}

	//
	// ---- dialogien taustaväri --------
	//COLORREF crBackground = RGB(255, 255, 0); // kirkkaan keltainen
	//COLORREF crBackground = RGB(128, 255, 255); // vaaleansininen
	//COLORREF crBackground = RGB(64, 128, 128); // sinivihreä windows-väri (ei käy punainen teksti !!! kokeile valkoista ..)
	//COLORREF crBackground = RGB(128, 128, 64); // ruskeanvihreä :)
	COLORREF crBackground = RGB(192, 192, 192); // harmaa
	//
	// ---- tekstin väri ---
	//COLORREF crText = RGB(255, 0, 0); // punainen
	//COLORREF crText = RGB(255, 255, 255); // valkoinen
	COLORREF crText = RGB(0, 0, 0); // musta

	SetDialogBkColor(crBackground, crText);


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPanttiApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPanttiApp message handlers


void CPanttiApp::OnHallintaAsetukset()
{
	CDlgAsetus* pdlgAs = new CDlgAsetus;

	pdlgAs->m_iLaina_aika = m_pAsetusRS->m_AT_LainaAika;
	pdlgAs->m_sToimisto = m_pAsetusRS->m_AT_Toimisto;
	pdlgAs->m_sKatuOs = m_pAsetusRS->m_AT_Katu;
	pdlgAs->m_sPtp = m_pAsetusRS->m_AT_Ptp;
	pdlgAs->m_sPuh = m_pAsetusRS->m_AT_Puh;
	pdlgAs->m_sFax = m_pAsetusRS->m_AT_Fax;


	pdlgAs->setKuittimaksu(this->makeRounding(m_pAsetusRS->m_AT_Kuittimaksu));
	if (m_pAsetusRS->m_AT_SeurHKPv != NULL)
	{
		pdlgAs->m_sSeurHKPv = m_pAsetusRS->m_AT_SeurHKPv.Format("%d.%m.%Y");
		m_sSeuraavaHuutokauppaPvm = pdlgAs->m_sSeurHKPv;
	}
	else
	{
		pdlgAs->m_sSeurHKPv = "??.??.????";
		m_sSeuraavaHuutokauppaPvm = pdlgAs->m_sSeurHKPv;
	}
	if (m_pAsetusRS->m_AT_HKEraPvRaja != NULL)
	{
		pdlgAs->m_sHkEraPvRaja = m_pAsetusRS->m_AT_HKEraPvRaja.Format("%d.%m.%Y");
		m_sHkEraPvRaja = pdlgAs->m_sHkEraPvRaja;
	}
	else
	{
		pdlgAs->m_sHkEraPvRaja = "??.??.????";
		m_sHkEraPvRaja = pdlgAs->m_sHkEraPvRaja;
	}
	pdlgAs->setKuitinkatoaminen(this->makeRounding(m_pAsetusRS->m_AT_KuitinKatoaminen));
	pdlgAs->m_iToimenpidekieltoraja = m_pAsetusRS->m_AT_ToimenpideKieltoPv;
	pdlgAs->setMuistutuskirjemaksu(this->makeRounding(m_pAsetusRS->m_AT_MuKirjemaksu));
	pdlgAs->setVakuusvarmennusmaksu(this->makeRounding(m_pAsetusRS->m_AT_VakVarmMaksu));
	pdlgAs->setPostitusmaksu(this->makeRounding(m_pAsetusRS->m_AT_PostitusMaksu));
	pdlgAs->m_dSHVMaksuPr = m_pAsetusRS->m_AT_SHVMaksuPr;


	pdlgAs->m_dKorko1	= m_pAsetusRS->m_AT_LKorkoPr1;
	pdlgAs->setRaja1(this->makeRounding(m_pAsetusRS->m_AT_LRaja1));
	pdlgAs->m_dKorko2	= m_pAsetusRS->m_AT_LKorkoPr2;
	pdlgAs->setRaja2(this->makeRounding(m_pAsetusRS->m_AT_LRaja2));
	pdlgAs->m_dKorko3	= m_pAsetusRS->m_AT_LKorkoPr3;
	pdlgAs->setRaja3(this->makeRounding(m_pAsetusRS->m_AT_LRaja3));
	pdlgAs->m_dKorko4	= m_pAsetusRS->m_AT_LKorkoPr4;

	pdlgAs->setHkPoistoMaksu(this->makeRounding(m_pAsetusRS->m_AT_HKPoMaksu));
	pdlgAs->m_dMyValmMaksuPr = m_pAsetusRS->m_AT_MyValmMaksuPr;
	pdlgAs->setMyValmMaksuMin(this->makeRounding(m_pAsetusRS->m_AT_MyValmMaksuMin));
	pdlgAs->m_dArvopapValMaksuPr = m_pAsetusRS->m_AT_ArvopapValMaksuPr;


	pdlgAs->setMuistutuskirjeraja(this->makeRounding(m_pAsetusRS->m_AT_MuKirjeRajaMk));
	pdlgAs->m_iMuistutuskirje1raja_pv = m_pAsetusRS->m_AT_MuKirje1RajaPv;
	pdlgAs->m_iMuistutuskirje2raja_pv = m_pAsetusRS->m_AT_MuKirje2RajaPv;
	pdlgAs->m_dHkMaksuProsentti = m_pAsetusRS->m_AT_HKMaksuPr;

	pdlgAs->m_iYlijaamanTilitysaika = m_pAsetusRS->m_AT_YlijKuitAikaraja;
	pdlgAs->setYlijaamanIlmMaksu(this->makeRounding(m_pAsetusRS->m_AT_YlijIlmMaksu));
	pdlgAs->setYlijaamanAlaraja(this->makeRounding(m_pAsetusRS->m_AT_LainYlijAlarajaMk));

	if (pdlgAs->DoModal() == IDOK) // talletus
	{
	}

	delete pdlgAs;
	HaeUudetAsetukset();
}

void CPanttiApp::HaeUudetAsetukset()
{
	try
	{
		m_pAsetusRS->Close();
		m_pAsetusRS->Open();
		if (m_pAsetusRS->IsEOF()) // asetustietoja ei ole talletettu
		{
			m_bAsetusOK = FALSE;
			AfxMessageBox("Asetustietoja ei ole vielä talletettu!");
		}

		//
		// ----
		if (m_pAsetusRS->m_AT_SeurHKPv != NULL)
			m_sSeuraavaHuutokauppaPvm = m_pAsetusRS->m_AT_SeurHKPv.Format("%d.%m.%Y");
		else
			m_sSeuraavaHuutokauppaPvm = "??.??.????";
		//
		//
		// ----
		if (m_pAsetusRS->m_AT_HKEraPvRaja != NULL)
			m_sHkEraPvRaja = m_pAsetusRS->m_AT_HKEraPvRaja.Format("%d.%m.%Y");
		else
			m_sHkEraPvRaja = "??.??.????";

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
}

/*CAsetusRS* CPanttiApp::GetAs()
{

}*/



double CPanttiApp::GetInterestRate(double dLainaSumma)
{
	ASSERT(m_pAsetusRS->IsOpen());
	double dRtn=-999999;
	//TRACE("Lainasumma=%7.2f:",dLainaSumma);
	if (dLainaSumma < m_pAsetusRS->m_AT_LRaja1)
	{
		dRtn = m_pAsetusRS->m_AT_LKorkoPr1;
	}
	else if ((dLainaSumma >= m_pAsetusRS->m_AT_LRaja1) &&
		     (dLainaSumma <  m_pAsetusRS->m_AT_LRaja2))
	{
		dRtn = m_pAsetusRS->m_AT_LKorkoPr2;
	}
	else if ((dLainaSumma >= m_pAsetusRS->m_AT_LRaja2) &&
		     (dLainaSumma <  m_pAsetusRS->m_AT_LRaja3))
	{
		dRtn = m_pAsetusRS->m_AT_LKorkoPr3;
	}
	else if (dLainaSumma >= m_pAsetusRS->m_AT_LRaja3)
	{
		dRtn = m_pAsetusRS->m_AT_LKorkoPr4;
	}
	//TRACE(" KorkoPr=%7.2f\n", dRtn);
	return dRtn;
}


int CPanttiApp::GetLoanMonths(int iLainaAika, BOOL bLainaAika) // default bLainaAika = TRUE
{
	
	// return arvo (irtn) = 1 silloin kun iLainaAika = 0
	
	int irtn = 0;
	int i = 1;
	int kk = 1;

	if (iLainaAika <= 0)
	{
		irtn = 0;
	}
	else if (iLainaAika > 0 && iLainaAika <= 30) // tässä oli = merkki myös, Ylimsäilytysmak:ko vuoksi??? 
	{
		irtn = 1;
	}
	/*else if (iLainaAika >30 && iLainaAika <= 60)
	{
		irtn = 2;
	}
	else if (iLainaAika >60 && iLainaAika <= 90)
	{
		irtn = 3;
	}
	else if (iLainaAika >90 && iLainaAika <= 120)
	{
		irtn = 4;
	}*/
	else
	{
		while	(!	((iLainaAika >(i*30)) &&  (iLainaAika <= ((i*30)+30))	))
		{
			i++;
		}
		irtn = i+1;
	}

	if (bLainaAika)
	{
		if (iLainaAika > m_pAsetusRS->m_AT_LainaAika*30)
		{
			irtn = m_pAsetusRS->m_AT_LainaAika;	// lainan hoitaminen on myöhässä.
		}
	}
	return irtn;
}

void CPanttiApp::OnHallintaArviomiehet()
{
	CDlgArviomies* pAm = new CDlgArviomies;
	if (pAm->DoModal() == IDOK) // talletus ?
	{
	}

	delete pAm;
}

CString CPanttiApp::RemoveSpaces(CString sText)
{
	CString st = "";
	int i = 0;
	//TRACE("%s, %d\n", sText, sText.GetLength());
	while (i != sText.GetLength())
	{
		//TRACE("'%s'\n",sText.Mid(i,1));
		if (sText.Mid(i,1) != " ")
			break;
		i++;
	}
	//TRACE("%s\n", sText.Right(sText.GetLength() - i));
	st = sText.Right(sText.GetLength() - i);
	i = st.GetLength()-1;
	while (i >= 0)
	{
		//TRACE("'%s'\n",st.Mid(i,1));
		if (st.Mid(i,1) != " ")
			break;
		i--;
	}
	return st.Left(i+1);
}


//---------------------------------------------------------------------------
CTime CPanttiApp::GetDate(CString dateText)
//---------------------------------------------------------------------------
{
	char buf[50];
	int vuosi,kk,pv=0;

	sprintf(buf, "%s", dateText);
	MuutaTekstiPvmksi(buf, &vuosi, &kk, &pv);
   //TRACE("GetDate:vuosi=%d, kk=%d, pv=%d\n", vuosi, kk, pv);
   if (pv < 1 || pv > 31 || kk < 1 || kk > 12 || vuosi < 1970 || vuosi > 2038)
   {
      //MessageBeep(1);   // epäkelpo päiväys
      //AfxMessageBox("Epäkelpo päiväys");
      dateText = "";
   }
   if (dateText != "")
	{
   	CTime APvm(vuosi, kk, pv, 0, 0, 0); // vuosi neljällä numerolla
   	//sprintf(buf,"%s",APvm.Format("%d.%m.%Y"));
   	//TRACE("pvm=%s\n", buf);
   	return APvm;
   }
   else
   {
		//TRACE("pvm=%s\n", "?");
		return NULL;
	}
}


//---------------------------------------------------------------------------
void CPanttiApp::MuutaTekstiPvmksi(char* temp,int* vuosi,int* kk,int* pv)
//---------------------------------------------------------------------------
{
   CString jono = temp;
   int x;
   //
   // tarkastetaan pituus järkeväksi
   //
   //TRACE("jono=%s\n", jono);
   if (jono.GetLength() <= 7 || jono.GetLength() >= 11)
   {
   	*pv = 0;
   	*kk = 0;
   	*vuosi = 0;
   	return;
   }
   //
   // tulkitaan kaksi ensimmäistä merkkiä pv:ksi, olipa päivä annettu
   // yhdellä tai kahdella numerolla. (07.05.1997/7.5.1997)
   // Piste ei sotke sscanf:n toimintaa
   if (sscanf(jono.Left(2), "%d", &x) == EOF)
      *pv = 0;
   else
   	*pv = x;
   //-----------------------------------------
   if (jono.Mid(1,1) == ".")   // onko päivä yksi vai kaksinumeroinen
   {
      if (sscanf(jono.Mid(2,2), "%d", &x) == EOF)
         *kk = 0;
      else
      	*kk = x;
   }
   else // päivä on kaksinumeroinen (>9)
   {
      if (sscanf(jono.Mid(3,2), "%d", &x) == EOF)
         *kk = 0;
      else
      	*kk = x;
   }
   //-----------------------------------------
   if (sscanf(jono.Right(4), "%d", &x) == EOF)  // vuosi neljällä nrolla
      *vuosi = 0;
   else
   	*vuosi = x;
   //TRACE("MTP:vuosi=%d, kk=%d, pv=%d\n", *vuosi, *kk, *pv);
}






void CPanttiApp::OnHallintaKassat()
{
/*	CDlgKassa* pKa = new CDlgKassa;
	if (pKa->DoModal() == IDOK) // talletus ?
	{
	}

	delete pKa;
*/
	m_pMC->CashDeskOperations();
}

void CPanttiApp::OnHallintaTuotteet()
{
	m_pMC->Products();
}

void CPanttiApp::OnHallintaKassansaldo()
{
	m_pMC->dlgCheckDesk();
}


void CPanttiApp::OnRaportitKassapivkirja()
{
	m_pMC->DeskReport();
}

void CPanttiApp::OnRaportitMuistutuskirjeet()
{
	CString msg = "";
	msg.Format("Ohjelma tarkastaa lainat ja muodostaa tietokantaan muistutuskirjelistan.\n Tarkastus voi kestää jonkin aikaa.\n Jatketaanko ?");
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return;
	}
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_pMC->remainderRequest();
	m_pMC->m_pPView->SelchangeSnimi();
}




void CPanttiApp::OnHuutokauppaHakulista()
{
	CString msg = "";
	CDlgHakulista dlgHL;
	// m_sSeuraavaHuutokauppaPvm, m_sHkEraPvRaja
	msg.Format("Ohjelma tulostaa paperille huutokaupan hakulistan.\n\nASETUSTIEDOT:\nSeuraava huutokauppapäivä: %s\nEräpäiväraja: %s\n\n  Jatketaanko ?", m_sSeuraavaHuutokauppaPvm, m_sHkEraPvRaja);
	//if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	//{
	//	return;
	//}
	dlgHL.m_sHakulistaInfoTxt = msg;

	dlgHL.DoModal();

	//m_pMC->startAuctionSearchList();
	//m_pMC->m_pPView->SelchangeSnimi();
}

void CPanttiApp::OnHuutokauppaSiirtohuutokauppaan()
{
	CString msg = "";
	// m_sSeuraavaHuutokauppaPvm, m_sHkEraPvRaja
	if (m_sSeuraavaHuutokauppaPvm.IsEmpty() || m_sHkEraPvRaja.IsEmpty())
	{
		msg.Format("Tarkasta asetustiedot: Huutokauppapäivä ja Eräpäiväraja");
		if (AfxMessageBox(msg))
		{
			return;
		}
	}
	if (m_sSeuraavaHuutokauppaPvm == "??.??.????" || m_sHkEraPvRaja == "??.??.????")
	{
		msg.Format("Tarkasta asetustiedot: Huutokauppapäivä ja Eräpäiväraja");
		if (AfxMessageBox(msg))
		{
			return;
		}
	}
	msg.Format("Ohjelma siirtää lainat hakulistan mukaisesti huutokauppaan.\n\nASETUSTIEDOT:\n -Seuraava huutokauppapäivä: %s\n -Eräpäiväraja: %s\n\nHuutokauppapäivä talletetaan huutokauppatietoihin.\n\n	Jatketaanko ?", m_sSeuraavaHuutokauppaPvm, m_sHkEraPvRaja);
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return;
	}
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_pMC->startAuctionMove();
	msg.Format("Siirto valmis!");
	AfxMessageBox(msg);
	m_pMC->m_pPView->SelchangeSnimi();
}


double CPanttiApp::makeRounding(double dPrice, BOOL bCurrency) // // FALSE = Markka , TRUE= Euro default
{
	CString sTmp = "";
	double dP = 0;
	sTmp.Format("%7.2f          ", dPrice);
	int i = sTmp.Find('.');   // desimaalipisteen paikka
	//double dAlkup = atof(sTmp);
	//TRACE("Pyöristys: summa ilman desim. %s, kokonaisosan pituus:%d\n", sTmp.Left(i), i);
	//double dP = atof(sTmp.Left(i+2)); // ens. desim tulee mukaan

	if (bCurrency == FALSE) // markkojen/pennien pyöristys, pyör kymmenille penneille
	{
		if (sTmp.Mid(i+1, 2) == "00")
		{
			dP = atof(sTmp);
		}
		/*else if (sTmp.Mid(i+2, 1) == "1" || sTmp.Mid(i+2, 1) == "2" || sTmp.Mid(i+2, 1) == "3" || sTmp.Mid(i+2, 1) == "4")
		{
			sTmp = sTmp.Left(i+2) + "0";
			dP = atof(sTmp);
		}
		
		else if (sTmp.Mid(i+2, 1) == "5" || sTmp.Mid(i+2, 1) == "6" || sTmp.Mid(i+2, 1) == "7" || sTmp.Mid(i+2, 1) == "8" || sTmp.Mid(i+2, 1) == "9")		
		{
			sTmp = sTmp.Left(i+2) + "0";
			dP = atof(sTmp);
			dP = dP + 0.10;
		}*/
		dP = atof(sTmp.Left(i));
		//TRACE("Erotus = %f\n", dMarkat-dAlkup);
		if (dP < 0)
			dP = dP -1.000000000000;

	}
	else // Eurosummien pyöristys, 5-senttiset käytössä
	{
		if (sTmp.Mid(i+2, 1) == "0")
		{
			dP = atof(sTmp);  // jos toinen desimaali = 0, ei tehdä luvulle mitään muutosta
		}
		else if (sTmp.Mid(i+2, 1) == "1" || sTmp.Mid(i+2, 1) == "2")
		{
			sTmp = sTmp.Left(i+2) + "0"; // jos toinen desim =1 tai 2, asetetaan toinen desimaali =0
			dP = atof(sTmp);
		}
		else if (sTmp.Mid(i+2, 1) == "3" || sTmp.Mid(i+2, 1) == "4")		
		{
			sTmp = sTmp.Left(i+2) + "5";// jos toinen desim = 3 tai 4 , asetetaan toinen desimaali =5
			dP = atof(sTmp);
		}
		else if (sTmp.Mid(i+2, 1) == "5")		
		{
			dP = atof(sTmp);
		}
		else if (sTmp.Mid(i+2, 1) == "6" || sTmp.Mid(i+2, 1) == "7")				
		{
			sTmp = sTmp.Left(i+2) + "5";
			dP = atof(sTmp);
		}
		else if (sTmp.Mid(i+2, 1) == "8" || sTmp.Mid(i+2, 1) == "9")				
		{
			sTmp = sTmp.Left(i+2) + "0";
			dP = atof(sTmp);
			if (dP < 0)
			{
				dP = dP - 0.10;
			}
			else
			{
				dP = dP + 0.10;
			}
		}
	}
	//if (sTmp.Mid(i+1, 2) != "00")
	//	dP = dP + 1.0;
	return dP;
}




void CPanttiApp::OnRaportitOdotuslista()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_pMC->printWaitList();
	
	


}

void CPanttiApp::OnHuutokauppaLainansiirtohuutokauppaan()
{
	CString msg = "";
	long lAuctionID = 0;
	TRACE("Siirrettävän lainan numero on %ld\n", m_pMC->getLoanNumber());
	msg.Format("Siirretäänkö laina %ld huutokauppaan ?", m_pMC->getLoanNumber());
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return;
	}
	//
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	lAuctionID = theApp.m_pMC->m_pDB->saveCurrentAuctionDate();
	theApp.m_pMC->m_pDB->setLoanStatus(m_pMC->getLoanNumber(), "H", lAuctionID);
	m_pMC->m_pPView->SelchangeSnimi();
}

void CPanttiApp::OnUpdateHuutokauppaLainansiirtohuutokauppaan(CCmdUI* pCmdUI)
{
	TRACE("Lainan nro: %ld\n", m_pMC->getLoanNumber());
	if (m_pMC->getLoanNumber() > 0)
	{
		if (this->m_bAdminUser == TRUE)
		{
			pCmdUI->Enable(TRUE);
		}
		else
		{
			pCmdUI->Enable(FALSE);
		}
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CPanttiApp::OnHuutokauppaYlijmkirjeet()
{
	m_pMC->printAuctionBalanceLetters();
}

void CPanttiApp::OnHuutokauppaYlijmnkuittausasiakkaalle()
{
	m_pMC->auctionBalanceSetOff();
}

void CPanttiApp::OnHuutokauppaYlijmnkuittlainaamolle()
{
	m_pMC->balSetOffForPawnShop();
}

void CPanttiApp::OnHuutokauppaAlijPeriminenAsiakkaalta()
{
	m_pMC->alijPeriminenAsiakkaalta();
}

void CPanttiApp::OnUpdateHuutokauppaAlijPeriminenAsiakkaalta(CCmdUI* pCmdUI)
{
	//TRACE("As nro: %ld\n", m_pMC->getSelectedCustomerID());
	if (m_pMC->getSelectedCustomerID() > 0)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnLainatLainaluottotappioihin()
{
	m_pMC->creditLoss();
	m_pMC->m_pPView->SelchangeSnimi();
}

void CPanttiApp::OnUpdateLainatLainaluottotappioihin(CCmdUI* pCmdUI)
{
	//TRACE("La nro: %ld\n", m_pMC->getLoanNumber());
	
	if ((m_pMC->getSelectedCustomerID() > 0) && (theApp.m_pMC->m_pDB->getCurrentLoan()->getRedemptionLoan()->getLoanStatus() == "A"))
	{
		if (this->m_bAdminUser == TRUE)
		{
			pCmdUI->Enable(TRUE);
		}
		else
		{
			pCmdUI->Enable(FALSE);
		}
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CPanttiApp::OnLainatHaltijanmuutos()
{
	m_pMC->loanOwner();
	m_pMC->m_pPView->SelchangeSnimi();
}

void CPanttiApp::OnUpdateLainatHaltijanmuutos(CCmdUI* pCmdUI)
{
	TRACE("La nro: %ld\n", m_pMC->getLoanNumber());
	if ((m_pMC->getSelectedCustomerID() > 0) && (theApp.m_pMC->m_pDB->getCurrentLoan()->getRedemptionLoan()->getLoanStatus() == "A"))
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}


void CPanttiApp::setDBConnection()
{
	m_pAsetusRS = new CAsetusRS;
	try
	{
		m_pAsetusRS->Open();
		m_pdatabase = m_pAsetusRS->m_pDatabase; // asettaa m_pDatabase:n yleiseen käyttöön
		if (m_pAsetusRS->IsEOF()) // asetustietoja ei ole talletettu
		{
			m_bAsetusOK = FALSE;
			AfxMessageBox("Asetustietoja ei ole vielä talletettu!");
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pdatabase = NULL;
	}
}

CString CPanttiApp::buildReferenceNumberFor(long loanNr)
{
	CString Jono = "";
    CString sRtn = "";
	char temp[20];
	char buf[20];
    long summa = 0;
    long tarkiste = 0;
	int pituus = 0;
	int j = 0;

    int m[7];
	int kertoimet[7];
    for (int i=0; i<7; i++)
	{
		m[i]=0;
	}
	kertoimet[0] = 7;
	kertoimet[1] = 3;
	kertoimet[2] = 1;
	kertoimet[3] = 7;
	kertoimet[4] = 3;
	kertoimet[5] = 1;
	kertoimet[6] = 7;
	memset( buf, 0, sizeof(buf));

    sprintf(temp, "%ld", loanNr);
    Jono = temp;
    //
    // numerot siirretään merkkijonosta taulukkoon m[]
    //
	pituus = Jono.GetLength();
	TRACE("Pituus=%d\n", pituus);
    for (i=0; i < pituus; i++)
    {
      //TRACE("%s\n", Jono.Mid(Jono.GetLength()-i-1, 1));
      if (sscanf(Jono.Mid(Jono.GetLength()-i-1, 1), "%d", &m[i]) == EOF)
         break;
    }
    //
    //taulukossa olevat luvut kerrotaan
    // painoarvoilla oikealta lähtien
    // 731731731jne
    //
    for (i=0; i<pituus; i++)
	{
		TRACE("%d\n", m[i]);
		summa = summa + (m[i]*kertoimet[i]); //m[0]*7 + m[1]*3 + m[2]*1 + m[3]*7 + m[4]*3 + m[5]*1;
    }
	//
    //
    if (summa == (summa/10)*10)
      tarkiste = 0;
    else
      tarkiste = ((summa/10)+1)*10 - summa;

	TRACE("Summa=%d \n", summa);
	TRACE("Tarkiste=%d \n", tarkiste);

    //sprintf(temp, "%d%d %d%d%d%d%d", m[5],m[4],m[3],m[2],m[1],m[0],tarkiste);
	j += sprintf(buf + j, "%d", tarkiste);
	for (i=0; i<pituus; i++)
	{
		TRACE("%d\n", m[i]);
		j += sprintf(buf + j, "%d", m[i]);
	}
	//TRACE("buf=%s\n", buf);
    j = 0;
	Jono = buf;
	for (i=0; i<Jono.GetLength(); i++)
	{
		//TRACE("%d\n", Jono.GetLength()-i-1);
		//TRACE("%s\n", Jono.Mid(Jono.GetLength()-i-1, 1));
		j += sprintf(temp + j, "%s", Jono.Mid(Jono.GetLength()-i-1, 1));
		//TRACE("%s\n", temp);
	}
	Jono = temp;
	memset( buf, 0, sizeof(buf));
	j = 0;
	for (i=0; i<Jono.GetLength(); i++)
	{
		if ((i == (Jono.GetLength()-5)) || (i == (Jono.GetLength()-10)))
		{
			j += sprintf(buf + j, " ");
		}
		j += sprintf(buf + j, "%s", Jono.Mid(i, 1));
	}
	sRtn = buf;
	return sRtn;
}

void CPanttiApp::OnRaportitKassaloki() 
{
	m_pMC->showDeskLog();
}

double CPanttiApp::euroToMk(double dEuro)
{
	return 5.94573*dEuro;
}

double CPanttiApp::mkToEuro(double dMk)
{
	return dMk/5.94573;
}

CString CPanttiApp::showEuro(double dEuro, int iPrecision)
{
	CString stmp = "";
	switch (iPrecision)
	{
	case 0:
		stmp.Format("%7.0f", dEuro);
			break;
	case 1:
		stmp.Format("%7.1f", dEuro);
			break;
	case 2:
		stmp.Format("%7.2f", dEuro);
			break;
	case 3:
		stmp.Format("%7.3f", dEuro);
			break;
	case 4:
		stmp.Format("%7.1f", dEuro);
			break;
	default:
		stmp.Format("%f", dEuro);
	}
	return stmp;
}


CString CPanttiApp::dot(CString s)
{
	//TRACE("'%s'->", s);
	//for (int i = 0; i < s.GetLength(); i++)
	//{
	//	if (s.Mid(i, 1) == ",")
	s.Replace(",", ".");
	//}
	//TRACE("'%s'\n", s);
	return s;
}


void CPanttiApp::OnHuutokauppaHuutokauppa() 
{
	m_pMC->auctionDlg();
	m_pMC->m_pPView->SelchangeSnimi();
}

BOOL CPanttiApp::isSame(double da, double db)
{
	BOOL brtn = FALSE;
	if (da < 0)
		da = -da;
	if (db < 0)
		db = -db;

	if (da > db)
	{
		if ( da - db < 0.0000001)
			brtn = TRUE;
	}
	else
	{
		if ( db - da < 0.0000001)
			brtn = TRUE;
	}

	return brtn;
}

void CPanttiApp::OnRaportitKirje1() 
{
	CString msg = "";
	msg.Format("Tulostetaanko muistutuskirjeet #1 voimassaolevan muistutuslistan mukaisesti?");
	if (AfxMessageBox(msg, MB_YESNO) == IDYES) // IDNO)
	{
		this->m_pMC->printRemainderNr1();
	}
}

void CPanttiApp::OnRaportitKirje2() 
{
	CString msg = "";
	msg.Format("Tulostetaanko muistutuskirjeet #2 voimassaolevan muistutuslistan mukaisesti?");
	if (AfxMessageBox(msg, MB_YESNO) == IDYES) // IDNO)
	{
		this->m_pMC->printRemainderNr2();	
	}
}

void CPanttiApp::OnRaportitUusikuitti() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	this->m_pMC->printNewTicket(this->m_pPrintRes);
}

void CPanttiApp::OnUpdateRaportitUusikuitti(CCmdUI* pCmdUI) 
{
	TRACE("La nro: %ld\n", m_pMC->getLoanNumber());
	if ((m_pMC->getSelectedCustomerID() > 0) && 
			((theApp.m_pMC->m_pDB->getCurrentLoan()->getRedemptionLoan()->getLoanStatus() == "A") ||
			 (theApp.m_pMC->m_pDB->getCurrentLoan()->getRedemptionLoan()->getLoanStatus() == "H"))
			)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateHallintaArviomiehet(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);	
}

void CPanttiApp::OnUpdateHallintaTuotteet(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateHallintaKassat(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateHallintaKassansaldo(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateHallintaAsetukset(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateRaportitMuistutuskirjeet(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateRaportitKirje1(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateRaportitKirje2(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateHuutokauppaHakulista(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateHuutokauppaSiirtohuutokauppaan(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateHuutokauppaYlijmkirjeet(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnUpdateHuutokauppaYlijmnkuittlainaamolle(CCmdUI* pCmdUI) 
{
	if (this->m_bAdminUser == TRUE)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiApp::OnAsiakkaatHenktunnus() 
{
	theApp.m_pMC->m_pPView->moveToHenkTun();
}


//
// ---- eräpäivä ---
//
CTime CPanttiApp::getDueDate()
{
	int iYears = 0;
	int iMonths = 0;
	CTimeSpan t2days(2,0,0,0);
	CTimeSpan t1days(1,0,0,0);
	
	if (CTime::GetCurrentTime().GetMonth() + this->GetAs()->m_AT_LainaAika > 24)
	{
		iYears = 2;
		iMonths = CTime::GetCurrentTime().GetMonth() + this->GetAs()->m_AT_LainaAika - 24;
	}
	else if (CTime::GetCurrentTime().GetMonth() + this->GetAs()->m_AT_LainaAika > 12)
	{
		iYears = 1;
		iMonths = CTime::GetCurrentTime().GetMonth() + this->GetAs()->m_AT_LainaAika - 12;
	}
	else
	{
		iYears = 0;
		iMonths = CTime::GetCurrentTime().GetMonth() + this->GetAs()->m_AT_LainaAika;
	}
	/*
	CTime tdd((CTime::GetCurrentTime().GetYear()), 
		(CTime::GetCurrentTime().GetMonth()) + this->GetAs()->m_AT_LainaAika, 
		(CTime::GetCurrentTime().GetDay()), 
		0,
		0,
		0);
	*/
	
	CTime tdd((CTime::GetCurrentTime().GetYear()) + iYears, 
		iMonths, 
		(CTime::GetCurrentTime().GetDay()), 
		0,
		0,
		0);
	TRACE("getDueDate: %s (pv=%d)\n", tdd.Format("%d.%m.%Y, klo: %H.%M.%S"), tdd.GetDayOfWeek());
	if (tdd.GetDayOfWeek() == 7) // lauantai
	{
		tdd = tdd + t2days;
	}
	else if (tdd.GetDayOfWeek() == 1) // sunnuntai
	{
		tdd = tdd + t1days;
	}

	TRACE("getDueDate: %s (pv=%d)\n", tdd.Format("%d.%m.%Y, klo: %H.%M.%S"), tdd.GetDayOfWeek());
	//CTimeSpan lainaaika = tdd - CTime::GetCurrentTime();
	//TRACE("getDueDate: %ld\n", lainaaika.GetDays());

	return tdd;
}

void CPanttiApp::OnUpdateHuutokauppaAllevuodenvanhatylijmt(CCmdUI* pCmdUI) 
{
	TRACE("Lainan nro: %ld\n", m_pMC->getLoanNumber());
	if (m_pMC->getLoanNumber() > 0 && theApp.m_pMC->m_pActl->getCustomerPayableAuctionBalance() > 0.01)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CPanttiApp::OnHuutokauppaAllevuodenvanhatylijmt() 
{
	theApp.m_pMC->m_pActl->showYjTilitys();
}

