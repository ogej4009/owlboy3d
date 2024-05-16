#pragma once
#include <GameObjListTFuncMgr.h>
#include "GameVirtualProgress.h"



#pragma region ������Ʈ-ACTOR ����ȭ 
/*
	�̸��� �ο��ϴ� �� �� �ִ� ��� ���� Actor==Object��� ���Ѵ�.
	�׸��� �װͿ� �ο��ϴ� ��ɵ��� Component��� ���Ѵ�.
	������Ʈ�� ��� ����� �������� ����.
	����� ���̷� �ٸ��� �к��Ѵ�.
	Actor�� ���鶧 ��ġ�� �ο��Ѵ�.
	Component�� �̸��� �ο��ϴ� ��� ���̴�. ��ġ�� Component �̴�.
*/
#pragma endregion

class GameTransform;
class ActorComponent;
class GameScene;
class GameActor : public CRef, public GameVirtualProgress, public GameObjListTFuncMgrProgress<ActorComponent> // ���⿡ ���� ����� �� �ִ�. 
{
public:
	template<typename _TYPE>
	friend class GameObjListTFuncMgrProgress;
	friend GameScene;
	friend GameTransform;

#pragma region HAS_A ����
	/*
		private:
		HAS A ����
		std::list<CPtr<GameComponent>>		m_ComList;
	*/
#pragma endregion

public:
	template<typename COMTYPE, typename ...REST>
	CPtr<COMTYPE> CreateComByName(const GameString& _Name = L"", REST ... _ARG)
	{
		CPtr<COMTYPE> NewCom = GameObjListTFuncMgr<ActorComponent>::CreateObj<COMTYPE>(_Name);
		NewCom->Actor(this);
		NewCom->Init(_ARG...);
		return NewCom;
	}

#pragma region ������Ʈ �����Լ� 
	/*
		������ Component�� ��Ī�� Actor�� ������ Actor���� �����ϰ�,
		�� Component�� ���۵ɶ� �ݵ�� Init()�Լ��� ������ �� �ֵ��� �Ѵ�.
	*/
#pragma endregion

#pragma region ���ø� �������� ������� 
	/*
		�����Ӿִϸ��̼��� �ϳ��� ��������Ʈ �������� �ִϸ��̼��� �����ϴ�.
		��,��ü ��������Ʈ�� �и��ϰ�, �����ϱ� ���� �������.
	*/
#pragma endregion
	template<typename COMTYPE, typename ...REST>
	CPtr<COMTYPE> CreateCom(REST ... _ARG)
	{
		CPtr<COMTYPE> NewCom = GameObjListTFuncMgr<ActorComponent>::CreateObj<COMTYPE>();
		NewCom->Actor(this);
		NewCom->Init(_ARG...);
		return NewCom;
	}

	// Actor�� Ʈ������, ���� �ݵ�� ����ؾ� �ϴ� �� 
private:
	GameScene* m_Scene;
	GameTransform* m_Trans;

public:
	GameTransform* GetTrans();
	GameScene* GetScene();

public:
	template<typename FINDTYPE>
	FINDTYPE* FindComName(std::wstring _Name)
	{
		return FindObjName<FINDTYPE>(_Name);
	}

	template<typename FINDTYPE>
	CPtr<FINDTYPE> FindComType()
	{
		return FindObjType<FINDTYPE>();
	}

	template<typename FINDTYPE>
	std::list<CPtr<FINDTYPE>> FindComTypeAll()
	{
		return FindObjTypeAll<FINDTYPE>();
	}

private:
	void UpdatePrev() 		override;
	void Update() 			override;
	void UpdateNext() 		override;
	void RenderPrev() 		override;
	void RenderNext() 		override;
	void CollisionPrev()	override;
	void CollisionNext()	override;
	void SceneChangeEnd() 	override;
	void SceneChangeStart() override;
	void Release()			override;

public:
	GameActor();
	~GameActor();

};

