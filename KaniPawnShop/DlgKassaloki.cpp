// DlgKassaloki.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgKassaloki.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CDlgKassaloki dialog


CDlgKassaloki::CDlgKassaloki(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKassaloki::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKassaloki)
	m_sPvm = _T("");
	//}}AFX_DATA_INIT
	m_pDeskLogRows = new CRGXDeskLogRows;
	m_pKRS = new CKassaRS;
	m_pKRS->m_pDatabase = theApp.GetDatabase();
}


CDlgKassaloki::~CDlgKassaloki()
{
	delete m_pDeskLogRows;
	delete m_pKRS;
}


void CDlgKassaloki::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKassaloki)
	DDX_Control(pDX, IDC_KASSA, m_ctlKassa);
	DDX_Text(pDX, IDC_PVM, m_sPvm);
	DDV_MaxChars(pDX, m_sPvm, 10);
	//}}AFX_DATA_MAP
	DDV_GXGridWnd(pDX, m_pDeskLogRows);
}


BEGIN_MESSAGE_MAP(CDlgKassaloki, CDialog)
	//{{AFX_MSG_MAP(CDlgKassaloki)
	ON_CBN_SELCHANGE(IDC_KASSA, OnSelchangeKassa)
	ON_BN_CLICKED(IDC_HAE, OnHae)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKassaloki message handlers

BOOL CDlgKassaloki::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CTime t = CTime::GetCurrentTime();
	CString s = "";
	s.Format("%s", t.Format("%d.%m.%Y@%H:%M.%S"));
	TRACE("%s\n", s);
	
	int ivuosi = t.GetYear();
	int ikk = t.GetMonth();
	int ipv = t.GetDay();
	CTime tx(ivuosi, ikk, ipv, 0, 0, 0);
	s.Format("%d.%d.%d", ipv, ikk,ivuosi);
	m_sPvm = s;

	// TODO: Add extra initialization here
	m_pDeskLogRows->SubclassDlgItem(IDC_DESKLOGROWS, this);
	m_pDeskLogRows->Initialize();
	m_pDeskLogRows->initGrid();
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	getDeskList();
	
	m_pDeskLogRows->fillGrid(tx, theApp.m_lDeskId);

	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/** funktio lukee kassojen tiedot dropdown-listaan */

void CDlgKassaloki::getDeskList()
{
	CString stmp = "";
	long ld = -1;
	int i = 0;
	
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	m_ctlKassa.ResetContent();
	//TRACE("Lisätään ensimmäinen rivi 'Kaikki'\n");
	m_ctlKassa.SetItemData(
    		m_ctlKassa.InsertString(-1, "Kaikki kassat"),
    		-1);
	try
	{
		m_pKRS->m_strFilter.Format("");
		m_pKRS->Open();
		while (!m_pKRS->IsEOF())
		{
			//
			// -- kassatiedot valikoihin ---
			i = i + 1;
			m_ctlKassa.SetItemData(
      			m_ctlKassa.InsertString(-1, m_pKRS->m_KS_KassanNimi),
      			m_pKRS->m_KS_Tunnus);
	
			if (theApp.m_lDeskId == m_pKRS->m_KS_Tunnus)
			{
				ld = i;
			}
			m_pKRS->MoveNext();
		}
		m_pKRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKRS->Close();
	}
	m_ctlKassa.SetCurSel(ld);
}



void CDlgKassaloki::OnSelchangeKassa() 
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	long lKassa = m_ctlKassa.GetItemData(m_ctlKassa.GetCurSel());
	//m_pDeskLogRows->fillGrid(NULL, lKassa);
	OnHae();
}

void CDlgKassaloki::OnHae() 
{
	CString s = "";
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	long lKassa = m_ctlKassa.GetItemData(m_ctlKassa.GetCurSel());
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	CTime tx = theApp.GetDate(theApp.dot(m_sPvm));
	//s.Format("%s", tx.Format("%d.%m.%Y@%H:%M.%S"));
	//TRACE("%s\n", s);
	m_pDeskLogRows->fillGrid(tx, lKassa);
}
