// Dlg2.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "afxdialogex.h"
#include "Dlg2.h"


// Dlg2 대화 상자

IMPLEMENT_DYNAMIC(Dlg2, CDialogEx)

Dlg2::Dlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG2, pParent)
{

}

Dlg2::~Dlg2()
{
}

void Dlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dlg2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CAP, &Dlg2::OnBnClickedButtonCap)
	ON_WM_CAPTURECHANGED()
END_MESSAGE_MAP()


// Dlg2 메시지 처리기


void Dlg2::OnBnClickedButtonCap()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Dlg2::OnCaptureChanged(CWnd* pWnd)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int a = 0;
	CDialogEx::OnCaptureChanged(pWnd);
}
