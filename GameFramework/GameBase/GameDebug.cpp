#include "GameDebug.h"

GameDebug::GameDebugStarter	GameDebug::Starter = GameDebug::GameDebugStarter();
bool GameDebug::IsLeckCheck = false;
FILE* GameDebug::stream;
int GameDebug::m_FrameCount = 0;
bool GameDebug::bConsole = false;