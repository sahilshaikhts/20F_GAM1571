#pragma once

#include "Math/Vector.h"

namespace fw {

class ShaderProgram;

class Mesh
{
public:
    Mesh();
    Mesh(int primitiveType, int numVertices, const float* pVertices);
    virtual ~Mesh();

    void CreateShape(int primitiveType, int numVertices, const float* pVertices);
    void CreateCircle(float radius,int numVertices,bool isFilled);
    void SetUniform1f(ShaderProgram* pShader, char* name, float value);
    void SetUniform2f(ShaderProgram* pShader, char* name, vec2 value);
    void SetUniform4f(ShaderProgram* pShader, char* name, vec4 value);

    void Draw(vec2 pos, ShaderProgram* pShader, vec4 color);

protected:
    GLuint m_VBO = 0;

    int m_NumVertices = 0;
    int m_PrimitiveType = GL_POINTS;
};

} // namespace fw
