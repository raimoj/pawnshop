// PanttiView.cpp : implementation of the CPanttiView class
//

#include "stdafx.h"
#include "Pantti.h"

#include "PanttiDoc.h"
#include "PanttiView.h"
//#include "DlgUusiLaina.h"
#include "DlgLunastus.h"
#include "DlgUudistus.h"
#include "DlgVakuusmuutos.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;



/////////////////////////////////////////////////////////////////////////////
// CPanttiView

IMPLEMENT_DYNCREATE(CPanttiView, CFormView)

BEGIN_MESSAGE_MAP(CPanttiView, CFormView)
	//{{AFX_MSG_MAP(CPanttiView)
	ON_CBN_SELCHANGE(IDC_SNIMI, OnSelchangeSnimi)
	ON_BN_CLICKED(IDC_ETSI, OnEtsi)
	ON_BN_CLICKED(IDC_ETSI_LAINA, OnEtsiLaina)
	ON_BN_CLICKED(IDC_UUSI_LAINA, OnUusiLaina)
	ON_BN_CLICKED(IDC_KUITTI, OnKuitti)
	ON_BN_CLICKED(IDC_LUNASTUS, OnLunastus)
	ON_BN_CLICKED(IDC_UUDISTUS, OnUudistus)
	ON_BN_CLICKED(IDC_VAKMUUTOS, OnVakmuutos)
	ON_COMMAND(ID_LAINAT_UUSILAINA, OnLainatUusilaina)
	ON_BN_CLICKED(IDC_CLEAR_SJONO, OnClearSjono)
	ON_BN_CLICKED(IDC_TYHJENNA, OnTyhjenna)
	ON_BN_CLICKED(IDC_TALLENNA, OnTallenna)
	ON_BN_CLICKED(IDC_KORJAA, OnKorjaa)
//	ON_LBN_DBLCLK(IDC_SUORITUSJONO, OnDblclkSuoritusjono)  TILAPƒISESTI POIS KAYTOSTA, pitaa korjata lainarivikirjaus korotus/lyhennys tap
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_VKEYTOITEM()
	ON_BN_CLICKED(IDC_REMOVE_SJONORIVI, OnRemoveSjonorivi)
	ON_BN_CLICKED(IDC_LAINAN_TAPAHTUMAT, OnLainanTapahtumat)
	ON_BN_CLICKED(IDC_SP2, OnSp2)
	ON_BN_CLICKED(IDC_SP1, OnSp1)
	ON_COMMAND(ID_LAINAT_LAINANMITTINTI, OnLainatCancelEvent)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_LAINANMITTINTI, OnUpdateLainatCancelEvent)
	ON_COMMAND(ID_LAINAT_LUNASTUS, OnLainatLunastus)
	ON_COMMAND(ID_LAINAT_UUDISTUS, OnLainatUudistus)
	ON_COMMAND(ID_LAINAT_VAKUUSMUUTOS, OnLainatVakuusmuutos)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_UUSILAINA, OnUpdateLainatUusilaina)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_LUNASTUS, OnUpdateLainatLunastus)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_UUDISTUS, OnUpdateLainatUudistus)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_VAKUUSMUUTOS, OnUpdateLainatVakuusmuutos)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_KOROT_JA_SHV_KULUT, OnKorotJaShvKulut)
	ON_COMMAND(ID_ETSI_ETSIASIAKAS, OnEtsiEtsiasiakas)
	ON_COMMAND(ID_ETSI_TYHJENNASIAKASTIED, OnEtsiTyhjennasiakastied)
	ON_COMMAND(ID_ETSI_ETSILAINA, OnEtsiEtsilaina)
	ON_COMMAND(ID_ASIAKKAAT_TALLETAUUSIASIAKAS, OnAsiakkaatTalletauusiasiakas)
	ON_COMMAND(ID_ASIAKKAAT_TALLETAMUUTTUNEETASIAKASTIEDOT, OnAsiakkaatTalletamuuttuneetasiakastiedot)
	ON_COMMAND(ID_LAINAT_TULOSTAKUITITSUORITJONONTAP, OnLainatTulostakuititsuoritjonontap)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_TULOSTAKUITITSUORITJONONTAP, OnUpdateLainatTulostakuititsuoritjonontap)
	ON_COMMAND(ID_LAINAT_LAINANKULUT, OnLainatLainankulut)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_LAINANKULUT, OnUpdateLainatLainankulut)
	ON_COMMAND(ID_LAINAT_LAINANTAPAHTUMAT, OnLainatLainantapahtumat)
	ON_UPDATE_COMMAND_UI(ID_LAINAT_LAINANTAPAHTUMAT, OnUpdateLainatLainantapahtumat)
	ON_EN_UPDATE(IDC_HTUN, OnUpdateHtun)
	ON_COMMAND(ID_ASETUKSET_TYHJENNRUUTU, OnAsetuksetTyhjennruutu)
	ON_CONTROL(RJ_OG_PARENT_DLG, IDC_CUSTOM_GRIDLAINAT, OnShowPawnTicketNumber)
	ON_COMMAND(ID_ASIAKKAAT_OSOITE, OnAsiakkaatOsoite)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanttiView construction/destruction

CPanttiView::CPanttiView()
	: CFormView(CPanttiView::IDD)
{
	//{{AFX_DATA_INIT(CPanttiView)
	m_sHtun = _T("");
	m_sKatuos = _T("");
	m_sPtp = _T("");
	m_sHuom = _T("");
	m_sLainanumero = _T("");
	m_sVakuusarvo = _T("");
	m_sLainasumma = _T("");
	m_sSuoritusjononSumma = _T("");
	m_bKielto = FALSE;
	m_iSp = 0 /*-1*/; // naiset oletusarvona
	m_bRuotsHTun = FALSE;
	m_bEiMuist = FALSE;
	m_sTilastoTxt1 = _T("");
	m_sTilastoTxt2 = _T("");
	m_sLainojaYht = _T("");
	m_sUserInfo = _T("");
	m_SEdit = _T("");
	m_sLoppusummaEuroina = _T("");
	//}}AFX_DATA_INIT

	m_sUserInfo = theApp.m_sUser + "\n" + theApp.m_sDesk + "\n" + theApp.m_sODBCDataSource;
	m_lAsId = 0;
	dSuoritusjononSumma = 0.0;

	theApp.m_pMC = new CMC(this);

	m_pAsSet = theApp.m_pMC->getCurrentCustomerSet();
	m_pAsSet->m_pDatabase = theApp.GetDatabase();

	/*m_brBack.CreateSolidBrush(RGB(255, 255, 0)); //kirkkaan keltainen
	//m_brBack.CreateSolidBrush(RGB(128, 128, 64)); // ruskeanvihre‰ :)
	m_brBack2.CreateSolidBrush(RGB(128, 255, 255)); // vaaleansininen
	m_brBack3.CreateSolidBrush(RGB(255, 255, 255)); // valk
	m_brBack4.CreateSolidBrush(RGB(64, 128, 128)); // wind t vihr
	*/
}

CPanttiView::~CPanttiView()
{
	theApp.m_pMC->ClearQueueList();

	if (theApp.m_pMC) delete theApp.m_pMC;
}

