#include<Framework.h>
#include "Game.h"

Game::~Game()
{
}

void Game::Update()
{
}

void Game::Draw()
{
	glClearColor(0.6f,0.96f,0.26f,1);
	glClear(GL_COLOR_BUFFER_BIT);
}
