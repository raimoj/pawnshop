// DlgYjTilitys.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgYjTilitys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgYjTilitys dialog



CDlgYjTilitys::CDlgYjTilitys(CAuctionCtrl* pActrl, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgYjTilitys::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgYjTilitys)
	m_sCustomerinfo = _T("");
	m_sYj = _T("");
	//}}AFX_DATA_INIT
	m_pCAuctionCtrl = pActrl;
}

void CDlgYjTilitys::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgYjTilitys)
	DDX_Text(pDX, IDC_CUSTOMERINFO, m_sCustomerinfo);
	DDX_Text(pDX, IDC_YJ, m_sYj);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgYjTilitys, CDialog)
	//{{AFX_MSG_MAP(CDlgYjTilitys)
	ON_BN_CLICKED(IDCANCEL, OnCancelMaksa)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgYjTilitys message handlers


BOOL CDlgYjTilitys::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_sCustomerinfo = this->m_pCAuctionCtrl->m_pMC->m_pLoan->getCustomerInfo().m_AS_Nimi + " " +
		this->m_pCAuctionCtrl->m_pMC->m_pLoan->getCustomerInfo().m_AS_HTun;
	m_sYj.Format("Maksettava ylijäämä (ei kirjemaks) = %7.2f", this->m_pCAuctionCtrl->m_pcs->m_dPayableAuctionBalance);
	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgYjTilitys::OnCancelMaksa() 
{
	
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int xPos = 218;
	int yPos = 562;
	int iSivunAlku = 4; // cm, ensimm. sivu lyhyempi, seuraavat sivut tulostetaan yläreunasta alkaen
	CString strText = "";
	CString str = "";
	int lRows = 0;
	int iRo = 0;
	int iLRivinKork = 0;
	CString  tyhjaa = "                                                  "; //n.50 merkkiä
		long lAsID = 0;
	CString tmp = "";
	double dAsYlij = 0;
	double dYlij = 0;
	double dM = 0;
	double dY = 0;
	double dA = 0;
	double dAuctionBalance = 0;
	double dPayableAuctionBalance = 0;
	CTime t = CTime::GetCurrentTime();
	CTime tNow((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	CTimeSpan ts;
	double dAuctionSum = 0;
	double dAuctionDeficit = 0;
	long lLNr = 0;
	
	//
	//
	//
	theApp.m_pPrintRes->m_pdi->lpszDocName = "YJMAKSU";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit)));


	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontOtsikot); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( (8*562), - int(0.7*562),"Ylijäämämaksu");

	// -- lähettäjän yhteystiedot ---
	//
	lRows = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Toimisto); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Katu); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Ptp); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Puh); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Fax); lRows++;
	//
	// pvm
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	str.Format("%s", tNow.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->TextOut( (8*562), - int (1.5*562), str);
	//
	//
	lAsID = m_pCAuctionCtrl->m_pMC->m_pLoan->getCustomerInfo().m_lCustID;
	m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_strFilter.Format("HKL_AsID = %ld", lAsID);
	m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_strSort = "";

	try
	{
		// -- asiakkaan yhteystiedot ---
		lRows = 0;
		TRACE("AsID=%ld\n", lAsID);
		m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->m_strFilter.Format("AS_ID = %ld", lAsID);
		m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->Open();
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontBold); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->m_AS_Nimi); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->m_AS_ENimet); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->m_AS_KatuOs); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->m_AS_Ptp); lRows++;
		m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->Close();
		//
		// -- huutokauppalainat käydään läpi ja tulostetaan ---
		m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->Open();
		
		while (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsEOF())
		{
			TRACE("Laina#=%ld\n", m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr);
			dM = 0;
			if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij) &&
				m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij > 0.01)
			{
				// 
				if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina))
				{
					dM = m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina;
					dAuctionSum = dAuctionSum + m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina;
				}
				
				if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut))
				{
					dM = dM + m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut;
				}
				
				if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut))
				{
					dM = dM + m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut;
				}
				// -- ylijäämä ---
				if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta))
				{
					if (dM <= m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta)  // ylijäämä
					{
						dY = m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta - dM;
						dAuctionBalance = dAuctionBalance + dY;
						
						//
						//
						//if (hklaina >1v ja maksamaton)
						ts = tNow - m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_MyyntiPv;
						//					
						/*TRACE("Myynnistä aikaa %ld vrk\n", ts.GetDays());
						if( m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Kuittaus == TRUE)
							TRACE("pALrs->m_HKL_Kuittaus == TRUE\n");
						TRACE("Laina-kulut= %7.2f\n", dY);
						if( m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_YlijKuittausPv))
							TRACE("pALrs->m_HKL_YlijKuittausPv=NULL\n");
						if( m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_YlijMaksuPv))
							TRACE("m_HKL_YlijMaksuPv=NULL\n");
						*///
						//
						if ((m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Kuittaus == TRUE) &&
							(dY > 0.01) &&
							(m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_YlijKuittausPv)) &&
							(m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_YlijMaksuPv))
						   )
						{
							if (ts.GetDays() <= theApp.GetAs()->m_AT_YlijKuitAikaraja)
							{
								dPayableAuctionBalance = dPayableAuctionBalance + m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij;
							}
						}
					}
					else  // alijäämä
					{
						dA = dM - m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta;
						dAuctionDeficit = dAuctionDeficit + dA;
					}
				}
				//
				theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
				theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm);
				theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
				tmp.Format("Lainanumero . . . . . . . . . . . . %ld", m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr);
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
				tmp.Format("Lainasumma  . . . . . . . . . . . . %7.2f", m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina);
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
				tmp.Format("Myyntipäivä . . . . . . . . . . . . %s", m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_MyyntiPv.Format("%d.%m.%Y"));
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
				tmp.Format("Korot ja kulut yht. . . . . . . . . %7.2f", m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut);
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
				tmp.Format("Huutokauppakulut yht. . . . . . . . %7.2f", m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut);
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
				// 
				if (m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta))
					tmp.Format("Myyntihinta huutokaupassa . . . . . puuttuva tieto");
				else
					tmp.Format("Myyntihinta huutokaupassa . . . . . %7.2f", m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta);
				
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
				//
				if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij))
					dYlij = m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij;
				else
					dYlij = 0;
				tmp.Format("Ylijäämä  . . . . . . . . . . . . . %7.2f", dYlij);
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
				//
				tmp.Format("Ylijäämäilmoitusmaksu . . . . . . . %7.2f", theApp.GetAs()->m_AT_YlijIlmMaksu);
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
				tmp.Format("                                  ===========");
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
				tmp.Format("MAKSETAAN LAINASTA                       %7.2f", theApp.makeRounding(m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij - theApp.GetAs()->m_AT_YlijIlmMaksu));
				theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows = lRows + 2;
				//
				// --- sivunvaihto  --
				iRo++;
				if (iRo > 4)
				{
					iRo = 0;
					lRows = 0;
					theApp.m_pPrintRes->m_pdc->EndPage();
				}
			}
			m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->MoveNext();
		}
		m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->Close();
		lRows = lRows + 2;
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		tmp.Format("Kuitataan suoritetuksi YHTEENSÄ: %7.2f", dPayableAuctionBalance);
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;

		
		theApp.m_pPrintRes->stopPrinter();

		tmp.Format("Onnistuiko kuitin tulostus?\n Kyllä = Merkitään suoritus lainatietoihin\n Ei    = Perutaan tapahtuma ja yj-kuittaus voidaan tehdä myöhemmin");
		if (AfxMessageBox(tmp, MB_YESNO) == IDYES /*IDNO*/)
		{
			m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_strFilter.Format("HKL_AsID = %ld", lAsID);
			m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_strSort = "";
			m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->Open();

			while (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsEOF())
			{
				if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij) &&
					m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij > 0.01)
				{
					if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina))
					{
						dM = m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina;
						dAuctionSum = dAuctionSum + m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina;
					}
					
					if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut))
					{
						dM = dM + m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut;
					}
					
					if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut))
					{
						dM = dM + m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut;
					}
					// -- ylijäämä ---
					if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta))
					{
						if (dM <= m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta)  // ylijäämä
						{
							dY = m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta - dM;
							dAuctionBalance = dAuctionBalance + dY;
							
							//
							//
							//if (hklaina >1v ja maksamaton)
							ts = tNow - m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_MyyntiPv;
							//					
							if ((m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Kuittaus == TRUE) &&
								(dY > 0.01) &&
								(m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_YlijKuittausPv)) &&
								(m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_YlijMaksuPv))
							   )
							{
								if (ts.GetDays() <= theApp.GetAs()->m_AT_YlijKuitAikaraja)
								{
									lLNr = m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr;
									m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->Edit();
									m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_YlijMaksuPv = tNow;
									m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->Update();
									//
									// --- merkintä lainatapahtumiin (LAINATAPAHTUMA-taulu)---
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_strFilter.Format("TP_LA_Nr=%ld", lLNr);
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->Open();
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->AddNew();

									//m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Tap;
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_LA_Nr = lLNr;
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_KS_Tunnus = theApp.m_lDeskId; // kassan tunnus
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Varmennus = "";
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Aika = CTime::GetCurrentTime();
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_AM_Nimikirjaimet = theApp.m_sUser; // arviomies
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Summa = 0; // miksi
									
 									//  ei tiedossa !
									//m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_VakSumma = m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_ //this->m_LA_VakSumma;
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_VanhaLaina = m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina;
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_UusiLaina = m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina;
									
									//
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Maksettava = dYlij - theApp.GetAs()->m_AT_YlijIlmMaksu;
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Tyyppi = "Y";
									
									//m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Alijaama;	
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Ylijaama = dYlij - theApp.GetAs()->m_AT_YlijIlmMaksu;
												
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Selitys = "ylijäämän maksu";
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->m_TP_Huom = "";

									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->Update();
									m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->Close();
								}
							}
						}
					}
				}
				//
				m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->MoveNext();
			}
			m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->Close();
			//
			// --- maksu kasvattaa asiakastiedoissa olevaa asiakkaalle maksettujen ylijäämien summaa
			m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->m_strFilter.Format("AS_ID = %ld", lAsID);
			m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->Open();
			if (!m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->IsFieldNull(&m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->m_AS_Ylij))
			{
				dAsYlij = m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->m_AS_Ylij;
			}
			m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->Edit();
			m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->m_AS_Ylij = dPayableAuctionBalance + dAsYlij;
			m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->Update();
			m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->Close();

			//
			// --- kassalokimerkintä (KASSALOKI-taulu)----
			CKassalokiRS kl;
			BOOL brtn = 
				kl.writeDeskLogEntry(
					"Y",				// Tapahtuman tyyppi: U/D/L/....// tType = "Y"= ylijäämän maksu (ei kuittaus)
					NULL,					// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
					"Ylijäämämaksu asiakkaalle",		// Selite
					NULL,				// Lainan numero
					NULL,					// Lainasumma ennen operaatiota
					NULL,					// Lainasumma operaation jälkeen
					NULL,					// Korkojen osuus
					NULL,					// SHVMaksut
					NULL,					// Toimitusmaksut
					NULL,					// Pyöristys
					(-1) * dPayableAuctionBalance,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
					dPayableAuctionBalance,	// Ylijäämä
					NULL);	// Alijäämä
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pCAuctionCtrl->m_pMC->m_pDB->getAsRs()->Close();
		m_pCAuctionCtrl->m_pMC->m_pDB->getLoanEventsRS()->Close();
		m_pCAuctionCtrl->m_pMC->m_pDB->getAuctionLoanRS3()->Close();
	}		

	OnOK(); 
}

void CDlgYjTilitys::OnOK() 
{
	CDialog::OnOK();
}
