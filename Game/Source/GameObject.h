#pragma once
#include"Framework.h"
class GameObject
{
public:
	GameObject();
	~GameObject();

	void Draw();
	void Update();
	void SetMesh(fw::Mesh* aMesh);
	void SetShader(fw::ShaderProgram* aShader);
private:
	float x, y;
	fw::Mesh* mesh;
	fw::ShaderProgram* shader;
};