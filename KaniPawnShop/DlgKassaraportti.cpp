// DlgKassaraportti.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgKassaraportti.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;



/////////////////////////////////////////////////////////////////////////////
// CDlgKassaraportti dialog


CDlgKassaraportti::CDlgKassaraportti(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKassaraportti::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKassaraportti)
	m_sRapPvm = _T("");
	m_sPvkStart = _T("");
	m_sPvkStop = _T("");
	m_sLainakanta = _T("");
	m_sKassanNimi = _T("");
	m_sSiirtosumma = _T("");
	m_sYhtRahaaKoKassassa = _T("");
	m_sVisaSiirtoSumma = _T("");
	//}}AFX_DATA_INIT
	m_pKRGrid = new CRGXKassaraportti;
	m_pKRS = new CKassaRS;
	m_pKRS->m_pDatabase = theApp.GetDatabase();

	m_dSiirtosumma = 0;
	m_dVisaSiirtosumma = 0;
	m_sSiirtosumma = "";
	m_bDeskSelectionOK = FALSE;
	m_sKassa1 = "";
	m_sKassa2 = "";
}

CDlgKassaraportti::~CDlgKassaraportti()
{
	delete m_pKRGrid;
	delete m_pKRS;
	
}

void CDlgKassaraportti::setController(CKRController* pKR)
{
	m_pKR = pKR;
}


void CDlgKassaraportti::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKassaraportti)
	DDX_Control(pDX, IDC_VISA, m_ctlBtnVisa);
	DDX_Control(pDX, IDC_UNDO, m_ctlUndo);
	DDX_Control(pDX, IDC_KASSA2, m_ctlKassa2);
	DDX_Control(pDX, IDC_SIIRTO, m_ctlBtnSiirto);
	DDX_Control(pDX, IDC_PANO, m_ctlBtnPano);
	DDX_Control(pDX, IDC_NOSTO, m_ctlBtnNosto);
	DDX_Control(pDX, IDC_KASSA1, m_ctlKassa1);
	DDX_Control(pDX, IDC_PAIVAKIRJA, m_ctlPaivakirja);
	DDX_Text(pDX, IDC_RAP_PVM, m_sRapPvm);
	DDX_Text(pDX, IDC_PVKSTART, m_sPvkStart);
	DDX_Text(pDX, IDC_PVKSTOP, m_sPvkStop);
	DDX_Text(pDX, IDC_LAINAKANTA, m_sLainakanta);
	DDX_Text(pDX, IDC_KASSA, m_sKassanNimi);
	DDX_Text(pDX, IDC_SIIRTOSUMMA, m_sSiirtosumma);
	DDX_Text(pDX, IDC_YHT, m_sYhtRahaaKoKassassa);
	DDX_Text(pDX, IDC_VISASIIRTO, m_sVisaSiirtoSumma);
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX, m_pKRGrid);
}


BEGIN_MESSAGE_MAP(CDlgKassaraportti, CDialog)
	//{{AFX_MSG_MAP(CDlgKassaraportti)
	ON_BN_CLICKED(IDC_ETSI, OnEtsi)
	ON_BN_CLICKED(IDC_PAIVAKIRJA, OnPaivakirja)
	ON_BN_CLICKED(IDC_KP_RAPORTTI, OnKpRaportti)
	ON_BN_CLICKED(IDC_SIIRTO, OnSiirto)
	ON_CBN_SELCHANGE(IDC_KASSA1, OnSelchangeKassa1)
	ON_EN_CHANGE(IDC_SIIRTOSUMMA, OnChangeSiirtosumma)
	ON_CBN_SELCHANGE(IDC_KASSA2, OnSelchangeKassa2)
	ON_BN_CLICKED(IDC_NOSTO, OnNosto)
	ON_BN_CLICKED(IDC_PANO, OnPano)
	ON_BN_CLICKED(IDSALDO_OK, OnSaldoOk)
	ON_BN_CLICKED(IDC_BTN_LAINAKANTA, OnBtnLainakanta)
	ON_BN_CLICKED(IDC_SIIRTOSAATAVAT, OnSiirtosaatavat)
	ON_BN_CLICKED(IDC_UNDO, OnUndo)
	ON_BN_CLICKED(IDC_VISA, OnVisa)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKassaraportti message handlers

