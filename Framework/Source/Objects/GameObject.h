#pragma once
#include "Math/Vector.h"
namespace fw {

	class Mesh;
	class ShaderProgram;
	class GameCore;

	class GameObject
	{
	public:
		vec2 position;
		vec4 color;
		GameObject(GameCore* aCore, std::string aName, vec4 aColor);
		~GameObject();

		void Draw();
		virtual void Update(float deltaTime);
		void SetMesh(Mesh* aMesh);
		void SetShader(ShaderProgram* aShader);
		std::string GetName();
	private:
		ShaderProgram* shader = nullptr;
	protected:
		Mesh* mesh = nullptr;
		GameCore* m_Core = nullptr;
		std::string m_name;
	};
}