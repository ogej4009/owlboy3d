#pragma once
#include "GameString.h"
#include <list>

// CFile
#pragma region 프로그래머 기본소양
/*
	디버깅
	파일입출력
	문자열
*/
#pragma endregion

#pragma region _ljGameIO의 목적
/*	경로에 필요한 기능들을 담당하는 클래스 */
#pragma endregion

class GamePath
{
public:
	GameString m_Str;

public:
	static bool IsExistence(const GameString& _Str)
	{
		// 0 : 해당 파일의 존재여부 
		// 2 : 해당 파일의 모드(r,w)
		if (0 == _waccess_s(_Str, 0))
		{
			return true;
		}

		return false;
	}

public:
	GamePath() {}
	GamePath(const wchar_t* _Path) : m_Str(_Path) {}
	GamePath(const GameString& _Path) : m_Str(_Path) {}
	~GamePath() {}

};

class GameIO
{
protected:
	GamePath m_Path;

public:
	GameString CombineFileName(const GameString& _Path)
	{
		return m_Path.m_Str + L"\\" + _Path;
	}

	static GameString FileName(const GameString& _Path)
	{
		size_t Start = _Path.FindLast(L"\\");
		size_t End = _Path.StrCount();
		return _Path.RangeToStr(Start, End);

		/* 
		size_t Start1 = _Path.FindLast(L"\\");

		if (Start1 == std::string::npos)
		{
			Start1 = 0;
		}

		size_t Start2 = _Path.FindLast(L"/");

		if (Start2 == std::string::npos)
		{
			Start2 = 0;
		}

		size_t Start = std::string::npos;

		if (Start1 > Start2)
		{
			Start = Start1;
		}
		else 
		{
			Start = Start2;
		}

		if (Start == std::string::npos)
		{
			Start = 0;
		}

		size_t End = _Path.StrCount();

		GameString Name = _Path.RangeToStr(Start, End);
		
		return Name;
		*/
	}

public:
	const wchar_t* PCONSTWCHAR()
	{
		return m_Path.m_Str;
	}

	GameString IOName() const
	{
		size_t Start = m_Path.m_Str.FindLast(L"\\");
		size_t End = m_Path.m_Str.StrCount();
		return m_Path.m_Str.RangeToStr(Start, End);
	}

	/* 
	GameString IOName() const
	{
		return GameIO::FileName(m_Path.m_Str);
	}
	
	*/

	void SetPath(const GameString& _Path)
	{
		m_Path = _Path;
	}

	/* 
	GameString DirPath() const
	{
		GameString Path = m_Path.m_Str;
		Path.EraseStr(GameIO::FileName(m_Path.m_Str));
		return Path;
	}	
	*/

public:
	GameIO() {}
	~GameIO() {}
};


class GameFile;
class GameDirectory : public GameIO
{
public:
	void MoveParent();
	void MoveParent(const GameString& _Folder);
	//void Move(const GameString& _Folder);
	void Move(const GameString& _Folder, bool _wantnewfolder = false);

public:
	std::list<GameFile> DirAllFile(const wchar_t* _Ext = L"", const wchar_t* _Name = L"");
	std::list<GameFile> DirAllDic(const wchar_t* _Ext = L"", const wchar_t* _Name = L"");
	GameString FolderName();
	bool IsFileExist(const GameString& _FileName);

public:
#pragma region Memo
	/* _ljGameDirectory가 생성된다. m_Path에 지금 실행되는 경로를 넣는 것으로 결국 자신의 경로로 만든다. */
#pragma endregion
	GameDirectory();
	~GameDirectory();
};