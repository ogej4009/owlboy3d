#include "GameWin.h"
#include <Windows.h>
#include <assert.h>
//#include "GameSound.h"
#include "GameMovie.h" //// 추가했습니다. 


#pragma region 메모리 관리 이슈
/*
	메모리의 메커니즘
	영역이 자동으로 만든다.
	데이터 영역에 순서가 있다. 메모리의 생명주기(lifecycle)에 순서가 있다.
*/
#pragma endregion

GameWin::GameWinStarter GameWin::Starter = GameWin::GameWinStarter();
bool GameWin::IsProcess = true;

//////////////////////////////////////////////////////////// 추가했습니다. 
void CALLBACK OnGraphEvent(HWND hwnd, long evCode, LONG_PTR param1, LONG_PTR param2)
{
	switch (evCode)
	{
	case EC_COMPLETE:
	case EC_USERABORT:
	{
		wchar_t ArrName[256];
		GetWindowText(hwnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);
		Ptr->GetMoviePlayer()->MovieStop();
		break;
	}
	case EC_ERRORABORT:
		// NotifyError(hwnd, L"Playback error.");
	{
		MSG_ASSERT_CODE(L"영상 재생에 문제가 있습니다.");
		wchar_t ArrName[256];
		GetWindowText(hwnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);
		Ptr->GetMoviePlayer()->MovieStop();
		break;
	}
	}
}


LRESULT CALLBACK GameWin::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	/////////////////////////////////// 추가 적용? 

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	/*{
		wchar_t ArrName[256];
		GetWindowText(hWnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);

		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);

		if (nullptr != Ptr)
		{
			if (Ptr->MoviePlayer->State() != STATE_NO_GRAPH && Ptr->MoviePlayer->HasVideo())
			{
				Ptr->MoviePlayer->Repaint(hdc);
			}
			else
			{
				FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			}
		}

		EndPaint(hWnd, &ps);
	}*/

	break;
	case WM_CREATE:   //////// 추가했습니다. 
	{
		wchar_t ArrName[256] = L"";
		// mfc은 HWndProc가 실행이 안된다. 
		GetWindowText(hWnd, ArrName, 256);
		break;
	}
	case WM_SETCURSOR:
	{
		// Turn off window cursor 
		SetCursor(NULL);
		ShowCursor(FALSE);
		return TRUE; // prevent Windows from setting cursor to window class cursor
	}
	break;

	/*case WM_DISPLAYCHANGE:
	{
		wchar_t ArrName[256];
		GetWindowText(hWnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);
		Ptr->MoviePlayer->DisplayModeChanged();
		break;
	}
	case WM_GRAPH_EVENT:
	{
		wchar_t ArrName[256];
		GetWindowTextW(hWnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);
		Ptr->MoviePlayer->HandleGraphEvent(OnGraphEvent);
		return 0;
	}*/

	case WM_DESTROY:
		IsProcess = false;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void GameWin::RegDef()
{
	GameDebug::LeckCheck();

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &GameWin::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = nullptr;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"DEF";
	wcex.hIconSm = nullptr;

	RegisterClassExW(&wcex);
}

void GameWin::WINMESSAGE(INITFUNC _Init, DEADTIME _CallBack)
{
#pragma region 메세지루프 
	/*
		기본 메시지 루프.
		어차피 이 GetMessage 사용하지 않는다.
		동기(synchronization) 함수라서 메세지가 올 때까지 멈춘다.
	*/
#pragma endregion
	if (nullptr != _Init)
	{
		_Init();
	}

	MSG msg;

	while (true == IsProcess)
	{
#pragma region 픽메세지함수 == 비동기함수 
		/*
			PeekMessage 메세지 함수는 '비동기 함수' 입니다.
			PeekMessage 비동기 함수가 바로 리턴되는 방식입니다. 즉 멈추지 않는다.
			<옵션 인자>
			메세지가 순식간에 너무 많이 들어와서 메세지가 쌓일 경우 어떻게 처리되는가?
			PM_NOREMOVE : 안 지우고 다 처리한다.
			PM_REMOVE : 밀리면 다 지우고 밀어버린다.
			최근의 컴퓨터수준은 처리가 안되는 경우는 없다.
			메세지가 없어도 리턴함수이다.
			메세지가 있는 경우 ->  유의미한 0이상의 수(값)을 리턴.
			메세지가 없는 경우 ->  0을 리턴.
		*/
#pragma endregion
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (nullptr != _CallBack)
			{
				//GameSound::Update();
				GameDebug::DebugFrameUpdate();
				_CallBack();
			}
		}
	}

