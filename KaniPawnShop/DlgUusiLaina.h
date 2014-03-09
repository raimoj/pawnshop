#if !defined(AFX_DLGUUSILAINA_H__31AADA73_A507_11D5_8AC1_0000E8C7E630__INCLUDED_)
#define AFX_DLGUUSILAINA_H__31AADA73_A507_11D5_8AC1_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUusiLaina.h : header file
//

#include "RGXUusiLainaRGrid.h"
#include "Loan.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgUusiLaina dialog


class CPQueue;

class CDlgUusiLaina : public CDialog
{
// Construction
public:
	void fromGrid();
	CRGXUusiLainaRGrid* m_pLainarivit;
	CString GetDlgString();
	BOOL m_bCanceled;
	CDlgUusiLaina(CWnd* pParent = NULL);   // standard constructor
	~CDlgUusiLaina();

	CString m_sSNimi;
	CString m_sHtun;
	long m_AsId;

	double GetFee();
	bool Kuitti();
	
// Dialog Data
	//{{AFX_DATA(CDlgUusiLaina)
	enum { IDD = IDD_DLG_UUSI_LAINA };
	CStatic	m_ctlLainasumma;
	CStatic	m_ctlVakuusarvo;
	CComboBox	m_ctlHenkTark;
	CEdit	m_ctlVarasto;
	CComboBox	m_ctlLainanTuoteryhma;
	CString	m_sPv;
	CString	m_sEraPv;
	CString	m_sLiitteet;
	CString	m_sHuom;
	BOOL	m_bEiMuistutusta;
	CString	m_sLainanNimi;
	double	m_dKorkoPr;
	double	m_dSHVMaksuPr;
	CString	m_sHtun_Nimi;
	CString	m_sHuom2;
	CString	m_sVarasto;
	CString	m_sVakuusarvo;
	CString	m_sLainasumma;
	CString	m_sYlimSailMaksu;
	CString	m_sSeuraavaLyhennys;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUusiLaina)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUusiLaina)
	virtual void OnOK();
	afx_msg void OnKuitti();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnLaske();
	virtual void OnCancel();
	afx_msg void OnPeru();
	afx_msg void OnTeelaina();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	double m_dYlimSailMaksu;
	double m_dLainasumma;
	double m_dVakuusarvo;
	CString m_sVarmennus;
	bool m_bDlgAlreadyExists;
	long m_lLNr;
	int m_rows;
	CLoan* m_pLoan;
	CString m_sSelectedProductGroup;
	int m_iSelectedProductGroup;
	CTime m_dateEraPv;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUUSILAINA_H__31AADA73_A507_11D5_8AC1_0000E8C7E630__INCLUDED_)
