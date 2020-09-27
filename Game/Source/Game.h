#pragma once
class Game: public fw::GameCore
{
public:
	Game(fw::FWCore* pFramework);
	void Init();
	void Human();
	void Animal();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual ~Game();
	

protected:
	fw::ImGuiManager* uiManager=nullptr;
	fw::ShaderProgram* m_pShader= nullptr;
	fw::Mesh* m_pMesh= nullptr;

	std::vector< fw::GameObject*> objects;
};
