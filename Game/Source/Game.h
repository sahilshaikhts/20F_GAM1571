#pragma once
class Player;
class PlayerController;
class Game: public fw::GameCore
{

public:
	
	Game(fw::FWCore* pFramework, fw::GameState& aGameState);
	virtual ~Game();

	void Init();
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void OnEvent(fw::Event* pEvent) override;

	void GameStart();

	void GamePlaying();

	void GamePaused();
	void GameResume();

	void GameRestart();

	void GameEnd();
	
	void DebugUI();
	void Human();
	void GeneratePlayer();
	void SpawnEnemy();
	
	bool vSync;


protected:
	//arena
	vec2 arenaCenter;
	float arenaRadius;

	fw::GameState& gameState;
	fw::ImGuiManager* uiManager=nullptr;
	fw::ShaderProgram* m_pShader= nullptr;
	fw::Mesh* m_pMesh = nullptr;
	fw::Mesh* mesh_enemy = nullptr;
	PlayerController* m_controller;

	std::vector< fw::GameObject*> objects;
	fw::GameObject* arena;
	Player* player;

	vec2 pos;

private:
	float timer,spawnInterval, lastSpawnTime;
};
