#if !defined(AFX_RGXMAINWNDLRGRID_H__FFA49944_D941_11D2_89C2_0000E8C7E630__INCLUDED_)
#define AFX_RGXMAINWNDLRGRID_H__FFA49944_D941_11D2_89C2_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXMainWndLRGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXMainWndLRGrid window

class CRGXMainWndLRGrid : public /*CWnd*/ /*CGXRecordWnd*/ CGXGridWnd
{
// Construction
public:
	CRGXMainWndLRGrid();

// Attributes
public:
	//CGXDynamicRecordset* m_pLRiviRS;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXMainWndLRGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	void clear();
	virtual ~CRGXMainWndLRGrid();
	virtual void OnInitialUpdate();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXMainWndLRGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXMAINWNDLRGRID_H__FFA49944_D941_11D2_89C2_0000E8C7E630__INCLUDED_)
