#include"FrameworkPCH.h"
#include "GameObject.h"

#include "Mesh.h"
<<<<<<< HEAD

namespace fw {
	GameObject::GameObject()
	{
		position.x = 0;
		position.y = 0;
=======
namespace fw {
	GameObject::GameObject()
	{
		x = 0;
		y = 0;
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33

	}

	GameObject::~GameObject()
	{
<<<<<<< HEAD

=======
		/*if (mesh != nullptr) {		//note:CAUSED EXCEPTION [need to do deep copying as temp object destroys this 2 var once out of scope ]
			delete mesh;
			mesh = nullptr;
		}

		if (shader != nullptr) {
			delete shader;
			shader = nullptr;
		}*/
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
	}

	void GameObject::Draw()
	{
<<<<<<< HEAD
		
		mesh->Draw(position.x, position.y, shader);
	}

	void GameObject::Update(float deltaTime)
	{
		
		
=======
		mesh->Draw(x, y, shader);
	}

	void GameObject::Update()
	{
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
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
