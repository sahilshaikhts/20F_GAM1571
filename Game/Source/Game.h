#pragma once

class PlayerController;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore* pFramework);
    virtual ~Game();

    void Init();
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

protected:
    fw::ImGuiManager* m_pImGuiManager = nullptr;

    fw::ShaderProgram* m_pShader = nullptr;
    fw::Mesh* m_pMeshHuman = nullptr;
    fw::Mesh* m_pMeshEnemy = nullptr;
    fw::Mesh* m_pMeshTest = nullptr;
    fw::Mesh* m_Arena=nullptr;

    PlayerController* m_pPlayerController = nullptr;

    std::vector<fw::GameObject*> m_Objects;

    // Settings.
    bool m_VSyncEnabled = true;

    int vertices = 40;
};
