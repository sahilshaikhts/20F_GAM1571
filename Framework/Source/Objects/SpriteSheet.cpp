#include "FrameworkPCH.h"

#include "Objects/SpriteSheet.h"
#include "Utility/Helpers.h"

namespace fw
{

SpriteSheet::SpriteSheet(const char* filename)
{
	char* jsonString = LoadCompleteFile( filename, nullptr );
	rapidjson::Document document;
	document.Parse( jsonString );
	delete[] jsonString;

	// Convert texture size to floats, so scale/offset math below works.
	float texWidth = (float)document["Width"].GetInt();
	float texHeight = (float)document["Height"].GetInt();

	// Load all the sprites from the json file and store the UV scales and offsets.
	rapidjson::Value& spriteArray = document["Sprites"];
	for( rapidjson::SizeType i=0; i<spriteArray.Size(); i++ )
	{
		rapidjson::Value& sprite = spriteArray[i];

		vec2 UVScale( sprite["W"].GetInt()/texWidth, sprite["H"].GetInt()/texHeight );
		vec2 UVOffset( sprite["X"].GetInt()/texWidth, sprite["Y"].GetInt()/texHeight );

		m_Sprites[sprite["Name"].GetString()] = Sprite( UVScale, UVOffset );
	}
}

SpriteSheet::~SpriteSheet()
{
}

Sprite* SpriteSheet::GetSpriteInfo(const char* spriteName)
{
	return &m_Sprites.at( spriteName );
}

Sprite* SpriteSheet::GetSpriteInfo(const std::string spriteName)
{
	return &m_Sprites.at(spriteName);
}

} // namespace fw
