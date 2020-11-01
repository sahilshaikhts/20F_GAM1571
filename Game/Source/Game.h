#pragma once
class Player;

class Game: public fw::GameCore
{
public:
	Game(fw::FWCore* pFramework);
	void Init();
	void Human();
	void Animal();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void OnEvent(fw::Event* pEvent) override;

	virtual ~Game();
	bool v;


protected:
	fw::ImGuiManager* uiManager=nullptr;
	fw::ShaderProgram* m_pShader= nullptr;
	fw::Mesh* m_pMesh= nullptr;
    fw::EventManager* m_pEventManager = nullptr;

	std::vector< fw::GameObject*> objects;
	vec2 pos;
};
