#include "FrameworkPCH.h"
#include "Mesh.h"
#include "Vector2.h"

namespace fw {

    Mesh::Mesh()
    {
    }

    Mesh::~Mesh()
    {
    }

    void Mesh::Draw()
    {
        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Get the attribute variable’s location from the shader.
        GLint loc = 0; //glGetAttribLocation( m_pShader->m_Program, "a_Position" );
        glEnableVertexAttribArray(loc);

        // Describe the attributes in the VBO to OpenGL.
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);

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
        m_PrimitiveType = GL_TRIANGLES;

        // Copy our attribute data into the VBO.
        int numAttributeComponents = m_NumVertices * 2; // x & y for each vertex.
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponents, attribs, GL_STATIC_DRAW);


        delete[] attribs;
    }

    Vector2  Mesh::ConvertScreenToWorldPosition(Vector2 sPosition)
    {
        Vector2 newPos;

        //For x
        float pX;
        float screenHalf = (600 / 2);
        if (sPosition.x < screenHalf)
        {
            pX = sPosition.x / screenHalf;
            if (pX > 0)
                newPos.x = -(1 - pX);
            else
                newPos.x = -1;
        }
        else
        {
            newPos.x = (sPosition.x - screenHalf) / (600 - screenHalf);
        }

        //For y
        float pY = 0;
        if (sPosition.y < screenHalf)
        {
            pY = sPosition.y / screenHalf;
            if (pY > 0)
                newPos.y = -(1 - pY);
            else
                newPos.y = -1;
        }
        else
        {
            newPos.y = (sPosition.y - screenHalf) / (600 - screenHalf);
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

    void Mesh::AddVertex(Vector2 position)
    {

        vertices.push_back(position.x);
        vertices.push_back(position.y);
        m_NumVertices++;
        GenerateMesh();
    }

}