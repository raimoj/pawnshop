#if !defined(AFX_RRECORDSET_H__765FA3D1_8BD5_11D4_8A69_0000E8C7E630__INCLUDED_)
#define AFX_RRECORDSET_H__765FA3D1_8BD5_11D4_8A69_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RRecordset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRRecordset recordset

class CRRecordset : public CRecordset
{
public:
	CRRecordset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRRecordset)

// Field/Param Data
	//{{AFX_FIELD(CRRecordset, CRecordset)
	long	m_VR_ID;
	CString	m_VR_Huom;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRRecordset)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
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

#endif // !defined(AFX_RRECORDSET_H__765FA3D1_8BD5_11D4_8A69_0000E8C7E630__INCLUDED_)