void CPanttiView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanttiView)
	DDX_Control(pDX, IDC_LAINANRO, m_ctlLainanumero);
	DDX_Control(pDX, IDC_SP1, m_ctlSP);
	DDX_Control(pDX, IDC_KOROT_JA_SHV_KULUT, m_ctlKorotJaSHVkulut);
	DDX_Control(pDX, IDC_HUOM, m_ctlHuom);
	DDX_Control(pDX, IDC_LAINAN_TAPAHTUMAT, m_ctlLainanTapahtumat);
	DDX_Control(pDX, IDC_PTP, m_ctlPtp);
	DDX_Control(pDX, IDC_KATUOS, m_ctlKatuos);
	DDX_Control(pDX, IDC_KUITTI, m_ctlKuitti);
	DDX_Control(pDX, IDC_VAKMUUTOS, m_ctlVakuusmuutos);
	DDX_Control(pDX, IDC_UUDISTUS, m_ctlUudistus);
	DDX_Control(pDX, IDC_LUNASTUS, m_ctlLunastus);
	DDX_Control(pDX, IDC_UUSI_LAINA, m_ctlUusiLaina);
	DDX_Control(pDX, IDC_SUORITUSJONO, m_ctlSuoritusjono);
	DDX_Control(pDX, IDC_SNIMI, m_ctlSnimi);
	DDX_Control(pDX, IDC_HTUN, m_ctlHtun);
	DDX_Control(pDX, IDC_ETSI, m_ctlEtsi);
	DDX_Text(pDX, IDC_HTUN, m_sHtun);
	DDX_Text(pDX, IDC_KATUOS, m_sKatuos);
	DDX_Text(pDX, IDC_PTP, m_sPtp);
	DDX_Text(pDX, IDC_HUOM, m_sHuom);
	DDX_Text(pDX, IDC_LAINANRO, m_sLainanumero);
	DDX_Text(pDX, IDC_VAKUUSARVO, m_sVakuusarvo);
	DDX_Text(pDX, IDC_LAINASUMMA, m_sLainasumma);
	DDX_Text(pDX, IDC_SUORITUSJONON_SUMMA, m_sSuoritusjononSumma);
	DDX_Check(pDX, IDC_KIELTO, m_bKielto);
	DDX_Radio(pDX, IDC_SP1, m_iSp);
	DDX_Check(pDX, IDC_RUOTS_HTUN, m_bRuotsHTun);
	DDX_Check(pDX, IDC_EI_MUIST, m_bEiMuist);
	DDX_Text(pDX, IDC_TILASTOTXT1, m_sTilastoTxt1);
	DDX_Text(pDX, IDC_TILASTOTXT2, m_sTilastoTxt2);
	DDX_Text(pDX, IDC_LAINOJAYHT, m_sLainojaYht);
	DDX_Text(pDX, IDC_USERINFO, m_sUserInfo);
	DDX_Text(pDX, IDC_LOPPSUMMA_EUROINA, m_sLoppusummaEuroina);
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX, &m_wndLainaGrid);
}

BOOL CPanttiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CPanttiView::OnInitialUpdate()
{

	int i=0;
	CString rivi="";
	TRACE("pDoc=%ld\n", GetDocument());
	theApp.m_pDoc = GetDocument();


	// --- orig ----
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	

	// --- GRID LAINANUMEROT ----
	// seuraavat rivit tarvitaan gridin n‰ytt‰miseksi
	m_wndLainaGrid.SubclassDlgItem(IDC_CUSTOM_GRIDLAINAT, this);
	m_wndLainaGrid.Initialize();
	//
	// esimerkiksi r2s2 asetetaan valintalistaksi !
	// m_wndLainaGrid.SetStyleRange(CGXRange(2, 2), CGXStyle()
	//		.SetControl(GX_IDS_CTRL_TEXTFIT)
	//		.SetChoiceList(_T("one\ntwo\nthree\nfour\nfive\nsix\nseven\neight"))
	//	);

	// --- GRID LAINARIVIT ----
	// seuraavat rivit tarvitaan gridin n‰ytt‰miseksi
	m_wndLainaRivitGrid.SubclassDlgItem(IDC_CUSTOM_GRID_LAINARIVIT, this);
	m_wndLainaRivitGrid.Initialize();

	// ---- dlg-komponentit ---
	/*for(int i=1; i<=1000; i++)
	{
		rivi.Format("%s %d", "Test string",i);
		m_ctlCombo1.AddString(rivi);
	}*/

	m_brBack.CreateSolidBrush(RGB(255, 255, 0)); //kirkkaan keltainen
	//m_brBack.CreateSolidBrush(RGB(128, 128, 64)); // ruskeanvihre‰ :)
	m_brBack2.CreateSolidBrush(RGB(128, 255, 255)); // vaaleansininen
	m_brBack3.CreateSolidBrush(RGB(255, 255, 255)); // valk
	//m_brBack4.CreateSolidBrush(RGB(166, 202, 240)); // sky blue
	//m_brBack4.CreateSolidBrush(RGB(132, 152, 204)); // sky blue (DARKER)
	m_brBack4.CreateSolidBrush(RGB(160, 200, 184)); // sky GREEN !

	//
	// ---- komponenttikohtaiset sˆyttˆrajoitteet ---
	//
	m_ctlHtun.LimitText(11);
	m_ctlSnimi.LimitText(50);
	m_ctlKatuos.LimitText(50);
	m_ctlPtp.LimitText(50);
	//m_ctlPuh1.LimitText(20);
	//m_ctlPuh2.LimitText(20);
	m_ctlHuom.LimitText(255);


	/*m_pAsSet->m_strSort = "AS_Nimi";
	m_pAsSet->m_strFilter.Format("AS_Sp=0"); // Valitaan aluksi vain naiset !
	TRACE("Filter=%s\n", m_pAsSet->m_strFilter);
	try
	{
		m_pAsSet->Open();
		while (!m_pAsSet->IsEOF())
		{
			TRACE("ASID=ld,", m_pAsSet->m_AS_ID);
			TRACE(" Nimi=%s\n", m_pAsSet->m_AS_Nimi);
			m_ctlSnimi.SetItemData(
      			m_ctlSnimi.InsertString(-1, m_pAsSet->m_AS_Nimi),
      			m_pAsSet->m_AS_ID);
			m_pAsSet->MoveNext();
		}
		m_pAsSet->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}


	//MessageBeep(0);
	TRACE("Rivej‰=%d\n", m_ctlSnimi.GetCount());*/
	UpdateButtons(T_BEG); // T_BEG/T_ALKU/T_LIS/T_ENS/T_VII/T_OK/T_TYH
	//OnEtsi();
}

/////////////////////////////////////////////////////////////////////////////
// CPanttiView printing

BOOL CPanttiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPanttiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPanttiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPanttiView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CPanttiView diagnostics

#ifdef _DEBUG
void CPanttiView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPanttiView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPanttiDoc* CPanttiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPanttiDoc)));
	return (CPanttiDoc*)m_pDocument;
}
#endif //_DEBUG


////////////////////////////////////////////////////////////////////////////
// CPanttiView message handlers

