#pragma once
#include <GameObjTFuncMgr.h>
#include <GameObjListTFuncMgr.h>
#include <GameActor.h>
class CutScene : public GameObjTFuncMgr<CutScene>, public GameObjListTFuncMgr<GameActor>
{
public:
	template<typename T>
	static CPtr<T> Create(const GameString& _Name)
	{
		return CreateAndInsertToChild<T>(_Name); // �ڽĿ� �߰�
	}

	static CPtr<CutScene> CurCutScene; // ���� �������� �ƾ� 

public:
	static void StartCutScene(const GameString& _Name)
	{
		if (nullptr != CurCutScene)
		{
			return;
		}

		CPtr<CutScene> FindScene = Find(_Name);

		if (nullptr == FindScene)
		{
			MSG_ASSERT_CODE(L"�������� �ʴ� �ƾ����� �ٲٷ��� �߽��ϴ�.");
		}

		CurCutScene = FindScene;

		if (true == CurCutScene->m_IsEnd)
		{
			return;
		}

		CurCutScene->CutSceneInit();
	}

	static bool IsEnd(const GameString& _Name)
	{
		CPtr<CutScene> PTR = Find(_Name);

		return PTR->m_IsEnd;
	}

	static bool IsCutScene()
	{
		if (nullptr != CurCutScene)
		{
			return true;
		}

		return false;
	}

	static void Update()
	{
		if (nullptr == CurCutScene)
		{
			return;
		}

		if (true == CurCutScene->m_IsEnd)
		{
			CurCutScene = nullptr;
		}

		if (nullptr != CurCutScene)
		{
			CurCutScene->CutSceneUpdate();
		}
	}

private:
	bool m_IsEnd;

protected:
	void End()
	{
		m_IsEnd = true;
	}

protected:
	virtual void CutSceneInit() = 0;
	virtual void CutSceneUpdate() = 0;

public:
	CutScene();
	~CutScene() {}
};