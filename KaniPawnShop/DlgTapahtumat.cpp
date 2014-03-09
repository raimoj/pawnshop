// DlgTapahtumat.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgTapahtumat.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CDlgTapahtumat dialog


CDlgTapahtumat::CDlgTapahtumat(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTapahtumat::IDD, pParent)
{
	ASSERT(0);
	//{{AFX_DATA_INIT(CDlgTapahtumat)
	m_sAsiakas_LainaNr = _T("");
	//}}AFX_DATA_INIT
	//m_pTapRS = new CTapahtumaRS;
	//m_pTapRS->m_pDatabase = theApp.GetDatabase();
	m_pTapRS = theApp.m_pMC->getDBCtl()->getLoanEventsRS();
}

CDlgTapahtumat::CDlgTapahtumat(CMC* pMC, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTapahtumat::IDD, pParent)
{
	m_pwndEs = new CRGXEvents();
	m_pwndERows = new CRGXEventRows();
	
	m_pMC = pMC;
	//{{AFX_DATA_INIT(CDlgTapahtumat)
	m_sAsiakas_LainaNr = _T("");
	//}}AFX_DATA_INIT
	//m_pTapRS = new CTapahtumaRS;
	//m_pTapRS->m_pDatabase = theApp.GetDatabase();
	m_pTapRS = m_pMC->getDBCtl()->getLoanEventsRS();

}


CDlgTapahtumat::~CDlgTapahtumat()
{
	//if (m_pTapRS) delete m_pTapRS;
	delete m_pwndEs;
	delete m_pwndERows;
}


void CDlgTapahtumat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTapahtumat)
	DDX_Text(pDX, IDC_ASIAKAS_LAINANR, m_sAsiakas_LainaNr);
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX, m_pwndEs);
}


BEGIN_MESSAGE_MAP(CDlgTapahtumat, CDialog)
	//{{AFX_MSG_MAP(CDlgTapahtumat)
	ON_WM_CANCELMODE()
	ON_CONTROL(RJ_OG_PARENT_DLG, IDC_EVENTS, OnShowEventRows)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTapahtumat message handlers

