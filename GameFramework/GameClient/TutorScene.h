#pragma once
#include <GameUnity.h>
class TutorScene : public SceneComponent
{
	float m_FpsResult;
	float m_FpsTime;
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
	TutorScene();
	~TutorScene();
};

