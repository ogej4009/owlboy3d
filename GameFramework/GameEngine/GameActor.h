#pragma once
#include <GameObjListTFuncMgr.h>
#include "GameVirtualProgress.h"



#pragma region 오브젝트-ACTOR 개념화 
/*
	이름을 부여하는 할 수 있는 모든 것을 Actor==Object라고 명한다.
	그리고 그것에 부여하는 기능들을 Component라고 명한다.
	오브젝트는 모두 평등한 관점으로 본다.
	기능의 차이로 다름을 분별한다.
	Actor를 만들때 위치를 부여한다.
	Component는 이름에 부여하는 모든 것이다. 위치도 Component 이다.
*/
#pragma endregion

class GameTransform;
class ActorComponent;
class GameScene;
class GameActor : public CRef, public GameVirtualProgress, public GameObjListTFuncMgrProgress<ActorComponent> // 여기에 관리 기능이 다 있다. 
{
public:
	template<typename _TYPE>
	friend class GameObjListTFuncMgrProgress;
	friend GameScene;
	friend GameTransform;

#pragma region HAS_A 관계
	/*
		private:
		HAS A 관계
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

#pragma region 컴포넌트 생성함수 
	/*
		생성한 Component에 매칭된 Actor를 현재의 Actor임을 결정하고,
		그 Component가 시작될때 반드시 Init()함수를 실행할 수 있도록 한다.
	*/
#pragma endregion

#pragma region 템플릿 가변인자 사용이유 
	/*
		프레임애니메이션은 하나의 스프라이트 랜더러만 애니메이션이 가능하다.
		상,하체 스프라이트를 분리하고, 구현하기 위해 만들었다.
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

	// Actor와 트랜스폼, 씬은 반드시 고려해야 하는 것 
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