void CPanttiView::OnSelchangeSnimi()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString msg = "";
	CString sTmp = "";
	int j=0;
	ROWCOL nRow, nCol;

    m_pAsSet->m_strFilter = "";

	m_lAsId = m_ctlSnimi.GetItemData(m_ctlSnimi.GetCurSel());
	TRACE("lAsId=%ld\n", m_lAsId);
	theApp.m_pMC->setSelectedCustomer(m_lAsId);
	m_pAsSet->setCurrentCustomerID(m_lAsId);
	/*j  = sprintf(buf,     "%s", "AS_ID=");
	j += sprintf(buf + j, "%ld", m_lAsId);
	TRACE("Filter=%s\n", buf);*/

	m_pAsSet->Close();
	//m_pAsSet->m_strFilter = buf;
	m_pAsSet->m_strFilter.Format("AS_ID=%d", (int)m_lAsId);
	TRACE("Filter=%s\n", m_pAsSet->m_strFilter);
	//m_pAsSet->m_strSort = "AS_Nimi";
	try
	{
		m_pAsSet->Open();

		if (m_pAsSet->m_AS_Sp == TRUE) // // -1/Yes/TRUE=Nainen, 0/FALSE=Mies
		{
			m_iSp = 0; // k‰yttˆliittym‰ss‰ k‰sitell‰‰n sp arvoilla 0 ja 1
		}
		else
		{
			m_iSp = 1;
		}
		m_sHtun = m_pAsSet->m_AS_HTun;
		m_bRuotsHTun = m_pAsSet->m_AS_RuotsHTun;
		//m_sEnimi = m_pAsSet->m_AS_ENimi;
		m_sKatuos = m_pAsSet->m_AS_KatuOs;
		m_sPtp = m_pAsSet->m_AS_Ptp;
		//m_sPuh1 = m_pAsSet->m_AS_Puh1;
		//m_sPuh2 = m_pAsSet->m_AS_Puh2;
		if (m_pAsSet->m_AS_Kielto == 0)
		{
			m_bKielto = FALSE;
		}
		else
		{
			m_bKielto = TRUE;
			MessageBeep(1);
			msg = "Valitulla asiakkaalla on lainauskielto";
			if (AfxMessageBox(msg/*, MB_YESNO*/) == IDYES /*IDNO*/)
			{
			}
		}
		m_dMaksetutYlij = 0;
		m_dMaksetutAlij = 0;
		if (!m_pAsSet->IsFieldNull(&m_pAsSet->m_AS_Ylij))
			m_dMaksetutYlij = m_pAsSet->m_AS_Ylij;
		if (!m_pAsSet->IsFieldNull(&m_pAsSet->m_AS_Alij))
			m_dMaksetutAlij = m_pAsSet->m_AS_Alij;
		if (m_pAsSet->m_AS_MuistEsto == 0)
		{
			m_bEiMuist = FALSE;
		}
		else
		{
			m_bEiMuist = TRUE;
		}

		m_sHuom = m_pAsSet->m_AS_Huom;

		m_pAsSet->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsSet->Close();
		return;
	}

	// Valittu uusi asiakas => Lainat n‰kyviin !
	TRACE("Lainat henkilˆtunnukselle %s\n", m_sHtun);
	m_wndLainaRivitGrid.clear();
	m_wndLainaGrid.clear();

	m_sLainanumero = m_wndLainaGrid.ShowPawnTicketNumbers(m_lAsId);
	if (!m_sLainanumero.IsEmpty())
	{
		m_wndLainaGrid.GetCurrentCell(nRow, nCol);
		m_sVakuusarvo.Format("%7.2f",atof(m_wndLainaGrid.GetValueRowCol(nRow,6)));
		m_sLainasumma.Format("%7.2f",atof(m_wndLainaGrid.GetValueRowCol(nRow,7)));
		//m_wndLainaRivitGrid.ShowPawnContent(m_sLainanumero);
		theApp.m_pMC->showPawnContent(m_sLainanumero, &m_wndLainaRivitGrid); // n‰ytt‰‰ lainarivit
		UpdateButtons(T_AOK_LOK); // T_BEG/T_AOK_LNOK/T_AOK_LOK
	}
	else
	{
		m_sVakuusarvo="";
		m_sLainasumma="";
		UpdateButtons(T_AOK_LNOK); // T_BEG/T_AOK_LNOK
	}
	showSelectedLoanNumber();
	
	CCustomerStatistics* pcs = theApp.m_pMC->getCustomerStatistics(m_lAsId);
	//CCustomerStatistics* pcs = new CCustomerStatistics(lCustomerID, this, m_pMC);
	TRACE("CuStat: Ylij‰‰m‰=%f\n", pcs->m_dAuctionBalance);
	TRACE("CuStat: Alij‰‰m‰=%f\n", pcs->m_dAuctionDeficit);
	TRACE("CuStat: Lainoja myyty HK:ssa=%ld\n", pcs->m_iLoansInAuction);

	//
	sTmp.Format("LainojaYht %ld kpl [%7.2fe]    A=%ld kpl [%7.2fe]    L=%ld", 
			m_wndLainaGrid.m_lLainojaKpl, 
			m_wndLainaGrid.m_dLainojaYhtEuro,
			m_wndLainaGrid.m_lAktiivisiaKpl,
			m_wndLainaGrid.m_dAktLainojaYhtEuro,
			m_wndLainaGrid.m_lLunastetutKpl);
	m_sLainojaYht = sTmp;
	//sTmp.Format("Ylij‰‰m‰ = %7.2f, Alij‰‰m‰ = %7.2f", cs.m_dAuctionBalance, cs.m_dAuctionDeficit);
	sTmp.Format("MaksamatonYlij‰‰m‰(<1v)=%7.2f, Alij= %7.2f",
				pcs->m_dPayableAuctionBalance /*cs.m_dAuctionBalance*//* - m_dMaksetutYlij*/, 
				pcs->m_dAuctionDeficit/* - m_dMaksetutAlij*/);
	m_sTilastoTxt1 = sTmp;
	sTmp.Format("Lainoja HK:ssa yht %d kpl = %7.2fe", pcs->m_iLoansInAuction, pcs->m_dAuctionSum);
	m_sTilastoTxt2 = sTmp;

	if (theApp.m_pMC->clearQueue() == true)
		this->UpdateQueue();
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}


