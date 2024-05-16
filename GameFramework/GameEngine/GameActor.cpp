#include "GameActor.h"

GameTransform* GameActor::GetTrans()
{
	return m_Trans;
}

GameScene* GameActor::GetScene()
{
	return m_Scene;
}

void GameActor::UpdatePrev()
{
	GameObjListTFuncMgrProgress<ActorComponent>::UpdatePrev();
}

void GameActor::Update()
{
	GameObjListTFuncMgrProgress<ActorComponent>::Update();
}

void GameActor::UpdateNext()
{
	GameObjListTFuncMgrProgress<ActorComponent>::UpdateNext();
}

void GameActor::RenderPrev()
{
	GameObjListTFuncMgrProgress<ActorComponent>::RenderPrev();
}

void GameActor::RenderNext()
{
	GameObjListTFuncMgrProgress<ActorComponent>::RenderNext();
}

void GameActor::CollisionPrev()
{
	GameObjListTFuncMgrProgress<ActorComponent>::CollisionPrev();
}

void GameActor::CollisionNext()
{
	GameObjListTFuncMgrProgress<ActorComponent>::CollisionNext();
}

void GameActor::SceneChangeEnd()
{
	GameObjListTFuncMgrProgress<ActorComponent>::SceneChangeEnd();
}

void GameActor::SceneChangeStart()
{
	GameObjListTFuncMgrProgress<ActorComponent>::SceneChangeStart();
}

void GameActor::Release()
{
	GameObjListTFuncMgrProgress<ActorComponent>::Release();
}

GameActor::GameActor()
{
}

GameActor::~GameActor()
{
}
