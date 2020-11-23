#pragma once
#include "Math/Vector.h"
namespace fw {
    class ShaderProgram;

    class Mesh
    {
    public:
        Mesh();
        virtual ~Mesh();
        void Mesh::Draw(float x, float y, ShaderProgram* pShader, vec4 color);

        void AddVertex(float aX, float aY);
        void AddVertex(vec2 position);
        void AddVertex(vec4 position);

        void SetUniform1f(ShaderProgram* pShader, char* name, float value);
        void SetUniform2f(ShaderProgram* pShader, char* name, vec2 value);
        void SetUniform4f(ShaderProgram* pShader, char* name, vec4 value);

        void SetDrawMode(int mode);
       
        void GenerateMesh();
        void CreateCircle(unsigned int numSegments,float radius);
    protected:
        GLuint m_VBO = 0;

        int m_NumVertices = 0;
        int m_PrimitiveType = GL_POINTS;
        std::vector<float> vertices;
        
    };

}