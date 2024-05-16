#pragma once
#include "GameUnity.h"
class ItemSlot : public ActorComponent
{

public:
	void Init() override;
	void Update() override;

public:
	ItemSlot();
	~ItemSlot();
};

