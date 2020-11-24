#pragma once
namespace fw {
	class Texture
	{
	public:
		Texture(const char* fName);
		~Texture();

		GLuint GetHandle() {return m_TextureHandle;}
	private:
		GLuint m_TextureHandle = 0;
	};
}