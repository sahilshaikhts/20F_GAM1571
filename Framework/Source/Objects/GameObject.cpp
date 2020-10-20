#include "FrameworkPCH.h"

#include "GameObject.h"
#include "Mesh.h"
#include "../../Libraries/imgui/imgui.h"

namespace fw {

GameObject::GameObject(GameCore* pGameCore, std::string name, vec2 pos, Mesh* pMesh, ShaderProgram* pShader, vec4 color)
{
    m_pGameCore = pGameCore;

    m_Name = name;

    m_Position = pos;

    m_pMesh = pMesh;
    m_pShader = pShader;
    m_Color = color;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw()
{
    m_pMesh->Draw( m_Position, m_pShader, m_Color );
}

} // namespace fw
