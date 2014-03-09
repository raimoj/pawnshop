#if !defined(AFX_DLGARVIOMIES_H__E28C28F6_3B89_11D3_89F5_0000E8C7E630__INCLUDED_)
#define AFX_DLGARVIOMIES_H__E28C28F6_3B89_11D3_89F5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgArviomies.h : header file
//


#include "RGXArviomies.h"
#include "ArviomiesRS.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgArviomies dialog

class CDlgArviomies : public CDialog
{
// Construction
public:
	CDlgArviomies(CWnd* pParent = NULL);   // standard constructor
	~CDlgArviomies();   // standard destructor

// Dialog Data
	//{{AFX_DATA(CDlgArviomies)
	enum { IDD = IDD_DLG_ARVIOMIES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgArviomies)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgArviomies)
	virtual BOOL OnInitDialog();
	afx_msg void OnUusiArviomiesrivi();
	virtual void OnOK();
	afx_msg void OnTalleta();
	afx_msg void OnPoista();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnValuerListClicked();
	void UpdateAM(long lAMId, CString sNimikirj, CString sNimi, int iOik);
	BOOL PoistaAM();
	int iRowCount;
	BOOL ShowArviomiehet();
	CRGXArviomies* m_pGXArviomies;

	CArviomiesRS* m_pAMRS;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGARVIOMIES_H__E28C28F6_3B89_11D3_89F5_0000E8C7E630__INCLUDED_)
