// Dlg3.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "afxdialogex.h"
#include "Dlg3.h"


// Dlg3 대화 상자

IMPLEMENT_DYNAMIC(Dlg3, CDialogEx)

Dlg3::Dlg3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG3, pParent)
{

}

Dlg3::~Dlg3()
{
}

void Dlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TILE_GRID_COMBO, m_ComboBoxList);
}


BEGIN_MESSAGE_MAP(Dlg3, CDialogEx)
	ON_CBN_SELCHANGE(IDC_TILE_GRID_COMBO, &Dlg3::OnCbnSelchangeTileGridCombo)
	ON_BN_CLICKED(IDC_TILE_SEL_BTN, &Dlg3::OnBnClickedTileSelBtn)
END_MESSAGE_MAP()


// Dlg3 메시지 처리기


void Dlg3::OnCbnSelchangeTileGridCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}


BOOL Dlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetIcon(0, TRUE);
	SetIcon(0, FALSE);

	m_ComboBoxList.AddString(_T("BLUE"));
	m_ComboBoxList.AddString(_T("BROWN"));
	m_ComboBoxList.AddString(_T("DARK"));
	m_ComboBoxList.AddString(_T("EMERALD"));
	m_ComboBoxList.AddString(_T("MAGENTA"));
	m_ComboBoxList.AddString(_T("MAINMENU"));
	m_ComboBoxList.AddString(_T("MARKERINSTADEATH"));
	m_ComboBoxList.AddString(_T("NAVY"));
	m_ComboBoxList.AddString(_T("PURPLE"));
	m_ComboBoxList.AddString(_T("RED"));
	m_ComboBoxList.AddString(_T("SKYBLUE"));
	m_ComboBoxList.AddString(_T("TEXTCOLOR"));
	m_ComboBoxList.AddString(_T("WHITE"));



	// 콤보 박스에 항목이 1개 이상인 경우 첫번째 항목으로 선택
	if (m_ComboBoxList.GetCount() > 0)
	{
		m_ComboBoxList.SetCurSel(0);
	}
	int a = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Dlg3::OnBnClickedTileSelBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCurSel = m_ComboBoxList.GetCurSel();
	// 선택 Focus가 없어진 경우에는 -1을 반환

	if (nCurSel >= 0)
	{
		CString StrText = _T("");
		StrText.Format(_T("현재 선택한 콤보 박스의 인덱스는 %d 입니다."), nCurSel);
		MessageBox(StrText);
		m_bDlg3Trigger = true;
	}

	//LevelDesignView::GetMainMapToolEditor()->TileTrigger(m_bDlg3Trigger); 
	//LevelDesignView::GetMainMapToolEditor()->TileInit(nCurSel);


}
