#include"FrameworkPCH.h"
#include"../../Game/Source/GamePCH.h"
#include "SpriteSheet.h"

#include "Mesh.h"

namespace fw {
	SpriteSheet::SpriteSheet(const char* fName):m_currentSprite(nullptr)
	{
		m_dataJason = fw::LoadCompleteFile(fName, nullptr);
		m_spriteJson.Parse(m_dataJason);
		m_SpriteSheetSize = vec2(m_spriteJson["Width"].GetFloat(), m_spriteJson["Height"].GetFloat());
		m_frameIndex = 0;
	}
	SpriteSheet::~SpriteSheet()
	{
		for (fw::Sprite* cSprite : m_sprites)
		{
			delete cSprite;
		}
		m_currentSprite = nullptr;
	}
	void SpriteSheet::AddSprite(Sprite* spr)
	{
		m_sprites.push_back(spr);
	}
	void SpriteSheet::AddSprite(const std::string aName){
			rapidjson::Value& spriteList = m_spriteJson["Sprites"];

			for (int n = 0; ; n++)
			{			
				std::string resultName = spriteList[n]["Name"].GetString();
			
				if (resultName == aName)
				{
					Sprite* spr=new Sprite();
					spr->UVOffset = vec2(spriteList[n]["X"].GetInt()/m_SpriteSheetSize.x, spriteList[n]["Y"].GetFloat()/ m_SpriteSheetSize.y);
					spr->UVScale = vec2(spriteList[n]["W"].GetInt()/m_SpriteSheetSize.x, spriteList[n]["H"].GetFloat()/ m_SpriteSheetSize.y);
					m_sprites.push_back(spr);
					break;
				}
			}
	
		if (m_currentSprite == nullptr)
			m_currentSprite = m_sprites[0];
	}
	void SpriteSheet::NextFrame() 
	{
		if (m_frameIndex < m_sprites.size() - 1)
		{
			m_frameIndex++;
			m_currentSprite = m_sprites[m_frameIndex];
		}
	}

}
