// DlgKassa.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgKassa.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgKassa dialog

extern CPanttiApp theApp;


CDlgKassa::CDlgKassa(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKassa::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKassa)
	m_dSiirtosumma = 0.0;
	m_sKassa1 = _T("");
	m_sKassa2 = _T("");
	//}}AFX_DATA_INIT
	m_pGXKassalista = new CRGXKassa;
	m_pKRS = new CKassaRS;
	m_pKRS->m_pDatabase = theApp.GetDatabase();
	m_bDeskSelectionOK = FALSE;
}

CDlgKassa::~CDlgKassa()
{
	delete m_pGXKassalista;
	delete m_pKRS;
}

void CDlgKassa::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKassa)
	DDX_Control(pDX, IDC_SIIRTOSUMMA, m_ctlSiirtosumma);
	DDX_Control(pDX, IDC_SIIRTO, m_ctlBtnSiirto);
	DDX_Control(pDX, IDC_PANO, m_ctlBtnPano);
	DDX_Control(pDX, IDC_NOSTO, m_ctlBtnNosto);
	DDX_Control(pDX, IDC_RAHASIIRROT_KASSA, m_ctlRahasiirrotKassa);
	DDX_Control(pDX, IDC_KASSA2, m_ctlKassa2);
	DDX_Control(pDX, IDC_KASSA1, m_ctlKassa1);
	DDX_Text(pDX, IDC_SIIRTOSUMMA, m_dSiirtosumma);
	DDX_CBString(pDX, IDC_KASSA1, m_sKassa1);
	DDX_CBString(pDX, IDC_KASSA2, m_sKassa2);
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX, m_pGXKassalista);
}


BEGIN_MESSAGE_MAP(CDlgKassa, CDialog)
	//{{AFX_MSG_MAP(CDlgKassa)
	ON_BN_CLICKED(IDC_LISAA_UUSI_KASSA, OnLisaaUusiKassa)
	ON_CBN_SELCHANGE(IDC_KASSA1, OnSelchangeKassa1)
	ON_CBN_SELCHANGE(IDC_KASSA2, OnSelchangeKassa2)
	ON_EN_CHANGE(IDC_SIIRTOSUMMA, OnChangeSiirtosumma)
	ON_BN_CLICKED(IDC_PANO, OnPano)
	ON_BN_CLICKED(IDC_NOSTO, OnNosto)
	ON_BN_CLICKED(IDC_SIIRTO, OnSiirto)
	ON_BN_CLICKED(IDC_TALLETA, OnTalleta)
	ON_CONTROL(RJ_OG_PARENT_DLG, IDC_KASSALISTA, OnDeskListClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKassa message handlers

BOOL CDlgKassa::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pGXKassalista->SubclassDlgItem(IDC_KASSALISTA, this);
	m_pGXKassalista->Initialize();
	SetColumns();
	ShowKassat();
	UpdateButtons(T_ALKU);


	// --------
	CString stmp = "";
	m_sKassanNimi =  theApp.m_sDesk; //theApp.RemoveSpaces(

	UpdateButtons(T_KASSA_SOK);
	stmp.Format("Kassa = '%s'", m_sKassanNimi);
	m_ctlRahasiirrotKassa.SetWindowText(stmp);
	m_bDeskSelectionOK = TRUE;
	// --------

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgKassa::SetColumns()
{
	m_pGXKassalista->GetParam()->EnableUndo(FALSE);
	m_pGXKassalista->SetRowCount(50);
	m_pGXKassalista->SetColCount(4);

	m_pGXKassalista->SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("Nimi"));
	m_pGXKassalista->SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("ID"));
	m_pGXKassalista->SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("Saldo ed. tarkastuksessa"));
	m_pGXKassalista->SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("Tarkastusaika"));

	m_pGXKassalista->SetColWidth(0,0,20); // Rivinrot
	m_pGXKassalista->SetColWidth(1,1,45); // KassanNimi
	m_pGXKassalista->SetColWidth(2,2,20); // ID
	m_pGXKassalista->SetColWidth(3,3,120); // Saldo ed. tarkastuksessa
	m_pGXKassalista->SetColWidth(4,4,120); // Tarkastusaika

	m_pGXKassalista->GetParam()->EnableUndo(TRUE);
	m_pGXKassalista->SetFocus();
}

