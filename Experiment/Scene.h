#pragma once
class Player;
class PlayerController;
class Scene: public fw::GameCore		//CANCELING FOR NOW ,WILL TRY TO IMPLEMENT LATER
{
public:
	Scene(fw::FWCore* pFramework);
	virtual ~Scene();

	void Init();
	virtual void StartFrame(float deltaTime) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void OnEvent(fw::Event* pEvent) override;
	


protected:
	fw::ImGuiManager* uiManager=nullptr;
	PlayerController* m_controller;
	std::vector< fw::GameObject*> objects;
	Player* player;

private:
	bool vSync;
};
