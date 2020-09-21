#include "GameObject.h"

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
	glUseProgram(shader->GetProgram());
	mesh->Draw();
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

