#pragma once
#include "GameUnity.h"

enum class DIR_STATE
{
	DIRU,
	DIRD,
	DIRL,
	DIRR,
	DIRMAX,
};

enum class DIR_STATE_PLUS
{
	DIRU,
	DIRD,
	DIRL,
	DIRR,
	DIRUR,
	DIRUL,
	DIRDR,
	DIRDL,
	DIRMAX,
};

class Entity : public ActorComponent
{
public:
	Entity() {}
	~Entity() {}
};