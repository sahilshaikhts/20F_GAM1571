#include <iostream>
#include <map>

class  Animation_Player
{
public:
	enum State
	{
		stop = -1,
		walk_Left = 0,
		walk_Right,
		walk_Up,
		walk_Down,
	};

	Animation_Player(char* fName) {
		m_spriteSheet = new fw::SpriteSheet(fName);
		//NAME OF FRAMES FROM JSON
		frames[State::walk_Left].push_back("WalkLeft1");
		frames[State::walk_Left].push_back("WalkLeft2");
		
		frames[State::walk_Right].push_back("WalkRight1");
		frames[State::walk_Right].push_back("WalkRight2");
		
		frames[State::walk_Up].push_back("WalkUp1");
		frames[State::walk_Up].push_back("WalkUp2");
		
		frames[State::walk_Down].push_back("WalkDown1");
		frames[State::walk_Down].push_back("WalkDown2");
	}
	~Animation_Player()
	{
		delete m_spriteSheet; //throwing exception on deleting
	}
	std::map<State, std::vector<std::string>> frames;
	
	State currentState;
	int currentFrame = -1;
	fw::SpriteSheet* m_spriteSheet;

	void ChangeState(State aState) { currentState = aState; };
	fw::Sprite* GetNextKeyFrame(State aState)
	{
		if (aState != currentState)
		{
			currentFrame = 0;
			currentState = aState;
		}else
		if (currentFrame < frames[currentState].size() -1)
		{
			currentFrame++;
		}
		else
			currentFrame = 0;

		return  m_spriteSheet->GetSpriteInfo(frames[currentState][currentFrame]);
	}
	
};