// DlgArviomies.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgArviomies.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CDlgArviomies dialog


CDlgArviomies::CDlgArviomies(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgArviomies::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgArviomies)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pGXArviomies = new CRGXArviomies;
	m_pAMRS = new CArviomiesRS;
	m_pAMRS->m_pDatabase = theApp.GetDatabase();


}

CDlgArviomies::~CDlgArviomies()
{
	delete m_pAMRS;
	delete m_pGXArviomies;
}


void CDlgArviomies::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgArviomies)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX, m_pGXArviomies);
}


BEGIN_MESSAGE_MAP(CDlgArviomies, CDialog)
	//{{AFX_MSG_MAP(CDlgArviomies)
	ON_BN_CLICKED(IDC_UUSI_ARVIOMIESRIVI, OnUusiArviomiesrivi)
	ON_BN_CLICKED(IDC_TALLETA, OnTalleta)
	ON_BN_CLICKED(IDC_POISTA, OnPoista)
	ON_CONTROL(RJ_OG_PARENT_DLG, IDC_ARVIOMIESRIVIT, OnValuerListClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgArviomies message handlers

BOOL CDlgArviomies::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pGXArviomies->SubclassDlgItem(IDC_ARVIOMIESRIVIT, this);
	m_pGXArviomies->Initialize();


	//m_pGXArviomies->GetParam()->EnableUndo(FALSE);
	m_pGXArviomies->SetRowCount(50);
	m_pGXArviomies->SetColCount(4);

	m_pGXArviomies->SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("Nkirj"));
	m_pGXArviomies->SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("Nimi"));
	m_pGXArviomies->SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("Oikeudet"));
	m_pGXArviomies->SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("Tunnus"));
	m_pGXArviomies->SetColWidth(0,0,20); // Rivinrot
	m_pGXArviomies->SetColWidth(1,1,50); // Nimi
	m_pGXArviomies->SetColWidth(2,2,150); // Nimi
	m_pGXArviomies->SetColWidth(3,3,20); // Oikeudet
	m_pGXArviomies->SetColWidth(4,4,0); // Tunnus =ID

	//m_pGXArviomies->GetParam()->EnableUndo(TRUE);
	m_pGXArviomies->SetFocus();

	ShowArviomiehet();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgArviomies::ShowArviomiehet()
{
	m_pGXArviomies->SetTopRow(1);
	m_pGXArviomies->MoveCurrentCell(GX_TOPLEFT);
	m_pGXArviomies->SetRowCount(0);

	try
	{
		// --- luetaan arviomiesten tiedot ---
		//
		m_pAMRS->m_strFilter.Format("");
		m_pAMRS->Open();
		iRowCount = 0;
		while (!m_pAMRS->IsEOF())
		{
			iRowCount++;
			m_pGXArviomies->SetRowCount(iRowCount);

			m_pGXArviomies->SetValueRange(CGXRange(iRowCount, 1), m_pAMRS->m_AM_Nimikirjaimet);
			m_pGXArviomies->SetValueRange(CGXRange(iRowCount, 2), m_pAMRS->m_AM_Nimi);
			m_pGXArviomies->SetValueRange(CGXRange(iRowCount, 3), m_pAMRS->m_AM_Oikeudet);
			m_pGXArviomies->SetValueRange(CGXRange(iRowCount, 4), m_pAMRS->m_AM_Tunnus);

			m_pAMRS->MoveNext();
		}
		m_pAMRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAMRS->Close();
		return FALSE;
	}
	return TRUE;
}

void CDlgArviomies::OnUusiArviomiesrivi()
{
	OnTalleta();
	try
	{
		m_pAMRS->m_strFilter.Format("");
		m_pAMRS->Open();
		m_pAMRS->AddNew();

		m_pAMRS->m_AM_Nimikirjaimet = "?";
		m_pAMRS->m_AM_Nimi = "?";
		m_pAMRS->m_AM_Oikeudet = 0;

		m_pAMRS->Update();
		m_pAMRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAMRS->Close();
	}
	ShowArviomiehet();
}

