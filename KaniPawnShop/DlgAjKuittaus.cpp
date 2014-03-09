// DlgAjKuittaus.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgAjKuittaus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAjKuittaus dialog


CDlgAjKuittaus::CDlgAjKuittaus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAjKuittaus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAjKuittaus)
	m_sCustID = _T("");
	m_sCusName = _T("");
	m_sPersonID = _T("");
	m_sDeficit = _T("0.00");
	m_sBalance = _T("0.00");
	m_sPayment = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAjKuittaus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAjKuittaus)
	DDX_Text(pDX, IDC_CUSTID, m_sCustID);
	DDX_Text(pDX, IDC_CUSTNAME, m_sCusName);
	DDX_Text(pDX, IDC_PERSONID, m_sPersonID);
	DDX_Text(pDX, IDC_DEFICIT, m_sDeficit);
	DDX_Text(pDX, IDC_BALANCE, m_sBalance);
	DDX_Text(pDX, IDC_PAYMENT, m_sPayment);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAjKuittaus, CDialog)
	//{{AFX_MSG_MAP(CDlgAjKuittaus)
	ON_BN_CLICKED(IDC_ACCEPT, OnAccept)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAjKuittaus message handlers

BOOL CDlgAjKuittaus::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_sCustID.Format("%ld", m_lCustomerID);

	//CTime t = CTime::GetCurrentTime();
	//CTime tTheTime((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	//CTimeSpan ts;


	m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->m_strFilter.Format("AS_ID = %ld", m_lCustomerID);
	try
	{
		m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->Open();
		if (!m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->IsEOF())
		{
			m_sCusName = m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->m_AS_Nimi;
			m_sPersonID = m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->m_AS_HTun;
			if (!m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->IsFieldNull(&m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->m_AS_Alij))
				m_sDeficit.Format("%7.2f", m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->m_AS_Alij);
			if (!m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->IsFieldNull(&m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->m_AS_Ylij))
				m_sBalance.Format("%7.2f", m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->m_AS_Ylij);
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
	m_pCAuctionCtrl->getMainCtl()->getDBCtl()->getAsRs()->Close();


	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAjKuittaus::OnAccept()
{
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	m_dPayment = atof(m_sPayment);
	if (m_dPayment <= 0)
		return;
	TRACE("Asiakkaan suorittama alijäämämaksu %7.2f\n", m_dPayment);
	m_pCAuctionCtrl->printDeficitPaymentReceipt(m_dPayment, m_lCustomerID);
	OnOK();
}

void CDlgAjKuittaus::OnCancel()
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CDlgAjKuittaus::OnOK()
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}
