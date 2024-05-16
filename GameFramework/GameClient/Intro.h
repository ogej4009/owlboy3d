#pragma once
#include <GameUnity.h>
class Intro : public SceneComponent
{
public:
	void Init() override;
	void Update() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
	void SceneDebugDisplay();
	void SceneValueDataInit();

public:
	Intro();
	~Intro();
};

