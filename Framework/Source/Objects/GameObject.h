#pragma once
namespace fw {

	class Mesh;
	class ShaderProgram;
	class FrameWorkPCH;

	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void Draw();
		void Update();
		void SetMesh(Mesh* aMesh);
		void SetShader(ShaderProgram* aShader);
	private:
		float x, y;
		Mesh* mesh= nullptr;
		ShaderProgram* shader= nullptr;
	};
}