void CPanttiView::OnEtsi() // asiakastietojen perusteella
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString sFind;
	char	buf[50];
	int		j=0;
	long lkm = 0;
	CString msg="";
	CString ehto1="";
	CString sFilter1 = "";
	
	memset( buf, 0, sizeof(buf));
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	//TRACE("Etsit‰‰n: %s\n", this->m_sHtun);
	if (m_sHtun.GetLength() > 10)
	{
		if (  (m_sHtun.Left(1) >= 0x30) && (m_sHtun.Left(1) < 0x40) ) // teksti alkaa numerolla -> varmaankin HTunnus
		{
			m_ci.GetHtun(m_sHtun, this->m_bRuotsHTun);
		}
	}
	if ( m_sHtun == "")
	{
		TRACE("Ei hakuehtoa => Valitaan kaikki miesten tai naisten nimet\n");
		if (m_iSp == 0)
			j  = sprintf(buf,     "AS_Sp=1");
		else
			j  = sprintf(buf,     "AS_Sp=0");
	}
	else
	{
		sFind = m_sHtun.GetAt(0);
		TRACE("Ensimm: %s\n", sFind);
		if (sFind == "0" || sFind == "1" || sFind == "2" || sFind == "3" || sFind == "4" || sFind == "5" ||
			sFind == "6" || sFind == "7" || sFind == "8" || sFind == "9")
		{
			TRACE("Henkilˆtunnus:\n");
			ehto1 = "[Htun=" + m_sHtun + "]";
			j  = sprintf(buf,     "%s", "AS_HTun LIKE '");
			j += sprintf(buf + j, "%s", m_sHtun);
			j += sprintf(buf + j, "%s", "%'"); // Access k‰ytt‰‰ *-merkki‰ jokerimerkkin‰
			TRACE("Hakuehto:'%s'\n", buf);
		}
		else
		{
			TRACE("Nimi:\n");
			ehto1 = "[Nimi="+ m_sHtun + "]";
			j  = sprintf(buf,     "%s", "AS_Nimi LIKE '");
			j += sprintf(buf + j, "%s", m_sHtun); //m_sHtun sis. nimen tai sen alkuosan
			j += sprintf(buf + j, "%s", "%'");  // Access k‰ytt‰‰ *-merkki‰ jokerimerkkin‰
		}
		sFilter1 = buf;
	}
	TRACE("Filter=%s\n", buf);
	sFilter1 = buf;
	
	lkm = this->queryCustomerDB(sFilter1);
	if ( lkm == 0)
	{
		msg = "Asiakastietoja hakuehdolla\n" + ehto1 + "\n" + "\nei lˆydy asiakkaita!";
		AfxMessageBox(msg);
	}
	else if (lkm == 1)
	{
		m_ctlSnimi.SetCurSel(0);
		OnSelchangeSnimi();
	}
	else if (lkm > 1)
	{
		msg.Format("Hakuehdolla lˆytyi %ld asiakasta", lkm);
		AfxMessageBox(msg);
	}
	else
	{
		//m_iSp = -1;
		m_sKatuos = "";
		m_sPtp = "";
		//m_sPuh1 = "";
		//m_sPuh2 = "";
		m_bKielto = FALSE;
		m_sHuom = "";
		UpdateButtons(T_BEG); // T_BEG/T_ALKU/T_LIS/T_ENS/T_VII/T_OK/T_TYH
	}
	UpdateData(FALSE);	//dialog box is being initialized (FALSE)
	//UpdateButtons(T_AOK_LOK); // T_BEG/T_AOK_LNOK/T_AOK_LOK
}


long CPanttiView::queryCustomerDB(CString sFilter)
{
	long lkm = 0;
	m_pAsSet->m_strFilter = sFilter;
	m_pAsSet->m_strSort = "AS_Nimi";
	try
	{
		m_pAsSet->Open();
		//m_sHtun = m_pAsSet->m_AS_HTun;
		m_ctlSnimi.ResetContent();
		while (!m_pAsSet->IsEOF())
		{
			m_ctlSnimi.SetItemData(
      			m_ctlSnimi.InsertString(-1, m_pAsSet->m_AS_Nimi),
      			m_pAsSet->m_AS_ID);
			lkm++;
			m_pAsSet->MoveNext();
		}
		m_pAsSet->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsSet->Close();
	}
	return lkm;
}




void CPanttiView::OnShowPawnTicketNumber()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	ROWCOL nRow, nCol;
    if (m_wndLainaGrid.GetCurrentCell(nRow, nCol)) // valittu asiallinen laina
	{
		if (nRow >=1)
		{
			TRACE("Rivi %d\n", nRow);
			m_sLainanumero = m_wndLainaGrid.GetValueRowCol(nRow,1);
			//
			//
			//
			m_sVakuusarvo.Format("%7.2f",atof(m_wndLainaGrid.GetValueRowCol(nRow,6)));
			m_sLainasumma.Format("%7.2f",atof(m_wndLainaGrid.GetValueRowCol(nRow,7)));

			sLainanTila = m_wndLainaGrid.GetValueRowCol(nRow,5);
			if (sLainanTila == "A")					// "A" = Aktiivinen laina
			{
				UpdateButtons(T_AOK_LOK);
			}
			else if (sLainanTila == "L" ||			// "L" = Lunastus
				    sLainanTila == "T" ||			// "O" = ??? -> "T" = luottotappio
					sLainanTila == "H" ||			// "H" = Huutokauppa
					sLainanTila == "M" )			// "M" = Myyty HK:ssa
			{
				UpdateButtons(T_AOK_LHK);
			}
			else
			{
				UpdateButtons(T_AOK_LOK); // T_BEG/T_AOK_LNOK/T_AOK_LOK
			}
			m_wndLainaGrid.setRowBoldFont(nRow);
		}
	}
	else
	{
		m_sLainanumero = "";			//jos ei yht‰‰n rivi‰ niin ...
		UpdateButtons(T_AOK_LNOK); // T_BEG/T_AOK_LNOK
	}
	UpdateData(FALSE);	//dialog box is being initialized (FALSE)
	//m_wndLainaRivitGrid.ShowPawnContent(m_sLainanumero);
	theApp.m_pMC->showPawnContent(m_sLainanumero, &m_wndLainaRivitGrid);
	showSelectedLoanNumber();
}


void CPanttiView::OnEtsiLaina()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int i=0;
	int j=m_ctlSnimi.GetCount();
	long lLainaID=0;
	long lTmp = 0;
	CString msg;
	CString nimi;
	char buf[150];

	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	//ASSERT( !m_sLainanumero.IsEmpty() );

	lLainaID = atol(m_ci.RemoveSpaces(m_sLainanumero));
	if ((m_sLainanumero.IsEmpty()) || (lLainaID <= 0))
	{
		//MessageBeep(1);
		return;
	}
	//
	// etsit‰‰n lainan asiakasID
	m_lAsId = theApp.m_pMC->m_pDB->GetPawnTicketOwner(lLainaID);
	TRACE("lAsId=%ld\n", m_lAsId);
	if(m_lAsId <= 0)
	{
		msg.Format("Lainanumeroa %ld ei lˆydy!\nAsiakastunnus: %ld", lLainaID, m_lAsId);
		AfxMessageBox(msg);
		return;
	}
	OnTyhjenna();
	m_ctlSnimi.ResetContent();

	m_pAsSet->m_strFilter = "";
	j  = sprintf(buf,     "%s", "AS_ID=");
	j += sprintf(buf + j, "%ld", m_lAsId);
	TRACE("Filter=%s\n", buf);
	m_pAsSet->m_strFilter = buf;

	try
	{
		m_pAsSet->Open();
		if (m_pAsSet->IsEOF())
		{
			msg.Format("Asiakastunnusta '%ld' ei lˆydy", m_lAsId);
			AfxMessageBox(msg);
			m_pAsSet->Close();
			return;
		}
		else
		{
			if (m_pAsSet->m_AS_Sp == FALSE) // mies
				m_iSp = 0;
			else
				m_iSp = 1;
			m_sHtun = m_pAsSet->m_AS_HTun.Left(11);
			
			m_bRuotsHTun = m_pAsSet->m_AS_RuotsHTun;
			m_ctlSnimi.SetWindowText(m_pAsSet->m_AS_Nimi);
			m_sKatuos = m_pAsSet->m_AS_KatuOs;
			m_sPtp = m_pAsSet->m_AS_Ptp;

			if (m_pAsSet->m_AS_Kielto == 1 )
			{
				m_bKielto = TRUE;
			}
			else
			{
				m_bKielto = FALSE;
			}
			m_sHuom = m_pAsSet->m_AS_Huom;
		}
		m_pAsSet->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsSet->Close();
	}
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	OnEtsi(); // ko asiakkaan kaikki lainat
	m_wndLainaGrid.setDefaultFont();
	if (m_wndLainaGrid.FindRow(lLainaID, TRUE) != TRUE) // etsi asiakkaan lainoista se haluttu laina
	{
		msg.Format("Lainaa %ld ei lˆydy!", lLainaID);
		AfxMessageBox(msg);
		//UpdateButtons(T_AOK_LNOK); // T_BEG/T_AOK_LNOK
	}
	else
	{
		//UpdateButtons(T_AOK_LOK); // T_BEG/T_AOK_LNOK/T_AOK_LOK
	}

	if (sLainanTila == "L" ||			// "L" = Lunastus
			sLainanTila == "T" ||			// "O" = ??? -> "T" = luottotappio
			sLainanTila == "H" ||			// "H" = Huutokauppa
			sLainanTila == "M" )			// "M" = Myyty HK:ssa
	{
		UpdateButtons(T_AOK_LHK);
	}
	else
		UpdateButtons(T_AOK_LOK); // T_BEG/T_AOK_LNOK/T_AOK_LOK
}


