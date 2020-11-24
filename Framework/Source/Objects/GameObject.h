#pragma once
#include "../Math/Vector.h"
namespace fw {

	class Mesh;
	class ShaderProgram;
	class GameCore;
	class Texture;
	class GameObject
	{
	public:
		bool isVisible=true;
		vec2 position, m_UVScale=vec2(1,1), m_UVOffset=vec2(0,0);
		vec4 color;
		GameObject();
		GameObject(GameCore* aCore, std::string aName, vec4 aColor);
		~GameObject();

		void Draw();
		virtual void Update(float deltaTime);
		virtual void OnCollision(GameObject* other, fw::CollisionState aState);

		void SetMesh(Mesh* aMesh);
		void SetShader(ShaderProgram* aShader);
		void SetTexture(Texture* aTexture);
		std::string GetName();
		std::string m_name;

	private:
		ShaderProgram* shader = nullptr;
		Texture* m_texture;
	protected:
		Mesh* mesh = nullptr;
		GameCore* m_Core = nullptr;
	};
}