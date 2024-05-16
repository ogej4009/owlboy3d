#pragma once
#include <list>
#include <map>
#include <vector>
#include <set>
#include <GameString.h>
#include <GameObjTFuncMgr.h>
#include <GameObjListTFuncMgr.h>
#include "GameVirtualProgress.h"

//////////////////////// �߰��߽��ϴ�. 
#include "GameComponent.h"
#include "GameRenderingData.h"
/*
	template<typename T>
	class _CGameObjMgr
	{
	protected:
		// ���� : �Ҹ��ϸ鼭 �Ҹ��� ȣ��
		std::list<CPtr<T>>	m_ObjList;
	};
*/

#pragma region �������Ģ
/*
	������ ���ư��� ���߿��� ���� ������ �ʴ´�.
	���� ��ȭ�� ��� ������ ������ ��, �Ͼ��. �ݴ뵵 ��������
	���� �ٲ�� ���� > ������Ʈ�� ����� �Ѵ� > ������Ʈ�� ����� �Ѵ�.
	���߿� ��ȭ�� �ݵ�� �־�� �ϴ� ���̽��� ���ַ̼��̼��� �ɼ��ְ� ������ �����ؾ� �Ѵ�.
	������ ���� �Ǵ� ����̴�. ������Ʈ,�浹,������ ����� ������ ������ �����Ѵ�.
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


	// ù���� > init() ����
	static CPtr<GameScene> Create(const GameString& _Name)
	{
		CPtr<GameScene> Res = CreateAndInsert(_Name);
		return Res;
	}

	// ù���� > ������Ʈ ����
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


#pragma region ������ڵ�
	/*
		���� null�� �ǰ� ���� �ʱ� ����, ���� ���� �����ϰ� init�Ѵ�.
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

	// �浹
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

#pragma region �ڷᱸ��insert����
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
			MSG_ASSERT_CODE(L"���� �׷�� �ι� �浹�Ϸ��� �߽��ϴ�.");
		}
		_Value.insert(_PushIndex);
		ColLinkPush(_Value, _ARG ...);
	}

	void ColLinkPush(std::set<int>& _Value, int _PushIndex)
	{
		if (_Value.end() != _Value.find(_PushIndex))
		{
			MSG_ASSERT_CODE(L"���� �׷�� �ι� �浹�Ϸ��� �߽��ϴ�.");
		}

		_Value.insert(_PushIndex);
	}

public:
	GameScene();
	~GameScene();
};

//#pragma region �������ӿ�ũ�Ǵ���
//	/*
//		[���]
//		~~~.h���� �Ϻκ��̶� Actor�� ���θ� �˾ƾ� �ϴ� �����̴�.  
//		�׷��ٺ��� ��������� ��ȯ������ ������ �ִ�.
//
//		[����]
//		- ����Ʈ������,�Ҹ��ڰ���
//		~GameScene();
//		{
//			��Ӱ��迡���� ���������� �����Ǿ��ִ� ��
//			�ڵ����� �ȿ� ���� ��Ӱ��迡 ���� ����ȴ�.
//			PTR.~CPtr()
//			GameObjTFuncMgr�� �����ް� ��ü��
//			CRef�� ���� ��� �� �ΰ��� �Լ��� ������. AddRefCount(), DecRefCount()
//		}
//
//		�̻�Ȳ�� �����Ϸ��� _ljGameScene���� ��ӵ� �ڿ����� �ƴ��� �����.
//		�׷��� ���漱�����δ� �Լ����� ��Ʈ�� �Ҽ�����. ���漱�����δ� �����ͷ� ��(����)�� �޴� �͸� �����ϴ�. 
//		���� ~~~.h �������� ��Ӱ��踦 �˾ƾ� �Ѵ�. (�Լ��� ����ϱ� ����)����� �־�� �Ѵ�. ����� ���δ�. 
//		�׷��� ���� �ڿ����� ������ ����� ��ĥ �� �ִ�. 
//
//	*/
//#pragma endregion

