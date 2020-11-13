#pragma once
#include "Math/Vector.h"
namespace fw {

	class Mesh;
	class ShaderProgram;
	class GameCore;

	class GameObject
	{
	public:
		bool isVisible=true;
		vec2 position;
		vec4 color;
		GameObject();
		GameObject(GameCore* aCore, std::string aName, vec4 aColor);
		~GameObject();

		void Draw();
		virtual void Update(float deltaTime);
		virtual void OnCollision(GameObject* other, fw::CollisionState aState);

		void SetMesh(Mesh* aMesh);
		void SetShader(ShaderProgram* aShader);
		std::string GetName();
		std::string m_name;
	private:
		ShaderProgram* shader = nullptr;
	protected:
		Mesh* mesh = nullptr;
		GameCore* m_Core = nullptr;
	};
}