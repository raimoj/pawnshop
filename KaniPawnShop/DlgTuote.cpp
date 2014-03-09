// DlgTuote.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgTuote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTuote dialog


extern CPanttiApp theApp;


CDlgTuote::CDlgTuote(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTuote::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTuote)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT


	//m_pGXTuoterivit = new CRGXTuoterivit;

	m_pGXTuoterivit2 = new CRGXTuoterivit2;
	m_pGXTuoteryhmat = new CRGXTuoteryhmat;

	//m_pTuRS = new CTuoteRS;
	//m_pTuRS->m_pDatabase = theApp.GetDatabase();
}

CDlgTuote::~CDlgTuote()
{
	//delete m_pGXTuoterivit;
	delete m_pGXTuoterivit2;
	delete m_pGXTuoteryhmat;
	//delete m_pTuRS;
}

void CDlgTuote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTuote)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	//DDV_GXGridWnd(pDX, m_pGXTuoterivit);
}


BEGIN_MESSAGE_MAP(CDlgTuote, CDialog)
	//{{AFX_MSG_MAP(CDlgTuote)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTuote message handlers

BOOL CDlgTuote::OnInitDialog()
{
	CGXStyle style;
	//style.SetControl(
	CDialog::OnInitDialog();

	//m_pGXTuoterivit->SubclassDlgItem(IDC_TUOTELISTA, this);
	//m_pGXTuoterivit->Initialize();

	m_pGXTuoteryhmat->SubclassDlgItem(IDC_TUOTERYHMAT, this);
	m_pGXTuoteryhmat->Initialize();
	m_pGXTuoteryhmat->GetParam()->SetNewGridLineMode(TRUE);

	m_pGXTuoterivit2->SubclassDlgItem(IDC_TUOTELISTA2, this);
	m_pGXTuoterivit2->Initialize();
	m_pGXTuoterivit2->GetParam()->SetNewGridLineMode(TRUE);
	m_pGXTuoterivit2->SetStyleRange(CGXRange().SetCols(1),
								CGXStyle().SetReadOnly(TRUE));
	m_pGXTuoterivit2->SetStyleRange(CGXRange().SetCols(6),
								CGXStyle().SetControl(GX_IDS_CTRL_COMBOBOX).SetChoiceList("kpl\ng\nKPL\nG\nGR"));

	//m_pGXTuoterivit2->SetStyleRange(CGXRange().SetCols(1),
	//							CGXStyle().SetColWidth());
	//m_pGXTuoterivit2->SetDefaultColWidth(30);

	SetColumns();
	//ShowTuotteet();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTuote::SetColumns()
{
	m_pGXTuoterivit2->GetParam()->EnableUndo(FALSE);
	//m_pGXTuoterivit2->SetRowCount(50);
	m_pGXTuoterivit2->SetColCount(7);

	m_pGXTuoterivit2->SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("ID-tunnus"));
	m_pGXTuoterivit2->SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("TRyhmä"));
	m_pGXTuoterivit2->SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("TNr"));
	m_pGXTuoterivit2->SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("Kuvaus"));
	m_pGXTuoterivit2->SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("Jalomet"));
	m_pGXTuoterivit2->SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("Yks"));
	m_pGXTuoterivit2->SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("YksHinta"));

	m_pGXTuoterivit2->SetColWidth(0,0,20); // rivinro
	m_pGXTuoterivit2->SetColWidth(1,1,0); // ID  // poistettu näkyvistä!!!
	m_pGXTuoterivit2->SetColWidth(2,2,40); // Tuoteryhmä
	m_pGXTuoterivit2->SetColWidth(3,3,40); // Tuotenumero
	m_pGXTuoterivit2->SetColWidth(4,4,250); // kuvaus
	m_pGXTuoterivit2->SetColWidth(5,5,50); // jmet
	m_pGXTuoterivit2->SetColWidth(6,6,60); // Yks
	m_pGXTuoterivit2->SetColWidth(7,7,60); // YksHinta

