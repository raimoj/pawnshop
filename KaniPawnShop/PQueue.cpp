// PQueue.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "PQueue.h"

#include "DlgID.h"

#include "DlgUusiLaina.h"
#include "DlgLunastus.h"
#include "DlgUudistus.h"
#include "DlgVakuusmuutos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CPQueue

//IMPLEMENT_DYNCREATE(CPQueue, CCmdTarget)

CPQueue::CPQueue()
{
	m_pDoc = theApp.m_pDoc;
}

CPQueue::~CPQueue()
{
	m_dlgList.RemoveAll();
}


BEGIN_MESSAGE_MAP(CPQueue, CCmdTarget)
	//{{AFX_MSG_MAP(CPQueue)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPQueue message handlers

bool CPQueue::NewPawnRequest(CString sHtun, long lAsId, CString sNimi)
{
	TRACE("CPQueue::NewPawnRequest\n");
	//char buf[20];
	//long lNewNr = GetDocument()->GetNewPawnTicketNr();
	//TRACE("Uusi lainanumero = %ld\n", lNewNr);

	//m_wndLainaRivitGrid.ChangeStandardStyle(CGXStyle()
	//	.SetControl(GX_IDS_CTRL_EDIT)
	//	.SetReadOnly(FALSE));
	//m_wndLainaRivitGrid.SetReadOnly(FALSE);
	//m_wndLainaRivitGrid.Redraw();
		//m_wndLainaGrid.SetColumnWidths();
		//m_wndLainaGrid.Redraw();

	CDlgID* pDlg = new CDlgID;
	//TRACE("Sizeof CDlgID-obj=%d\n", sizeof(CDlgID));
	//TRACE("Uusi CDlgID-obj=%d\n", pDlg);
	CDlgUusiLaina* pdlgUusiLaina = new CDlgUusiLaina;
	//TRACE("Sizeof CDlgUusiLaina-obj=%d\n", sizeof(CDlgUusiLaina));
	TRACE("Uusi laina-obj=%d\n", pdlgUusiLaina);

	pDlg->m_iDlgType = 1;
	pDlg->m_pDlg = pdlgUusiLaina;
	pDlg->m_lLoanNr = 0;

	m_dlgList.AddTail(pDlg);
	TRACE("pDoc=%ld\n", m_pDoc);

	pdlgUusiLaina->m_sHtun_Nimi = RemoveSpaces(sNimi) + ", " + RemoveSpaces(sHtun);
	pdlgUusiLaina->m_sHtun = sHtun;
	pdlgUusiLaina->m_AsId = lAsId;
	pdlgUusiLaina->m_sSNimi = sNimi;

	if (pdlgUusiLaina->DoModal() == IDOK)
	{
	}
	//TRACE("Maksettava=%7.2f\n", pdlgUusiLaina->m_dLainasumma);
	if (pdlgUusiLaina->m_bCanceled)
	{
		RemoveQItem(pdlgUusiLaina);
	}
	return TRUE;
}


int CPQueue::GetQueueRowCount()
{
	return m_dlgList.GetCount();
}


CString CPQueue::GetDlgString(POSITION pos)
{
	CString sTr = "";
	CDlgUusiLaina* pUl;
	CDlgLunastus* pL;
	CDlgUudistus* pUud;
	CDlgVakuusmuutos* pC;

	CDlgID* pd = (CDlgID*) m_dlgList.GetAt(pos);
	switch (pd->m_iDlgType)
	{
	case 1:
		pUl = (CDlgUusiLaina*) pd->m_pDlg;
		sTr = pUl->GetDlgString();
		break;
	case 2:
		pL = (CDlgLunastus*) pd->m_pDlg;
		sTr = pL->GetDlgString();
		break;
	case 3:
		pUud = (CDlgUudistus*) pd->m_pDlg;
		sTr = pUud->GetDlgString();
		break;
	case 4:
		pC = (CDlgVakuusmuutos*) pd->m_pDlg;
		sTr = pC->GetDlgString();
		break;

	default:
		//CDialog* pdl = (CDialog*) pd->m_pDlg;
		sTr = "Mikä dlg ?";
	}
	return sTr;
}

