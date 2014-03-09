// ArviomiesRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "ArviomiesRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArviomiesRS

IMPLEMENT_DYNAMIC(CArviomiesRS, CRecordset)

CArviomiesRS::CArviomiesRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CArviomiesRS)
	m_AM_Tunnus = 0;//_T("");
	m_AM_Nimikirjaimet = _T("");
	m_AM_Nimi = _T("");
	m_AM_Oikeudet = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CArviomiesRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/


CString CArviomiesRS::GetDefaultSQL()
{
	//return _T("[dbo].[ARVIOMIES]");
	return _T("[ARVIOMIES]");
}

void CArviomiesRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CArviomiesRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[AM_Tunnus]"), m_AM_Tunnus);
	RFX_Text(pFX, _T("[AM_Nimikirjaimet]"), m_AM_Nimikirjaimet);
	RFX_Text(pFX, _T("[AM_Nimi]"), m_AM_Nimi);
	RFX_Long(pFX, _T("[AM_Oikeudet]"), m_AM_Oikeudet);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CArviomiesRS diagnostics

#ifdef _DEBUG
void CArviomiesRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CArviomiesRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
