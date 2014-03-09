#if !defined(AFX_DLGYJMAKSU_H__7A38FE98_D821_11D3_8A36_0000E8C7E630__INCLUDED_)
#define AFX_DLGYJMAKSU_H__7A38FE98_D821_11D3_8A36_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgYjMaksu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgYjMaksu dialog

class CRGXAuctBalSetOff;
class CAuctionCtrl;

class CDlgYjMaksu : public CDialog
{
// Construction
public:
	void setSelectedLoan(long lLNr, bool bLock);
	CDlgYjMaksu(CWnd* pParent = NULL);   // standard constructor
	CDlgYjMaksu(CAuctionCtrl* pActl, CWnd* pParent = NULL);   // new constructor
	~CDlgYjMaksu();   // standard dtor


// Dialog Data
	//{{AFX_DATA(CDlgYjMaksu)
	enum { IDD = IDD_DLG_YJ_MAKSU };
	CStatic	m_ctlValittuLaina;
	CButton	m_ctlBtnKuitti;
	CComboBox	m_ctlKirjeNr;
	CComboBox	m_ctlHenkTun;
	CString	m_sKirjeNr;
	CString	m_sHenkTun;
	CString	m_sValittuLaina;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgYjMaksu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgYjMaksu)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeKirjenr();
	afx_msg void OnSelchangeHenktun();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSulje();
	afx_msg void OnEtsi();
	afx_msg void OnKuitti();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_lSelectedLoan;
	CRGXAuctBalSetOff* m_pCRGXAuctBalSetOff;
	CAuctionCtrl* m_pActl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGYJKUITTAUS_H__7A38FE98_D821_11D3_8A36_0000E8C7E630__INCLUDED_)
