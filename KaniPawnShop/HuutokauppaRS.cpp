// HuutokauppaRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "HuutokauppaRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuutokauppaRS

IMPLEMENT_DYNAMIC(CHuutokauppaRS, CRecordset)

CHuutokauppaRS::CHuutokauppaRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CHuutokauppaRS)
	m_HK_Nr = 0; //_T("");
	m_HK_Aika = 0;			// HUOM ! Tämä pitää muistaa lisätä !
	m_HK_KuittausAika = 0; // HUOM ! Tämä pitää muistaa lisätä !
	m_HK_Huom = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CHuutokauppaRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CHuutokauppaRS::GetDefaultSQL()
{
	//return _T("[dbo].[HUUTOKAUPPA]");
	return _T("[HUUTOKAUPPA]");
}

void CHuutokauppaRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CHuutokauppaRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[HK_Nr]"), m_HK_Nr);
	RFX_Date(pFX, _T("[HK_Aika]"), m_HK_Aika);
	RFX_Date(pFX, _T("[HK_KuittausAika]"), m_HK_KuittausAika);
	RFX_Text(pFX, _T("[HK_Huom]"), m_HK_Huom);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CHuutokauppaRS diagnostics

#ifdef _DEBUG
void CHuutokauppaRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CHuutokauppaRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
