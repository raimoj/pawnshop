// MuistutusListaRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "MuistutusListaRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMuistutusListaRS

IMPLEMENT_DYNAMIC(CMuistutusListaRS, CRecordset)

CMuistutusListaRS::CMuistutusListaRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMuistutusListaRS)
	m_MU_Rivi = 0; //_T("");
	m_MU_AS_ID = 0; //_T("");
	m_MU_Nimi = _T("");
	m_MU_LA_Nr = 0;
	m_MU_Laina = 0.0; //_T("");
	m_MU_EraPv = 0;				// HUOM ! Tämä pitää muistaa lisätä !
	m_MU_KirjeNr = 0;
	m_MU_EiMuistutusta = FALSE;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CMuistutusListaRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CMuistutusListaRS::GetDefaultSQL()
{
	//return _T("[dbo].[MUISTUTUSLISTA]");
	return _T("[MUISTUTUSLISTA]");
}

void CMuistutusListaRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMuistutusListaRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[MU_Rivi]"), m_MU_Rivi);
	RFX_Long(pFX, _T("[MU_AS_ID]"), m_MU_AS_ID);
	RFX_Text(pFX, _T("[MU_Nimi]"), m_MU_Nimi);
	RFX_Long(pFX, _T("[MU_LA_Nr]"), m_MU_LA_Nr);
	RFX_Double(pFX, _T("[MU_Laina]"), m_MU_Laina);
	RFX_Date(pFX, _T("[MU_EraPv]"), m_MU_EraPv);
	RFX_Long(pFX, _T("[MU_KirjeNr]"), m_MU_KirjeNr);
	RFX_Bool(pFX, _T("[MU_EiMuistutusta]"), m_MU_EiMuistutusta);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMuistutusListaRS diagnostics

#ifdef _DEBUG
void CMuistutusListaRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CMuistutusListaRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
