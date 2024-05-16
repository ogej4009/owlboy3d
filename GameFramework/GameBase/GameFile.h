#pragma once
#include "GameIO.h"

class GameFile : public GameIO
{
public:
	FILE* FILEPOINTER;
	bool m_IsOpen;

public:
	bool IsOpen()
	{
		return m_IsOpen;
	}

	GameString FullPath() const
	{
		return m_Path.m_Str;
	}

	GameString FileName() const
	{
		return IOName();
	}

	GameString Ext() const;

public:
	template<typename T>
	void operator>>(T& _Value)
	{
		fread_s(&_Value, sizeof(T), sizeof(T), 1, FILEPOINTER);
	}


	void operator>>(GameString& _Value)
	{
		int Size = (int)_Value.StrCount();
		fread_s(&Size, sizeof(int), sizeof(int), 1, FILEPOINTER);
		wchar_t* Str = new wchar_t[Size];
		fread_s(Str, sizeof(wchar_t) * Size, sizeof(wchar_t) * Size, 1, FILEPOINTER);
		_Value = Str;
		delete[] Str;
	}

	template<typename T>
	void operator<<(const T& _Value)
	{
		fwrite(&_Value, sizeof(T), 1, FILEPOINTER);
	}

	void operator<<(GameString& _Value)
	{
		int Size = (int)_Value.StrCount();
		Size += 1;
		fwrite(&Size, sizeof(int), 1, FILEPOINTER);
		fwrite(_Value.PointerStr(), sizeof(wchar_t) * Size, 1, FILEPOINTER);
	}


	// * & 이중포인터 주의 
	template<typename T>
	void Save(const T& _Value) // const 
	{
		fwrite(&_Value, sizeof(T), 1, FILEPOINTER);
	}

	template<typename T>
	void Save(T* _Value, int _Count) // 자료형 벡터의 사이즈를 넣어준다.  
	{
		fwrite(_Value, sizeof(T) * _Count, 1, FILEPOINTER);
	}

	template<typename T>
	void Load(T& _Value)
	{
		fread_s(&_Value, sizeof(T), sizeof(T), 1, FILEPOINTER);
	}

	template<typename T>
	void SaveValue(const T& _Value)
	{
		fwrite(&_Value, sizeof(T), 1, FILEPOINTER);
	}

	template<typename T>
	void SavePointer(T* _Value, int _Count)
	{
		fwrite(_Value, sizeof(T) * _Count, 1, FILEPOINTER);
	}


	template<typename T>
	void LoadValue(T& _Value)
	{
		int Value = sizeof(T);

		fread_s(&_Value, sizeof(T), sizeof(T), 1, FILEPOINTER);
	}

	template<typename T>
	void LoadPointer(T* _Value, int _Count)
	{
		fread_s(_Value, sizeof(T) * _Count, sizeof(T) * _Count, 1, FILEPOINTER);
	}

	GameString AllText()
	{
		// 이동시키는건데.
		fseek(FILEPOINTER, 0, SEEK_END);

		// 파일의 시작에서부터 거기가 얼마인지
		// 제로베이스.
		long size = ftell(FILEPOINTER);
		// 다시 최초로 보내고.
		fseek(FILEPOINTER, 0, SEEK_SET);
		char* NewPtr = new char[(long)size];
		LoadPointer(NewPtr, size);
		NewPtr[size - 1] = 0;

		std::string StrText = NewPtr;

		// 멀티바이트 <> 유니코드
		// 아스키코드 <> 와이드바이트
		// HGAMESTRING Str = CA2W( NewPtr).m_psz;
		GameString Str = CA2W(NewPtr, CP_UTF8).m_psz;
		delete[] NewPtr;
		return Str;
	}



public:
	GameFile() : m_IsOpen(false), FILEPOINTER(nullptr) {}

	GameFile(const GameString& _FilePath) : m_IsOpen(false), FILEPOINTER(nullptr)
	{
		m_Path = _FilePath; // SetPath(_Path)
	}

	GameFile(const wchar_t* _Path) : m_IsOpen(false), FILEPOINTER(nullptr)
	{
		m_Path = _Path;
	}

	GameFile(const GameString& _FilePath, const GameString& _FileMode)
		: FILEPOINTER(nullptr), m_IsOpen(false)
	{
		_wfopen_s(&FILEPOINTER, _FilePath, _FileMode);
		//wopen
		//fopen_s(PTR, "C:DJKALFSDJFKLDASJFKLA.PNG", "wb");

		if (nullptr != FILEPOINTER)
		{
			m_IsOpen = true; // == 실행중
		}
	}

	~GameFile()
	{
#pragma region 파일의 스코프 생명주기 활용 기법
		/*
			Local ==> Stack
			만들어진 곳에서 {}스코프를 넘어가면 자연스럽게 사라진다.
			파일은 그곳에서 사라진다.
		*/
#pragma endregion

		if (nullptr != FILEPOINTER)
		{
			fclose(FILEPOINTER);
		}
	}
};

#pragma region 파일 포인터 크기 
/*
	FILE* PTR;
	int 1
	== b 0000 0001 0000 0000 0000 0000 0000 0000
	  '1'
*/
#pragma endregion

#pragma region 모드 
// write, read, textmode, binarymode 
// "rb" 
// "rt"
// "wb"
// "wt"
#pragma endregion