void CPanttiView::showSelectedLoanNumber()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	//TRACE("Valittu lainanumero = %s\n", m_sLainanumero);
	long lNr = atol(m_ci.RemoveSpaces(m_sLainanumero));
	CLoan* pLoan = theApp.m_pMC->m_pDB->setCurrentLoan(lNr);
	if (pLoan->getRedemptionLoan()->m_LA_Nr == lNr)
	{
		//TRACE("Laina valittu!\n");
		theApp.m_pMC->setLoanNumber(lNr);
	}
	else
	{
		//TRACE("Virhe lainan hakemisessa!\n");
		theApp.m_pMC->setLoanNumber(0);
	}
	if (theApp.m_pMC->isLoanBanned())
	{
		UpdateButtons(T_AOK_LKIELTO);
	}
	else if (!m_sLainanumero.IsEmpty())
	{
		//m_wndLainaGrid.GetCurrentCell(nRow, nCol);
		//m_sVakuusarvo.Format("%7.2f",atof(m_wndLainaGrid.GetValueRowCol(nRow,6)));
		//m_sLainasumma.Format("%7.2f",atof(m_wndLainaGrid.GetValueRowCol(nRow,7)));
		////m_wndLainaRivitGrid.ShowPawnContent(m_sLainanumero);
		//theApp.m_pMC->showPawnContent(m_sLainanumero, &m_wndLainaRivitGrid); // n‰ytt‰‰ lainarivit
		
		
		//UpdateButtons(T_AOK_LOK); // T_BEG/T_AOK_LNOK/T_AOK_LOK
	}
	else
	{
		//m_sVakuusarvo="";
		//m_sLainasumma="";
		UpdateButtons(T_AOK_LNOK); // T_BEG/T_AOK_LNOK
	}


#ifdef _DEBUG
	theApp.m_pMC->m_pDB->printCurrentLoan();
#endif //_DEBUG
}


void CPanttiView::OnUusiLaina()
{
	CString sn = "";
	CString msg = "";

	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	CString sHTun = "";
	if (!theApp.m_pMC->getCurrentCustomerSet()->isCustomerSelected())
	{
		msg.Format("Valitse ensin asiakas !");
		AfxMessageBox(msg);
		return;
	}
	sHTun = m_ci.RemoveSpaces(m_sHtun).Left(11);
	m_ctlSnimi.GetWindowText(sn);
	if (!theApp.m_pMC->NewPawnRequest(sHTun, m_lAsId, sn))
	{
		TRACE("New Pawn Request Error!!!!\n");
	}
	UpdateQueue();
	m_ctlKuitti.SetFocus();
}


void CPanttiView::OnLunastus()
{
	long ln = 0;
	ROWCOL nRow, nCol;
	CString sn = "";
	CString sHTun = "";
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	sHTun = m_ci.RemoveSpaces(m_sHtun).Left(11);
	m_ctlSnimi.GetWindowText(sn);
	if (m_wndLainaGrid.GetCurrentCell(nRow, nCol)) //jos ei yht‰‰n rivi‰ niin ...
	{
		ln = atol(m_wndLainaGrid.GetValueRowCol(nRow,1));
	}
	else
	{
		return;
	}
	if (!theApp.m_pMC->RedemptRequest(ln, sHTun, m_lAsId, sn))
	{
		TRACE("Redemption Request Error!!!!\n");
	}
	UpdateQueue();
	m_ctlKuitti.SetFocus();
	
}

void CPanttiView::OnUudistus()
{
	long ln = 0;
	ROWCOL nRow, nCol;
	CString sn = "";

	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	CString sHTun = "";
	sHTun = m_ci.RemoveSpaces(m_sHtun).Left(11);

	m_ctlSnimi.GetWindowText(sn);
	if (m_wndLainaGrid.GetCurrentCell(nRow, nCol)) //jos ei yht‰‰n rivi‰ niin ...
	{
		ln = atol(m_wndLainaGrid.GetValueRowCol(nRow,1));
	}

	if (!theApp.m_pMC->RenewRequest(ln, sHTun, m_lAsId, sn))
	{
		TRACE("RenewRequest Request Error!!!!\n");
	}
	UpdateQueue();
	m_ctlKuitti.SetFocus();
	

}

void CPanttiView::OnVakmuutos()
{
	long ln = 0;
	ROWCOL nRow, nCol;
	CString sn = "";
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	CString sHTun = "";
	sHTun = m_ci.RemoveSpaces(m_sHtun).Left(11);
	m_ctlSnimi.GetWindowText(sn);

	if (m_wndLainaGrid.GetCurrentCell(nRow, nCol)) //jos ei yht‰‰n rivi‰ niin ...
	{
		ln = atol(m_wndLainaGrid.GetValueRowCol(nRow,1));
	}

	if (!theApp.m_pMC->ChangeRequest(ln, sHTun, m_lAsId, sn))
	{
		TRACE("Change Request Error!!!!\n");
	}
	UpdateQueue();
		
	this->m_wndLainaGrid.updateLoanRowInfo(theApp.m_pMC->getLoanNumber());
	this->m_wndLainaGrid.FindRow(theApp.m_pMC->getLoanNumber());
	
	m_ctlKuitti.SetFocus();
	
}


void CPanttiView::OnKuitti()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString msg="";
	//msg.Format("Tulostetaanko kuitti kaikista jonon tapahtumista");
	//if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	//{
	//	return;
	//}
	theApp.m_pMC->PawnTicketRequest();
	UpdateQueue();
	
	this->m_sLainanumero.Format("%ld", theApp.m_pMC->getLoanNumber());
	if (theApp.m_pMC->getLoanNumber() == 0)
	{
		this->OnSelchangeSnimi();
	}

	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	this->OnEtsiLaina();
}


void CPanttiView::OnClearSjono()
{
	if (AfxMessageBox("Tyhjennet‰‰nkˆ suoritysjono ?", MB_YESNO) == IDYES)
	{
		//m_ctlSuoritusjono.ResetContent();
		theApp.m_pMC->ClearQueueList();
		UpdateQueue();

		dSuoritusjononSumma = 0.0;
		m_sSuoritusjononSumma = "";
		m_sLoppusummaEuroina = "";
		UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	}
}