long CPQueue::GetDlgID(POSITION pos)
{
	CDlgID* pd = (CDlgID*) m_dlgList.GetAt(pos);
	return (long)pd->m_pDlg;
}


void CPQueue::RemoveAll()
{
	POSITION pos;
	CDlgUusiLaina* pUl;
	CDlgLunastus* pL;
	CDlgUudistus* pUud;
	CDlgVakuusmuutos* pC;


	//int iDlgLkm = m_dlgList.GetCount();

	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		CDlgID* pd = (CDlgID*) m_dlgList.GetAt(pos);
		switch (pd->m_iDlgType)
		{
		case 1: // uusi laina
			pUl = (CDlgUusiLaina*) pd->m_pDlg;
			delete pUl;
			TRACE("RemoveAll:Poistetaan UusiLainaDlg %d\n", pUl);
			break;
		case 2: // lunastus
			pL = (CDlgLunastus*) pd->m_pDlg;
			delete pL;
			TRACE("RemoveAll:Poistetaan LunastusDlg %d\n", pL);
			break;
		case 3: // uudistus
			pUud = (CDlgUudistus*) pd->m_pDlg;
			delete pUud;
			TRACE("RemoveAll:Poistetaan uudistusDlg %d\n", pUud);
			break;
		case 4: // vakuusmuutos
			pC = (CDlgVakuusmuutos*) pd->m_pDlg;
			delete pC;
			TRACE("RemoveAll:Poistetaan MuutosDlg %d\n", pC);
			break;

		default:
			//CDialog* pdl = (CDialog*) pd->m_pDlg;
			break;
		}
		delete m_dlgList.GetNext(pos);
	}
	m_dlgList.RemoveAll();
}

void CPQueue::ShowDlg(int iRow, long lItemData)
{
	int k = 0;
	POSITION pos;
	CDlgUusiLaina* pUl;
	CDlgLunastus* pL;
	CDlgUudistus* pUud;
	CDlgVakuusmuutos* pC;

	CDlgID* pd;

	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		k++;
		TRACE("Looking for the queue item... %d\n", k);
		pd = (CDlgID*) m_dlgList.GetAt(pos);
		if (pd->m_pDlg == (CDialog*)lItemData)
		{
			switch (pd->m_iDlgType)
			{
			case 1:
				pUl = (CDlgUusiLaina*) pd->m_pDlg;
				TRACE("ShowDlg: Uusi laina %ld\n", pUl);
				pUl->DoModal();
				if (pUl->m_bCanceled)
				{
					RemoveQItem(pUl);
				}
				return;
				break;
			case 2:
				pL = (CDlgLunastus*) pd->m_pDlg;
				TRACE("ShowDlg: Lunastus %ld\n", pL);
				pL->DoModal();
				if (pL->m_bCanceled)
				{
					RemoveQItem(pL);
				}
				return;
				break;
			case 3: // uudistus
				pUud = (CDlgUudistus*) pd->m_pDlg;
				TRACE("ShowDlg: Uudistus %ld\n", pUud);
				pUud->DoModal();
				if (pUud->m_bCanceled)
				{
					RemoveQItem(pUud);
				}
				return;
				break;
			case 4: // muutos
				pC = (CDlgVakuusmuutos*) pd->m_pDlg;
				TRACE("ShowDlg: MootosDlg %ld\n", pC);
				pC->DoModal();
				if (pC->m_bCanceled)
				{
					RemoveQItem(pC);
				}
				return;
				break;

			default:
				//CDialog* pdl = (CDialog*) pd->m_pDlg;
				break;
			}
		}
		m_dlgList.GetNext(pos);
	}
}

