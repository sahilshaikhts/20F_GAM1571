#include "FrameworkPCH.h"
#include "Mesh.h"
#include "Math/Vector.h"
#include "Utility/ShaderProgram.h"
#include"Utility/Helpers.h"

namespace fw {

    Mesh::Mesh(){

    }


    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &m_VBO);
    }

    void Mesh::Draw(float x, float y, ShaderProgram* pShader, vec4 color)
    {

        glUseProgram(pShader->GetProgram());

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Get the attribute variable’s location from the shader.
        GLint loc = glGetAttribLocation(pShader->GetProgram(), "a_Position");
        glEnableVertexAttribArray(loc);
        glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 16, (void*)0);  // Describe the attributes in the VBO to OpenGL.

        loc = glGetAttribLocation(pShader->GetProgram(), "a_UV");
        if (loc != -1) {
            glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 16, (void*)8);  // Describe the attributes in the VBO to OpenGL.
            SetUniform2f(pShader, "u_newPos", vec2(x, y));
            SetUniform4f(pShader, "u_Color", color);
        }
        // Draw the primitive.
        glDrawArrays(m_PrimitiveType, 0, m_NumVertices);
    }
    void Mesh::SetUniform1f(ShaderProgram* pShader, char* name, float value)
    {
        int loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform1f(loc, value);
    }

    void Mesh::SetUniform2f(ShaderProgram* pShader, char* name, vec2 value)
    {
        int loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform2f(loc, value.x, value.y);
    }

    void Mesh::SetUniform4f(ShaderProgram* pShader, char* name, vec4 value)
    {
        int loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform4f(loc, value.x, value.y, value.z, value.w);
    }

    void Mesh::GenerateMesh()
    {
        
        // Generate a buffer for our vertex attributes.
        glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        float* attribs = new float[(int)(m_NumVertices * sizeof(vertices) / 4)];
        std::copy(vertices.begin(), vertices.end(), attribs);

        // Copy our attribute data into the VBO.
        int numAttributeComponents = m_NumVertices * sizeof(vertices)/4; // x , y(& u,v) for each vertex.
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponents, attribs, GL_STATIC_DRAW);

        if (attribs != nullptr) { //Release memory
            delete[] attribs;
            attribs = nullptr;
        }
    }

    void Mesh::CreateCircle(unsigned int numSegments, float radius)
    {
        float segmentInterval = 2*3.1415927f / numSegments;
        for (unsigned int i = 0; i < numSegments; i++)
        {
            float angle = segmentInterval * i;

            vertices.push_back(cos(angle)*radius);//x
            vertices.push_back(sin(angle) * radius);//y
            vertices.push_back(0);//u
            vertices.push_back(0);//v
            m_NumVertices ++;
        }
        GenerateMesh();
    }

    
    void Mesh::AddVertex(float aX, float aY)
    {
        vertices.push_back(aX);
        vertices.push_back(aY);

        m_NumVertices++;
        GenerateMesh();//probaly not a good idea to call it repeatedly
    }

    void Mesh::AddVertex(vec2 position)
    {
        vertices.push_back(position.x);
        vertices.push_back(position.y);

        m_NumVertices++;
        GenerateMesh();
    }

    void Mesh::SetDrawMode(int mode)
    {
        m_PrimitiveType = mode;
    }
    void Mesh::AddVertex(vec4 position)
    {
        vertices.push_back(position.x);
        vertices.push_back(position.y);
        vertices.push_back(position.u);
        vertices.push_back(position.v);
        m_NumVertices++;

        GenerateMesh();
    }

}