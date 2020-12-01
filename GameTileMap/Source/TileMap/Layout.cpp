#include "GamePCH.h"

#include "TileMap.h"
#include "Layout.h"

using TT = TileMap::TileType;

const ivec2 Size_TestMap=ivec2(10,10);
const TileMap::TileType Layout_TestMap[] =
{
	TT::wall,TT::wall,TT::wall,TT::wall,TT::water,TT::water,TT::empty,TT::empty,TT::empty,TT::empty,
	TT::wall,TT::wall,TT::wall,TT::water,TT::water,TT::water,TT::empty,TT::empty,TT::dirt,TT::dirt,
	TT::wall,TT::wall,TT::water,TT::water,TT::water,TT::water,TT::empty,TT::dirt,TT::dirt,TT::dirt,
	TT::wall,TT::water,TT::water,TT::water,TT::water,TT::dirt,TT::dirt,TT::dirt,TT::empty,TT::empty,
	 TT::wall,TT::wall,TT::water,TT::water,TT::dirt,TT::dirt,TT::dirt,TT::dirt,TT::empty,TT::wall,
	 TT::empty,TT::dirt,TT::empty,TT::dirt,TT::dirt,TT::empty,TT::empty,TT::empty,TT::tree,TT::wall,
	 TT::empty,TT::empty,TT::empty,TT::empty,TT::empty,TT::empty,TT::empty,TT::empty,TT::wall,TT::wall,
	 TT::dirt,TT::dirt,TT::empty,TT::empty,TT::tree,TT::tree,TT::empty,TT::empty,TT::wall,TT::wall,
	 TT::dirt,TT::empty,TT::empty,TT::tree,TT::tree,TT::dirt,TT::tree,TT::empty,TT::empty,TT::wall,
	 TT::dirt,TT::empty,TT::dirt,TT::dirt,TT::tree,TT::tree,TT::tree,TT::empty,TT::empty,TT::dirt,
};