// Muistutuskirje2RS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "Muistutuskirje2RS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMuistutuskirje2RS

IMPLEMENT_DYNAMIC(CMuistutuskirje2RS, CRecordset)

CMuistutuskirje2RS::CMuistutuskirje2RS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMuistutuskirje2RS)
	m_AS_ID = 0;
	m_AS_HTun = _T("");
	m_AS_Nimi = _T("");
	m_AS_KatuOs = _T("");
	m_AS_Ptp = _T("");
	m_AS_Kielto = 0;
	m_AS_KieltoAika = 0;			// HUOM! Tämä pitää muistaa lisätä!
	m_AS_MuistEsto = 0;
	
	m_MU_AS_ID = _T("");
	m_MU_Nimi = _T("");
	m_MU_LA_Nr = 0;
	m_MU_Laina = 0;//_T("");
	m_MU_EraPv = 0;			// HUOM! Tämä pitää muistaa lisätä!
	m_MU_KirjeNr = 0;
	m_MU_EiMuistutusta = FALSE;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CMuistutuskirje2RS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CMuistutuskirje2RS::GetDefaultSQL()
{
	//return _T("[dbo].[ASIAKAS],[dbo].[MUISTUTUSLISTA]");
	return _T("[ASIAKAS],[MUISTUTUSLISTA]");
}

void CMuistutuskirje2RS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMuistutuskirje2RS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[AS_ID]"), m_AS_ID);
	RFX_Text(pFX, _T("[AS_HTun]"), m_AS_HTun);
	RFX_Text(pFX, _T("[AS_Nimi]"), m_AS_Nimi);
	RFX_Text(pFX, _T("[AS_KatuOs]"), m_AS_KatuOs);
	RFX_Text(pFX, _T("[AS_Ptp]"), m_AS_Ptp);
	RFX_Long(pFX, _T("[AS_Kielto]"), m_AS_Kielto);
	RFX_Date(pFX, _T("[AS_KieltoAika]"), m_AS_KieltoAika);
	RFX_Long(pFX, _T("[AS_MuistEsto]"), m_AS_MuistEsto);
	
	RFX_Text(pFX, _T("[MU_AS_ID]"), m_MU_AS_ID);
	RFX_Text(pFX, _T("[MU_Nimi]"), m_MU_Nimi);
	RFX_Long(pFX, _T("[MU_LA_Nr]"), m_MU_LA_Nr);
	RFX_Double(pFX, _T("[MU_Laina]"), m_MU_Laina);
	RFX_Date(pFX, _T("[MU_EraPv]"), m_MU_EraPv);
	RFX_Long(pFX, _T("[MU_KirjeNr]"), m_MU_KirjeNr);
	RFX_Bool(pFX, _T("[MU_EiMuistutusta]"), m_MU_EiMuistutusta);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMuistutuskirje2RS diagnostics

#ifdef _DEBUG
void CMuistutuskirje2RS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CMuistutuskirje2RS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
