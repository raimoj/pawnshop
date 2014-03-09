// CustomerInfo.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "CustomerInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCustomerInfo

CCustomerInfo::CCustomerInfo()
{
	m_lCustID = 0;
	m_AS_Ptp = "?";
	m_AS_KatuOs = "?";
	m_AS_ENimet = "?";
	m_AS_HTun = "?";
	m_AS_Nimi = "?";
	m_pDBLoan = NULL;
}

CCustomerInfo::CCustomerInfo(CDBLoan* pDBLoan, long lCustomerID)
{
	this->m_pDBLoan = pDBLoan;
	setCustomer(lCustomerID);
}

CCustomerInfo::CCustomerInfo(const CCustomerInfo& customerinfo)
{
	m_lCustID = customerinfo.m_lCustID;
	m_AS_Ptp = customerinfo.m_AS_Ptp;
	m_AS_KatuOs = customerinfo.m_AS_KatuOs;
	m_AS_ENimet = customerinfo.m_AS_ENimet;
	m_AS_HTun = customerinfo.m_AS_HTun;
	m_AS_Nimi = customerinfo.m_AS_Nimi;
	m_pDBLoan = customerinfo.m_pDBLoan;
}

CCustomerInfo::~CCustomerInfo()
{
}


BEGIN_MESSAGE_MAP(CCustomerInfo, CWnd)
	//{{AFX_MSG_MAP(CCustomerInfo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustomerInfo message handlers

void CCustomerInfo::setCustomer(long lCustomerID)
{
	m_lCustID = lCustomerID;
	m_pDBLoan->m_pDB->getAsCIRs()->m_strFilter.Format("AS_ID = %ld", lCustomerID);
	try
	{
		m_pDBLoan->m_pDB->getAsCIRs()->Open();
		if (!m_pDBLoan->m_pDB->getAsCIRs()->IsEOF())
		{
			this->m_AS_Nimi = m_pDBLoan->m_pDB->getAsCIRs()->m_AS_Nimi;
			this->m_AS_ENimet = m_pDBLoan->m_pDB->getAsCIRs()->m_AS_ENimet;
			this->m_AS_HTun = m_pDBLoan->m_pDB->getAsCIRs()->m_AS_HTun;
			this->m_AS_KatuOs = m_pDBLoan->m_pDB->getAsCIRs()->m_AS_KatuOs;
			this->m_AS_Ptp = m_pDBLoan->m_pDB->getAsCIRs()->m_AS_Ptp;
		}
		m_pDBLoan->m_pDB->getAsCIRs()->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pDBLoan->m_pDB->getAsCIRs()->Close();
	}
}

