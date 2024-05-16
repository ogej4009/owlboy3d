#include "GameIO.h"
#include <Windows.h>
#include <assert.h>
#include <iostream> 
#include <io.h> 
#include "GameFile.h"

GameDirectory::GameDirectory()
{
#pragma region CASE
	/*
		GetCurrentDirectory : ���� ����Ǵ� ��ο� ���� ����

		LPWSTR typedef �ؼ�
		LP : ������
		STR : ���ڿ�
		W : ���̵� ����Ʈ ���ڿ�
	*/
#pragma endregion

	WCHAR Str[256];
	GetCurrentDirectory(256, Str);
	m_Path.m_Str = Str;
}


GameDirectory::~GameDirectory() {}


void GameDirectory::MoveParent()
{
	size_t Start = m_Path.m_Str.FindLast(L"\\");
	size_t End = m_Path.m_Str.StrCount();
	m_Path.m_Str.EraseStr(Start, End);
}


void GameDirectory::MoveParent(const GameString& _Folder)
{
	while (true)
	{
		GameString Folder = FolderName();

		size_t S1 = Folder.StrCount();
		size_t S2 = _Folder.StrCount();

		if (Folder != _Folder)
		{
			MoveParent();
		}
		else
		{
			break;
		}
	}
}

GameString GameDirectory::FolderName()
{
	return IOName();
}

//void GameDirectory::Move(const GameString& _Folder)
//{
//	GameString Path = m_Path.m_Str;
//
//	Path += L"\\" + _Folder;
//
//	if (false == GamePath::IsExistence(Path))
//	{
//		assert(false);
//	}
//
//	m_Path.m_Str = Path;
//}


void GameDirectory::Move(const GameString& _Folder, bool _wantnewfolder)
{
	GameString Path = m_Path.m_Str;

	Path += L"\\" + _Folder;

	// �� ��ΰ� ���� �����ϴ� ������� Ȯ���غ��� �Ѵ�.
	if (false == GamePath::IsExistence(Path))
	{
		if (_wantnewfolder == false)
		{
			assert(false);
			return;
		}
		else
		{
			int nResult = _wmkdir(Path);

			if (nResult == 0)
			{
				printf("���� ���� ����");
			}
			else if (nResult == -1)
			{
				perror("���� ���� ���� - ������ �̹� �ְų� ����Ȯ��\n");
				printf("errorno : %d", errno);
			}
		}


	}

	m_Path.m_Str = Path;
}


#pragma region �ؼ�
/*
	C://*.*
	C:// ����̺��� * ��� ���ϸ� . * ��� Ȯ���ڸ� ã�ƶ�.
*/
#pragma endregion


std::list<GameFile> GameDirectory::DirAllFile(const wchar_t* _Ext, const wchar_t* _Name)
{
	std::list<GameFile> AllFileList;
	int checkDirFile = 0;
	GameString dirPath;
	GameString Ext = _Ext;
	GameString Name = _Name;

	if (Name != L"")
	{
		dirPath = m_Path.m_Str + L"\\" + Name + L"*";
	}
	else
	{
		dirPath = m_Path.m_Str + L"\\*";
	}

	if (Ext != L"")
	{
		dirPath += L"." + Ext;
	}
	else
	{
		dirPath += L".*";
	}

	_wfinddata64i32_t fd; // ���丮 �� ���� �� ���� ���� ���� ��ü
	intptr_t handle;

#pragma region ���ϵ� �ڵ��̴�
	if ((handle = _wfindfirst(dirPath, &fd)) == -1L) // ������ ���� ã�� //fd ����ü �ʱ�ȭ.
	{
		return AllFileList;
	}
#pragma endregion

	do
	{
		if (fd.attrib & _A_SUBDIR)
		{
			// ���丮
			checkDirFile = 0;
		}
		else
		{
			// ����
			checkDirFile = 1;
		}

#pragma region this Case Directory ����� ȣ��
		/*
			if (checkDirFile == 0 && fd.name[0] != '.')
			{
				cout << "Dir  : " << path << "\\" << fd.name << endl;
				searchingDir(path + "\\" + fd.name);
			}
		*/
#pragma endregion

		if (fd.name[0] == L'.')
		{
			continue;
		}

		if (checkDirFile == 1)
		{
			GameString FilePath = m_Path.m_Str + L"\\" + fd.name;

			GameFile NewFile = GameFile(FilePath);

			AllFileList.push_back(NewFile);
		}


	} while (_wfindnext(handle, &fd) == 0); // ������ ���� : return -1 

	_findclose(handle);

	return AllFileList;
}

