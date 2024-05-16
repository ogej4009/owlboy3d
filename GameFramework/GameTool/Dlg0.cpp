// Dlg0.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "afxdialogex.h"
#include "Dlg0.h"


// Dlg0 대화 상자

IMPLEMENT_DYNAMIC(Dlg0, CDialogEx)

Dlg0::Dlg0(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG0, pParent)
{

}

Dlg0::~Dlg0()
{
}

void Dlg0::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BD_VIEW_LAYER_LIST, m_ChkList);
}


BEGIN_MESSAGE_MAP(Dlg0, CDialogEx)
	ON_LBN_SELCHANGE(IDC_BD_VIEW_LAYER_LIST, &Dlg0::OnLbnSelchangeBdViewLayerList)
	ON_CBN_SELCHANGE(IDC_NEW_BD_NAME_COMBO, &Dlg0::OnCbnSelchangeNewBdNameCombo)
	ON_BN_CLICKED(IDC_BD_UPDATE_BTN, &Dlg0::OnBnClickedBdUpdateBtn)
END_MESSAGE_MAP()


// Dlg0 메시지 처리기


BOOL Dlg0::OnInitDialog()
{
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CDialogEx::OnInitDialog();

	SetIcon(0, TRUE);
	SetIcon(0, FALSE);

	//m_ChkList.SubclassDlgItem(IDC_BD_VIEW_LAYER_LIST, this);
	m_ChkList.InsertString(0, L"0");
	m_ChkList.InsertString(1, L"1");
	m_ChkList.InsertString(2, L"2");
	m_ChkList.InsertString(3, L"3");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Dlg0::OnLbnSelchangeBdViewLayerList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Dlg0::OnCbnSelchangeNewBdNameCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Dlg0::OnBnClickedBdUpdateBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
