#pragma once
#include "GameUnity.h"
enum class BORDERSTATE
{
	B_IN,
	B_OUT,
	MAX,
};

class BorderTrigger : public ActorComponent
{
	CPtr<GameSpriteRenderer> m_Render;
	BORDERSTATE m_State;

public:
	void Move(const CVector& _Dir, float _Speed);

public:
	void Init() override;
	void Update() override;

public:
	BorderTrigger();
	~BorderTrigger();
};

