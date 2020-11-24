#pragma once
class Player;
class PlayerController;
class Game: public fw::GameCore
{

public:
	
	Game(fw::FWCore* pFramework);
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

	void GameEnd(fw::GameState endState);
	
	void DebugUI();

	bool vSync;


protected:
	std::vector< fw::GameObject*> objects;
	std::map<std::string, fw::ShaderProgram*>m_shaders;

	fw::GameState gameState;
	fw::ImGuiManager* uiManager=nullptr;
	PlayerController* m_controller;

	Player* player;
	fw::Mesh* mesh_player;
	fw::Texture* texture_player;

private:
	float timer;
};