void CPQueue::RemoveQItem(int iRow, long lItemData)
{
	POSITION pos;
	CDlgUusiLaina* pUl;
	CDlgLunastus* pL;
	CDlgUudistus* pUud;
	CDlgVakuusmuutos* pC;

	CDlgID* pd;

	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);
		if (pd->m_pDlg == (CDialog*)lItemData)
		{
			switch (pd->m_iDlgType)
			{
			case 1:
				pUl = (CDlgUusiLaina*) pd->m_pDlg;
				delete pUl;
				TRACE("RemoveQItem: Poistetaan UusiLainaDlg %d\n", pUl);
				delete m_dlgList.GetAt(pos);
				m_dlgList.RemoveAt(pos);
				return; // ei saa jatkaa
				break;
			case 2:
				pL = (CDlgLunastus*) pd->m_pDlg;
				delete pL;
				TRACE("RemoveQItem: Poistetaan LunastusDlg %d\n", pL);
				delete m_dlgList.GetAt(pos);
				m_dlgList.RemoveAt(pos);
				return; // ei saa jatkaa
				break;
			case 3:
				pUud = (CDlgUudistus*) pd->m_pDlg;
				delete pUud;
				TRACE("RemoveQItem: Poistetaan uudistusDlg %d\n", pUud);
				delete m_dlgList.GetAt(pos);
				m_dlgList.RemoveAt(pos);
				return; // ei saa jatkaa
				break;
			case 4:
				pC = (CDlgVakuusmuutos*) pd->m_pDlg;
				delete pC;
				TRACE("RemoveQItem: Poistetaan muutosDlg %d\n", pC);
				delete m_dlgList.GetAt(pos);
				m_dlgList.RemoveAt(pos);
				return; // ei saa jatkaa
				break;

			default:
				//CDialog* pdl = (CDialog*) pd->m_pDlg;
				break;
			}
		}
		m_dlgList.GetNext( pos );
	}
}

bool CPQueue::RedemptRequest(long lNr, CString sHtun, long lAsId, CString sNimi)
{
	POSITION pos;
	char buf[20];
	CDlgLunastus* pL;
	CDlgID* pd;

	TRACE("CPQueue::RedemptRequest\n");

	//
	// is there already in queue a pending redempt for this loan ?
	//
	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);

		if ((pd->m_iDlgType == 2) && (pd->m_lLoanNr == lNr))
		{
			pL = (CDlgLunastus*) pd->m_pDlg;
			TRACE("RedemptRequest: Lunastus %ld\n", pL);
			pL->DoModal();
			if (pL->m_bCanceled)
			{
				RemoveQItem(pL);
			}
			return TRUE;
		}
		m_dlgList.GetNext( pos );
	}
	//
	// is there any other pending events for this loan ?
	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);

		if (pd->m_lLoanNr == lNr)
		{
			return FALSE;
		}
		m_dlgList.GetNext( pos );
	}

	CDlgID* pDlg = new CDlgID;
	CDlgLunastus* pdlgLunastus = new CDlgLunastus(lNr);

	pDlg->m_iDlgType = 2;
	pDlg->m_pDlg = pdlgLunastus;
	pDlg->m_lLoanNr = lNr;
	m_dlgList.AddTail(pDlg);

	/*pdlgLunastus->SetpDoc(GetDocument());
	pdlgLunastus->m_sHtun = m_sHtun;
	pdlgLunastus->m_lAsId = m_lAsId;
	m_ctlSnimi.GetWindowText(pdlgLunastus->m_sSNimi);
	*//*if (m_wndLainaGrid.GetCurrentCell(nRow, nCol)) //jos ei yhtään riviä niin ...
	{
		pdlgLunastus->m_sPv = m_wndLainaGrid.GetValueRowCol(nRow,7);
		pdlgLunastus->m_dateEraPv = m_wndLainaGrid.GetValueRowCol(nRow,8);
		pdlgLunastus->m_dSailVakMaksu = m_wndLainaGrid.GetValueRowCol(nRow,14);
		pdlgLunastus->m_dKuittimaksu = m_wndLainaGrid.GetValueRowCol(nRow,15);
		pdlgLunastus->m_dYlimSailMaksu = m_wndLainaGrid.GetValueRowCol(nRow,16);
		pdlgLunastus->m_dKorkoPr = m_wndLainaGrid.GetValueRowCol(nRow,12);
	}*/

	/*if (m_wndLainaGrid.GetCurrentCell(nRow, nCol)) //jos ei yhtään riviä niin ...
	{
		pdlgLunastus->m_sLainaNr = m_wndLainaGrid.GetValueRowCol(nRow,1);
	}
	*/
	ltoa(lNr, buf, 10);
	pdlgLunastus->m_sLainaNr = buf;
	pdlgLunastus->m_lAsId = lAsId;
	pdlgLunastus->m_sNimiHTun = "[" + sHtun + "] " + sNimi;
	if (pdlgLunastus->DoModal() == IDOK)
	{
		//m_ctlSuoritusjono.InsertString(-1,pdlgLunastus->m_sSuoritusjonoRivi);
		//dSuoritusjononSumma = dSuoritusjononSumma + (pdlgLunastus->m_dMaksettava);
		//m_sSuoritusjononSumma.Format("%7.2f", dSuoritusjononSumma);
	}
	if (pdlgLunastus->m_bCanceled)
	{
		RemoveQItem(pdlgLunastus);
	}
	//delete pdlgLunastus;
	//UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)
	//OnSelchangeSnimi();
	return TRUE;
}

