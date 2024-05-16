#pragma once
#include <CPtr.h>
#include <GameMath.h>
#include <list>
#include "GameVirtualProgress.h"
#include "GameScene.h"
#include "GameActor.h"

class GameComponent : public CRef, public GameVirtualProgress
{
#pragma region ������Ʈ 
	/*
		Actor�� �̸��� �ο��� �� �ִ� ���� ���� ��� �ڿ���
		component�� �� Actor�� �̸��� �߰��Ǵ� ��� ����, ��
	*/
#pragma endregion
};

class GameScene;
class SceneComponent : public GameComponent
{
	friend GameScene;

#pragma region ħ��
	/*
		Actor�� Scene�� ��� ������� ��ġ�� ���Ѵ�.
		���� friend�� _ljGameScene�� �����ϴ�.
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

#pragma region ħ��
	/*
		������ Actor�� ��� ������� ��ġ�� ���Ѵ�.
		���� friend�� _ljGameActor�� �����ϴ�.
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