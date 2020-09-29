#include"FrameworkPCH.h"
#include "GameObject.h"

#include "Mesh.h"

namespace fw {
	GameObject::GameObject()
	{
		//-1 as the origin(0,0) will be at (-1,-1)
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

	void GameObject::Update()
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
