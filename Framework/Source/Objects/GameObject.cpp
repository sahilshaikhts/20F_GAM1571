#include"FrameworkPCH.h"
#include "GameObject.h"

#include "Mesh.h"

namespace fw {
	GameObject::GameObject(){}
	GameObject::GameObject(GameCore* aCore, std::string aName, vec4 aColor)
	{
		position.x = 0;
		position.y = 0;
		m_name = aName;
		m_Core = aCore;
		color = aColor;
	}

	GameObject::~GameObject()
	{

	}

	void GameObject::Draw()
	{
		
		mesh->Draw(position.x, position.y, shader,color);
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
	std::string GameObject::GetName()
	{
		return m_name;
	}
}