BOOL CDlgTapahtumat::OnInitDialog()
{
	CString msg = "";
	CDialog::OnInitDialog();

	m_pwndEs->SubclassDlgItem(IDC_EVENTS, this);
	m_pwndEs->Initialize();

	m_pwndERows->SubclassDlgItem(IDC_EVENTROWS, this);
	m_pwndERows->Initialize();
	
	SetColumns();
	if ( ! UpdateRows())
	{
		msg.Format("Lainan %ld tapahtumia ei löydy", m_lNr);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTapahtumat::OnCancelMode()
{
	CDialog::OnCancelMode();

	// TODO: Add your message handler code here

}

void CDlgTapahtumat::SetColumns()
{
	m_pwndEs->GetParam()->EnableUndo(FALSE);
	m_pwndEs->SetRowCount(50);
	m_pwndEs->SetColCount(17);
	m_pwndEs->SetReadOnly(FALSE);

	m_pwndEs->SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("Aika"));
	m_pwndEs->SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("Arviomies"));
	m_pwndEs->SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("Vakuus"));
	m_pwndEs->SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("V-Laina"));
	m_pwndEs->SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("U-Laina"));
	m_pwndEs->SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("Muutos")); // MUUTOS
	m_pwndEs->SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("Korot"));
	m_pwndEs->SetStyleRange(CGXRange(0,8), CGXStyle().SetValue("SHV"));
	m_pwndEs->SetStyleRange(CGXRange(0,9), CGXStyle().SetValue("Toim"));
	m_pwndEs->SetStyleRange(CGXRange(0,10), CGXStyle().SetValue("Ale"));
	m_pwndEs->SetStyleRange(CGXRange(0,11), CGXStyle().SetValue("Maksettu"));
	m_pwndEs->SetStyleRange(CGXRange(0,12), CGXStyle().SetValue("Tap"));
	m_pwndEs->SetStyleRange(CGXRange(0,13), CGXStyle().SetValue("Selitys"));
	m_pwndEs->SetStyleRange(CGXRange(0,14), CGXStyle().SetValue("Huom"));
	m_pwndEs->SetStyleRange(CGXRange(0,15), CGXStyle().SetValue("Varm"));
	m_pwndEs->SetStyleRange(CGXRange(0,16), CGXStyle().SetValue("Kassa"));
	m_pwndEs->SetStyleRange(CGXRange(0,17), CGXStyle().SetValue("TapID"));
	m_pwndEs->SetColWidth(0,0,20); // Rivinrot
	m_pwndEs->SetColWidth(1,1,60); // Aika
	m_pwndEs->SetColWidth(2,2,40); // Arviomies
	m_pwndEs->SetColWidth(3,3,60); // Vakuus
	m_pwndEs->SetColWidth(4,4,60); // V-Laina
	m_pwndEs->SetColWidth(5,5,60); // U-Laina
	m_pwndEs->SetColWidth(6,6,50); // MUUTOS
	m_pwndEs->SetColWidth(7,7,60); // Korot
	m_pwndEs->SetColWidth(8,8,60); // shv
	m_pwndEs->SetColWidth(9,9,60); // toim
	m_pwndEs->SetColWidth(10,10,60); // ale
	m_pwndEs->SetColWidth(11,11,60); // Maksettu
	m_pwndEs->SetColWidth(12,12,15); // TapTyyppi
	m_pwndEs->SetColWidth(13,13,120);// Selitys
	m_pwndEs->SetColWidth(14,14,150); // Huom
	m_pwndEs->SetColWidth(15,15,50); // Varmennus
	m_pwndEs->SetColWidth(16,16,20); // KassaID
	m_pwndEs->SetColWidth(17,17,0); // TapID

	m_pwndEs->GetParam()->EnableUndo(TRUE);
	m_pwndEs->SetFocus();
	//
	// --- tapahtumien rivit ---
	m_pwndERows->GetParam()->EnableUndo(FALSE);
	m_pwndERows->SetRowCount(0);
	m_pwndERows->SetColCount(7);

	m_pwndERows->SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("TuoteNr"));
	m_pwndERows->SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("Lkm"));
	m_pwndERows->SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("YksPaino"));
	m_pwndERows->SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("Kuvaus"));
	m_pwndERows->SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("Huom"));
	m_pwndERows->SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("Vakuus"));
	m_pwndERows->SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("Laina"));
	m_pwndERows->SetColWidth(0,0,20); // Rivi
	m_pwndERows->SetColWidth(1,1,60); // TuoteNr
	m_pwndERows->SetColWidth(2,2,25); // Lkm
	m_pwndERows->SetColWidth(3,3,80); // YksPaino
	m_pwndERows->SetColWidth(4,4,480); // Kuvaus
	m_pwndERows->SetColWidth(5,5,200); // Huom
	m_pwndERows->SetColWidth(6,6,60); // Vakuus
	m_pwndERows->SetColWidth(7,7,60); // Laina

	m_pwndERows->GetParam()->EnableUndo(TRUE);
	m_pwndEs->SetReadOnly(TRUE);
}

