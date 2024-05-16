#pragma once
#include <list>
#include <map>
#include <vector>
#include <set>
#include <GameString.h>
#include <GameObjTFuncMgr.h>
#include <GameObjListTFuncMgr.h>
#include "GameVirtualProgress.h"

//////////////////////// 추가했습니다. 
#include "GameComponent.h"
#include "GameRenderingData.h"
/*
	template<typename T>
	class _CGameObjMgr
	{
	protected:
		// 값형 : 소멸하면서 소멸자 호출
		std::list<CPtr<T>>	m_ObjList;
	};
*/

#pragma region 씬설계원칙
/*
	루프가 돌아가는 도중에는 씬이 변하지 않는다.
	씬의 변화는 모든 루프가 끝났을 때, 일어난다. 반대도 마찬가지
	씬이 바뀌는 순간 > 오브젝트가 어떤일을 한다 > 컴포넌트가 어떤일을 한다.
	도중에 변화가 반드시 있어야 하는 케이스는 아이솔레이션이 될수있게 구조를 조정해야 한다.
	생각이 쉽게 되는 방식이다. 업데이트,충돌,랜더링 등등이 루프가 끝나고 조정한다.
*/
#pragma endregion

class GameLight;
class GameCamera;
class GameCol;
class GameTransform;
class GameRenderer;
class SceneComponent;
class GameActor;
class GameScene
	: public GameObjTFuncMgr<GameScene>
	, public GameVirtualProgress
	, GameObjListTFuncMgrProgress<GameActor>
	, GameObjListTFuncMgrProgress<SceneComponent>
{
public:
	static CPtr<GameScene> m_CurScene;
	static CPtr<GameScene> m_NextScene;
	static void Progress();

public:
	static CVector HeroPos;
	static CPtr<GameActor> HeroActor;


	// 첫생성 > init() 안함
	static CPtr<GameScene> Create(const GameString& _Name)
	{
		CPtr<GameScene> Res = CreateAndInsert(_Name);
		return Res;
	}

	// 첫생성 > 컴포넌트 생성
	template<typename FIRSTCOM>
	static CPtr<GameScene> Create(const GameString& _Name)
	{
		CPtr<GameScene> Res = CreateAndInsert(_Name);
		Res->CreateCom<FIRSTCOM>();
		return Res;
	}

	static void ChangeScene(const GameString& _Name);

public:
	CPtr<GameActor> CreateActor(const GameString& _Name = L"");


#pragma region 방어적코드
	/*
		씬이 null이 되게 하지 않기 위해, 씬을 먼저 세팅하고 init한다.
		NewCom->Scene(this);
		NewCom->Init();
	*/
#pragma endregion

	template<typename COMTYPE>
	CPtr<COMTYPE> CreateCom(const GameString& _Name = L"")
	{
		CPtr<COMTYPE> NewCom = GameObjListTFuncMgr<SceneComponent>::CreateObj<COMTYPE>(_Name);
		NewCom->Scene(this);
		NewCom->Init();
		return NewCom;
	}

	template<typename COMTYPE>
	CPtr<COMTYPE> FindCom(const GameString& _Name = L"")
	{
		return GameObjListTFuncMgr<SceneComponent>::FindObjType<COMTYPE>();
	}


public:
	void UpdatePrev() 		override;
	void Update() 			override;
	void UpdateNext() 		override;
	void RenderPrev() 		override;
	void Render();
	void RenderNext() 		override;
	void CollisionPrev()	override;
	void Collision();
	void CollisionNext()	override;
	void SceneChangeEnd() 	override;
	void SceneChangeStart() override;
	void Release()			override;
	//void ActorClear();

private:
	friend GameTransform;

	std::list<CPtr<GameTransform>> m_AllTrans;

private:
	friend GameCamera;
	friend GameRenderer;
	friend GameLight;
	CPtr<GameCamera> m_MainCam;

	std::map<int, CPtr<GameCamera>> m_AllCam;
	std::map<int, std::list<CPtr<GameRenderer>>> m_AllRender;

	std::map<int, std::vector<CPtr<GameLight>>> m_AllLight;
	std::map<int, ObjectLightData> m_AllLightData;

	void PushCam(CPtr<GameCamera> _Cam);
	void PushRender(CPtr<GameRenderer> _Render);
	void PushLight(CPtr<GameLight> _Light);
	void PushCol(CPtr<GameCol> _Col);
	void LightCheck();
	static bool ZSort(CPtr<GameRenderer>& _Left, CPtr<GameRenderer>& _Right);

public:
	CPtr<GameCamera> MainCam();
	void CreateRenderGroupLight(int _Index);
	ObjectLightData* GetLightData(int _Index);

private:
	friend GameCol;

	// 충돌
	std::map<int, std::set<int>> m_ColLink;
	std::map<int, std::list<CPtr<GameCol>>> m_AllCol;

public:
	void RayColLink()
	{
		ColLink(6, 1, 0);
	}

public:
	template<typename ... REST>
	void ColLink(int _Order, REST ... _ARG)
	{
		if (m_ColLink.end() == m_ColLink.find(_Order))
		{
			m_ColLink[_Order];
		}
		ColLinkPush(m_ColLink[_Order], _ARG ...);
	}

#pragma region 자료구조insert망식
	/*
		m_ColIndex.insert(std::map<int, std::set<int>>::value_type(_Order, std::set<int>()));
		m_ColIndex.insert(std::make_pair(_Order, std::set<int>()));
		m_ColIndex[_Order] = std::set<int>();
	*/
#pragma endregion


	template<typename ... REST>
	void ColLinkPush(std::set<int>& _Value, int _PushIndex, REST ... _ARG)
	{
		if (_Value.end() != _Value.find(_PushIndex))
		{
			MSG_ASSERT_CODE(L"같은 그룹과 두번 충돌하려고 했습니다.");
		}
		_Value.insert(_PushIndex);
		ColLinkPush(_Value, _ARG ...);
	}

	void ColLinkPush(std::set<int>& _Value, int _PushIndex)
	{
		if (_Value.end() != _Value.find(_PushIndex))
		{
			MSG_ASSERT_CODE(L"같은 그룹과 두번 충돌하려고 했습니다.");
		}

		_Value.insert(_PushIndex);
	}

public:
	GameScene();
	~GameScene();
};

//#pragma region ★프레임워크의단점
//	/*
//		[결론]
//		~~~.h에서 일부분이라도 Actor의 내부를 알아야 하는 구조이다.  
//		그렇다보니 결과적으로 순환참조의 위험이 있다.
//
//		[원인]
//		- 디폴트생성자,소멸자개념
//		~GameScene();
//		{
//			상속관계에의해 내부적으로 생략되어있는 것
//			자동으로 안에 먼저 상속관계에 의해 실행된다.
//			PTR.~CPtr()
//			GameObjTFuncMgr로 관리받고 개체는
//			CRef에 의해 모두 이 두개의 함수를 가진다. AddRefCount(), DecRefCount()
//		}
//
//		이상황에 컴파일러는 _ljGameScene에게 상속된 자원들을 아는지 물어본다.
//		그러나 전방선언으로는 함수들을 컨트롤 할수없다. 전방선언으로는 포인터로 값(값형)을 받는 것만 가능하다. 
//		따라서 ~~~.h 차원에서 상속관계를 알아야 한다. (함수를 사용하기 위해)헤더가 있어야 한다. 헤더가 쌓인다. 
//		그래서 가진 자원들의 순서와 사용이 겹칠 수 있다. 
//
//	*/
//#pragma endregion

