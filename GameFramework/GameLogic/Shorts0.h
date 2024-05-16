#pragma once
#include "CutScene.h"

enum class SHORTS0_STATE
{
	EVENT0,
	EVENT1,
	EVENT2,
	MAX,
};

class Shorts0 : public CutScene
{
	SHORTS0_STATE	m_State;

public:
	void EVENT0();
	void EVENT1();
	void EVENT2();

public:
	void CutSceneInit() override;
	void CutSceneUpdate() override;

public:
	Shorts0();
	~Shorts0();
};

