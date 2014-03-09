#if !defined(AFX_HUUTOKAUPPARS_H__1EC1C3F1_A751_11D3_8A1D_0000E8C7E630__INCLUDED_)
#define AFX_HUUTOKAUPPARS_H__1EC1C3F1_A751_11D3_8A1D_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HuutokauppaRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHuutokauppaRS recordset

class CHuutokauppaRS : public CRRecordset
{
public:
	CHuutokauppaRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHuutokauppaRS)

// Field/Param Data
	//{{AFX_FIELD(CHuutokauppaRS, CRRecordset)
	long	m_HK_Nr;
	CTime	m_HK_Aika;
	CTime	m_HK_KuittausAika;
	CString	m_HK_Huom;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHuutokauppaRS)
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

#endif // !defined(AFX_HUUTOKAUPPARS_H__1EC1C3F1_A751_11D3_8A1D_0000E8C7E630__INCLUDED_)
