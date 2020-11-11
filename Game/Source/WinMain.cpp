#include<GamePCH.h>
#include "Game.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	fw::GameState gameState;
	gameState = fw::GameState::Paused;

	fw::FWCore* pFramework = new fw::FWCore();
	pFramework->Init(600, 600);

	Game* pGame;
	pGame = new Game(pFramework, gameState);
	pGame->Init();

	pFramework->Run(pGame);
	pFramework->Shutdown();
	
	delete pGame;
	delete pFramework;
}