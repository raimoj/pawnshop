#if !defined(AFX_PRINTRESOURCE_H__EE0E41E3_8DAF_11D5_8AB5_0000E8C7E630__INCLUDED_)
#define AFX_PRINTRESOURCE_H__EE0E41E3_8DAF_11D5_8AB5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintResource.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintResource window

class CPrintResource : public CWnd
{
// Construction
public:
	CPrintResource();

// Attributes
public:
	// --- dlg ---
	CPrintDialog* m_pdlg;
	DEVMODE* m_pdm;
	CDC* m_pdc;

	// --- fonts ----
	CFont* m_pOldFont;
	CFont font;
	CFont fontTiny;
	CFont fontbold;
	CFont fontOtsikot;
	CFont fontRivit;
	CFont fontBold;
	CFont fontSuper;

	// --- DOCINFO ----
	DOCINFO* m_pdi;
	// --- PRINTINFO ----
	CPrintInfo* m_pInfo;
	// --- TEXTMETRIC ---
	TEXTMETRIC* m_ptm;
	int m_iHeight; //rivinväli


private:

// Operations
public:

	void stopPrinter();
	void startPrinter();

private:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintResource)
	//}}AFX_VIRTUAL

// Implementation
public:
	//void printTestPage();
	void setPrintJobName(CString name);
	virtual ~CPrintResource();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPrintResource)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTRESOURCE_H__EE0E41E3_8DAF_11D5_8AB5_0000E8C7E630__INCLUDED_)
