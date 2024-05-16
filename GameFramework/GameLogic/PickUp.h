#pragma once
#include "Entity.h"

enum class PICKUPTARGET
{
	MECHANIC,
	PIRATE,
	SPIDER,
	FRUIT,
	JUG,
	RAINCLOUD,
	STEAMBOMB,
	WEIGHT,
	TORTOISEMASK,
	MAX,
};

class Hero;
class PickUp : public Entity
{
public:
	friend Hero;

protected:
	int	TargetIndex;
	float m_AimAngle;

public:
	static PickUp* m_PickUp;
	static CPtr<GameActor> ArrPickUpTarget[(UINT)PICKUPTARGET::MAX];

protected:
	PICKUPTARGET m_Target;
	GameString	PickUpTargetName[(UINT)PICKUPTARGET::MAX];

protected:
	virtual void CalAimAngle() {}

	virtual void Join(CPtr<GameTransform> _Parent);
	virtual void Withdraw();

	void AimDotInit() {}
	void AimDotUpdate() {}

public:
	PickUp();
	virtual ~PickUp() {}
};