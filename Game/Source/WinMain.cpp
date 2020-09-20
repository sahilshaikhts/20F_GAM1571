#include<Framework.h>
#include "Game.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	fw::FWCore* pFramework = new fw::FWCore();
	
	Game* pGame = new Game();

	pFramework->Init(600, 600);
	pFramework->Run(pGame);
	
	pFramework->Shutdown();
	delete pGame;
	delete pFramework;
}