BOOL CDlgKassa::ShowKassat()
{
	CString stmp = "";
	char buf[50];
	m_pGXKassalista->SetTopRow(1);
	m_pGXKassalista->MoveCurrentCell(GX_TOPLEFT);
	m_pGXKassalista->SetRowCount(0);

	m_ctlKassa1.ResetContent();
	m_ctlKassa2.ResetContent();
	try
	{
		m_pKRS->m_strFilter.Format("");
		m_pKRS->Open();
		m_iRowCount = 0;
		while (!m_pKRS->IsEOF())
		{
			m_iRowCount++;
			m_pGXKassalista->SetRowCount(m_iRowCount);

			m_pGXKassalista->SetValueRange(CGXRange(m_iRowCount, 1), m_pKRS->m_KS_KassanNimi);
			// ---------------
			stmp.Format("'%7.2f'\n", m_pKRS->m_KS_Saldo);
			TRACE("%s\n", stmp);
			TRACE("Saldo      ='%f'\n", m_pKRS->m_KS_Saldo);
			if (m_pKRS->m_KS_Saldo == NULL)
				stmp.Format("%7.2f", 0);
			else
				stmp.Format("%7.2f", m_pKRS->m_KS_Saldo);
			m_pGXKassalista->SetValueRange(CGXRange(m_iRowCount, 3), stmp);
			// ---------------
			if (m_pKRS->m_KS_TarkastusAika == NULL)
				sprintf(buf, "%s", "?");
			else
				sprintf(buf, "%s", m_pKRS->m_KS_TarkastusAika.Format("%d.%m.%Y: %H.%M.%S"));
			m_pGXKassalista->SetValueRange(CGXRange(m_iRowCount, 4), buf);
			m_pGXKassalista->SetValueRange(CGXRange(m_iRowCount, 2), m_pKRS->m_KS_Tunnus);

			//
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

void CDlgKassa::OnOK()
{
	CDialog::OnOK();
}

void CDlgKassa::OnLisaaUusiKassa()
{
	//OnTalleta();
	try
	{
		m_pKRS->m_strFilter.Format("");
		m_pKRS->Open();
		m_pKRS->AddNew();

		m_pKRS->m_KS_KassanNimi = "?";
		m_pKRS->m_KS_Saldo = 0.00;
		m_pKRS->SetFieldNull(&m_pKRS->m_KS_TarkastusAika);

		m_pKRS->Update();

		m_pKRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKRS->Close();
	}
	ShowKassat();
}


void CDlgKassa::OnDeskListClicked()
{
	/*CString stmp = "";
	TRACE("OnDeskListClicked!\n");
	ROWCOL nRow, nCol;
    if (m_pGXKassalista->GetCurrentCell(nRow, nCol)) // valittu kassalistan rivi
	{
		if (nRow >=1)
		{
			TRACE("Rivi %d\n", nRow);
			m_iSelectedRow = nRow;
			m_sKassanNimi = *//*theApp.RemoveSpaces(
											*//*m_pGXKassalista->GetValueRowCol(nRow,1)/*)*//*;
			UpdateButtons(T_KASSA_SOK);
			stmp.Format("Kassa = '%s'", m_sKassanNimi);
			m_ctlRahasiirrotKassa.SetWindowText(stmp);
			m_bDeskSelectionOK = TRUE;
		}
	}
	else
	{
		m_sKassanNimi = "?";			//jos ei yht‰‰n rivi‰ niin ...
		UpdateButtons(T_ALKU);
	}
	IsTransferAllowed();*/
}


int CDlgKassa::UpdateButtons(int iState)
{
	switch(iState)
	{
		case T_ALKU :
			EnableButtons( 0 );  // OK on ainoa aktiivinen painike ( aina aktiivinen)
			break;
		case T_KASSA_SNOK :
			EnableButtons( 0 );
			break;
		case T_KASSA_SOK :
			EnableButtons(  B_NOST |
                         B_PANO);
			break;
		case T_SIIRTO :
			EnableButtons(  B_NOST |
                         B_PANO |
                         B_SIIRT);
			break;
		case T_VAINSIIRTO :
			EnableButtons( B_SIIRT);
			break;

	}
	return IS_OK;
}

int CDlgKassa::EnableButtons(int iButtons)
{
	m_ctlBtnNosto.EnableWindow(iButtons & B_NOST);
	m_ctlBtnPano.EnableWindow(iButtons & B_PANO);
	m_ctlBtnSiirto.EnableWindow(iButtons & B_SIIRT);
	return IS_OK;
}

void CDlgKassa::OnSelchangeKassa1()
{
	IsTransferAllowed();
	TRACE("Kassa1 vaihdettu\n");
}

void CDlgKassa::OnSelchangeKassa2()
{
	IsTransferAllowed();
	TRACE("Kassa2 vaihdettu\n");
}

BOOL CDlgKassa::IsTransferAllowed()
{
	UpdateData(); // data is being retrieved (TRUE = default) //
	if (m_dSiirtosumma > 0 &&
		(!m_sKassa1.IsEmpty()) &&
		(!m_sKassa2.IsEmpty()) &&
		(m_sKassa1 != m_sKassa2))
	{
		if (m_bDeskSelectionOK)
			UpdateButtons(T_SIIRTO);
		else
			UpdateButtons(T_VAINSIIRTO);
		return TRUE;
	}
	else
	{
		if (m_bDeskSelectionOK)
			UpdateButtons(T_KASSA_SOK);
		else
			UpdateButtons(T_ALKU);
		return FALSE;
	}
	return FALSE;
}



void CDlgKassa::OnChangeSiirtosumma()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	IsTransferAllowed();
	// TODO: Add your control notification handler code here

}

void CDlgKassa::OnPano()
{
	double dSumma = 0;
	CString tm1 = "";
	CString tm2 = "";
	CString stmp = "";
	UpdateData(); // data is being retrieved (TRUE = default)
	if (!((m_dSiirtosumma > 0) && m_bDeskSelectionOK))
	{
		stmp.Format("Kirjoita ensin siirtosumma");
		if (AfxMessageBox(stmp/*, MB_YESNO*/) == IDOK/*IDYES IDNO*/)
		{
			return;
		}
	}
	TRACE("Panosumma = %f\n", m_dSiirtosumma);
	//
	// --- kassalokimerkint‰ ----
	CKassalokiRS kl;
	BOOL brtn = 
		kl.writeDeskLogEntry(
			"P",				// Tapahtuman tyyppi: U/D/L/....// tType = Z, luottotappio
			m_dSiirtosumma,		// Rahasumma kassasiirroissa (ei kohdistu mihink‰‰n lainaan, lainaNr j‰‰ tyhj‰ksi)
			"Talletus: rahaa talletettu pankista kassaan",				// Selite
			NULL,				// Lainan numero
			NULL,				// Lainasumma ennen operaatiota
			NULL,				// Lainasumma operaation j‰lkeen
			NULL,				// Korkojen osuus
			NULL,				// SHVMaksut
			NULL,				// Toimitusmaksut
			NULL,				// Pyˆristys
			NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
			NULL,	// Ylij‰‰m‰
			NULL,	// Alij‰‰m‰
			NULL);	// NULL=oletuskassa: Kassan tunnus (Kassasiirrot p‰‰tt‰‰ itse mik‰ kassa kyseess‰ (ei aina oletuskassa!)
	ShowKassat();
	m_dSiirtosumma = 0;
	UpdateData(FALSE); // data is being retrieved (TRUE = default)
}

void CDlgKassa::OnNosto()
{
	double dSumma = 0;
	CString stmp = "";
	CString tm1 = "";
	CString tm2 = "";
	UpdateData(); // data is being retrieved (TRUE = default)
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
	// --- kassalokimerkint‰ ----
	CKassalokiRS kl;
	BOOL brtn = 
		kl.writeDeskLogEntry(
			"N",				// Tapahtuman tyyppi: U/D/L/....// tType = Z, luottotappio
			m_dSiirtosumma,		// Rahasumma kassasiirroissa (ei kohdistu mihink‰‰n lainaan, lainaNr j‰‰ tyhj‰ksi)
			"Nosto: rahaa nostettu kassasta pankkiin",				// Selite
			NULL,				// Lainan numero
			NULL,				// Lainasumma ennen operaatiota
			NULL,				// Lainasumma operaation j‰lkeen
			NULL,				// Korkojen osuus
			NULL,				// SHVMaksut
			NULL,				// Toimitusmaksut
			NULL,				// Pyˆristys
			NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
			NULL,	// Ylij‰‰m‰
			NULL,	// Alij‰‰m‰
			NULL);	// NULL=oletuskassa: Kassan tunnus (Kassasiirrot p‰‰tt‰‰ itse mik‰ kassa kyseess‰ (ei aina oletuskassa!)
	ShowKassat();
	m_dSiirtosumma = 0;
	UpdateData(FALSE); // data is being retrieved (TRUE = default)
}

void CDlgKassa::OnSiirto()
{
	double dSumma = 0;
	long lKassaId = 0;
	CString stmp = "";
	//CString tm1 = "";
	//CString tm2 = "";
	//int iRow1 = 0;
	//int iRow2 = 0;
	UpdateData(); // data is being retrieved (TRUE = default)
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
		stmp.Format("SiirtoA (kassasta #%ld)", lKassaId);
		//
		// --- kassalokimerkint‰ ----
		CKassalokiRS kl;
		BOOL brtn = 
			kl.writeDeskLogEntry(
				"A",				// Tapahtuman tyyppi: U/D/L/....// tType = Z, luottotappio
				(-1)*m_dSiirtosumma,		// Rahasumma kassasiirroissa (ei kohdistu mihink‰‰n lainaan, lainaNr j‰‰ tyhj‰ksi)
				stmp,				// Selite
				NULL,				// Lainan numero
				NULL,				// Lainasumma ennen operaatiota
				NULL,				// Lainasumma operaation j‰lkeen
				NULL,				// Korkojen osuus
				NULL,				// SHVMaksut
				NULL,				// Toimitusmaksut
				NULL,				// Pyˆristys
				NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
				NULL,	// Ylij‰‰m‰
				NULL,	// Alij‰‰m‰
				lKassaId);	// Kassan tunnus (Kassasiirrot p‰‰tt‰‰ itse mik‰ kassa kyseess‰ (ei aina oletuskassa!)
		//
		lKassaId = m_ctlKassa2.GetItemData(m_ctlKassa2.GetCurSel());
		stmp.Format("SiirtoB (kassaan #%ld)", lKassaId);
		//
		// --- kassalokimerkint‰ ----
		brtn = 
			kl.writeDeskLogEntry(
				"B",				// Tapahtuman tyyppi: U/D/L/....// tType = Z, luottotappio
				m_dSiirtosumma,		// Rahasumma kassasiirroissa (ei kohdistu mihink‰‰n lainaan, lainaNr j‰‰ tyhj‰ksi)
				stmp,				// Selite
				NULL,				// Lainan numero
				NULL,				// Lainasumma ennen operaatiota
				NULL,				// Lainasumma operaation j‰lkeen
				NULL,				// Korkojen osuus
				NULL,				// SHVMaksut
				NULL,				// Toimitusmaksut
				NULL,				// Pyˆristys
				NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
				NULL,	// Ylij‰‰m‰
				NULL,	// Alij‰‰m‰
				lKassaId);	// Kassan tunnus (Kassasiirrot p‰‰tt‰‰ itse mik‰ kassa kyseess‰ (ei aina oletuskassa!)
	}
	else
	{
		stmp.Format("Valitse ensin kassat ja kirjoita siirtosumma");
		if (AfxMessageBox(stmp/*, MB_YESNO*/) == IDOK/*IDYES IDNO*/)
		{
			return;
		}
	}
	ShowKassat();
	m_dSiirtosumma = 0;
	UpdateData(FALSE); // data is being retrieved (TRUE = default)
}

/*int CDlgKassa::GetListRow(CString sKassaNimi)
{
	UINT r = 0;

	for (r = 1; r <= m_pGXKassalista->GetRowCount(); r++)
	{
		if (m_pGXKassalista->GetValueRowCol(r,1) == sKassaNimi)
		{
			return r;
		}
	}

	return 0;
}*/

void CDlgKassa::OnTalleta()
{
	UINT r = 0;
	CString stmp = "";
	CTime t = 0;
	TRACE("Rivej‰ %d kpl\n", m_pGXKassalista->GetRowCount());
	/*for (r = 1; r <= m_pGXKassalista->GetRowCount(); r++)
	{
		TRACE("KassanNimi=%s\n", m_pGXKassalista->GetValueRowCol(r,1));
	}*/
	for (r = 1; r <= m_pGXKassalista->GetRowCount(); r++)
	{
		if ( ! m_pGXKassalista->GetValueRowCol(r,1).IsEmpty()) // kassalla pit‰‰ olla nimi
		{
			//
			TRACE("PvkAika    ='%s'\n", m_pGXKassalista->GetValueRowCol(r,4));
			//if (! (m_pGXKassalista->GetValueRowCol(r,3).IsEmpty()))
			//	t = theApp.GetDate(m_pGXKassalista->GetValueRowCol(r,3));

			UpdateDesk(	atol(m_pGXKassalista->GetValueRowCol(r,2)),
						theApp.RemoveSpaces( m_pGXKassalista->GetValueRowCol(r,1))/*,
						theApp.RemoveSpaces( m_pGXKassalista->GetValueRowCol(r,2)),
						atof(m_pGXKassalista->GetValueRowCol(r,3)),
						t*/);
		}
		else
		{
			MessageBeep(1);
		}
	}

}

void CDlgKassa::UpdateDesk(long lDeskId, CString sNimi/*, CString sAMTunnus, double dSaldo, CTime TarkastusAika*/)
{
	TRACE("Talletetaan kassa #%ld\n", lDeskId);
	try
	{
		m_pKRS->m_strFilter.Format("KS_Tunnus = %ld", lDeskId);
		m_pKRS->Open();
		if ( ! m_pKRS->IsEOF())
		{
			m_pKRS->Edit();

			m_pKRS->m_KS_KassanNimi = theApp.RemoveSpaces(sNimi);
			//m_pKRS->m_KS_AM_Tunnus = theApp.RemoveSpaces(sAMTunnus);
			//m_pKRS->m_KS_Saldo = dSaldo;
			//m_pKRS->m_KS_TarkastusAika = TarkastusAika;

			m_pKRS->Update();
		}
		m_pKRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKRS->Close();
	}
}


double CDlgKassa::changeBalance(long lDeskId, double dSum)
{
	double drtn = 0;
	TRACE("Muutetaan kassan #%ld saldo\n", lDeskId);
	try
	{
		m_pKRS->m_strFilter.Format("KS_Tunnus = %ld", lDeskId);
		m_pKRS->Open();
		if ( ! m_pKRS->IsEOF())
		{
			m_pKRS->Edit();

			//m_pKRS->m_KS_KassanNimi = theApp.RemoveSpaces(sNimi);
			//m_pKRS->m_KS_AM_Tunnus = theApp.RemoveSpaces(sAMTunnus);
			m_pKRS->m_KS_Saldo = m_pKRS->m_KS_Saldo + dSum;
			//m_pKRS->m_KS_TarkastusAika = TarkastusAika;

			m_pKRS->Update();
		}
		m_pKRS->Close();
		drtn = dSum;
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKRS->Close();
	}
	return drtn;
}

