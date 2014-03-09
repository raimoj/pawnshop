// DlgHaltijanMuutos.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgHaltijanMuutos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgHaltijanMuutos dialog


CDlgHaltijanMuutos::CDlgHaltijanMuutos(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHaltijanMuutos::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHaltijanMuutos)
	m_sLainaNr = _T("");
	m_sAsNimi = _T("");
	m_sHtun1 = _T("");
	m_sHtun2 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgHaltijanMuutos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHaltijanMuutos)
	DDX_Text(pDX, IDC_LANR, m_sLainaNr);
	DDX_Text(pDX, IDC_ASNIMI, m_sAsNimi);
	DDX_Text(pDX, IDC_HTUN1, m_sHtun1);
	DDX_Text(pDX, IDC_HTUN2, m_sHtun2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHaltijanMuutos, CDialog)
	//{{AFX_MSG_MAP(CDlgHaltijanMuutos)
	ON_BN_CLICKED(IDC_MOVE, OnMove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHaltijanMuutos message handlers

void CDlgHaltijanMuutos::OnMove()
{
	CString strText = "";
	CString sHT = "";
	CString sN = "";
	UpdateData(TRUE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	sHT = theApp.RemoveSpaces(m_sHtun2);
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	sN = m_pMC->getDBCtl()->getCustomerName(sHT);
	if (sN == "?")
	{
		strText.Format("Asiakasta ei l�ydy: Htun='%s'\nTalleteta asiakastiedot ensin !", sHT);
		AfxMessageBox(strText);
		return;
	}

	strText.Format("Uuden asiakkaan henkil�tunnus '%s'\nNimi: '%s'\n\nTalletetaanko lainatiedot ?", sHT, sN);
	if (AfxMessageBox(strText, MB_YESNO) == IDYES /*IDNO*/)
	{
		m_pMC->changeLoanOwner(sHT, m_sHtun1);
	}
	CLoan* pcLoan;
	pcLoan = new CLoan(atol(m_sLainaNr));
	pcLoan->getCDBLoan()->printTicket();
	
	//
	// --- talletetaan tapahtuma ---
	pcLoan->getCDBLoan()->writeLoanEvent("B",				// tap. tyyppi esim D=uudistus
										"Haltijan muutos",	// explanation
										"", 
										pcLoan->getCDBLoan()->m_LA_VakSumma, // lainan vakuusarvo // on jo euroina
										pcLoan->getCDBLoan()->m_LA_Laina,	// vanha lainasumma	// on jo euroina
										pcLoan->getCDBLoan()->m_LA_Laina,	// uusi lainasumma =0 lunastuksessa
										0,  // euroa		// maksettava
										"_", // varmennus
										0,		//Rahasumma kassasiirroissa. T�ll�in operaatio ei kohdistu mihink��n lainaan, joten KL_LainaNr-kentt� j�� tyhj�ksi
										0, // korot
										0,		// shv-maksut
										0,	// toimitusmaksut: ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
										0,		//alennus+ py�ristys, Rahasumma laskennallisen summan py�rist�miseksi sopivaksi tasaluvuksi (=Maksettava)
										0,	// alij��m�	
										0	// ylij��m�	
										);
	delete pcLoan;

	OnOK();
}

void CDlgHaltijanMuutos::OnOK()
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}