void CPQueue::DlgActivationTest(int iTest, int iRow, long lItemData)
{
	int i = 0;
	for (i=0; i<iTest; i++)
	{
		ShowDlg(iRow, lItemData);
	}
}


bool CPQueue::RenewRequest(long lNr, CString sHtun, long lAsId, CString sNimi)
{
	POSITION pos;
	char buf[20];
	CDlgUudistus* pUud;
	CDlgID* pd;

	TRACE("CPQueue::RenewRequest\n");

	//
	// is there already in queue a pending renew for this loan
	//
	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);

		if ((pd->m_iDlgType == 3) && (pd->m_lLoanNr == lNr))
		{
			pUud = (CDlgUudistus*) pd->m_pDlg;
			TRACE("RedemptRequest: Lunastus %ld\n", pUud);
			pUud->DoModal();
			if (pUud->m_bCanceled)
			{
				RemoveQItem(pUud);
			}
			return TRUE;
		}
		m_dlgList.GetNext( pos );
	}
	//
	// is there any other pending evants for this loan ?
	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);

		if (pd->m_lLoanNr == lNr)
		{
			return FALSE;
		}
		m_dlgList.GetNext( pos );
	}

	CDlgID* pDlg = new CDlgID();
	CDlgUudistus* pdlgUudistus = new CDlgUudistus(lNr);
	pDlg->m_iDlgType = 3;
	pDlg->m_pDlg = pdlgUudistus;
	pDlg->m_lLoanNr = lNr;
	m_dlgList.AddTail(pDlg);

	ltoa(lNr, buf, 10);
	pdlgUudistus->m_sLainaNr = buf;
	//pdlgUudistus->m_sHtun = sHtun;
	pdlgUudistus->m_lAsId = lAsId;
	pdlgUudistus->m_sNimiHTun = "[" + sHtun + "] " + sNimi;
	//pdlgUudistus->m_sSNimi = sNimi;
	if (pdlgUudistus->DoModal() == IDOK)
	{
	}
	if (pdlgUudistus->m_bCanceled)
	{
		RemoveQItem(pdlgUudistus);
	}
	return TRUE;
}


