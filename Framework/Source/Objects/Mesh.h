#pragma once
class vec2;
namespace fw {
    class ShaderProgram;

    class Mesh
    {
    public:
        Mesh();
        virtual ~Mesh();
        void Mesh::Draw(float x, float y, ShaderProgram* pShader);

        void AddVertex(float aX, float aY);
<<<<<<< HEAD:Framework/Source/Objects/Mesh.h
        void AddVertex(vec2 position);
=======
        void AddVertex(Vector2 position);
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33:Framework/Source/Mesh.h

        void SetDrawMode(int mode);
        void GenerateMesh();

<<<<<<< HEAD:Framework/Source/Objects/Mesh.h
        vec2 ConvertScreenToWorldPosition(vec2 scrn_position);
=======
        Vector2 ConvertScreenToWorldPosition(Vector2 scrn_position);
>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33:Framework/Source/Mesh.h
    protected:
        GLuint m_VBO = 0;

        int m_NumVertices = 0;
        int m_PrimitiveType = GL_POINTS;
        std::vector<float> vertices;
<<<<<<< HEAD:Framework/Source/Objects/Mesh.h
        
=======

>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33:Framework/Source/Mesh.h
    };

}