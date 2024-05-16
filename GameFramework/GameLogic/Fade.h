#pragma once
#include "GameUnity.h"

enum class FADEIO
{
	FADEIN,
	FADEOUT,
	MAX,
};

class Fade : public ActorComponent
{
protected:
	FADEIO m_Mode;

protected:
	virtual void FadeIn() {}
	virtual void FadeOut() {}

public:
	Fade() {}
	virtual ~Fade() {}
};