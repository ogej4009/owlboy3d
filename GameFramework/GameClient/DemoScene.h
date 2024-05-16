#pragma once
#include <GameUnity.h>
class DemoScene : public SceneComponent
{

	CPtr<GameSpriteRenderer> m_Debug;

public:
	// Parallax
	// Layer

public:
	void Init() override;
	void Update() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
	void SceneDebugDisplay();
	void SceneValueDataInit();

public:
	DemoScene();
	~DemoScene();
};