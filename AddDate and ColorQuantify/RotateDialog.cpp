// RotateDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AddDate and ColorQuantify.h"
#include "RotateDialog.h"
#include "afxdialogex.h"


// RotateDialog �Ի���

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


// RotateDialog ��Ϣ�������
