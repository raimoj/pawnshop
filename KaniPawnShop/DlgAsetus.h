#if !defined(AFX_DLGASETUS_H__A81A5943_E8C7_11D2_89C7_0000E8C7E630__INCLUDED_)
#define AFX_DLGASETUS_H__A81A5943_E8C7_11D2_89C7_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAsetus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAsetus dialog

class CDlgAsetus : public CDialog
{
// Construction
public:
	void setYlijaamanAlaraja(double d);
	void setYlijaamanIlmMaksu(double d);
	void setMyValmMaksuMin(double d);
	void setHkPoistoMaksu(double d);
	void setMuistutuskirjeraja(double d);
	void setPostitusmaksu(double d);
	void setVakuusvarmennusmaksu(double d);
	void setMuistutuskirjemaksu(double d);
	void setKuitinkatoaminen(double d);
	void setKuittimaksu(double d);
	void setRaja3(double d);
	void setRaja2(double d);
	void setRaja1(double d);
	void Talleta();
	CDlgAsetus(CWnd* pParent = NULL);   // standard constructor

	double getRaja1();
	double getRaja2();
	double getRaja3();
	double getKuittimaksu();
	double getKuitinkatoaminen();
	double getMuistutuskirjemaksu();
	double getVakuusvarmennusmaksu();
	double getPostitusmaksu();
	double getMuistutuskirjeraja();
	double getHkPoistoMaksu();
	double getMyValmMaksuMin();
	double getYlijaamanIlmMaksu();
	double getYlijaamanAlaraja();




// Dialog Data
	//{{AFX_DATA(CDlgAsetus)
	enum { IDD = IDD_DLG_ASETUS };
	int		m_iLaina_aika;
	CString	m_sToimisto;
	CString	m_sSeurHKPv;
	double	m_dKorko1;
	double	m_dKorko2;
	double	m_dKorko3;
	double	m_dKorko4;
	CString	m_sKatuOs;
	CString	m_sPtp;
	CString	m_sPuh;
	CString	m_sFax;
	double	m_dSHVMaksuPr;
	int		m_iMuistutuskirje1raja_pv;
	int		m_iMuistutuskirje2raja_pv;
	CString	m_sHkEraPvRaja;
	double	m_dHkMaksuProsentti;
	double	m_dMyValmMaksuPr;
	double	m_dArvopapValMaksuPr;
	int		m_iToimenpidekieltoraja;
	int		m_iYlijaamanTilitysaika;
	double	m_dKuittimaksu;
	double	m_dRaja1;
	double	m_dRaja2;
	double	m_dRaja3;
	double	m_dKuitinKatoaminen;
	double	m_dMuistutuskirjemaksu;
	double	m_dVakuusvarmennusmaksu;
	double	m_dPostitusmaksu;
	double	m_dMuistutuskirjeraja_mk;
	double	m_dHkPoMaksu;
	double	m_dMyMalmMaksuMin;
	double	m_dYlijaamanAlaraja;
	double	m_dYlijaamanIlmoitusmaksu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAsetus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTime GetDate(CString dateText);
	void MuutaTekstiPvmksi(char* temp,int* vuosi,int* kk,int* pv);

	// Generated message map functions
	//{{AFX_MSG(CDlgAsetus)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGASETUS_H__A81A5943_E8C7_11D2_89C7_0000E8C7E630__INCLUDED_)
