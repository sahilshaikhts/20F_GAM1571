#include "FrameworkPCH.h"
#include"Core/FWCore.h"
#include "GameCore.h"

namespace fw {

GameCore::GameCore(FWCore* pFramework)
{
    m_pFramework = pFramework;
}
void GameCore::ShutDownGame()
{
	m_pFramework->Shutdown();
}
GameCore::~GameCore()
{
}

} // namespace fw

