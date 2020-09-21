#pragma once
class Vector2;
namespace fw {

    class Mesh
    {
    public:
        Mesh();
        virtual ~Mesh();
        void Draw();
       // void Draw(float x,float y,ShaderProgram* aShader);
        void AddVertex(float aX,float aY);
        void AddVertex(Vector2 position);

        void GenerateMesh();
        Vector2 ConvertScreenToWorldPosition(Vector2 value);
    protected:
        GLuint m_VBO = 0;
        
        int m_NumVertices = 0;
        int m_PrimitiveType = GL_POINTS;
        std::vector<float>vertices;

    };

}