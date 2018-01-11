// ChangeScale.cpp : 实现文件
//

#include "stdafx.h"
#include "AddDate and ColorQuantify.h"
#include "ChangeScale.h"
#include "afxdialogex.h"


// ChangeScale 对话框

IMPLEMENT_DYNAMIC(ChangeScale, CDialogEx)

ChangeScale::ChangeScale(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChangeScale::IDD, pParent)
	, InputScale(0)
{

}

ChangeScale::~ChangeScale()
{
}

void ChangeScale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, InputScale);
}


BEGIN_MESSAGE_MAP(ChangeScale, CDialogEx)
END_MESSAGE_MAP()


// ChangeScale 消息处理程序
