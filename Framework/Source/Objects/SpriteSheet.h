#pragma once

#include "Math/Vector.h"

namespace fw {

	struct Sprite
	{
		vec2 m_UVScale = vec2(1,1);
		vec2 m_UVOffset = vec2(0,0);

		Sprite() {}
		Sprite(vec2 scale, vec2 offset) { m_UVScale = scale, m_UVOffset = offset; }
	};
class SpriteSheet
{
public:

public:
	SpriteSheet(const char* filename);
	virtual ~SpriteSheet();

	Sprite* GetSpriteInfo(const char* spriteName);
	Sprite* GetSpriteInfo(const std::string spriteName);

private:
	std::map<std::string, Sprite> m_Sprites;
};

} // namespace fw
