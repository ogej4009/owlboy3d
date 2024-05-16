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


	// * & ���������� ���� 
	template<typename T>
	void Save(const T& _Value) // const 
	{
		fwrite(&_Value, sizeof(T), 1, FILEPOINTER);
	}

	template<typename T>
	void Save(T* _Value, int _Count) // �ڷ��� ������ ����� �־��ش�.  
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
		// �̵���Ű�°ǵ�.
		fseek(FILEPOINTER, 0, SEEK_END);

		// ������ ���ۿ������� �űⰡ ������
		// ���κ��̽�.
		long size = ftell(FILEPOINTER);
		// �ٽ� ���ʷ� ������.
		fseek(FILEPOINTER, 0, SEEK_SET);
		char* NewPtr = new char[(long)size];
		LoadPointer(NewPtr, size);
		NewPtr[size - 1] = 0;

		std::string StrText = NewPtr;

		// ��Ƽ����Ʈ <> �����ڵ�
		// �ƽ�Ű�ڵ� <> ���̵����Ʈ
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
			m_IsOpen = true; // == ������
		}
	}

	~GameFile()
	{
#pragma region ������ ������ �����ֱ� Ȱ�� ���
		/*
			Local ==> Stack
			������� ������ {}�������� �Ѿ�� �ڿ������� �������.
			������ �װ����� �������.
		*/
#pragma endregion

		if (nullptr != FILEPOINTER)
		{
			fclose(FILEPOINTER);
		}
	}
};

#pragma region ���� ������ ũ�� 
/*
	FILE* PTR;
	int 1
	== b 0000 0001 0000 0000 0000 0000 0000 0000
	  '1'
*/
#pragma endregion

#pragma region ��� 
// write, read, textmode, binarymode 
// "rb" 
// "rt"
// "wb"
// "wt"
#pragma endregion