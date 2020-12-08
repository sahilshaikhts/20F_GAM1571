#pragma once
class Mesh;
class TileMap
{
public:	
	enum TileType
	{
		empty = 0,
		dirt,
		tree,
		wall,
		water,
		Size,
	};

	struct TileProperties
	{
		TileProperties(){}
		TileProperties(fw::Sprite* spr,bool aWalkable):sprite(spr),walkable((aWalkable)){}
		fw::Sprite* sprite=nullptr;
		bool walkable;
	};
	
	TileMap(const TileType* pLayout,fw::Texture* aTexture, fw::SpriteSheet* aSpriteSheet, fw::ShaderProgram* aShader, int width, int height);
	~TileMap();
	void Draw();

	bool IsWalkable(UINT aX, UINT aY);
	ivec2 GetMapSize() { return m_MapSize; }
private:
	fw::Mesh* m_mesh;
	fw::ShaderProgram* m_shader;
	fw::SpriteSheet* m_spriteSheet;
	fw::Texture* m_texture;
	TileType* m_layout;

	ivec2 m_MapSize = ivec2(0, 0); // Width and Height of the map in tiles.
	ivec2 m_TileSize = ivec2(5, 5); // How big is a tile in world units?
	
	std::vector<TileProperties> m_tilePropertieses;
	

};

