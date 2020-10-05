#pragma once
<<<<<<< HEAD
class Player;

=======
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
class Game: public fw::GameCore
{
public:
	Game(fw::FWCore* pFramework);
	void Init();
	void Human();
	void Animal();
<<<<<<< HEAD
	void SetVec2(float x, float y);
=======
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual ~Game();
	

protected:
	fw::ImGuiManager* uiManager=nullptr;
	fw::ShaderProgram* m_pShader= nullptr;
	fw::Mesh* m_pMesh= nullptr;

	std::vector< fw::GameObject*> objects;
<<<<<<< HEAD
	Player* player;
	vec2 pos;
=======
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
};