void CPanttiView::OnTyhjenna()
{
	//m_iSp = -1;
	m_sHtun = "";
	m_bRuotsHTun = FALSE;
	m_sKatuos = "";
	m_sPtp = "";
	//m_sPuh1 = "";
	//m_sPuh2 = "";
	m_bKielto = FALSE;
	m_bEiMuist = FALSE;
	m_sHuom = "";
	m_ctlSnimi.SetCurSel(-1);
	this->m_ctlHtun.SetFocus();
	m_ctlLainanumero.Clear();
	m_sLainanumero = "";
	m_sLainojaYht = "";
	m_sTilastoTxt1 = "";
	m_sTilastoTxt2 = "";
	m_sLainasumma = "";
	m_sVakuusarvo = "";

	this->m_wndLainaGrid.clear();
	this->m_wndLainaRivitGrid.clear();

	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	UpdateButtons(T_BEG); // T_BEG/T_ALKU/T_LIS/T_ENS/T_VII/T_OK/T_TYH
	theApp.m_pMC->getCurrentCustomerSet()->setCurrentCustomerID(0);

	m_ctlLainanumero.SetFocus();
}


void CPanttiView::OnTallenna()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int j=0;
	int iRtn = 0;
	char buf[150];
	CString msg = "";
	CString sHTun = "";


	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	if (m_ci.CheckGender(m_sHtun) == TRUE) // TRUE; // naisilla parillinen
	{
		// m_iSp = -1 ei mik‰‰n, 0=naiset, 1 = miehet
		m_iSp = 0;
	}
	else
	{
		m_iSp = 1;
	}

	sHTun = m_ci.GetHtun(m_sHtun, this->m_bRuotsHTun, this->m_iSp);
	if (sHTun.IsEmpty())
	{
		sHTun = m_ci.RemoveSpaces(m_sHtun).Left(11);
		msg.Format("Tunnus '%s' ei ole oikein.\nHaluatko silti tallettaa asiakastiedot t‰ll‰ tunnuksella?", sHTun);
		if (AfxMessageBox(msg, MB_YESNO) == IDNO)
		{
			return;
		}
	}
	m_pAsSet->m_strFilter = "";
	j  = sprintf(buf,     "%s", "AS_HTun='");
	j += sprintf(buf + j, "%s", sHTun);
	j += sprintf(buf + j, "%s", "'");
	TRACE("Filter=%s\n", buf);
	m_pAsSet->m_strFilter = buf;

	try
	{
		m_pAsSet->Close();
		m_pAsSet->Open();
		if (!m_pAsSet->IsEOF())
		{
			msg.Format("Henkilˆtunnus '%s' on varattu!\nTalletusta ei voi tehd‰!", sHTun);
			AfxMessageBox(msg);
		}
		else
		{
			m_pAsSet->AddNew();

			if (m_iSp == 0) // nainen
				m_pAsSet->m_AS_Sp = TRUE;
			else
				m_pAsSet->m_AS_Sp = FALSE;
			m_pAsSet->m_AS_HTun = sHTun;
			m_pAsSet->m_AS_RuotsHTun = m_bRuotsHTun;
			m_ctlSnimi.GetWindowText(m_pAsSet->m_AS_Nimi);
			m_pAsSet->m_AS_ENimet = "";
			m_pAsSet->m_AS_KatuOs = m_sKatuos;
			m_pAsSet->m_AS_Ptp = m_sPtp;
			m_pAsSet->m_AS_Puh = "";
			if (m_bKielto == TRUE)
			{
				m_pAsSet->m_AS_Kielto = 1;
			}
			else
			{
				m_pAsSet->m_AS_Kielto = 0;
			}
			if (m_bEiMuist == FALSE )
			{
				m_pAsSet->m_AS_MuistEsto = 0;
			}
			else
			{
				m_pAsSet->m_AS_MuistEsto = 1;
			}
			m_pAsSet->m_AS_Huom = m_sHuom;
			m_pAsSet->m_AS_AsSuhtAlku = CTime::GetCurrentTime();

			m_pAsSet->Update();
			msg.Format("Henkilˆtunnus '%s' on talletettu!", sHTun);
			AfxMessageBox(msg);
		}
		m_pAsSet->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsSet->Close();
	}
	OnEtsi();
}

void CPanttiView::OnKorjaa()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int j=0;
	char buf[150];
	CString msg = "";
	CString sHTun = "";
	//m_lAsId = m_ctlSnimi.GetItemData(m_ctlSnimi.GetCurSel());
	m_lAsId = m_pAsSet->getCurrentCustomerID();
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	//TRACE("lAsId=%ld\n", m_lAsId);

	if (m_ci.CheckGender(m_sHtun) == TRUE) // TRUE; // naisilla parillinen
	{
		// m_iSp = -1 ei mik‰‰n, 0=naiset, 1 = miehet
		m_iSp = 0;
	}
	else
	{
		m_iSp = 1;
	}


	sHTun = m_ci.GetHtun(m_sHtun, this->m_bRuotsHTun, this->m_iSp);

	if (sHTun.IsEmpty())
	{
		sHTun = m_ci.RemoveSpaces(m_sHtun).Left(11);
		msg.Format("Tunnus '%s' ei ole oikein.\nHaluatko silti tallettaa asiakastiedot t‰ll‰ tunnuksella?", sHTun);
		if (AfxMessageBox(msg, MB_YESNO) == IDNO)
		{
			return;
		}
	}
	/*j  = sprintf(buf,     "%s", "AS_HTun='");
	j += sprintf(buf + j, "%s", sHTun);
	j += sprintf(buf + j, "%s", "'");
	TRACE("Filter=%s\n", buf);*/

	j  = sprintf(buf,     "%s", "AS_ID=");
	j += sprintf(buf + j, "%ld", m_lAsId);
	TRACE("Filter=%s\n", buf);
	m_pAsSet->m_strFilter = buf;
	try
	{
		m_pAsSet->Open();
		if (m_pAsSet->IsEOF())
		{
			msg.Format("Asiakastietoja ei lˆydy\nTalletatko uuden asiakkaan?");
			if (AfxMessageBox(msg, MB_YESNO) == IDYES)
			{
				m_pAsSet->Close();
				OnTallenna();
				return;
			}
		}
		else
		{
			m_pAsSet->Edit();

			if (m_iSp == 0) // nainen
				m_pAsSet->m_AS_Sp = TRUE;
			else
				m_pAsSet->m_AS_Sp = FALSE;
			m_pAsSet->m_AS_HTun = sHTun;
			m_pAsSet->m_AS_RuotsHTun = m_bRuotsHTun;
			m_ctlSnimi.GetWindowText(m_pAsSet->m_AS_Nimi);
			m_pAsSet->m_AS_ENimet = "";
			m_pAsSet->m_AS_KatuOs = m_sKatuos;
			m_pAsSet->m_AS_Ptp = m_sPtp;
			m_pAsSet->m_AS_Puh = "";
			if (m_bKielto == TRUE)
			{
				m_pAsSet->m_AS_Kielto = 1;
			}
			else
			{
				m_pAsSet->m_AS_Kielto = 0;
			}
			if (m_bEiMuist == FALSE )
			{
				m_pAsSet->m_AS_MuistEsto = 0;
			}
			else
			{
				m_pAsSet->m_AS_MuistEsto = 1;
			}
			m_pAsSet->m_AS_Huom = m_sHuom;

			m_pAsSet->Update();
			//msg.Format("Henkilˆtunnus '%s' on talletettu!", sHTun);
			//AfxMessageBox(msg);
		}
		m_pAsSet->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsSet->Close();
	}
	//OnEtsi();
}