bool CPQueue::ChangeRequest(long lNr, CString sHtun, long lAsId, CString sNimi)
{
	POSITION pos;
	CString s1;
	CString s2;
	//char buf[20];
	CDlgVakuusmuutos* pC;
	CDlgID* pd;

	TRACE("CPQueue::ChangeRequest\n");

	//
	// is there already in queue a pending renew for this loan
	//
	for( pos = m_dlgList.GetHeadPosition(); pos != NULL;)
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);

		if ((pd->m_iDlgType == 4) && (pd->m_lLoanNr == lNr))
		{
			pC = (CDlgVakuusmuutos*) pd->m_pDlg;
			TRACE("RedemptRequest: Lunastus %ld\n", pC);
			pC->DoModal();
			if (pC->m_bCanceled)
			{
				RemoveQItem(pC);
			}
			return TRUE;
		}
		m_dlgList.GetNext( pos );
	}
	//
	// is there any other pending events for this loan ?
	for( pos = m_dlgList.GetHeadPosition(); pos != NULL;)
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);

		if (pd->m_lLoanNr == lNr)
		{
			return FALSE;
		}
		m_dlgList.GetNext( pos );
	}

	CDlgID* pDlg = new CDlgID;
	CDlgVakuusmuutos* pdlgChange = new CDlgVakuusmuutos(lNr);
	pDlg->m_iDlgType = 4;
	pDlg->m_pDlg = pdlgChange;
	pDlg->m_lLoanNr = lNr;
	m_dlgList.AddTail(pDlg);

	/*ltoa(lNr, buf, 10);
	pdlgChange->m_sLainaNr = buf;
	pdlgChange->m_lAsId = lAsId;
	s1 = RemoveSpaces(sNimi);
	s2 = RemoveSpaces(sHtun);
	pdlgChange->m_sNimi_Htun = s1 + ", " + s2;*/
	if (pdlgChange->DoModal() == IDOK)
	{

	}
	if (pdlgChange->m_bCanceled)
	{
		RemoveQItem(pdlgChange);
	}
	return TRUE;
}

bool CPQueue::PrintPawnTickets()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	POSITION pos;
	bool rtn = TRUE;

	CDlgUusiLaina* pUl;
	CDlgLunastus* pL;
	CDlgUudistus* pUud;
	CDlgVakuusmuutos* pC;

	CDlgID* pd;

	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);

		switch (pd->m_iDlgType)
		{
		case 1:
			pUl = (CDlgUusiLaina*) pd->m_pDlg;
			TRACE("PrintPawnTickets: UusiLainaDlg %d\n", pUl);
			rtn = pUl->Kuitti();
			break;
		case 2:
			pL = (CDlgLunastus*) pd->m_pDlg;
			TRACE("PrintPawnTickets: LunastusDlg %d\n", pL);
			rtn = pL->Kuitti();
			break;
		case 3:
			pUud = (CDlgUudistus*) pd->m_pDlg;
			TRACE("PrintPawnTickets: uudistusDlg %d\n", pUud);
			rtn = pUud->Kuitti();
			break;
		case 4:
			pC = (CDlgVakuusmuutos*) pd->m_pDlg;
			TRACE("PrintPawnTickets: muutosDlg %d\n", pC);
			rtn = pC->Kuitti();
			break;

		default:
			//CDialog* pdl = (CDialog*) pd->m_pDlg;
			break;
		}
		m_dlgList.GetNext( pos );
	}
	RemoveAll();
	return rtn;
}


double CPQueue::GetFee(POSITION pos)
{
	CDlgUusiLaina* pUl;
	CDlgLunastus* pL;
	CDlgUudistus* pUud;
	CDlgVakuusmuutos* pC;
	double drtn = 0;

	CDlgID* pd = (CDlgID*) m_dlgList.GetAt(pos);
	switch (pd->m_iDlgType)
	{
	case 1:
		pUl = (CDlgUusiLaina*) pd->m_pDlg;
		drtn = pUl->GetFee();
		break;
	case 2:
		pL = (CDlgLunastus*) pd->m_pDlg;
		drtn = pL->GetFee();
		break;
	case 3:
		pUud = (CDlgUudistus*) pd->m_pDlg;
		drtn = pUud->GetFee();
		break;
	case 4:
		pC = (CDlgVakuusmuutos*) pd->m_pDlg;
		drtn = pC->GetFee();
		break;

	default:
		//CDialog* pdl = (CDialog*) pd->m_pDlg;
		drtn = 0;
	}
	return drtn;
}