#pragma region 데드타임
	/*
		'메세지'가 없는 시간을 데드타임이라고 한다.
		게임은 대부분 데드타임에서 돌아간다. 게임은 여기서 실행되면 된다.
		'메세지'와 게임이 동시에 돌아가니까 너무 걱정하지 않아도 된다.
		윈도우는 '메세지'가 없는 시간이 더 많다.
		미친듯이 윈도우 '메세지'가 많으면 게임이 정지할 수 있다.
	*/
#pragma endregion
}

void GameWin::Create(const GameString& _WindowName, const GameString& _ClassName)
{
	CPtr<GameWin> NewWindow = CreateAndInsert(_WindowName, _ClassName);
}

void GameWin::Create(const GameString& _WindowName, HWND _HWnd)
{
	CPtr<GameWin> NewWindow = CreateAndInsert(_WindowName, _HWnd);
}

GameWin::GameWin(const GameString& _Name)
{
	Style = WS_OVERLAPPEDWINDOW;
	m_HWND = CreateWindowW(L"DEF", _Name, Style, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		nullptr, nullptr, nullptr, nullptr);	// 윈도우 핸들이 있어야 HDC를 얻어올수 있다.

	if (!m_HWND)
	{
		assert(false);
	}

	m_HDC = GetDC(m_HWND);// 윈도우에 무언가를 그릴수 있는 권한

	ShowWindow(m_HWND, SW_SHOW);
	UpdateWindow(m_HWND);
}

GameWin::GameWin(HWND _HWnd)
{
	m_HWND = _HWnd;
	if (!m_HWND)
	{
		assert(false);
	}
	m_HDC = GetDC(m_HWND);
	UpdateWindow(m_HWND);
}

GameWin::~GameWin()
{
	///////////////////// 추가했습니다. 
	delete MoviePlayer;

}

void GameWin::Size(const CVector& _Size)
{
#pragma region 윈도우 사이즈 알기
	/*
		윈도우BAR가 있고, 추가로 좌우 사이드에도 BAR가 있다.
		그것을 알고 크기를 계산해야 한다.
		GetClientRect(m_HWND, ) : (위의BAR사이즈추가한)윈도우의 크기를 얻는 함수
	*/
#pragma endregion

	m_Size = _Size;
	RECT Rect = { 0, 0, _Size.IX(), _Size.IY() };

	AdjustWindowRect(&Rect, Style, FALSE);
	SetWindowPos(m_HWND, nullptr, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOMOVE | SWP_NOZORDER);
}

CVector GameWin::MousePos()
{
#pragma region 마우스좌표가져오기 
	/*
		마우스의 위치를 계산하는 개념에서 중요한 것은
		윈도우마다 그 절대 좌표 위치값이 다르다는 것이다.
		해상도에 따라 픽셀의 세밀함이 다르게 때문이다.
		GetCursorPos()를 통해 모니터에서의 마우스 위치를 알 수 있다.
		ScreenToClient(m_HWND, 현재 실행하는 윈도우 기준으로 계산해준다.
	*/
#pragma endregion

	POINT P;
	GetCursorPos(&P);
	ScreenToClient(m_HWND, &P);
	return { (float)P.x, (float)P.y };
}

CMatrix GameWin::ViewPort()
{
	CMatrix Mat;
	Mat.VIEWPORT(0.0f, 0.0f, Size().X, Size().Y, 0.0f, 1.0f);
	return Mat;
}

CVector GameWin::MousePosVec3D()
{
	CVector Pos = MousePos();
	Pos.X -= m_Size.HX();
	Pos.Y -= m_Size.HY();
	Pos.Y *= -1.0f;
	return Pos;
}

CVector GameWin::WindowPosTo3DPos(CVector _WindowPos)
{
	return CVector::WindowPosTo3dPos(_WindowPos, m_Size);
}

#pragma region 객체지향
/*
	SOLID 객체지향의 다섯가지 권장 설계 <인터페이스 분리원칙>
	자잘한함수를 만들고 그것들을 조합해서 새로운 기능을 만들어라.
*/
#pragma endregion