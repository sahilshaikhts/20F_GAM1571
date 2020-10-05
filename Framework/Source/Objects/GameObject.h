#pragma once
<<<<<<< HEAD
#include "Math/Vector.h"
=======
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
namespace fw {

	class Mesh;
	class ShaderProgram;
	class FrameWorkPCH;
<<<<<<< HEAD
	class GameObject
	{
	public:
		vec2 position;
=======

	class GameObject
	{
	public:
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
		GameObject();
		~GameObject();

		void Draw();
<<<<<<< HEAD
		virtual void Update(float deltaTime);
		void SetMesh(Mesh* aMesh);
		void SetShader(ShaderProgram* aShader);
	private:
		ShaderProgram* shader = nullptr;
	protected:
		Mesh* mesh = nullptr;

=======
		void Update();
		void SetMesh(Mesh* aMesh);
		void SetShader(ShaderProgram* aShader);
	private:
		float x, y;
		Mesh* mesh= nullptr;
		ShaderProgram* shader= nullptr;
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
	};
}