BOOL CDlgKassaraportti::OnInitDialog()
{
	//int vuosi,kk,pv = 0;
	//char buf[50];

	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	CString stmp = "";
	int iEiTarkKpl = 0;
	double dEiTarkMk = 0;
	double dUudet = 0;
	CTime tark;
	CTime tx(1990,1,1,0,0,0);
	CTime tNow = CTime::GetCurrentTime();
	m_pKR->setStartStopTimes(tNow);

	/*CTime */t = CTime::GetCurrentTime();
	CString sDateAndTime = t.Format("%d.%m.%Y, klo: %H.%M.%S");
	m_sRapPvm = t.Format("%d.%m.%Y");

	CDialog::OnInitDialog();

	// TODO: Add extra initialization here


	m_pKRGrid->SubclassDlgItem(IDC_GRID_KASSARAPORTTI, this);
	m_pKRGrid->Initialize();

	m_pKRGrid->GetParam()->EnableUndo(FALSE);
	m_pKRGrid->SetRowCount(0);
	m_pKRGrid->SetColCount(0);
	m_pKRGrid->m_pDlgKR = this;

	m_pKR->initKRGrid();

	if ( (! m_pKRGrid->isMainAccountPermissible()) ||  // tarkastamattomia kassoja
		 (m_pKR->isMainReportDone() ))                // tämän päivän raportti on jo tehty
	{
		m_ctlPaivakirja.EnableWindow(FALSE);
	}

	//
	// --- peruminen sallittu ? ---
	m_ctlUndo.EnableWindow(isUndoPossible());

	//
	//vuosi = tNow.GetYear();
	//kk = tNow.GetMonth();
	//pv = tNow.GetDay();


	m_sPvkStart = m_pKR->getPvkStartTime().Format("%d.%m.%Y @%H.%M.%S");
	m_sPvkStop = m_pKR->getPvkStopTime().Format("%d.%m.%Y @%H.%M.%S");
	m_sKassanNimi =  theApp.m_sDesk;

	//
	// --- kassat ---
	showDesks();
	m_bDeskSelectionOK = TRUE;
	updateButtons(T_ALKU);

	//m_sLainakanta.Format("Lainakanta = %8.2f", m_pKR->getLainakanta());
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgKassaraportti::OnOK()
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}

void CDlgKassaraportti::OnEtsi()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	UpdateData(); //data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	t = theApp.GetDate(m_sRapPvm);
	m_pKR->setStartStopTimes(t);
	m_pKR->updateKRGrid(/*t*/);

	m_sPvkStart = m_pKR->getPvkStartTime().Format("%d.%m.%Y @ %H.%M.%S");
	m_sPvkStop = m_pKR->getPvkStopTime().Format("%d.%m.%Y @ %H.%M.%S");

	//
	// --- peruminen sallittu ? ---
	m_ctlUndo.EnableWindow(isUndoPossible());

	UpdateData(FALSE); //data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}




void CDlgKassaraportti::OnPaivakirja()
{
	CString msg = "";
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	long lKPPRow = m_pKR->closeAccount(); // tekee PPVK-kirjauksen lukuunottamatta kassojen yhteissaldoa
	double dSaldoYhtYht = m_pKR->closeDeskAccounts(lKPPRow); // palauttaa yhteissaldon
	// päivitetään pääpäiväkirjan saldo
	m_pKR->updateMainAccountBalance(lKPPRow, dSaldoYhtYht);

	// --- tyhjennetään makulointitaulut LAINARIVIPERU ja LAINAPERU
	theApp.m_pMC->m_pDB->removeOldBackup(0);

	
	//msg.Format("PAAPAIVAKIRJA: \nRivi#: %ld\nSaldo: %7.2f€", lKPPRow, dSaldoYhtYht);
	//AfxMessageBox(msg);
	
	OnKpRaportti();	
	m_ctlPaivakirja.EnableWindow(FALSE);
	OnEtsi();
}






void CDlgKassaraportti::OnKpRaportti()
{
	m_pKRGrid->printMainReport();
	OnEtsi();
}

BOOL CDlgKassaraportti::showDesks()
{
	CString stmp = "";

	m_ctlKassa1.ResetContent();
	m_ctlKassa2.ResetContent();
	try
	{
		m_pKRS->m_strFilter.Format("");
		m_pKRS->Open();
		while (!m_pKRS->IsEOF())
		{
			// -- kassatiedot valikoihin ---
			m_ctlKassa1.SetItemData(
      			m_ctlKassa1.InsertString(-1, m_pKRS->m_KS_KassanNimi),
      			m_pKRS->m_KS_Tunnus);
			m_ctlKassa2.SetItemData(
      			m_ctlKassa2.InsertString(-1, m_pKRS->m_KS_KassanNimi),
      			m_pKRS->m_KS_Tunnus);
			m_pKRS->MoveNext();
		}
		m_pKRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKRS->Close();
		return FALSE;
	}
	return TRUE;
}



