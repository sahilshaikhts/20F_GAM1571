#pragma once
#include "Math/Vector.h"
namespace fw {

	class Mesh;
	class ShaderProgram;
	class FrameWorkPCH;
	class GameObject
	{
	public:
		vec2 position;
		GameObject();
		~GameObject();

		void Draw();
		virtual void Update(float deltaTime);
		void SetMesh(Mesh* aMesh);
		void SetShader(ShaderProgram* aShader);
	private:
		ShaderProgram* shader = nullptr;
	protected:
		Mesh* mesh = nullptr;

	};
}