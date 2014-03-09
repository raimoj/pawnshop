// RGXTuoterivit2.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXTuoterivit2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CRGXTuoterivit2

CRGXTuoterivit2::CRGXTuoterivit2()
{
	//m_pTuRS = new CTuoteRS;
	//m_pTuRS->m_pDatabase = theApp.GetDatabase();
}

CRGXTuoterivit2::~CRGXTuoterivit2()
{
	//delete m_pTuRS;
}


BEGIN_MESSAGE_MAP(CRGXTuoterivit2, /*CWnd CGXODBCGrid*/CGXRecordWnd)
	//{{AFX_MSG_MAP(CRGXTuoterivit2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXTuoterivit2 message handlers


void CRGXTuoterivit2::OnInitialUpdate()
{
	// initialize CGXDynamicRecordset query
	m_gxquerySet.m_pDatabase = theApp.GetDatabase();
	m_gxquerySet.SetSqlQuery("select * from TUOTE order by TU_TR_Ryhma, TU_Numero");

	/*SELECT TUOTE.TU_TR_Ryhma, TUOTE.TU_Numero, TUOTE.TU_Tunnus, TUOTE.TU_Kuvaus
	FROM TUOTE
	ORDER BY TUOTE.TU_TR_Ryhma, TUOTE.TU_Numero;*/

	// Attach query to CGXODBCGrid
	SetRecordset(&m_gxquerySet);

	// default initialization and open the recordset
	CGXRecordWnd::OnInitialUpdate();
}
