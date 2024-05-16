#pragma once
#include "GameUnity.h"
#include <SaveData.h>

class FreeCam;
class LevelDesignView : public SceneComponent // MapToolEditor
{
	friend class Dlg0;
	friend class Dlg1;
	friend class Dlg2;
	friend class Dlg3;
	friend class Dlg4;

	static LevelDesignView* MainView;

public:
	static LevelDesignView* GetMainView()
	{
		return MainView;
	}

public:
	CPtr<GameActor> m_FreeCamActor;
	CPtr<FreeCam>	m_FreeCamCom;

public:
	void Progress();

public:
	void Init() override;
	void Update() override;
	void SceneChangeStart() override;
	void SceneChangeEnd() override;
	void SceneDebugDisplay();

public:
	void FileCreate();
	void FileDelete();

public:
	LevelDesignView();
	~LevelDesignView();
};