int CPanttiView::UpdateButtons(int iState)
{
	switch(iState)
	{
		case T_BEG :
			EnableButtons( 0 );    // OK on ainoa aktiivinen painike ( aina aktiivinen)
         /*m_ctlInfo1.SetWindowText("Valitse asiakasryhm‰ ja asiakas,");
		   m_ctlInfo2.SetWindowText("tai kirjoita asiakkaan yhteystiedot !");
		   m_ctlInfo3.SetWindowText(""); */
			break;
		case T_AOK_LNOK :
			EnableButtons(  B_NEW );

			break;
		case T_AOK_LOK :
			EnableButtons(  B_NEW |
                         B_RDP |
						 B_RNW |
                         B_CHG |
						 B_EVN);

			break;

		case T_AOK_LHK : // asiakas valittu, laina valittu mutta se on huutokaupassa
			EnableButtons(  B_NEW |
                         B_EVN);
			break;

		case T_AOK_LKIELTO : // asiakas valittu, laina valittu mutta sille on m‰‰r‰tty kielto
			EnableButtons(  B_NEW |
                         B_CHG |
						 B_EVN);
			break;

		case T_AOK_LLUNOK :
			EnableButtons(  B_NEW |
						 B_EVN);

			break;

	}
	if (theApp.m_pMC->getLoanNumber() > 0)
		m_ctlKorotJaSHVkulut.EnableWindow(TRUE);
	else
		m_ctlKorotJaSHVkulut.EnableWindow(FALSE);
	return IS_OK;
}

int CPanttiView::EnableButtons(int iButtons)
{
	m_ctlUusiLaina.EnableWindow(iButtons & B_NEW);
	m_ctlLunastus.EnableWindow(iButtons & B_RDP);
	m_ctlUudistus.EnableWindow(iButtons & B_RNW);
	m_ctlVakuusmuutos.EnableWindow(iButtons & B_CHG);
	//m_ctlKuitti.EnableWindow(iButtons & B_RNW);
	m_ctlLainanTapahtumat.EnableWindow(iButtons & B_EVN);
	/*m_ctlEde.EnableWindow(iButtons & B_EDE);
   m_ctlSeu.EnableWindow(iButtons & B_SEU);
   m_ctlVii.EnableWindow(iButtons & B_VII);
   m_ctlUus.EnableWindow(iButtons & B_UUS);
   m_ctlTal.EnableWindow(iButtons & B_TAL);
   m_ctlPoi.EnableWindow(iButtons & B_POI);   // Poista l‰hete
   // tulostuspainikkeet
   m_ctlTulTo.EnableWindow(iButtons & B_TO);
   m_ctlTulKu.EnableWindow(iButtons & B_KA);
   m_ctlTulLa.EnableWindow(iButtons & B_LA);
   // tositerivikohtaiset painikkeet
   m_ctlPoiRi.EnableWindow(iButtons & BR_PO);  // poista rivi
   m_ctlKorRi.EnableWindow(iButtons & BR_KO);
   m_ctlLisRi.EnableWindow(iButtons & BR_LI);
   //
   m_ctlHyv.EnableWindow(iButtons & B_HY);
   m_ctlLaTu.EnableWindow(iButtons & B_LAS);  // "Laske"-painike
   */
	if (theApp.m_pMC->UpdateQueueList(&m_ctlSuoritusjono) > 0)
	{
		m_ctlKuitti.EnableWindow(TRUE);
	}
	else
	{
		m_ctlKuitti.EnableWindow(FALSE);
	}
	return IS_OK;
}



void CPanttiView::UpdateQueue()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int iRows = 0;
	iRows = theApp.m_pMC->UpdateQueueList(&m_ctlSuoritusjono);

	TRACE("Got %d rows from controller/queue\n", iRows);
	m_sSuoritusjononSumma.Format("%7.2f", theApp.euroToMk(theApp.m_pMC->m_dMaksettavaYht));
	m_sLoppusummaEuroina.Format("%7.2f", theApp.m_pMC->m_dMaksettavaYht);
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	if (iRows >=1)
		m_ctlKuitti.EnableWindow(TRUE);
	else
		m_ctlKuitti.EnableWindow(FALSE);
}

/*void CPanttiView::OnDblclkSuoritusjono()          TILAPƒISESTI POIS KAYTOSTA, pitaa korjata lainarivikirjaus korotus/lyhennys tap
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int iRow = m_ctlSuoritusjono.GetCurSel();
	TRACE("Valittu rivi: %d, ItemData=%ld\n", iRow, m_ctlSuoritusjono.GetItemData(iRow));
	theApp.m_pMC->ActivateDlg(iRow, m_ctlSuoritusjono.GetItemData(iRow));
	//theApp.m_pMC->DlgActivationTest(50, iRow, m_ctlSuoritusjono.GetItemData(iRow));
	UpdateQueue();
}
*/
void CPanttiView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int iRow = 0;
	TRACE("char=%d\n", nChar);
	CWnd* pW = GetFocus();
	if ( (pW == this->GetDlgItem(IDC_SUORITUSJONO)) /*&& (nChar == */ )
	{
		iRow = m_ctlSuoritusjono.GetCurSel();
	}



	CFormView::OnChar(nChar, nRepCnt, nFlags);
}

void CPanttiView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	TRACE("char=%d\n", nChar);

	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}

int CPanttiView::OnVKeyToItem(UINT nKey, CListBox* pListBox, UINT nIndex)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	TRACE("Key=%d\n", nKey);

	return CFormView::OnVKeyToItem(nKey, pListBox, nIndex);
}

void CPanttiView::OnRemoveSjonorivi()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString msg = "";
	int iRow = m_ctlSuoritusjono.GetCurSel();
	TRACE("Valittu rivi: %d\n", iRow);
	msg.Format("Poistetaanko rivi %d", iRow+1);
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return;
	}
	TRACE("Poistetaan rivi=%d, D=%ld\n", iRow, m_ctlSuoritusjono.GetItemData(iRow));
	theApp.m_pMC->RemoveQRow(iRow, m_ctlSuoritusjono.GetItemData(iRow));

	UpdateQueue();
}

void CPanttiView::OnLainanTapahtumat()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString msg = "";
	long ln = 0;
	ROWCOL nRow, nCol;
	CString sn = "";

	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	CString sHTun = "";
	sHTun = m_ci.RemoveSpaces(m_sHtun).Left(11);
	m_ctlSnimi.GetWindowText(sn);
	if (m_wndLainaGrid.GetCurrentCell(nRow, nCol)) //jos ei yht‰‰n rivi‰ niin ...
	{
		ln = atol(m_wndLainaGrid.GetValueRowCol(nRow,1));
	}
	else
	{
		MessageBeep(1);
		return;
	}
	if (!theApp.m_pMC->LoanEventsDlgReq(ln, sHTun, m_lAsId, sn))
	{
		MessageBeep(1);
		TRACE("LoanEvents Request Error!!!!\n");
	}
}





void CPanttiView::OnSp2()
{
	m_iSp = 1; // valittu miehet
	//OnTyhjenna(); // ei voi hakea automaattisesti koska muuten asiakastietojen korjaaminen ep‰onnistuu!
	//OnEtsi();
}

void CPanttiView::OnSp1()
{
	m_iSp = 0; // naiset
	//OnTyhjenna();
	//OnEtsi();
}

