#include "GameComponent.h"
#include "GameTransform.h"
#include "GameActor.h"

CPtr<GameScene> SceneComponent::GetScene()
{
	return m_Scene;
}

CPtr<GameActor> ActorComponent::GetActor()
{
	return m_Actor;
}

CPtr<GameScene> ActorComponent::GetScene()
{
	return m_Actor->GetScene();
}

CPtr<GameTransform> ActorComponent::GetTrans()
{
	return m_Actor->GetTrans();
}

bool ActorComponent::IsUpdateObj()
{
	return true == GameVirtualProgress::IsUpdateObj() && true == m_Actor->IsUpdateObj();
}

bool ActorComponent::IsDeathObj()
{
	return true == GameVirtualProgress::IsDeathObj() || true == m_Actor->IsDeathObj();
}