BOOL CDlgTapahtumat::UpdateRows()
{
	char buf[20];
	CString s = "";
	m_pwndEs->SetReadOnly(FALSE);
	m_pwndEs->SetTopRow(1);
	m_pwndEs->MoveCurrentCell(GX_TOPLEFT);
	m_pwndEs->SetRowCount(0);

	try
	{
		// --- luetaan tapahtumat ko. lainalle ---
		//
		m_pTapRS->m_strFilter.Format("TP_LA_Nr=%d", m_lNr);
		m_pTapRS->m_strSort = "TP_Tap desc"; // desc / asc
		m_pTapRS->Open();
		iRowCount = 0;
		/*while (!m_pTapRS->IsEOF())
		{
			iRowCount++;
			m_pTapRS->MoveNext();
		}
		if (iRowCount > 0)
			m_pTapRS->MoveFirst();
		TRACE("Tapahtumarivejä lainalle %ld on yhteensä %d kpl.", 0, iRowCount);
		*/
		while (!m_pTapRS->IsEOF())
		{
			iRowCount++;
			m_pwndEs->SetRowCount(iRowCount);

			sprintf(buf, "%s", m_pTapRS->m_TP_Aika.Format("%d.%m.%Y"));
			m_pwndEs->SetValueRange(CGXRange(iRowCount, 1), buf);

			m_pwndEs->SetValueRange(CGXRange(iRowCount, 2), m_pTapRS->m_TP_AM_Nimikirjaimet);
			if (!m_pTapRS->IsFieldNull(&m_pTapRS->m_TP_VakSumma))
			{
				s.Format("%7.2f", m_pTapRS->m_TP_VakSumma);
				m_pwndEs->SetValueRange(CGXRange(iRowCount, 3), s);
			}
			s.Format("%7.2f", m_pTapRS->m_TP_VanhaLaina);
			m_pwndEs->SetValueRange(CGXRange(iRowCount, 4), s);
			
			s.Format("%7.2f", m_pTapRS->m_TP_UusiLaina);
			m_pwndEs->SetValueRange(CGXRange(iRowCount, 5), s);

			s.Format("%7.2f", m_pTapRS->m_TP_UusiLaina - m_pTapRS->m_TP_VanhaLaina);    //MUUTOS
			m_pwndEs->SetValueRange(CGXRange(iRowCount, 6), s);

			if (!m_pTapRS->IsFieldNull(&m_pTapRS->m_TP_Korot))
			{
				s.Format("%7.2f", m_pTapRS->m_TP_Korot);
				m_pwndEs->SetValueRange(CGXRange(iRowCount, 7), s);
			}
			if (!m_pTapRS->IsFieldNull(&m_pTapRS->m_TP_SHVMaksut))
			{
				s.Format("%7.2f", m_pTapRS->m_TP_SHVMaksut);
				m_pwndEs->SetValueRange(CGXRange(iRowCount, 8), s);
			}
			if (!m_pTapRS->IsFieldNull(&m_pTapRS->m_TP_Toimitusmaksut))
			{
				s.Format("%7.2f", m_pTapRS->m_TP_Toimitusmaksut);
				m_pwndEs->SetValueRange(CGXRange(iRowCount, 9), s);
			}
			if (!m_pTapRS->IsFieldNull(&m_pTapRS->m_TP_AlePyor))
			{
				s.Format("%7.2f", m_pTapRS->m_TP_AlePyor);
				m_pwndEs->SetValueRange(CGXRange(iRowCount, 10), s);
			}
			
			s.Format("%7.2f", m_pTapRS->m_TP_Maksettava);
			m_pwndEs->SetValueRange(CGXRange(iRowCount, 11), s);

			m_pwndEs->SetValueRange(CGXRange(iRowCount, 12), m_pTapRS->m_TP_Tyyppi);

			if (m_pTapRS->m_TP_Tyyppi == "U")		// uusi laina -> vihr
			{
				m_pwndEs->SetStyleRange(CGXRange(iRowCount, 1, iRowCount, 17),
								CGXStyle().SetInterior(RGB(175,221,164))
								);
			}
			if (m_pTapRS->m_TP_Tyyppi == "D")  // uudistettu -> vihreä ?
			{
				m_pwndEs->SetStyleRange(CGXRange(iRowCount, 1, iRowCount, 17),
								CGXStyle().SetInterior(RGB(128,255,128))
								);
			}

			if (m_pTapRS->m_TP_Tyyppi == "L")  // Lunastus sininen
			{
				m_pwndEs->SetStyleRange(CGXRange(iRowCount, 1, iRowCount, 17),
								CGXStyle().SetInterior(RGB(137,248,237))
								);
			}


			m_pwndEs->SetValueRange(CGXRange(iRowCount, 13), m_pTapRS->m_TP_Selitys);
			m_pwndEs->SetValueRange(CGXRange(iRowCount, 14), m_pTapRS->m_TP_Huom);
			m_pwndEs->SetValueRange(CGXRange(iRowCount, 15), m_pTapRS->m_TP_Varmennus);
			m_pwndEs->SetValueRange(CGXRange(iRowCount, 16), m_pTapRS->m_TP_KS_Tunnus);
			m_pwndEs->SetValueRange(CGXRange(iRowCount, 17), m_pTapRS->m_TP_Tap);


			m_pTapRS->MoveNext();
		}
		m_pTapRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pTapRS->Close();
		return FALSE;
	}
	m_pwndEs->SetReadOnly(TRUE);
	return TRUE;
}


void CDlgTapahtumat::OnShowEventRows()
{
	TRACE("Valittun tap tunnus: %ld\n", m_pwndEs->m_lCurrentLoanEventNr );
	m_pwndEs->SetReadOnly(FALSE);
	theApp.m_pMC->m_pDB->fillEventRows(m_pwndERows, m_pwndEs->m_lCurrentLoanEventNr);
	m_pwndEs->SetReadOnly(TRUE);
}








