#pragma once
#include "afxdialogex.h"


// Dlg2 대화 상자

class Dlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg2)

public:
	Dlg2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Dlg2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCap();
	afx_msg void OnCaptureChanged(CWnd* pWnd);
};
