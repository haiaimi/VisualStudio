#pragma once


// RotateDialog �Ի���

class RotateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(RotateDialog)

public:
	RotateDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RotateDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float RotateAngle;
};