/*void CCustomerInfo::print(int xPos, int yPos, bool bNote)
{
	int j=0;
	//char buf[500];
	CString strText = "";

	m_pDBLoan->m_pdc->SelectObject(&m_pDBLoan->fontTiny);
	strText.LoadString(IDS_PKTEXT4);   m_pDBLoan->m_pdc->TextOut( xPos, - (yPos), strText);  // Panttaaja
	strText.LoadString(IDS_PKTEXT5);   m_pDBLoan->m_pdc->TextOut( xPos, - (yPos+180*4), strText); //HenkTun
	strText.LoadString(IDS_PKTEXT6);   m_pDBLoan->m_pdc->TextOut( xPos, - (yPos+180*7), strText); // Osoite
	//strText.LoadString(IDS_PKTEXT7);   m_pDBLoan->m_pdc->TextOut( xPos, - (yPos+180*3), strText); // Ptp
	//strText.LoadString(IDS_PKTEXT8);   m_pDBLoan->m_pdc->TextOut( xPos, - (yPos+180*4), strText); // Puh

	if (bNote)
	{
		//m_pDBLoan->m_pdc->SelectObject(&m_pDBLoan->fontTiny);
		strText.LoadString(IDS_PANKKIIN1);   m_pDBLoan->m_pdc->TextOut( xPos, -(yPos+(180*11)), strText); //maksut pankkiin
		strText.LoadString(IDS_PANKKIIN2);   m_pDBLoan->m_pdc->TextOut( xPos, -(yPos+(180*12)), strText); //maksut pankkiin
	}

	m_pDBLoan->m_pdc->SelectObject(&m_pDBLoan->fontRivit);

	//strText.LoadString(IDS_PKTEXT4);   m_pDBLoan->m_pdc->TextOut( 281, - (4496), strText);  // Panttaaja
	m_pDBLoan->m_pdc->TextOut( xPos+281, - (yPos+180*1), this->m_AS_Nimi.Left(19));  // Panttaaja
	m_pDBLoan->m_pdc->TextOut( xPos+281, - (yPos+180*2), this->m_AS_ENimet.Left(19));  // Panttaaja
	m_pDBLoan->m_pdc->TextOut( xPos+281, - (yPos+180*5), this->m_AS_HTun.Left(6));
	m_pDBLoan->m_pdc->TextOut( xPos+281, - (yPos+180*8), this->m_AS_KatuOs.Left(19));
	m_pDBLoan->m_pdc->TextOut( xPos+281, - (yPos+180*9), this->m_AS_Ptp.Left(19));

	//strText.LoadString(IDS_VIITE);   m_pDBLoan->m_pdc->TextOut( xPos, -(yPos+(180*13)), strText); // Viite
	//m_pDBLoan->m_pdc->TextOut( xPos+281+1124, -(yPos+(180*13)), LaskeViitenumero(m_lPawnIdNr));
}
*/



CString CCustomerInfo::updateHTun(CString ht)
{
	CString srtn = ht;
	CString stmp = "";
	
	if ((ht.GetLength() == 6) && (ht.GetLength() > m_sTempHtun.GetLength()))  // verrataan edellisen kierroksen tekstiin
	{																		// että saadaan selville onko käyttäjä korjaamassa (peruuttamassa <- näpp)
		if (  (ht.Left(1) == "0" ||											// vai kirjoittamassa uusia merkkejä
				ht.Left(1) == "1" ||
				ht.Left(1) == "2" ||
				ht.Left(1) == "3" ||
				ht.Left(1) == "4" ||
				ht.Left(1) == "5" ||
				ht.Left(1) == "6" ||
				ht.Left(1) == "7" ||
				ht.Left(1) == "8" ||
				ht.Left(1) == "9") )
		{
			srtn = ht + "-";
		}
	}
	srtn.MakeUpper();
	m_sTempHtun = srtn;
	return srtn;
}


CString CCustomerInfo::GetHtun(CString sHtun, BOOL bRuotsHTun, int iSp)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int iRtn = 0;
	CString sHTun = "";

	sHTun = RemoveSpaces(sHtun).Left(11);
	iRtn = CheckIdentityNumber(sHTun, bRuotsHTun, iSp);
	if (iRtn == 1)
	{
		AfxMessageBox("Tarkasta henkilötunnus: Virheellinen numero");
		return "";
	}
	else if (iRtn == 2)
	{
		AfxMessageBox("Mies/Nainen? Tarkasta sp");
		return "";
	}
	else if (iRtn == 3)
	{
		AfxMessageBox("Karkauspäivä!");
		return "";
	}
	else if (iRtn == 4)
	{
		AfxMessageBox("000 ja 001 eivät ole sallittuja päätteitä!");
		return "";
	}
	else if (iRtn == 5)
	{
		AfxMessageBox("Tarkastusmerkki virheellinen");
		return "";
	}
	else if (iRtn == 6)
	{
		AfxMessageBox("Henkilötunnuksen pituus ei ole oikein");
		return "";
	}
	else if (iRtn == 7)
	{
		AfxMessageBox("Kuukausi ei ole oikein");
		return "";
	}
	else if (iRtn == 8)
	{
		AfxMessageBox("Päivä ei ole oikein");
		return "";
	}
	return sHTun;
}


int CCustomerInfo::CheckIdentityNumber(CString sHTun, BOOL bRuotsHTun, int isp)
{
	int k = 0;
	int is = 0;
	CString s = "";
	if (isp == 1)
		TRACE("Mies\n");
	else if (isp == 0)
		TRACE("Nainen\n");
	else
		TRACE("SP=?\n");

	TRACE("%s: ", sHTun);
	TRACE("%d: ", sHTun.GetLength());

	if ((sHTun.GetLength() != 11) || (sHTun.Mid(6,1) != "-"))
	{
		return 6;
	}
	if (bRuotsHTun)
	{
		TRACE("Ruotsalainen tunnus!\n");
		return 0;
	}
	else
		TRACE("Suomalainen tunnus!\n");
	//
	// -- numerojen suuruus ---
	//
	if ( ! NumberCheck(sHTun.GetAt(0), 0, 3)) return 1;
	if ( ! NumberCheck(sHTun.GetAt(1), 0, 9)) return 1;
	if ( ! NumberCheck(sHTun.GetAt(2), 0, 1)) return 1;
	if ( ! NumberCheck(sHTun.GetAt(3), 0, 9)) return 1;
	if ( ! NumberCheck(sHTun.GetAt(4), 0, 9)) return 1;
	if ( ! NumberCheck(sHTun.GetAt(5), 0, 9)) return 1;

	if ( ! NumberCheck(sHTun.GetAt(7), 0, 9)) return 1;
	if ( ! NumberCheck(sHTun.GetAt(8), 0, 9)) return 1;
	if ( ! NumberCheck(sHTun.GetAt(9), 0, 9)) return 1;

	// -- kielletyt numerot --
	//
	if ( sHTun.Mid(7,3) == "000" || sHTun.Mid(7,3) == "001") return 4;
	//
	// -- sukupuoli --
	//
	s = sHTun.GetAt(9);
	TRACE("10.merkki =%s:", s);
	if (s == "2" ||
		s == "4" ||
		s == "6" ||
		s == "8" ||
		s == "0" )
	{
		TRACE("Parillinen ->nainen\n");
		is = 0; // naisilla parillinen
	}
	else
	{
		TRACE("Pariton ->mies\n");
		is = 1;
	}
	if (isp >= 0)
	{
		if (is != isp)
		{
			return 2;
		}
	}

	//
	// -- tarkastusmerkki --
	//
	s = sHTun.Left(6) + sHTun.Mid(7,3);
	if ( ! CheckChar(s, sHTun.GetAt(10)))
		return 5;
	//
	// -- karkauspv --
	//
	if (sHTun.Mid(2,2) == "02" && sHTun.Left(2) == "29")
		return 3;
	//
	// -- pv-tarkastus --
	//
	if ( ! NumberCheck(sHTun.Mid(2,2), 1, 12)) return 7;
	k = atoi(sHTun.Mid(2,2));
	switch (k)
	{
		case 1: if ( ! NumberCheck(sHTun.Left(2), 1, 31)) return 8; break; // tammikuu
		case 2: if ( ! NumberCheck(sHTun.Left(2), 1, 28)) return 8; break;
		case 3: if ( ! NumberCheck(sHTun.Left(2), 1, 31)) return 8; break;
		case 4: if ( ! NumberCheck(sHTun.Left(2), 1, 30)) return 8; break;
		case 5: if ( ! NumberCheck(sHTun.Left(2), 1, 31)) return 8; break;
		case 6: if ( ! NumberCheck(sHTun.Left(2), 1, 30)) return 8; break;
		case 7: if ( ! NumberCheck(sHTun.Left(2), 1, 31)) return 8; break;
		case 8: if ( ! NumberCheck(sHTun.Left(2), 1, 31)) return 8; break;
		case 9: if ( ! NumberCheck(sHTun.Left(2), 1, 30)) return 8; break;
		case 10: if ( ! NumberCheck(sHTun.Left(2), 1, 31)) return 8; break;
		case 11: if ( ! NumberCheck(sHTun.Left(2), 1, 30)) return 8; break;
		case 12: if ( ! NumberCheck(sHTun.Left(2), 1, 31)) return 8; break; // joulu
		default: return 8;
	};

	return 0;
}

