#if !defined(AFX_LOANROW_H__92268149_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_LOANROW_H__92268149_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoanRow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoanRow window

class CLoanRow : public /*CWnd*/ CObject
{
// Construction
public:
	CLoanRow();

// Attributes
public:
	long	m_LR_LRivi;
	long	m_LR_LA_Nr;
	long	m_LR_TP_Tap;
	long	m_LR_RiviNr;
	CString	m_LR_TU_Numero;
	long	m_LR_Maara;
	CString	m_LR_Yks;
	double	m_LR_YksPaino;
	CString	m_LR_Kuvaus;
	CString	m_LR_Huom;
	double	m_LR_Vakuus;
	double	m_LR_Laina;
	CString	m_LR_Varasto;
	double	m_LR_SeurLyh;

	double	m_muutos; // lainamuutokset, lyhennyksien huomioiminen jyvittämällä lainasummiin
	double	m_uusiLaina;
	double	m_kiinnitettyLainasumma;

	BOOL	m_bPoistettuMuutosDlgssa;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoanRow)
	//}}AFX_VIRTUAL

// Implementation
public:
	
	virtual ~CLoanRow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLoanRow)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOANROW_H__92268149_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_)
