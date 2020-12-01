#include <iostream>
class  Animation
{
public:
	Animation(char* fName);
	~Animation();

protected:
	fw::SpriteSheet* m_spriteSheet;
};