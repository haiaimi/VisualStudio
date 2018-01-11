#pragma once
#include "Resource.h"
#include "afxdtctl.h"

// CDlgAddData dialog

class CDlgAddData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddData)
public:
	CDlgAddData(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddData();
	CTime time;
// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl ctrDateTime;
	afx_msg void OnBnClickedOk();
};
