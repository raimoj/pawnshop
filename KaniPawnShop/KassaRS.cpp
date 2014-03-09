// KassaRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "KassaRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKassaRS

IMPLEMENT_DYNAMIC(CKassaRS, CRecordset)

CKassaRS::CKassaRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CKassaRS)
	m_KS_Tunnus = 0;//_T("");
	m_KS_KassanNimi = _T("");
	m_KS_Saldo = 0.0;//_T("");
	m_KS_TarkastusAika = 0; // HUOM ! Tämä pitää muistaa lisätä !
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CKassaRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=");
}*/

CString CKassaRS::GetDefaultSQL()
{
	//return _T("[dbo].[KASSA]");
	return _T("[KASSA]");
}

void CKassaRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CKassaRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[KS_Tunnus]"), m_KS_Tunnus);
	RFX_Text(pFX, _T("[KS_KassanNimi]"), m_KS_KassanNimi);
	RFX_Double(pFX, _T("[KS_Saldo]"), m_KS_Saldo);
	RFX_Date(pFX, _T("[KS_TarkastusAika]"), m_KS_TarkastusAika);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CKassaRS diagnostics

#ifdef _DEBUG
void CKassaRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CKassaRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
