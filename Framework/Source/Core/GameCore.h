#pragma once
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

