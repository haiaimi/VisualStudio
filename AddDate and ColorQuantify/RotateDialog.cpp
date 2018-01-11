// RotateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "AddDate and ColorQuantify.h"
#include "RotateDialog.h"
#include "afxdialogex.h"


// RotateDialog 对话框

IMPLEMENT_DYNAMIC(RotateDialog, CDialogEx)

RotateDialog::RotateDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(RotateDialog::IDD, pParent)
	, RotateAngle(0)
{

}

RotateDialog::~RotateDialog()
{
}

void RotateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, RotateAngle);
}


BEGIN_MESSAGE_MAP(RotateDialog, CDialogEx)
END_MESSAGE_MAP()


// RotateDialog 消息处理程序