CString CPQueue::RemoveSpaces(CString sText)
{
	CString st = "";
	int i = 0;
	TRACE("%s, %d\n", sText, sText.GetLength());
	while (i != sText.GetLength())
	{
		//TRACE("'%s'\n",sText.Mid(i,1));
		if (sText.Mid(i,1) != " ")
			break;
		i++;
	}
	TRACE("%s\n", sText.Right(sText.GetLength() - i));
	st = sText.Right(sText.GetLength() - i);
	i = st.GetLength()-1;
	while (i >= 0)
	{
		//TRACE("'%s'\n",st.Mid(i,1));
		if (st.Mid(i,1) != " ")
			break;
		i--;
	}
	return st.Left(i+1);
}

void CPQueue::RemoveQItem(CDlgUusiLaina *pUusiLainaDlg)
{
	POSITION pos;
	CDlgUusiLaina* pUl;
	CDlgID* pd;

	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);
		if (pd->m_pDlg == pUusiLainaDlg)
		{
			pUl = (CDlgUusiLaina*) pd->m_pDlg;
			delete pUl;
			TRACE("RemoveQItem: Poistetaan UusiLainaDlg %d\n", pUl);
			delete m_dlgList.GetAt(pos);
			m_dlgList.RemoveAt(pos);
			return; // ei saa jatkaa
		}
		m_dlgList.GetNext( pos );
	}
}

void CPQueue::RemoveQItem(CDlgLunastus *pLunastusDlg)
{
	POSITION pos;
	CDlgLunastus* pL;
	CDlgID* pd;

	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);
		if (pd->m_pDlg == pLunastusDlg)
		{
			pL = (CDlgLunastus*) pd->m_pDlg;
			delete pL;
			TRACE("RemoveQItem: Poistetaan LunastusDlg %d\n", pL);
			delete m_dlgList.GetAt(pos);
			m_dlgList.RemoveAt(pos);
			return; // ei saa jatkaa
		}
		m_dlgList.GetNext( pos );
	}
}

void CPQueue::RemoveQItem(CDlgUudistus *pUudistusDlg)
{
	POSITION pos;
	CDlgUudistus* pUud;
	CDlgID* pd;

	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);
		if (pd->m_pDlg == pUudistusDlg)
		{
			pUud = (CDlgUudistus*) pd->m_pDlg;
			delete pUud;
			TRACE("RemoveQItem: Poistetaan UudistusDlg %d\n", pUud);
			delete m_dlgList.GetAt(pos);
			m_dlgList.RemoveAt(pos);
			return; // ei saa jatkaa
		}
		m_dlgList.GetNext( pos );
	}
}

void CPQueue::RemoveQItem(CDlgVakuusmuutos *pVakuusmuutosDlg)
{
	POSITION pos;
	CDlgVakuusmuutos* pC;
	CDlgID* pd;

	for( pos = m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		pd = (CDlgID*) m_dlgList.GetAt(pos);
		if (pd->m_pDlg == pVakuusmuutosDlg)
		{
			pC = (CDlgVakuusmuutos*) pd->m_pDlg;
			delete pC;
			TRACE("RemoveQItem: Poistetaan VakuusmuutosDlg %d\n", pC);
			delete m_dlgList.GetAt(pos);
			m_dlgList.RemoveAt(pos);
			return; // ei saa jatkaa
		}
		m_dlgList.GetNext( pos );
	}
}

