#pragma once
<<<<<<< HEAD

namespace fw {

class FWCore;

class GameCore
{
public:
    GameCore(FWCore* pFramework);
    virtual ~GameCore();

    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
  
    FWCore* GetFrameWork()
    {
        return m_pFramework;
    }

protected:
    FWCore* m_pFramework;
};

} // namespace fw
=======
namespace fw
{
	class FWCore;

	class GameCore
	{
	protected:
		FWCore* m_pFramework;

	public:
		GameCore(FWCore* pFramework);
		virtual ~GameCore();
		virtual void Update(float deltaTime) = 0;
		virtual void Draw() = 0;
	};
}

>>>>>>> dbeebbdcdc4edd044416304e94b5b1661d12be33
