#pragma once
namespace fw
{
	class GameCore
	{
	public:
		virtual ~GameCore();
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}

