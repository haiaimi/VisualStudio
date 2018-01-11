// DlgAddData.cpp : implementation file
//

#include "stdafx.h"
#include "AddDate and ColorQuantify.h"
#include "DlgAddData.h"
#include "afxdialogex.h"


// CDlgAddData dialog

IMPLEMENT_DYNAMIC(CDlgAddData, CDialogEx)

CDlgAddData::CDlgAddData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAddData::IDD, pParent)
{

}

CDlgAddData::~CDlgAddData()
{
}

void CDlgAddData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, ctrDateTime);
}


BEGIN_MESSAGE_MAP(CDlgAddData, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgAddData::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgAddData message handlers


void CDlgAddData::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//将控件中的时间传到time变量中
	ctrDateTime.GetTime(time);
	CDialogEx::OnOK();
}