void CDlgArviomies::OnOK()
{
	OnTalleta();
	CDialog::OnOK();
}

BOOL CDlgArviomies::PoistaAM()
{
	/*try
	{
		m_pAMRS->m_strFilter.Format("");
		m_pAMRS->Open();
		while (!m_pAMRS->IsEOF())
		{
			m_pAMRS->Delete();
			m_pAMRS->MoveNext();
		}
		m_pAMRS->Close();
	}
	catch (CDBException* e)
	{
		e->Delete();
		m_pAMRS->Close();
		return FALSE;
	}*/
	return TRUE;
}

void CDlgArviomies::OnTalleta()
{
	UINT r = 0;
	TRACE("Rivejä %d kpl\n", m_pGXArviomies->GetRowCount());
	/*for (r = 1; r <= m_pGXArviomies->GetRowCount(); r++)
	{
		TRACE("Nimi=%s\n", m_pGXArviomies->GetValueRowCol(r,2));

	}*/
	for (r = 1; r <= m_pGXArviomies->GetRowCount(); r++)
	{
		TRACE("Nimmari=%s\n", m_pGXArviomies->GetValueRowCol(r,1));
		if ( ! m_pGXArviomies->GetValueRowCol(r,1).IsEmpty())
		{
			UpdateAM(	atol(m_pGXArviomies->GetValueRowCol(r,4)),
						theApp.RemoveSpaces( m_pGXArviomies->GetValueRowCol(r,1)),
						m_pGXArviomies->GetValueRowCol(r,2),
						atoi(m_pGXArviomies->GetValueRowCol(r,3)) );

		}
		else
		{
			MessageBeep(1);
		}
	}
}

void CDlgArviomies::UpdateAM(long lAMId, CString sNimikirj, CString sNimi, int iOik)
{
	TRACE("Talletetaan Arviomies #%ld\n", lAMId);
	try
	{
		m_pAMRS->m_strFilter.Format("AM_Tunnus = %ld", lAMId);
		m_pAMRS->Open();
		if ( ! m_pAMRS->IsEOF())
		{
			m_pAMRS->Edit();

			m_pAMRS->m_AM_Nimikirjaimet = theApp.RemoveSpaces(sNimikirj);
			m_pAMRS->m_AM_Nimi = theApp.RemoveSpaces(sNimi);
			m_pAMRS->m_AM_Oikeudet = iOik;

			m_pAMRS->Update();
		}
		m_pAMRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAMRS->Close();
	}

}

void CDlgArviomies::OnPoista()
{
	ROWCOL nRow, nCol;
	long lAMId = 0;

	/*if ( ! m_bDeskSelectionOK)
	{
		return;
	}*/
	if (m_pGXArviomies->GetCurrentCell(nRow, nCol)) // valittu kassalistan rivi
	{
		if (nRow >=1)
		{
			TRACE("Poistettava rivi %d\n", nRow);
			lAMId = atol(m_pGXArviomies->GetValueRowCol(nRow,4));
			TRACE("Poistettavan AM:n tunnus = %ld\n", lAMId);

			try
			{
				m_pAMRS->m_strFilter.Format("AM_Tunnus = %ld", lAMId);
				m_pAMRS->Open();
				if ( ! m_pAMRS->IsEOF())
				{
					m_pAMRS->Delete();
				}
				m_pAMRS->Close();
			}
			catch (CDBException* e)
			{
				AfxMessageBox(e->m_strError);
				e->Delete();
				m_pAMRS->Close();
			}
		}
		ShowArviomiehet();
	}
}

void CDlgArviomies::OnValuerListClicked()
{
	CString stmp = "";
	TRACE("OnValuerListClicked!\n");
	ROWCOL nRow, nCol;
    if (m_pGXArviomies->GetCurrentCell(nRow, nCol)) // valittu arviomieslistan rivi
	{
		if (nRow >=1)
		{
			TRACE("Rivi %d\n", nRow);
		}
	}
}