BOOL CDlgKassaraportti::isTransferAllowed()
{
	UpdateData(); // data is being retrieved (TRUE = default) //
	m_dSiirtosumma = atof(theApp.dot(m_sSiirtosumma));
	if (m_dSiirtosumma > 0 &&
		(!m_sKassa1.IsEmpty()) &&
		(!m_sKassa2.IsEmpty()) &&
		(m_sKassa1 != m_sKassa2))
	{
		if (m_bDeskSelectionOK)
			updateButtons(T_SIIRTO);
		else
			updateButtons(T_VAINSIIRTO);
		return TRUE;
	}
	else
	{
		if (m_bDeskSelectionOK)
			updateButtons(T_KASSA_SOK);
		else
			updateButtons(T_ALKU);
		return FALSE;
	}
	return FALSE;
}




int CDlgKassaraportti::updateButtons(int iState)
{
	switch(iState)
	{
		case T_ALKU :
			enableButtons( 0 );  // OK on ainoa aktiivinen painike ( aina aktiivinen)
			break;
		case T_KASSA_SNOK :
			enableButtons( 0 );
			break;
		case T_KASSA_SOK :
			enableButtons(  B_NOST |
                         B_PANO);
			break;
		case T_SIIRTO :
			enableButtons(  B_NOST |
                         B_PANO |
                         B_SIIRT);
			break;
		case T_VAINSIIRTO :
			enableButtons( B_SIIRT);
			break;

	}
	return IS_OK;
}

int CDlgKassaraportti::enableButtons(int iButtons)
{
	m_ctlBtnNosto.EnableWindow(iButtons & B_NOST);
	m_ctlBtnPano.EnableWindow(iButtons & B_PANO);
	m_ctlBtnSiirto.EnableWindow(iButtons & B_SIIRT);
	return IS_OK;
}

void CDlgKassaraportti::initCtls()
{
	m_ctlKassa1.SetCurSel(-1);
	m_ctlKassa2.SetCurSel(-1);
	m_sKassa1 = "";
	m_sKassa2 = "";
	m_dSiirtosumma = 0;
	m_sSiirtosumma = "";
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}

void CDlgKassaraportti::OnChangeSiirtosumma() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	isTransferAllowed();	
}

void CDlgKassaraportti::OnSelchangeKassa1() 
{
	//UpdateData(); // data is being retrieved (TRUE = default) //
	m_ctlKassa1.GetWindowText(m_sKassa1);
	TRACE("\n1:%s vaihdettu\n", m_sKassa1);
	TRACE("2:%s\n", m_sKassa2);
	isTransferAllowed();
}



void CDlgKassaraportti::OnSelchangeKassa2() 
{
	m_ctlKassa2.GetWindowText(m_sKassa2);
	TRACE("\n1:%s\n", m_sKassa1);
	TRACE("2:%s vaihdettu\n", m_sKassa2);
	isTransferAllowed();
}

void CDlgKassaraportti::OnNosto() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	double dSumma = 0;
	CString stmp = "";
	CString tm1 = "";
	CString tm2 = "";
	UpdateData(); // data is being retrieved (TRUE = default)
	m_dSiirtosumma = atof(theApp.dot(m_sSiirtosumma));
	if (!((m_dSiirtosumma > 0) && m_bDeskSelectionOK))
	{
		stmp.Format("Kirjoita ensin siirtosumma");
		if (AfxMessageBox(stmp/*, MB_YESNO*/) == IDOK/*IDYES IDNO*/)
		{
			return;
		}
	}
	TRACE("Nostosumma = %f\n", m_dSiirtosumma);
	//
	// --- kassalokimerkintä ----
	CKassalokiRS kl;
	BOOL brtn = 
		kl.writeDeskLogEntry(
			"N",				// Tapahtuman tyyppi: U/D/L/....// tType = Z, luottotappio
			m_dSiirtosumma,		// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
			"Nosto: rahaa nostettu kassasta pankkiin",				// Selite
			NULL,				// Lainan numero
			NULL,				// Lainasumma ennen operaatiota
			NULL,				// Lainasumma operaation jälkeen
			NULL,				// Korkojen osuus
			NULL,				// SHVMaksut
			NULL,				// Toimitusmaksut
			NULL,				// Pyöristys
			NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
			NULL,	// Ylijäämä
			NULL,	// Alijäämä
			NULL);	// NULL=oletuskassa: Kassan tunnus (Kassasiirrot päättää itse mikä kassa kyseessä (ei aina oletuskassa!)
	//showDesks();
	m_dSiirtosumma = 0;
	UpdateData(FALSE); // data is being retrieved (TRUE = default)
	this->m_pKR->deskActionDone();
	//m_pKR->updateKRGrid(/*t*/);
	//OnEtsi();
}

