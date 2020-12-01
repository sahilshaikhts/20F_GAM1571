#include "GamePCH.h"
#include"Math/Vector.h"

 vec4  shape_heart[] =
 {
     vec4(0.0f,0.05f,0,0),
     vec4(-0.05f,0.2f,0,0),
     vec4(-0.25f,0.2f,0,0),
     vec4(-0.25f,0.0f,0,0),
     vec4(0.0f,-0.3f,0,0),
     vec4(0.25f,0.0f,0,0),
     vec4(0.25f,0.2f,0,0),
     vec4(0.05f,0.2f,0,0),
     vec4(0.0f,0.05f,0,0)
 };
 vec4  shape_sprite[] =
{             
vec4(0,0,0,0),//bl
vec4(0,1,0,1),//tl
vec4(1,1,1,1),//tr
vec4(1,0,1,0),//br
};

 int totalVerts_heart = (int)std::size(shape_heart);
 int totalVerts_sprite = (int)std::size(shape_sprite);
 