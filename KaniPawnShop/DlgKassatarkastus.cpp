// DlgKassatarkastus.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgKassatarkastus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgKassatarkastus dialog


CDlgKassatarkastus::CDlgKassatarkastus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKassatarkastus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKassatarkastus)
	m_sKassanNimi = _T("");
	m_sArviomies = _T("");
	m_sAika = _T("");
	m_sEdellinenTarkastusaika = _T("");
	m_sEdellinenSaldo = _T("");
	m_sSaldo = _T("");
	m_sYht = _T("");
	//}}AFX_DATA_INIT

	m_KassaRS.m_pDatabase = theApp.GetDatabase();
	m_KassalokiRS.m_pDatabase = theApp.GetDatabase();
}


void CDlgKassatarkastus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKassatarkastus)
	DDX_Text(pDX, IDC_KASSA, m_sKassanNimi);
	DDX_Text(pDX, IDC_ARVIOMIES, m_sArviomies);
	DDX_Text(pDX, IDC_AIKA, m_sAika);
	DDX_Text(pDX, IDC_AIKA2, m_sEdellinenTarkastusaika);
	DDX_Text(pDX, IDC_EDELLINENSALDO, m_sEdellinenSaldo);
	DDX_Text(pDX, IDC_SALDOTOSITTEIDENMUKAAN, m_sSaldo);
	DDX_Text(pDX, IDC_YHT, m_sYht);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKassatarkastus, CDialog)
	//{{AFX_MSG_MAP(CDlgKassatarkastus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKassatarkastus message handlers

BOOL CDlgKassatarkastus::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*CTime */t = CTime::GetCurrentTime();
	/*CString */sDateAndTime = t.Format("%d.%m.%Y, klo: %H.%M.%S");

	CString sDT = "";


	m_sKassanNimi = theApp.m_sDesk;
	m_sArviomies = theApp.m_sUser;
	m_sAika = sDateAndTime;

	try
	{
		m_KassaRS.m_strFilter.Format("KS_Tunnus=%ld", theApp.m_lDeskId);
		//m_KassaRS.m_strSort = "";
		m_KassaRS.Open();
		if (! m_KassaRS.IsEOF())
		{
			if (m_KassaRS.m_KS_TarkastusAika != NULL)
			{
				CTime t2 = m_KassaRS.m_KS_TarkastusAika;
				sDT = t2.Format("%d.%m.%Y@%H.%M.%S");
				m_sEdellinenTarkastusaika = sDT;
			}
			else
			{
				m_sEdellinenTarkastusaika = "?";
			}
			m_sEdellinenSaldo.Format("%7.2f", m_KassaRS.m_KS_Saldo);

			//m_KassaRS.MoveNext();
		}

		m_KassaRS.Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_KassaRS.Close();
	}

	m_dS = GetTotal(theApp.m_lDeskId, m_KassaRS.m_KS_TarkastusAika);
	m_sSaldo.Format("%7.2f", m_dS);
	m_sYht.Format("%7.2f", m_dS + m_KassaRS.m_KS_Saldo);
	m_dS = m_dS + m_KassaRS.m_KS_Saldo;
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


double CDlgKassatarkastus::GetTotal(long lDeskId, CTime tchecked)
{
	double dS = 0;
	t = CTime::GetCurrentTime();
	m_KassalokiRS.m_pDatabase = theApp.GetDatabase();

	try
	{
		m_KassalokiRS.m_strFilter.Format("KL_KS_Tunnus = %ld", theApp.m_lDeskId);
		m_KassalokiRS.m_strSort = "KL_Aika desc";
		m_KassalokiRS.Open();
		while (! m_KassalokiRS.IsEOF())
		{

			if ((tchecked == NULL) || (tchecked < m_KassalokiRS.m_KL_Aika))
			{
				//TRACE("KL_Summa=%7.2f\n", m_KassalokiRS.m_KL_Summa);
				if (m_KassalokiRS.m_KL_TapahtumanTyyppi == "U" ||
					m_KassalokiRS.m_KL_TapahtumanTyyppi == "D" ||
					m_KassalokiRS.m_KL_TapahtumanTyyppi == "L" ||
					m_KassalokiRS.m_KL_TapahtumanTyyppi == "K" ||
					m_KassalokiRS.m_KL_TapahtumanTyyppi == "C" ||
					m_KassalokiRS.m_KL_TapahtumanTyyppi == "E" ||
					m_KassalokiRS.m_KL_TapahtumanTyyppi == "F" ||
					m_KassalokiRS.m_KL_TapahtumanTyyppi == "X" )
				{
					dS = dS + m_KassalokiRS.m_KL_Maksettava;
					TRACE(" - %7.2f", m_KassalokiRS.m_KL_Maksettava);
				}
				else
				{
					dS = dS + m_KassalokiRS.m_KL_Summa;
					TRACE(" + %7.2f", m_KassalokiRS.m_KL_Summa);
				}
			}

			m_KassalokiRS.MoveNext();
		}
		TRACE("\n");

		m_KassalokiRS.Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_KassalokiRS.Close();
		return 0;
	}
	return dS;
}

void CDlgKassatarkastus::OnOK()
{
	UpdateData(); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	UpdateDeskBalance();
	CDialog::OnOK();
}

BOOL CDlgKassatarkastus::UpdateDeskBalance()
{
	CString msg = "";
	//TRACE("Pankkikorttitositteita: %7.2f\n", atof(m_sPKTositteita));
	TRACE("Uusi saldo            : %7.2fe\n", m_dS);
	t = CTime::GetCurrentTime();
	sDateAndTime = t.Format("%d.%m.%Y, klo: %H.%M.%S");

	msg.Format("Tarkastuksen vahvistaminen %s\nSaldo=%7.2f", sDateAndTime, m_dS);
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return TRUE;
	}

	try
	{
		m_KassaRS.m_strFilter.Format("KS_Tunnus=%ld", theApp.m_lDeskId);
		//m_KassaRS.m_strSort = "";
		m_KassaRS.Open();
		if (! m_KassaRS.IsEOF())
		{
			m_KassaRS.Edit();

			m_KassaRS.m_KS_TarkastusAika = t;
			sDateAndTime = m_KassaRS.m_KS_TarkastusAika.Format("%d.%m.%Y, klo: %H.%M.%S");
			TRACE("AikaTalletettaessa=%s\n", sDateAndTime);
			m_KassaRS.m_KS_Saldo = m_dS;

			m_KassaRS.Update();
		}

		m_KassaRS.Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_KassaRS.Close();
		return FALSE;
	}

	return TRUE;
}

