#include"FrameworkPCH.h"
#include "GameObject.h"

#include "Mesh.h"

namespace fw {
	GameObject::GameObject()
	{
		position.x = 0;
		position.y = 0;

	}

	GameObject::~GameObject()
	{

	}

	void GameObject::Draw()
	{
		
		mesh->Draw(position.x, position.y, shader);
	}

	void GameObject::Update(float deltaTime)
	{
		
		
	}

	void GameObject::SetMesh(fw::Mesh* aMesh)
	{
		mesh = aMesh;
	}

	void GameObject::SetShader(fw::ShaderProgram* aShader)
	{
		shader = aShader;
	}
}
