#pragma once
class Vector2;
namespace fw {
    class ShaderProgram;

    class Mesh
    {
    public:
        Mesh();
        virtual ~Mesh();
        void Mesh::Draw(float x, float y, ShaderProgram* pShader);

        void AddVertex(float aX, float aY);
        void AddVertex(Vector2 position);

        void SetDrawMode(int mode);
        void GenerateMesh();

        Vector2 ConvertScreenToWorldPosition(Vector2 scrn_position);
    protected:
        GLuint m_VBO = 0;

        int m_NumVertices = 0;
        int m_PrimitiveType = GL_POINTS;
        std::vector<float> vertices;

    };

}