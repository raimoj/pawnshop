#if !defined(AFX_TUOTERYHMARS_H__F59BAED6_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_)
#define AFX_TUOTERYHMARS_H__F59BAED6_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TuoteryhmaRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTuoteryhmaRS recordset

class CTuoteryhmaRS : public CRRecordset
{
public:
	CTuoteryhmaRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTuoteryhmaRS)

// Field/Param Data
	//{{AFX_FIELD(CTuoteryhmaRS, CRRecordset)
	CString	m_TR_Ryhma;
	CString	m_TR_Nimi;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTuoteryhmaRS)
	public:
	//virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TUOTERYHMARS_H__F59BAED6_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_)
