#pragma once
#include <CPtr.h>
#include <GameMath.h>
#include <list>
#include "GameVirtualProgress.h"
#include "GameScene.h"
#include "GameActor.h"

class GameComponent : public CRef, public GameVirtualProgress
{
#pragma region 컴포넌트 
	/*
		Actor는 이름을 부여할 수 있는 게임 내의 모든 자원들
		component는 그 Actor의 이름에 추가되는 모든 정보, 명세
	*/
#pragma endregion
};

class GameScene;
class SceneComponent : public GameComponent
{
	friend GameScene;

#pragma region 침범
	/*
		Actor가 Scene에 어떠한 영향력을 끼치지 못한다.
		오직 friend한 _ljGameScene만 가능하다.
	*/
#pragma endregion

private:
	GameScene* m_Scene;

public:
	CPtr<GameScene> GetScene();

private:
	void Scene(GameScene* _Ptr)
	{
		m_Scene = _Ptr;
	}

};


class GameTransform;
class GameActor;
class ActorComponent : public GameComponent
{
private:
	friend GameActor;

#pragma region 침범
	/*
		누구도 Actor에 어떠한 영향력을 끼치지 못한다.
		오직 friend한 _ljGameActor만 가능하다.
	*/
#pragma endregion

private:
	GameActor* m_Actor;

public:
	CPtr<GameActor> GetActor();
	CPtr<GameScene> GetScene();
	CPtr<GameTransform> GetTrans();

public:
	bool IsUpdateObj() override;
	bool IsDeathObj() override;

private:
	void Actor(GameActor* _PTR)
	{
		m_Actor = _PTR;
	}

};