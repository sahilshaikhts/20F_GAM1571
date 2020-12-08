#include "GamePCH.h"
#include "TileMap.h"
#include "../Objects/Shape.h"

TileMap::TileMap(const TileType* pLayout, fw::Texture* aTexture, fw::SpriteSheet* aSpriteSheet,fw::ShaderProgram* aShader, int width, int height)
{
	m_spriteSheet = aSpriteSheet;
	m_tilePropertieses.resize((int)TileType::Size);
	m_tilePropertieses[TileType::empty] = TileProperties(m_spriteSheet->GetSpriteInfo("TileEmpty"), true);
	m_tilePropertieses[TileType::dirt] = TileProperties(m_spriteSheet->GetSpriteInfo("TileSand"), true);
	m_tilePropertieses[TileType::tree] = TileProperties(m_spriteSheet->GetSpriteInfo("TileTreeRed"), true);
	m_tilePropertieses[TileType::wall] = TileProperties(m_spriteSheet->GetSpriteInfo("TileMountain5"), false);
	m_tilePropertieses[TileType::water] = TileProperties(m_spriteSheet->GetSpriteInfo("TileWater5"), true);

	m_shader = aShader;
	m_texture = aTexture;
	m_mesh = new fw::Mesh();
	m_mesh->SetDrawMode(GL_TRIANGLE_FAN);
	for (int i = 0; i < totalVerts_sprite; i++) {
		m_mesh->AddVertex(shape_sprite[i]);
	}

	m_MapSize = ivec2(width, height);
	m_layout = new TileType[width*height];
	for (int y = 0,ry= m_MapSize.y-1; y < m_MapSize.y; y++,ry--)
	{
		for (int x = 0; x < m_MapSize.x; x++)
		{
			m_layout[(ry * m_MapSize.x + x)] = pLayout[(y * m_MapSize.x + x)];
		}
	}

}

TileMap::~TileMap()
{
	delete m_mesh;
	delete m_spriteSheet;
	delete[] m_layout;
}
void TileMap::Draw()
{
	for (int y = 0; y < m_MapSize.y; y++)
	{
		for (int x = 0; x < m_MapSize.x; x++)
		{
			int index = (y * m_MapSize.x + x);
			m_mesh->Draw((float)x, (float)y, vec2(1, 1), m_shader, m_texture, vec4::White()
				, m_tilePropertieses[m_layout[index]].sprite->m_UVScale, m_tilePropertieses[m_layout[index]].sprite->m_UVOffset);
		}
	}
}

bool TileMap::IsWalkable(UINT aX,UINT aY)
{
	if(m_layout[(aY * m_MapSize.x + aX)]== TileType::empty || m_layout[(aY * m_MapSize.x + aX)] == TileType::dirt)
	{
		return true;
	}
	return false;
}