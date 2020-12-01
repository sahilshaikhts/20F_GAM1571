#include"FrameworkPCH.h"
#include"../../Game/Source/GamePCH.h"
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
		sprite_scale = vec2(1, 1);
	}

	GameObject::~GameObject()
	{
		
	}

	void GameObject::Draw()
	{
		if(isVisible)
		mesh->Draw(position.x, position.y, sprite_scale, shader,m_texture,color,m_UVScale,m_UVOffset);
	}

	void GameObject::Update(float deltaTime)
	{
		
		
	}

	void GameObject::OnCollision(GameObject* other, CollisionState aState)
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
	void GameObject::SetTexture(Texture* aTexture)
	{
		m_texture = aTexture;
	}
	std::string GameObject::GetName()
	{
		return m_name;
	}
}
