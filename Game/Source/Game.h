#pragma once
class GameObject;

class Game: public fw::GameCore
{
public:
	Game();
	void Init();
	void Human();
	void Animal();
	virtual void Update() override;
	virtual void Draw() override;
	virtual ~Game();


protected:
	fw::ShaderProgram* m_pShader;
	fw::Mesh* m_pMesh; 
	std::vector<GameObject> objects;
};