void CDlgKassaraportti::OnPano() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	double dSumma = 0;
	CString tm1 = "";
	CString tm2 = "";
	CString stmp = "";
	UpdateData(); // data is being retrieved (TRUE = default)
	m_dSiirtosumma = atof(theApp.dot(m_sSiirtosumma));
	if (!((m_dSiirtosumma > 0) && m_bDeskSelectionOK))
	{
		stmp.Format("Kirjoita ensin siirtosumma");
		if (AfxMessageBox(stmp/*, MB_YESNO*/) == IDOK/*IDYES IDNO*/)
		{
			return;
		}
	}
	TRACE("Panosumma = %7.2fe\n", m_dSiirtosumma);
	//
	// --- kassalokimerkintä ----
	CKassalokiRS kl;
	BOOL brtn = 
		kl.writeDeskLogEntry(
			"P",				// Tapahtuman tyyppi: U/D/L/....// tType = Z, luottotappio
			m_dSiirtosumma,		// euroina, Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
			"Talletus: rahaa talletettu pankista kassaan",				// Selite
			NULL,				// Lainan numero
			NULL,				// Lainasumma ennen operaatiota
			NULL,				// Lainasumma operaation jälkeen
			NULL,				// Korkojen osuus
			NULL,				// SHVMaksut
			NULL,				// Toimitusmaksut
			NULL,				// Pyöristys
			NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
			NULL,	// Ylijäämä
			NULL,	// Alijäämä
			NULL);	// NULL=oletuskassa: Kassan tunnus (Kassasiirrot päättää itse mikä kassa kyseessä (ei aina oletuskassa!)
	//showDesks();
	m_dSiirtosumma = 0;
	UpdateData(FALSE); // data is being retrieved (TRUE = default)
	this->m_pKR->deskActionDone();
	//m_pKR->updateKRGrid(/*t*/);
	//OnEtsi();
}


void CDlgKassaraportti::OnVisa() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString stmp = "";
	UpdateData(); // data is being retrieved (TRUE = default)
	m_dVisaSiirtosumma = atof(theApp.dot(m_sVisaSiirtoSumma));
	if (!((m_dVisaSiirtosumma > 0) && m_bDeskSelectionOK))
	{
		stmp.Format("Kirjoita ensin Visa-maksun summa");
		if (AfxMessageBox(stmp/*, MB_YESNO*/) == IDOK/*IDYES IDNO*/)
		{
			return;
		}
	}
	TRACE("Visasumma = %7.2fe\n", m_dVisaSiirtosumma);
	//
	// --- kassalokimerkintä ----
	CKassalokiRS kl;
	BOOL brtn = 
		kl.writeDeskLogEntry(
			"V",				// Tapahtuman tyyppi: U/D/L/..../V=Visa/ tType = Z, luottotappio
			m_dVisaSiirtosumma,		// euroina, Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
			"Visamaksu",				// Selite
			NULL,				// Lainan numero
			NULL,				// Lainasumma ennen operaatiota
			NULL,				// Lainasumma operaation jälkeen
			NULL,				// Korkojen osuus
			NULL,				// SHVMaksut
			NULL,				// Toimitusmaksut
			NULL,				// Pyöristys
			NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
			NULL,	// Ylijäämä
			NULL,	// Alijäämä
			NULL);	// NULL=oletuskassa: Kassan tunnus (Kassasiirrot päättää itse mikä kassa kyseessä (ei aina oletuskassa!)
	//showDesks();
	m_dVisaSiirtosumma = 0;
	m_sVisaSiirtoSumma = "";
	UpdateData(FALSE); // data is being retrieved (TRUE = default)
	this->m_pKR->deskActionDone();
	
}