//	m_pGXTuoterivit->SetStyleRange(
//		range.SetCols(3), CGXStyle().SetControl(GX_IDS_CTRL_CHECKBOX3D)/*.SetChoiceList(_T("Checkbox")*/
//		);

	/*m_pGXTuoterivit->SetStyleRange(CGXRange(2, 2), CGXStyle()
			.SetControl(GX_IDS_CTRL_TEXTFIT)
			.SetChoiceList(_T("one\ntwo\nthree\nfour\nfive\nsix\nseven\neight"))
		);*/
//	m_pGXTuoterivit->GetParam()->EnableUndo(TRUE);
//	m_pGXTuoterivit->SetFocus();
}

BOOL CDlgTuote::ShowTuotteet()
{
	//CString stmp = "";
	//char buf[20];
/*	m_pGXTuoterivit->SetTopRow(1);
	m_pGXTuoterivit->MoveCurrentCell(GX_TOPLEFT);
	m_pGXTuoterivit->SetRowCount(1);

	try
	{
		m_pTuRS->m_strFilter.Format("");
		m_pTuRS->Open();
		m_iRowCount = 0;
		while (!m_pTuRS->IsEOF())
		{
			m_iRowCount++;
			m_pGXTuoterivit->SetRowCount(m_iRowCount);

			m_pGXTuoterivit->SetValueRange(CGXRange(m_iRowCount, 1), m_pTuRS->m_TU_Numero);
			m_pGXTuoterivit->SetValueRange(CGXRange(m_iRowCount, 2), m_pTuRS->m_TU_Kuvaus);
			//m_pGXTuoterivit->SetValueRange(CGXRange(m_iRowCount, 3), m_pTuRS->m_TU_Jalometalli);
			//m_pGXTuoterivit->SetValueRange(  SetValueRange(CGXRange(m_iRowCount, 3), 1);
			// ---------------
*/			/*stmp.Format("'%7.2f'\n", m_pTuRS->m_KS_Saldo);
			TRACE("%s\n", stmp);
			TRACE("Saldo      ='%f'\n", m_pTuRS->m_KS_Saldo);
			if (m_pKRS->m_KS_Saldo == NULL)
				stmp.Format("%7.2f", 0);
			else
				stmp.Format("%7.2f", m_pTuRS->m_KS_Saldo);
			m_pGXTuoterivit->SetValueRange(CGXRange(m_iRowCount, 3), stmp);
			*/// ---------------
			/*if (m_pTuRS->m_KS_PvkAjoAika == NULL)
				sprintf(buf, "%s", "?");
			else
				sprintf(buf, "%s", m_pTuRS->m_KS_PvkAjoAika.Format("%d.%m.%Y"));
			m_pGXTuoterivit->SetValueRange(CGXRange(m_iRowCount, 4), buf);
			m_pGXTuoterivit->SetValueRange(CGXRange(m_iRowCount, 5), m_pTuRS->m_KS_Tunnus);
	*/
/*			m_pTuRS->MoveNext();
		}
		m_pTuRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pTuRS->Close();
		return FALSE;
	}
	//m_pGXTuoterivit->SetValueRange(CGXRange(1, 1), "TuNro");
	//m_pGXTuoterivit->SetValueRange( CGXRange(1, 3), TRUE); // Ei toimi
	//m_pGXTuoterivit->SetValueRange( CGXRange(1, 3), short(TRUE)); // toimii
	m_pGXTuoterivit->SetValueRange( CGXRange(1, 3), _T("1")); // toimii
*/	return TRUE;
}

void CDlgTuote::OnOK()
{
	//CString sTulos;
		//m_pGXTuoterivit->SetValueRange( CGXRange(1, 3), short(TRUE)); // toimii
		//m_pGXTuoterivit->SetValueRange( CGXRange(1, 3), _T("1")); // toimii
	//sTulos = m_pGXTuoterivit->GetValueRowCol(1,3);
	//if (sTulos == "1")
	//	TRACE("TRUE\n");
	//else
	//	TRACE("FALSE\n");

	CDialog::OnOK();
}
