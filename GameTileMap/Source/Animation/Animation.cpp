#include "GamePCH.h"
#include "Animation.h"

Animation::Animation(char* fName)
{
	m_spriteSheet = new fw::SpriteSheet(fName);
	delete[] fName;
}
