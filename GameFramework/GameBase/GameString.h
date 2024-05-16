#pragma once
#include <string>
#include <atlstr.h> // char => wchar wchar => char로 변환시켜주는 함수가 들어있다.
#include <list>

#pragma region 
/*
	내부에 있는 배열의 포인터를 리턴. -> c_str()를 해서 문자열 + NULL 스타일로 바꿔줌
*/
#pragma endregion



class StringData;
class GameString
{
private:
	std::wstring m_Str;

public:
	const wchar_t* PointerStr()
	{
		return m_Str.c_str();
	}


public:
	static GameString IntToString(int _Value)
	{
		GameString ReturnStr;
		ReturnStr = std::to_wstring(_Value);
		return ReturnStr;
	}


	template<typename FmtType, typename... TemplateTypes>
	void Appendf(const FmtType& Fmt, TemplateTypes... Args)
	{
		AppendfInternal(Fmt, Args...);
	}

	void AppendfInternal(const char* fmt, ...);
	void AppendfInternal(const wchar_t* fmt, ...);

	wchar_t At(int _Index)
	{
		return m_Str.at(_Index);
	}
	wchar_t At(size_t _Pos)
	{
		return m_Str.at(_Pos);
	}

public:
	// 마지막
	bool IsEmpty() const
	{
		return m_Str.size() == 0;
	}

	size_t StrCount() const
	{
		return m_Str.size();
	}

public:
	operator const wchar_t* () const
	{
		return m_Str.c_str();
	}

	/*operator std::wstring() const
	{
		return m_Str;
	}*/

	operator std::string() const
	{
		return CW2A(m_Str.c_str()).m_psz;
	}

	operator char* () const
	{
		return CW2A(m_Str.c_str()).m_psz;
	}

	bool operator==(const wchar_t* _Other) const
	{
		return m_Str == _Other;
	}

	bool operator!=(const wchar_t* _Other) const
	{
		return m_Str != _Other;
	}

	bool operator==(const GameString& _Other) const
	{
		return _Other.m_Str == m_Str;
	}

	bool operator!=(const GameString& _Other) const
	{
		return _Other.m_Str != m_Str;
	}

	bool operator>(const GameString& _Other) const
	{
		return _Other.m_Str > m_Str;
	}

	bool operator<(const GameString& _Other) const
	{
		return _Other.m_Str < m_Str;
	}

	GameString& operator=(const wchar_t* _Ptr)
	{
		m_Str = _Ptr;
		return *this;
	}

	GameString& operator=(const GameString& _Other)
	{
		m_Str = _Other.m_Str;
		return *this;
	}

	GameString operator+(const wchar_t* _Other) const
	{
		return m_Str + _Other;
	}

	GameString operator+(const GameString& _Other) const
	{
		return m_Str + _Other.m_Str;
	}

	GameString& operator+=(const GameString& _Other)
	{
		m_Str += _Other.m_Str;
		return *this;
	}

#pragma region operater[] 오버로딩
	/*
		wchar_t operator[](const int index);

		std::wstring& operator[](int i);

		const std::wstring& operator[](int i) const;
	*/
#pragma endregion

	//std::wstring& operator[](const int index);

	size_t Find(const GameString& _Find, size_t _Off = 0) const
	{
		// find라는 함수가 wstring
		// wchar_t*
		return m_Str.find(_Find.m_Str, _Off);
	}

	/*size_t Find(const GameString& _Find) const
	{
		return m_Str.find(_Find.m_Str);
	}*/

	size_t FindLast(const GameString& _Find) const
	{
		return m_Str.find_last_of(_Find.m_Str);
	}

	void EraseStr(size_t _Start, size_t _End)
	{
		m_Str.replace(_Start, _End, L"");
	}

	void EraseStr(const GameString& _Other)
	{
		size_t Start = Find(_Other, 0);
		EraseStr(Start, Start + _Other.StrCount());
	}

	void ChangeStr(const GameString& _OldStr, const GameString& _NewStr)
	{
		size_t Start = Find(_OldStr, 0);
		EraseStr(Start, Start + _OldStr.StrCount());
		m_Str.insert(Start, _NewStr);
	}

	/* 문자열에서 일부만 뜯어냄 */
	GameString RangeToStr(size_t _Start, size_t _End) const
	{
		std::wstring Str;
		Str.resize(_End - _Start - 1); // 미리 버퍼 할당 
		m_Str.copy(&Str[0], _End - _Start - 1, _Start + 1);
		return Str;
	}

	GameString Cut(size_t _Start, size_t _End) const
	{
		return m_Str.substr(_Start, _End - _Start + 1); // '\\' 원하지 않는다
	}

	//////////////////////// 추가했습니다. 







	GameString GetChangeStr(const GameString& _OldStr, const GameString& _NewStr)
	{
		size_t Start = Find(_OldStr, 0);
		if (Start <= 1000)
		{
			EraseStr(Start, Start + _OldStr.StrCount());
			m_Str.insert(Start, _NewStr);
			return m_Str;
		}
		return L"";
	}



