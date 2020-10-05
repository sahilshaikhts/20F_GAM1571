#include "FrameworkPCH.h"
#include "Mesh.h"
<<<<<<< HEAD:Framework/Source/Objects/Mesh.cpp
#include "Math/Vector.h"
#include "Utility/ShaderProgram.h"
#include"Utility/Helpers.h"
=======
#include "Vector2.h"
#include "Utility/ShaderProgram.h"
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33:Framework/Source/Mesh.cpp

namespace fw {

    Mesh::Mesh(){

    }


    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &m_VBO);
    }

    void Mesh::Draw(float x, float y, ShaderProgram* pShader)
<<<<<<< HEAD:Framework/Source/Objects/Mesh.cpp
    { 
=======
    {
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33:Framework/Source/Mesh.cpp

        glUseProgram(pShader->GetProgram());

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Get the attribute variable’s location from the shader.
        GLint loc = 0; //glGetAttribLocation( m_pShader->m_Program, "a_Position" );
        glEnableVertexAttribArray(loc);

        // Describe the attributes in the VBO to OpenGL.
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);

        {
            
           int loc_x= glGetUniformLocation(pShader->GetProgram(), "vX");
           int loc_y = glGetUniformLocation(pShader->GetProgram(), "vY");

           glUniform1f(loc_x,x);
           glUniform1f(loc_y, y);
           
        }

        // Draw the primitive.
        glDrawArrays(m_PrimitiveType, 0, m_NumVertices);
    }

    void Mesh::GenerateMesh()
    {
        // Generate a buffer for our vertex attributes.
        glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        float* attribs = new float[m_NumVertices * 2];
        std::copy(vertices.begin(), vertices.end(), attribs);

        // Copy our attribute data into the VBO.
        int numAttributeComponents = m_NumVertices * 2; // x & y for each vertex.
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponents, attribs, GL_STATIC_DRAW);

        if (attribs != nullptr) { //Release memory
            delete[] attribs;
            attribs = nullptr;
        }
    }

<<<<<<< HEAD:Framework/Source/Objects/Mesh.cpp
    vec2  Mesh::ConvertScreenToWorldPosition(vec2 scrn_position)
=======
    Vector2  Mesh::ConvertScreenToWorldPosition(Vector2 scrn_position)
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33:Framework/Source/Mesh.cpp
    {
        vec2 newPos;

        //For x
        float pX;
        float screenHalf = (600 / 2);
        if (scrn_position.x < screenHalf)
        {
            pX = scrn_position.x / screenHalf;
            if (pX > 0)
                newPos.x = -(1 - pX);
            else
                newPos.x = -1;
        }
        else
        {
            newPos.x = (scrn_position.x - screenHalf) / (600 - screenHalf);
        }

        //For y
        float pY = 0;
        if (scrn_position.y < screenHalf)
        {
            pY = scrn_position.y / screenHalf;
            if (pY > 0)
                newPos.y = -(1 - pY);
            else
                newPos.y = -1;
        }
        else
        {
            newPos.y = (scrn_position.y - screenHalf) / (600 - screenHalf);
        }

        return newPos;
    }

    void Mesh::AddVertex(float aX, float aY)
    {
        vertices.push_back(aX);
        vertices.push_back(aY);
        m_NumVertices++;
        GenerateMesh();
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



}