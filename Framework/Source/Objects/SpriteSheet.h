#pragma once
namespace fw {
	struct Sprite
	{
		vec2 UVScale=vec2(1,1);
		vec2 UVOffset=vec2(0,0);
	};
	class SpriteSheet
	{
	public:

		SpriteSheet(const char* fName);
		void AddSprite(const std::string name);
		void AddSprite(Sprite* spr);
		void NextFrame();
		void ChangeFrameIndex(int index);
		int GetIndex() { return m_frameIndex; }
		~SpriteSheet();
		Sprite* GetCurrentFrameSprite() { return m_currentSprite; };

	private:
		std::vector<Sprite*>m_sprites;
		rapidjson::Document m_spriteJson;
		Sprite* m_currentSprite;
		vec2 m_SpriteSheetSize;
		char* m_dataJason;
		int m_frameIndex;
	};
}