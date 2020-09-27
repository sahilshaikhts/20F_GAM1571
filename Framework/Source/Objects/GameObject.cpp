#include"FrameworkPCH.h"
#include "GameObject.h"

#include "Mesh.h"
namespace fw {
	GameObject::GameObject()
	{
		x = 0;
		y = 0;

	}

	GameObject::~GameObject()
	{
		/*if (mesh != nullptr) {		//note:CAUSED EXCEPTION [need to do deep copying as temp object destroys this 2 var once out of scope ]
			delete mesh;
			mesh = nullptr;
		}

		if (shader != nullptr) {
			delete shader;
			shader = nullptr;
		}*/
	}

	void GameObject::Draw()
	{
		mesh->Draw(x, y, shader);
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
