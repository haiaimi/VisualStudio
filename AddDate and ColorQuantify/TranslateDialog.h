#pragma once


// TranslateDialog 对话框

class TranslateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TranslateDialog)

public:
	TranslateDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TranslateDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float TranslateX;
	float TranslateY;
};
