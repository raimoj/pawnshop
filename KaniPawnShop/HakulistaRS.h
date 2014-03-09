#if !defined(AFX_HAKULISTARS_H__F59BAEDC_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_)
#define AFX_HAKULISTARS_H__F59BAEDC_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HakulistaRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHakulistaRS recordset

class CHakulistaRS : public CRRecordset
{
public:
	CHakulistaRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHakulistaRS)

// Field/Param Data
	//{{AFX_FIELD(CHakulistaRS, CRRecordset)
	long	m_HA_LA_Nr;
	long	m_HA_VNr;
	long	m_HA_AsID;
	CString	m_HA_AsHTun;
	CString	m_HA_LainanNimi;
	CString	m_HA_LainanTuoteryhma;
	CTime	m_HA_EraPv;
	double	m_HA_Laina;
	CString	m_HA_Varasto;
	BOOL	m_HA_Liitteet;
	BOOL	m_HA_Huom;
	BOOL	m_HA_Odotus;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHakulistaRS)
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

#endif // !defined(AFX_HAKULISTARS_H__F59BAEDC_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_)