void CDlgKassaraportti::OnSiirto() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		double dSumma = 0;
	long lKassaId = 0;
	CString stmp = "";
	CString tm1 = "";
	CString tm2 = "";
	//int iRow1 = 0;
	//int iRow2 = 0;
	UpdateData(); // data is being retrieved (TRUE = default)
	m_dSiirtosumma = atof(theApp.dot(m_sSiirtosumma));
	if (!(m_dSiirtosumma > 0) )
	{
		stmp.Format("Valitse ensin kassat ja kirjoita siirtosumma");
		if (AfxMessageBox(stmp/*, MB_YESNO*/) == IDOK/*IDYES IDNO*/)
		{
			return;
		}
	}
	//iRow1 = GetListRow(m_sKassa1);
	//iRow2 = GetListRow(m_sKassa2);
	//TRACE("Kassasta r=%d kassaan r=%d\n", iRow1, iRow2);
	//TRACE("Nostosumma = %f\n", m_dSiirtosumma);

	if ((m_ctlKassa1.GetCurSel() != CB_ERR) && (m_ctlKassa2.GetCurSel() != CB_ERR))
	{
		lKassaId = m_ctlKassa1.GetItemData(m_ctlKassa1.GetCurSel());
		m_ctlKassa1.GetWindowText(tm1);
		stmp.Format("SiirtoA (kassasta #%s)", tm1);
		//
		// --- kassalokimerkintä ----
		CKassalokiRS kl;
		BOOL brtn = 
			kl.writeDeskLogEntry(
				"A",				// Tapahtuman tyyppi: U/D/L/....// tType = Z, luottotappio
				(-1)*m_dSiirtosumma,		// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
				stmp,				// Selite
				NULL,				// Lainan numero
				NULL,				// Lainasumma ennen operaatiota
				NULL,				// Lainasumma operaation jälkeen
				NULL,				// Korkojen osuus
				NULL,				// SHVMaksut
				NULL,				// Toimitusmaksut
				NULL,				// Pyöristys
				NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
				NULL,	// Ylijäämä
				NULL,	// Alijäämä
				lKassaId);	// Kassan tunnus (Kassasiirrot päättää itse mikä kassa kyseessä (ei aina oletuskassa!)
		//
		lKassaId = m_ctlKassa2.GetItemData(m_ctlKassa2.GetCurSel());
		m_ctlKassa2.GetWindowText(tm2);
		stmp.Format("SiirtoB (kassaan #%s)", tm2);
		//
		// --- kassalokimerkintä ----
		brtn = 
			kl.writeDeskLogEntry(
				"B",				// Tapahtuman tyyppi: U/D/L/....// tType = Z, luottotappio
				m_dSiirtosumma,		// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
				stmp,				// Selite
				NULL,				// Lainan numero
				NULL,				// Lainasumma ennen operaatiota
				NULL,				// Lainasumma operaation jälkeen
				NULL,				// Korkojen osuus
				NULL,				// SHVMaksut
				NULL,				// Toimitusmaksut
				NULL,				// Pyöristys
				NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
				NULL,	// Ylijäämä
				NULL,	// Alijäämä
				lKassaId);	// Kassan tunnus (Kassasiirrot päättää itse mikä kassa kyseessä (ei aina oletuskassa!)
	}
	else
	{
		stmp.Format("Valitse ensin kassat ja kirjoita siirtosumma");
		if (AfxMessageBox(stmp/*, MB_YESNO*/) == IDOK/*IDYES IDNO*/)
		{
			return;
		}
	}
	showDesks();
	m_dSiirtosumma = 0;
	UpdateData(FALSE); // data is being retrieved (TRUE = default)
	this->m_pKR->deskActionDone();
	//m_pKR->updateKRGrid(/*t*/);
	//OnEtsi();
}


void CDlgKassaraportti::updateTimeRange()
{
	this->OnEtsi();
}

void CDlgKassaraportti::setYhtRahaaKoKassassa(double kassanSaldo)
{
	this->m_pKR->m_dDeskBalance = kassanSaldo;
	this->m_sYhtRahaaKoKassassa.Format("%7.2f", kassanSaldo);
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}



void CDlgKassaraportti::OnSaldoOk() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	this->m_pKR->UpdateDeskBalance();
	updateTimeRange();
	m_pKR->updateKRGrid(/*t*/);
	//
	// --- päiväkirjapainikkeen tila ---
	if ( (! m_pKRGrid->isMainAccountPermissible()) ||  // tarkastamattomia kassoja
		 (m_pKR->isMainReportDone() ))                // tämän päivän raportti on jo tehty
	{
		m_ctlPaivakirja.EnableWindow(FALSE);
	}
	else
	{
		m_ctlPaivakirja.EnableWindow(TRUE);
	}
}


void CDlgKassaraportti::OnBtnLainakanta() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_sLainakanta.Format("%8.2f E", m_pKR->getLainakanta());
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
}

void CDlgKassaraportti::OnSiirtosaatavat() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	UpdateData(); //data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	t = theApp.GetDate(m_sRapPvm);
	m_pKR->siirtosaatavat(t);
}

void CDlgKassaraportti::OnUndo() 
{
	if (m_pKR->undo() == TRUE)
	{
		OnEtsi();
	}
}


BOOL CDlgKassaraportti::isUndoPossible()
{
	return m_pKR->isUndoPossible();	
}

