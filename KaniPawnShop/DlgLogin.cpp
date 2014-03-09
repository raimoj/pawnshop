// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgLogin.h"
#include "ArviomiesRS.h"
#include "KassaRS.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog


CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogin)
	m_sUserId = _T("");
	m_sKassanNimi = _T("");
	m_sPassWord = _T("");
	//}}AFX_DATA_INIT
	m_bDeskOK = FALSE;
}


void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogin)
	DDX_Control(pDX, IDC_KASSA, m_ctlKassa);
	DDX_Control(pDX, IDC_USERID, m_ctlUserId);
	DDX_CBString(pDX, IDC_USERID, m_sUserId);
	DDX_CBString(pDX, IDC_KASSA, m_sKassanNimi);
	DDX_Text(pDX, IDC_PW, m_sPassWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	//{{AFX_MSG_MAP(CDlgLogin)
	ON_CBN_SELCHANGE(IDC_USERID, OnSelchangeUserid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin message handlers

void CDlgLogin::OnOK()
{
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	CDialog::OnOK();
}

BOOL CDlgLogin::OnInitDialog()
{
	CDialog::OnInitDialog();
	long lSelDesk = 0;
	int iSelRow = 0;
	int iRow = 0;

	//
	// --- arviomiehet ---
	//
	CArviomiesRS arm;
	arm.m_pDatabase = theApp.GetDatabase();
	try
	{
		arm.m_strFilter.Format("");
		arm.m_strSort = "AM_Nimikirjaimet";
		arm.Open();
		while (!arm.IsEOF())
		{
			TRACE("AM='%s'\n", theApp.RemoveSpaces(arm.m_AM_Nimikirjaimet));
			m_ctlUserId.SetItemData(
      			m_ctlUserId.InsertString(-1, arm.m_AM_Nimikirjaimet),
      			arm.m_AM_Tunnus);

			arm.MoveNext();
		}
		arm.Close();
	}
	catch (CDBException* e)
	{
		e->Delete();
		arm.Close();
	}
	//
	// --- kassat ---
	//
	CKassaRS ks;
	ks.m_pDatabase = theApp.GetDatabase();
	try
	{
		ks.m_strFilter.Format("");
		ks.m_strSort = "KS_KassanNimi";
		ks.Open();
		while (!ks.IsEOF())
		{
			iRow++;
			TRACE("KS='%s'\n", theApp.RemoveSpaces(ks.m_KS_KassanNimi));
			m_ctlKassa.SetItemData(
      			m_ctlKassa.InsertString(-1, ks.m_KS_KassanNimi),
      			ks.m_KS_Tunnus);
			if (ks.m_KS_KassanNimi == theApp.m_sDesk)
			{
				lSelDesk = ks.m_KS_Tunnus;
				TRACE("KassanNimi=%s\n", theApp.m_sDesk);
				iSelRow = iRow;
			}
			ks.MoveNext();
		}
		ks.Close();
	}
	catch (CDBException* e)
	{
		e->Delete();
		ks.Close();
	}

	if (m_bDeskOK == TRUE)
	{
		TRACE("Valitaan %ld. rivi listalta\n", iSelRow-1);
		m_ctlKassa.SetCurSel(iSelRow-1);
		m_ctlKassa.EnableWindow(FALSE);
	}
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLogin::OnSelchangeUserid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgLogin::OnCancel() 
{
	// TODO: Add extra cleanup here
	MessageBeep(0);
	//CDialog::OnCancel();
}
