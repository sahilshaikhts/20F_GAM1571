#pragma once

namespace fw {

class ShaderProgram
{
protected:
    char* m_VertShaderString;
    char* m_FragShaderString;

    GLuint m_VertShader;
    GLuint m_FragShader;
    GLuint m_Program;
    
protected:
    void Cleanup();

    void CompileShader(GLuint& shaderHandle, const char* shaderString);
    bool Init(const char* vertFilename, const char* fragFilename);
    bool Reload();

public:
    ShaderProgram();
    ShaderProgram(const char* vertFilename, const char* fragFilename);
    virtual ~ShaderProgram();

    GLuint GetProgram() { return m_Program; }
};

} // namespace fw
