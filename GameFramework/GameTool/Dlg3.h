#pragma once
#include "afxdialogex.h"


// Dlg3 대화 상자

class Dlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg3)

public:
	Dlg3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Dlg3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeTileGridCombo();
	virtual BOOL OnInitDialog();
	CComboBox m_ComboBoxList;
	bool m_bDlg3Trigger;
	afx_msg void OnBnClickedTileSelBtn();
};
