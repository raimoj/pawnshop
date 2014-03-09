#if !defined(AFX_RGXKASSARAPORTTI_H__552E4F94_62D7_11D3_8A0B_0000E8C7E630__INCLUDED_)
#define AFX_RGXKASSARAPORTTI_H__552E4F94_62D7_11D3_8A0B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXKassaraportti.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXKassaraportti window

class CKassaRS;
class CKassalokiRS;
class CKRController;
class CDlgKassaraportti;


class CRGXKassaraportti : public /*CWnd*/CGXGridWnd
{
// Construction
public:
	CRGXKassaraportti();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXKassaraportti)
	//}}AFX_VIRTUAL

// Implementation
public:
	double getFinalDeskBalance(long lDeskCounter);
	
	
	

	CDlgKassaraportti* m_pDlgKR;

	void printMainReport();
	bool isMainAccountPermissible();
	void initRowHeaders();
	void initColumnHeaders(CKassaRS* pKassaRS);
	virtual ~CRGXKassaraportti();

	void getDeskInfo(CKassaRS* pKassaRS);
	//void countGridData();
	void setKRController(CKRController* pKRC){m_pKRC = pKRC;};

	void compute(CKassaRS* pKassaRS, CKassalokiRS* pKassalokiRS);


	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXKassaraportti)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	double m_dAlennusYht;
	double m_dAlijMkYht;
	double m_dYlijMkYht;

	int		m_iUudetKplYht;
	double	m_dUudetMkYht;

	int		m_iLunastetutKplYht;
	double	m_dLunastetutMkYht;
	double m_dLunastetutTMMkYht;
	double m_dLunastetutSHVMkYht;
	double m_dLunastetutKorotMkYht;
	double m_dLunastetutKulutMkYht;

	int		m_iUudistetutKplYht;
	double	m_dUudistetutMkYht;
	double m_dUudistetutTMMkYht;
	double m_dUudistetutSHVMkYht;
	double m_dUudistetutKorotMkYht;
	double m_dUudistetutKulutMkYht;
	
	double	m_dPankistaMkYht;
	double	m_dPankkiinMkYht;
	double	m_dVisaYht;
	double	m_dKassastaMkYht;
	double	m_dKassaanMkYht;

	int		m_iKorotuksetKplYht;
	double	m_dKorotuksetMkYht;
	double m_dKorotuksetTMMkYht;
	double m_dKorotuksetSHVMkYht;
	double m_dKorotuksetKorotMkYht;
	double m_dKorotetutKulutMkYht;


	double	m_dLoppusaldoYht;
	double	m_dAlkusaldoYht;
	bool	bMainAccountClosingPermissible;

	CKRController* m_pKRC;
	int m_iColCount;
	CDC dc;

	void	printSubTitleRow(int iRow);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXKASSARAPORTTI_H__552E4F94_62D7_11D3_8A0B_0000E8C7E630__INCLUDED_)
