#pragma once
#include "Math/Vector.h"
namespace fw {

	class Mesh;
	class ShaderProgram;
	class FrameWorkPCH;
	class GameCore;
	class GameObject
	{
	public:
		vec2 position;
		GameCore* core;
		GameObject();
		~GameObject();

		void Draw();
		void Update();
		void SetMesh(Mesh* aMesh);
		void SetShader(ShaderProgram* aShader);
	private:
		Mesh* mesh = nullptr;
		ShaderProgram* shader = nullptr;
	};
}