#include "GameTransform.h"
#include "GameActor.h"
#include "GameScene.h"
#include <GameDebug.h>


bool GameTransform::SPHERE2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->SPHERE2D().Intersects(_Right->OBB2D());
}

bool GameTransform::SPHERE2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->SPHERE2D().Intersects(_Right->AABB2D());
}

bool GameTransform::SPHERE2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->SPHERE2D().Intersects(_Right->SPHERE2D());
}

bool GameTransform::AABB2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->AABB2D().Intersects(_Right->OBB2D());
}

bool GameTransform::AABB2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->AABB2D().Intersects(_Right->AABB2D());
}

bool GameTransform::AABB2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->AABB2D().Intersects(_Right->SPHERE2D());
}

bool GameTransform::OBB2DCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->OBB2D().Intersects(_Right->OBB2D());
}

bool GameTransform::OBB2DCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->OBB2D().Intersects(_Right->AABB2D());
}

bool GameTransform::OBB2DCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return _Left->OBB2D().Intersects(_Right->SPHERE2D());
}






bool __stdcall GameTransform::SPHERE2DCOLRAY(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	float Dis;

	_Left->RAY3D().Intersects(_Right->SPHERE2D(), Dis);

	if (0 != Dis)
	{
		return true;
	}

	return false;
}


bool __stdcall GameTransform::AABB2DCOLRAY(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	float Dis;

	_Left->RAY3D().Intersects(_Right->AABB2D(), Dis);

	if (0 != Dis)
	{
		return true;
	}

	return false;
}


bool __stdcall GameTransform::OBB2DCOLRAY(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	float Dis;

	_Left->RAY3D().Intersects(_Right->SPHERE2D(), Dis);

	if (0 != Dis)
	{
		return true;
	}

	return false;
}

bool __stdcall GameTransform::RAYCOLSPHERE2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	float Dis;

	_Left->RAY3D().Intersects(_Right->SPHERE2D(), Dis);

	if (0 != Dis)
	{
		return true;
	}

	return false;
}

bool __stdcall GameTransform::RAYCOLAABB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	float Dis;

	_Left->RAY3D().Intersects(_Right->AABB2D(), Dis);

	if (0 != Dis)
	{
		return true;
	}

	return false;
}

bool __stdcall GameTransform::RAYCOLOBB2D(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return false;
	// return _Left->RAY3D().Intersects(_Right->OBB2D());
}

bool __stdcall GameTransform::RAYCOLRAY(CPtr<GameTransform> _Left, CPtr<GameTransform> _Right)
{
	return false;
}

