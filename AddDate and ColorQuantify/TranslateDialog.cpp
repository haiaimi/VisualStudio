// TranslateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "AddDate and ColorQuantify.h"
#include "TranslateDialog.h"
#include "afxdialogex.h"


// TranslateDialog 对话框

IMPLEMENT_DYNAMIC(TranslateDialog, CDialogEx)

TranslateDialog::TranslateDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(TranslateDialog::IDD, pParent)
	, TranslateX(0)
	, TranslateY(0)
{

}

TranslateDialog::~TranslateDialog()
{
}

void TranslateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, TranslateX);
	DDX_Text(pDX, IDC_EDIT2, TranslateY);
}


BEGIN_MESSAGE_MAP(TranslateDialog, CDialogEx)
END_MESSAGE_MAP()


// TranslateDialog 消息处理程序
