#if !defined(AFX_HKLAINATRS2_H__012324B7_D651_11D3_8A35_0000E8C7E630__INCLUDED_)
#define AFX_HKLAINATRS2_H__012324B7_D651_11D3_8A35_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HKLainatRS2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHKLainatRS2 recordset

class CHKLainatRS2 : public CRRecordset
{
public:
	CHKLainatRS2(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHKLainatRS2)

// Field/Param Data
	//{{AFX_FIELD(CHKLainatRS2, CRRecordset)
	long	m_HKL_AsID;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHKLainatRS2)
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

#endif // !defined(AFX_HKLAINATRS2_H__012324B7_D651_11D3_8A35_0000E8C7E630__INCLUDED_)
