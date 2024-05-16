// Dlg1.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "afxdialogex.h"
#include "Dlg1.h"


// Dlg1 대화 상자

IMPLEMENT_DYNAMIC(Dlg1, CDialogEx)

Dlg1::Dlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG1, pParent)
{

}

Dlg1::~Dlg1()
{
}

void Dlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dlg1, CDialogEx)
END_MESSAGE_MAP()


// Dlg1 메시지 처리기
