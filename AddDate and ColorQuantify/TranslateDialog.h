#pragma once


// TranslateDialog �Ի���

class TranslateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TranslateDialog)

public:
	TranslateDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TranslateDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float TranslateX;
	float TranslateY;
};