/////////////////////////////////////////////////////////// FILE
GameString GameFile::Ext() const
{
	size_t Start = m_Path.m_Str.FindLast(L".");
	size_t End = m_Path.m_Str.StrCount();
	return m_Path.m_Str.RangeToStr(Start, End);
}


/////////// �߰��߽��ϴ�. 
bool GameDirectory::IsFileExist(const GameString& _FileName)
{
	return GamePath::IsExistence(CombineFileName(_FileName));
}



std::list<GameFile> GameDirectory::DirAllDic(const wchar_t* _Ext, const wchar_t* _Name)
{
	std::list<GameFile> AllFileList;

	int checkDirFile = 0;
	// + L"\\*.*" ���� ��ȣ��?
	// C://*.*
	// C:// ����̺��� * ��� ���ϸ� . * ��� Ȯ���ڸ� ã�ƶ�.
	GameString dirPath;
	GameString Ext = _Ext;
	GameString Name = _Name;

	// 
	if (Name != L"")
	{
		// c:\\AAA*
		// �̸��� ������ ��ο� �̸��� �߰��ϰ� * 
		dirPath = m_Path.m_Str + L"\\" + Name + L"*";
	}
	else
	{
		// �̸��� ������ ��ο� �׳� *
		dirPath = m_Path.m_Str + L"\\*";
	}

	if (Ext != L"")
	{
		// Ȯ����� ������ .�� Ȯ��� �߰� 
		dirPath += L"." + Ext;
	}
	else
	{
		// Ȯ����� ������ .�� *�� �߰� 
		dirPath += L".*";
	}

	_wfinddata64i32_t fd;//���丮 �� ���� �� ���� ���� ���� ��ü
	intptr_t handle;

	// ������ ������ ã�´�.
	// ���ϵ� �ڵ��̴�.

	if ((handle = _wfindfirst(dirPath, &fd)) == -1L) //fd ����ü �ʱ�ȭ.
	{
		return AllFileList;
	}

	do //���� Ž�� �ݺ� ����
	{
		// ��༮�̸� 
		if (fd.attrib & _A_SUBDIR)
		{
			// ���丮��
			checkDirFile = 0;
		}
		else
		{
			// �����̴�.
			checkDirFile = 1;
		}

		// ���� ���丮�� ��찡 �ʿ� ����.
		if (checkDirFile == 0 && fd.name[0] != '.') {
			// cout << "Dir  : " << path << "\\" << fd.name << endl;
			// searchingDir(path + "\\" + fd.name);//����� ȣ��
			int a = 0;
		}
		// 1�� �����϶��� 

		if (fd.name[0] == L'.')
		{
			int b = 0;
			continue;
		}



		if (checkDirFile == 0)
		{
			GameString FilePath = m_Path.m_Str + L"\\" + fd.name;

			if (std::string::npos != FilePath.Find(L"."))
			{
				continue;
			}

			GameFile NewFile = GameFile(FilePath);

			AllFileList.push_back(NewFile);
		}

		// ���� ������ ������ -1�ΰ��� ������ ���̴�.
	} while (_wfindnext(handle, &fd) == 0);

	_findclose(handle);


	return AllFileList;
}
