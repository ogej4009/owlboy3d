#include "CutScene.h"
CPtr<CutScene> CutScene::CurCutScene = nullptr;

CutScene::CutScene() : m_IsEnd(false)
{
}