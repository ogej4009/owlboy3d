#include "GameString.h"

GameString operator+(const wchar_t* _Left, const GameString& _Right)
{
	GameString Str = _Left;
	Str += _Right;
	return Str;
}

bool operator==(const wchar_t* _Left, const GameString& _Right)
{
	return _Right == _Left;
}

bool operator!=(const wchar_t* _Left, const GameString& _Right)
{
	return _Right != _Left;
}



void GameString::AppendfInternal(const char* fmt, ...)
{
	int BufferSize = 512;
	char StartingBuffer[512];
	char* Buffer = StartingBuffer;

	// 스택에 할당한 크기로 처리할 수있는지 확인
	va_list ap;
	va_start(ap, fmt);
	int Result = vsprintf_s(Buffer, BufferSize, fmt, ap);
	va_end(ap);

	// 실패하면 메모리에서 할당한다.
	if (Result >= BufferSize)
	{
		Buffer = nullptr;
		while (Result == -1)
		{
			BufferSize *= 2;
			Buffer = (char*)malloc(BufferSize * sizeof(char));
			va_start(ap, fmt);
			Result = vsprintf_s(Buffer, BufferSize, fmt, ap);
			va_end(ap);
		};
	}

	if (nullptr == Buffer)
	{
		return;
	}

	Buffer[Result] = 0;

	m_Str += CA2W(Buffer).m_psz;

	if (BufferSize != 512)
	{
		free(Buffer);
	}
}

void GameString::AppendfInternal(const wchar_t* fmt, ...)
{
	int BufferSize = 512;
	wchar_t	StartingBuffer[512];
	wchar_t* Buffer = StartingBuffer;

	// 스택에 할당한 크기로 처리할 수있는지 확인
	va_list ap;
	va_start(ap, fmt);
	int Result = vswprintf_s(Buffer, BufferSize, fmt, ap);
	va_end(ap);

	// 실패하면 메모리에서 할당한다.
	if (Result >= BufferSize)
	{
		Buffer = nullptr;
		while (Result == -1)
		{
			BufferSize *= 2;
			Buffer = (wchar_t*)malloc(BufferSize * sizeof(wchar_t));
			va_start(ap, fmt);
			Result = vswprintf_s(Buffer, BufferSize, fmt, ap);
			va_end(ap);
		};
	}

	if (nullptr == Buffer)
	{
		return;
	}

	Buffer[Result] = 0;

	m_Str += Buffer;

	if (BufferSize != 512)
	{
		free(Buffer);
	}
}



std::list<StringData> GameString::AllFindData(const GameString& _Name, size_t _Offset)
{
	std::list<StringData> Data;

	size_t CurSize = _Offset;

	while (true)
	{
		size_t FindSize = m_Str.find(_Name, CurSize + 1);

		if (FindSize == std::string::npos)
		{
			return Data;
		}

		CurSize = FindSize;
		Data.push_back({ _Name ,CurSize, CurSize + _Name.StrCount() });

	}


}

std::list<StringData> GameString::RerversAllFindData(const GameString& _Name, size_t _Offset)
{
	std::list<StringData> Data;

	size_t CurSize = _Offset;

	while (true)
	{
		size_t FindSize = m_Str.rfind(_Name, CurSize - 1);

		if (FindSize == std::string::npos)
		{
			return Data;
		}

		CurSize = FindSize;
		Data.push_back({ _Name ,CurSize, CurSize + _Name.StrCount() });
	}


}

size_t GameString::RerversTrimPos(size_t _Pos)
{
	// " fasdjkf,asdjkflasdjkl       ( asdhjklfasdjklfasdjkl"

	size_t EndPos = _Pos;

	while (L' ' == At(EndPos) || L'\n' == At(EndPos))
	{
		--EndPos;
	}

	return EndPos;
}


size_t GameString::RerversFindTrimPos(size_t _Pos)
{
	size_t EndPos = _Pos;

	while (true)
	{
		wchar_t Check = At(EndPos);

		if (L' ' == Check || L'\n' == Check)
		{
			return EndPos + 1;
		}

		--EndPos;

		if (0 == EndPos)
		{
			break;
		}
	}

	return EndPos;
}

// '\n'
StringData GameString::RerversTrimToTrim(size_t _Pos)
{
	size_t EndPos = RerversTrimPos(_Pos);
	size_t StartPos = RerversFindTrimPos(EndPos);
	return { Cut(StartPos, EndPos),StartPos,  EndPos };
}

size_t GameString::TrimPos(size_t _Pos)
{
	size_t EndPos = _Pos;

	while (L' ' == At(EndPos) || L'\n' == At(EndPos))
	{
		++EndPos;
	}

	return EndPos;
}

size_t GameString::FindTrimPos(size_t _Pos)
{
	size_t EndPos = _Pos;

	while (L' ' != At(EndPos) && L'\n' != At(EndPos))
	{
		++EndPos;
		if (0 == StrCount())
		{
			break;
		}

		if (EndPos >= StrCount())
		{
			break;
		}
	}

	return EndPos - 1;
}

StringData GameString::TrimToTrim(size_t _Pos)
{
	size_t StartPos = TrimPos(_Pos);
	size_t EndPos = FindTrimPos(StartPos);
	return { Cut(StartPos, EndPos), StartPos,  EndPos };
}

GameString GameString::ToUpperReturn()
{
	GameString Text = *this;


	for (size_t i = 0; i < Text.StrCount(); i++)
	{
		Text.m_Str[i] = toupper(At(i));
	}

	return Text;
}