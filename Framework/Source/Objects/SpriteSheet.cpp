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
	void SpriteSheet::AddSprite(const std::string aName)
	{
		if (m_dataJason != "")
		{
			rapidjson::Document document;
			document.Parse(m_dataJason);

			rapidjson::Value& spriteList = document["Sprites"];
			int n = 0;
			while (true)
			{
				std::string resultName = spriteList[n]["Name"].GetString();
			
				if (resultName == aName)
				{
					Sprite* spr=new Sprite();
					spr->UVOffset = vec2(spriteList[n]["X"].GetInt(), spriteList[n]["Y"].GetFloat());
					spr->UVOffset = vec2(spriteList[n]["W"].GetInt(), spriteList[n]["H"].GetFloat());
					m_sprites.push_back(spr);
				}
				n++;
			}
		}
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