BOOL CCustomerInfo::NumberCheck(CString sChar, int iMin, int iMax)
{
	int i = atoi(sChar);
	if (sChar.GetLength() == 1 )
	{
		if ( ! (sChar == "0" ||
				sChar == "1" ||
				sChar == "2" ||
				sChar == "3" ||
				sChar == "4" ||
				sChar == "5" ||
				sChar == "6" ||
				sChar == "7" ||
				sChar == "8" ||
				sChar == "9") )
		{
			return FALSE;
		}
	}
	if (i >= iMin && i <= iMax)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CCustomerInfo::CheckChar(CString sChar, CString s)
{
	int itmp = 0;
	CString sT = "";
	char buf[5];
	CString msg = "";

	TRACE("Merkkijono=%s, tarkastusmerkki=%s\n", sChar,s);
	long l = atol(sChar);
	TRACE(" ... ja numerona %ld\n", l);
	itmp = l%31;
	TRACE("Jakojäännös=%d -> ", itmp);
	if (itmp <= 9)
	{
		itoa(itmp, buf, 10);
		sT = buf;
	}
	else
	{
		switch (itmp)
		{
		case 10: sT = "A"; break;
		case 11: sT = "B"; break;
		case 12: sT = "C"; break;
		case 13: sT = "D"; break;
		case 14: sT = "E"; break;
		case 15: sT = "F"; break; // g puuttuu !
		case 16: sT = "H"; break;
		case 17: sT = "J"; break; // i puuttuu !
		case 18: sT = "K"; break;
		case 19: sT = "L"; break;
		case 20: sT = "M"; break;
		case 21: sT = "N"; break;
		case 22: sT = "P"; break; // o puuttuu !
		case 23: sT = "R"; break; // q puuttuu !
		case 24: sT = "S"; break;
		case 25: sT = "T"; break;
		case 26: sT = "U"; break;
		case 27: sT = "V"; break;
		case 28: sT = "W"; break;
		case 29: sT = "X"; break;
		case 30: sT = "Y"; break;
		default: sT="?";
		};
	}
	TRACE("tarkastusmerkki='%s'\n", sT);
	if (sT != s)
	{
		msg.Format("Tarkastusmerkki pitäisi olla '%s'", sT);
		AfxMessageBox(msg);
		return FALSE;
	}
	return TRUE;
}

CString CCustomerInfo::RemoveSpaces(CString sText)
{
	CString st = "";
	int i = 0;
	//TRACE("RemoveSpaces: Text=%s, Length=%d\n", sText, sText.GetLength());
	while (i != sText.GetLength())
	{
		//TRACE("'%s'\n",sText.Mid(i,1));
		if (sText.Mid(i,1) != " ")
			break;
		i++;
	}
	//TRACE("RemoveSpaces/NewText: %s\n", sText.Right(sText.GetLength() - i));
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

BOOL CCustomerInfo::CheckGender(CString sHtun)
{
	// -- sukupuoli --
	//
	CString s = sHtun + "          ";
	s = s.GetAt(9);
	TRACE("10.merkki =%s:", s);
	if (s == "2" ||
		s == "4" ||
		s == "6" ||
		s == "8" ||
		s == "0" )
	{
		TRACE("Parillinen ->nainen\n");
		return TRUE; // naisilla parillinen
	}
	else
	{
		TRACE("Pariton ->mies\n");
		return FALSE;
	}
}
