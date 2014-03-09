// KassaPvKRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "KassaPvKRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKassaPvKRS

IMPLEMENT_DYNAMIC(CKassaPvKRS, CRecordset)

CKassaPvKRS::CKassaPvKRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CKassaPvKRS)
	m_KP_Rivi = 0;//_T("");
	m_KP_KS_Tunnus = 0;//_T("");
	m_KP_KPP_Rivi = 0;//_T("");
	m_KP_Saldo = 0.0;//_T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CKassaPvKRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CKassaPvKRS::GetDefaultSQL()
{
	//return _T("[dbo].[KASSAPAIVAKIRJA]");
	return _T("[KASSAPAIVAKIRJA]");
}

void CKassaPvKRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CKassaPvKRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[KP_Rivi]"), m_KP_Rivi);
	RFX_Long(pFX, _T("[KP_KS_Tunnus]"), m_KP_KS_Tunnus);
	RFX_Long(pFX, _T("[KP_KPP_Rivi]"), m_KP_KPP_Rivi);
	RFX_Double(pFX, _T("[KP_Saldo]"), m_KP_Saldo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CKassaPvKRS diagnostics

#ifdef _DEBUG
void CKassaPvKRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CKassaPvKRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
