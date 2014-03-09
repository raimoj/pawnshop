#if !defined(AFX_DLGKASSARAPORTTI_H__552E4F91_62D7_11D3_8A0B_0000E8C7E630__INCLUDED_)
#define AFX_DLGKASSARAPORTTI_H__552E4F91_62D7_11D3_8A0B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKassaraportti.h : header file
//

#include "RGXKassaraportti.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgKassaraportti dialog

class CKRController;


class CDlgKassaraportti : public CDialog
{
// Construction

public:

	CDlgKassaraportti(CWnd* pParent = NULL);   // standard constructor
	~CDlgKassaraportti();

	void setController(CKRController* pKR);


// Dialog Data
	//{{AFX_DATA(CDlgKassaraportti)
	enum { IDD = IDD_DLG_KASSARAPORTTI };
	CButton	m_ctlBtnVisa;
	CButton	m_ctlUndo;
	CComboBox	m_ctlKassa2;
	CButton	m_ctlBtnSiirto;
	CButton	m_ctlBtnPano;
	CButton	m_ctlBtnNosto;
	CComboBox	m_ctlKassa1;
	CButton	m_ctlPaivakirja;
	CString	m_sRapPvm;
	CString	m_sPvkStart;
	CString	m_sPvkStop;
	CString	m_sLainakanta;
	CString	m_sKassanNimi;
	CString	m_sSiirtosumma;
	CString	m_sYhtRahaaKoKassassa;
	CString	m_sVisaSiirtoSumma;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgKassaraportti)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgKassaraportti)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEtsi();
	afx_msg void OnPaivakirja();
	afx_msg void OnKpRaportti();
	afx_msg void OnSiirto();
	afx_msg void OnSelchangeKassa1();
	afx_msg void OnChangeSiirtosumma();
	afx_msg void OnSelchangeKassa2();
	afx_msg void OnNosto();
	afx_msg void OnPano();
	afx_msg void OnSaldoOk();
	afx_msg void OnBtnLainakanta();
	afx_msg void OnSiirtosaatavat();
	afx_msg void OnUndo();
	afx_msg void OnVisa();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	void setYhtRahaaKoKassassa(double kassanSaldo);
	void updateTimeRange();
	void initCtls();
	
	CRGXKassaraportti* m_pKRGrid;

private:
	BOOL isUndoPossible();
	int enableButtons(int iButtons);
	int updateButtons(int iState);
	double m_dSiirtosumma;
	double m_dVisaSiirtosumma;
	BOOL isTransferAllowed();
	BOOL showDesks();
	CTime t;

	CKRController* m_pKR;

	CKassaRS* m_pKRS;
	BOOL m_bDeskSelectionOK;
	CString m_sKassa1;
	CString m_sKassa2;
	
	enum { B_NOST = 1,	// "Nosto"-painike
       B_PANO = 2,		// "Pano"-painike
       B_SIIRT = 4,		// Siirto + muut
       /*B_V = 8,		//
       B_TCK = 16,		// Kuitti (Ticket)
       B_EVN = 32,		// Tapahtumat (Events)
       B_POI = 64,
       B_TO = 128, // Tosittteen tulostus
       B_KA = 256, // K‰teiskuitin tulostuspainike
       B_LA = 512, // Laskun tulostus
       BR_PO = 1024, // Painike tositerivin poistamiseksi
       BR_KO = 2048, // rivin korjaus
       BR_LI = 4096, // Lis‰‰minen
		B_HY = 8192, // Painike uuden rivin hyv‰ksymiseksi
		B_LAS = 16384 // Laske Yht-hinnat*/
	};
	enum { T_ALKU = 1,  // painikkeiden tila dlg:n avauduttua
		T_KASSA_SNOK = 2,      // kassa on valittu, summa NOK
		T_KASSA_SOK = 3,	// kassa on valittu ja summa annettu
		T_SIIRTO = 4,      // kassat on valittu siirtoa varten (siirto+muut)
		T_VAINSIIRTO = 5	// vain siirto
		/*T_OK =5,
		T_TYH = 6,
		T_AOK_LLUNOK = 7 */
	};
	enum {IS_OK = 0, IS_ERROR = 1};


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGKASSARAPORTTI_H__552E4F91_62D7_11D3_8A0B_0000E8C7E630__INCLUDED_)