void CPanttiView::OnLainatCancelEvent()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	//CString msg;
	//msg.Format("Perutaanko lainan %ld viimeisin tapahtuma ?", theApp.m_pMC->m_pDB->getCurrentLoan()->m_LA_Nr);
	//if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	//{
	//	return;
	//}
	//TRACE("Peruminen\n");
	switch (theApp.m_pMC->CancelEventOfCurrentLoan())
	{
		case 0:	// uusi laina
			TRACE("Uusi laina on poistettu OK!\n");
			break;

		case 1: // lunastus
			break;

		case 2: // uudistus
			break;

		case 4: // ei tehd‰ mit‰‰n
			break;

		default:
			TRACE("Virhe!\n");
			break;
	}
	//OnSelchangeSnimi();
	this->m_sLainanumero.Format("%ld", theApp.m_pMC->getLoanNumber());
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	this->OnEtsiLaina();
}

void CPanttiView::OnUpdateLainatCancelEvent(CCmdUI* pCmdUI)
{
	if (theApp.m_pMC->getLoanNumber() > 0)
		pCmdUI->Enable(theApp.m_pMC->m_pDB->isRestorationPossible());
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiView::OnLainatUusilaina()
{
	OnUusiLaina();
}

void CPanttiView::OnLainatLunastus()
{
	OnLunastus();
}

void CPanttiView::OnLainatUudistus()
{
	OnUudistus();
}

void CPanttiView::OnLainatVakuusmuutos()
{
	OnVakmuutos();
}

void CPanttiView::OnUpdateLainatUusilaina(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(theApp.m_pMC->getCurrentCustomerSet()->isCustomerSelected());
}

void CPanttiView::OnUpdateLainatLunastus(CCmdUI* pCmdUI)
{
	if (theApp.m_pMC->getLoanNumber() > 0
		&& theApp.m_pMC->getDBCtl()->getCurrentLoan()->getRedemptionLoan()->getLoanStatus() == "A")
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiView::OnUpdateLainatUudistus(CCmdUI* pCmdUI)
{
	if (theApp.m_pMC->getLoanNumber() > 0 
		&& theApp.m_pMC->getDBCtl()->getCurrentLoan()->getRedemptionLoan()->getLoanStatus() == "A")
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiView::OnUpdateLainatVakuusmuutos(CCmdUI* pCmdUI)
{
	if (theApp.m_pMC->getLoanNumber() > 0 
		&& theApp.m_pMC->getDBCtl()->getCurrentLoan()->getRedemptionLoan()->getLoanStatus() == "A")
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiView::SelchangeSnimi()
{
	if ( m_ctlSnimi.GetCurSel() != CB_ERR)
		OnSelchangeSnimi();
}

/*HBRUSH CPanttiView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here

	// TODO: Return a different brush if the default is not desired
	return hbr;
}*/

HBRUSH CPanttiView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
		// TODO: Change any attributes of the DC here

		//if (nCtlColor == CTLCOLOR_STATIC)
		//	return m_brBack2;
		//else if (nCtlColor == CTLCOLOR_EDIT)
		//	return m_brBack3;
		//else
	//	return static_cast<HBRUSH>(m_brBack3.GetSafeHandle());

	if (pWnd->GetDlgCtrlID() == IDC_KUITTI)
	{
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->SetBkColor(RGB(255, 255, 0));

		//return hbr;
		//return static_cast<HBRUSH>(m_brBack.GetSafeHandle());
		return m_brBack;
	}

	switch(nCtlColor)
	{
		case CTLCOLOR_BTN:
			return static_cast<HBRUSH>(m_brBack.GetSafeHandle());
		case CTLCOLOR_STATIC:
			pDC->SetBkMode( TRANSPARENT );
			// Fall through

		case CTLCOLOR_DLG:
			return static_cast<HBRUSH>(m_brBack4.GetSafeHandle());
	}
	return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	//return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CPanttiView::OnKorotJaShvKulut()
{
	theApp.m_pMC->showInterestsDlg();
}

void CPanttiView::OnEtsiEtsiasiakas()
{
	OnEtsi();
}

void CPanttiView::OnEtsiTyhjennasiakastied()
{
	OnTyhjenna();
	this->m_ctlSP.SetFocus();
}

void CPanttiView::OnEtsiEtsilaina()
{
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	if (this->m_sLainanumero.IsEmpty())
		m_ctlLainanumero.SetFocus();
	else
		OnEtsiLaina();
}

void CPanttiView::OnAsiakkaatTalletauusiasiakas()
{
	OnTallenna();
}

void CPanttiView::OnAsiakkaatTalletamuuttuneetasiakastiedot()
{
	OnKorjaa();
}

void CPanttiView::OnLainatTulostakuititsuoritjonontap()
{
	OnKuitti();
}

void CPanttiView::OnUpdateLainatTulostakuititsuoritjonontap(CCmdUI* pCmdUI)
{
	int iRows = theApp.m_pMC->GetQueueRowCount();
	//TRACE("%d,", iRows);
	if (iRows >=1)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiView::OnLainatLainankulut()
{
	OnKorotJaShvKulut();
}

void CPanttiView::OnUpdateLainatLainankulut(CCmdUI* pCmdUI)
{
	if (theApp.m_pMC->getLoanNumber() > 0)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CPanttiView::OnLainatLainantapahtumat()
{
	OnLainanTapahtumat();
}

void CPanttiView::OnUpdateLainatLainantapahtumat(CCmdUI* pCmdUI)
{
	if (theApp.m_pMC->getLoanNumber() > 0)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}



void CPanttiView::OnUpdateHtun() 
{
	// ???? RJ 01102001 ????
			// TODO: If this is a RICHEDIT control, the control will not
			// send this notification unless you override the CFormView::OnInitDialog()
			// function to send the EM_SETEVENTMASK message to the control
			// with the ENM_UPDATE flag ORed into the lParam mask.
	// ???? RJ 01102001 ????

	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	TRACE("%s\n", this->m_sHtun);
	m_sHtun = m_ci.updateHTun(m_sHtun);
	//
	// vain henkilˆtunnuksen pituus rajoitetaan 11 merkkiin, ei nimen kirjoittamista
	/*if (  (m_sHtun.Left(1) == "0" ||
				m_sHtun.Left(1) == "1" ||
				m_sHtun.Left(1) == "2" ||
				m_sHtun.Left(1) == "3" ||
				m_sHtun.Left(1) == "4" ||
				m_sHtun.Left(1) == "5" ||
				m_sHtun.Left(1) == "6" ||
				m_sHtun.Left(1) == "7" ||
				m_sHtun.Left(1) == "8" ||
				m_sHtun.Left(1) == "9") )*/
	if (  (m_sHtun.Left(1) >= 0x30) && (m_sHtun.Left(1) < 0x40) ) // teksti alkaa numerolla -> varmaankin HTunnus
	{
		m_ctlHtun.LimitText(11);
	}
	else
	{
		m_ctlHtun.LimitText(50);
	}
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	this->m_ctlHtun.SetSel(m_sHtun.GetLength(),m_sHtun.GetLength());
}




void CPanttiView::moveToHenkTun()
{
	this->m_ctlHtun.SetFocus();
}

void CPanttiView::OnAsetuksetTyhjennruutu() 
{
	OnTyhjenna();
}

void CPanttiView::OnAsiakkaatOsoite() 
{
	this->m_ctlKatuos.SetFocus();
}