	template <typename T>
	void Change(T t)
	{
		for (size_t i = 0; i < StrCount(); i++)
		{
			if (m_Str[i] == t)
			{
				m_Str[i] = '#';
			}
		}
	}
	template<typename ... REST>
	void ChangeChar(wchar_t b, REST ..._Arg)
	{
		wchar_t* a = &b;

		wchar_t wsd;

		for (size_t z = 0; z < sizeof...(_Arg); z++)
		{
			wsd = *(a + (4 * (z + 1)));

			for (size_t i = 0; i < StrCount(); i++)
			{
				if (m_Str[i] == wsd)
				{
					m_Str[i] = b;
				}
			}
		}
	}

	GameString operator+=(const int _Other)
	{
		GameString numberString = IntToString(_Other); // IntToStringW
		return m_Str += numberString.m_Str;
	}

	GameString operator+=(const float _Other)
	{
		GameString numberString = FloatToString(_Other);
		return m_Str += numberString.m_Str;
	}

	static std::wstring IntToStringW(int _Num)
	{
		std::wstring a;

		int Dit = (int)log10(_Num) + 1;

		for (size_t i = Dit; i > 0; i--)
		{
			int Qun = 1;
			for (size_t z = 1; z < i; z++)
			{
				Qun *= 10;
			}
			int asd = _Num / Qun;

			_Num -= asd * Qun;

			wchar_t SingleDigit = asd + 48;
			a += (wchar_t)SingleDigit;
		}

		return a;
	}

	static std::wstring FloatToString(float _Num, int _time = -1)
	{
		std::wstring OutString = IntToStringW((int)_Num);

		OutString += L'.';

		float OnlyPoint = _Num - (int)_Num;

		while (true)
		{
			_time--;
			OnlyPoint *= 10.0f;

			if ((int)OnlyPoint == 0 || _time == -1)
			{
				break;
			}

			wchar_t SingleDigit = ((int)OnlyPoint) + 48;
			OutString += (wchar_t)SingleDigit;
			OnlyPoint -= (int)OnlyPoint;
		}

		return OutString;

	}









	std::list<GameString> DivideFromComma()
	{
		int StartPos = 0;
		int CommaPos = 0;

		std::list<GameString> SaveList;

		for (std::wstring::iterator Char = m_Str.begin(); Char != m_Str.end(); ++Char)
		{
			CommaPos++;
			if (*Char == L',')
			{
				GameString SaveString;
				for (int Start = StartPos; Start < CommaPos - 1; Start++)
				{
					SaveString.m_Str += (wchar_t)m_Str[Start];
				}
				SaveList.push_back(SaveString);
				StartPos = CommaPos;
			}

			if (Char == m_Str.end() - 1)
			{
				GameString SaveString;
				for (int Start = StartPos; Start < CommaPos; Start++)
				{
					SaveString.m_Str += (wchar_t)m_Str[Start];
				}
				SaveList.push_back(SaveString);
			}
		}
		return SaveList;
	}




	GameString ToLower() const
	{
		std::wstring Str = m_Str;

		for (std::wstring::iterator Char = Str.begin(); Char != Str.end(); ++Char)
		{
			*Char = tolower(*Char);
		}
		return Str;
	}



	std::list<StringData> AllFindData(const GameString& _Name, size_t _Offset = 0);
	std::list<StringData> RerversAllFindData(const GameString& _Name, size_t _Offset = 0);

	size_t RerversTrimPos(size_t _Pos);
	size_t RerversFindTrimPos(size_t _Pos);

	size_t TrimPos(size_t _Pos);
	size_t FindTrimPos(size_t _Pos);

	StringData RerversTrimToTrim(size_t _Pos);
	StringData TrimToTrim(size_t _Pos);


	GameString ToUpperReturn();

public:
	GameString() : m_Str() {}
	GameString(const char* _Ptr) : m_Str(CA2W(_Ptr).m_psz) {}
	GameString(const wchar_t* _Ptr) : m_Str(_Ptr) {}
	GameString(std::wstring _Str) : m_Str(_Str) {}
	GameString(const GameString& _Str) : m_Str(_Str) {}
};

class StringData
{
public:
	GameString StrText;
	size_t StartPos;
	size_t EndPos;
};

#pragma region 전역오퍼레이팅
/*
	전역 오퍼레이팅
	헤더에다가는 전역함수 구현해놓으면 안된다.
*/
#pragma endregion

GameString operator+(const wchar_t* _Left, const GameString& _Right);
bool operator==(const wchar_t* _Left, const GameString& _Right);
bool operator!=(const wchar_t* _Left, const GameString& _Right);

#pragma region wchar_t -> char
/*
	wchar_t* CharToWChar(const char* pstrSrc)
	{
		int nLen = strlen(pstrSrc)+1;
		wchar_t* pwstr      = (LPWSTR) malloc ( sizeof( wchar_t )* nLen);
		mbstowcs(pwstr, pstrSrc, nLen);
		return pwstr;
	}

	char* WCharToChar(const wchar_t* pwstrSrc)
	{
	#if !defined _DEBUG
		int len = 0;
		len = (wcslen(pwstrSrc) + 1)*2;
		char* pstr      = (char*) malloc ( sizeof( char) * len);
		WideCharToMultiByte( 949, 0, pwstrSrc, -1, pstr, len, NULL, NULL);
	#else
		int nLen = wcslen(pwstrSrc);
		char* pstr      = (char*) malloc ( sizeof( char) * nLen + 1);
		wcstombs(pstr, pwstrSrc, nLen+1);
	#endif
		return pstr;
	}
*/
#pragma endregion

