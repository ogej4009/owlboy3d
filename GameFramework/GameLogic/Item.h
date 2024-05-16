#pragma once
#include "GameUnity.h"
class Item : public ActorComponent
{
public:
	void Init() override;
	void Update() override;

public:
	Item();
	//Item();
	~Item();
};

