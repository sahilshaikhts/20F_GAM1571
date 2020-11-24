#include"Math/Vector.h"
#include "GamePCH.h"
#include<iostream>

vec4 shape_heart[] =
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
vec4 shape_sprite[] =
{
//vec4(0,0,85/265.0f,112/128.0f),//BL
//vec4(0,1,85 / 265.0f,(112+16)/128.0f),//TL
//vec4(1,1,(85+16)/256.0f,(112+16)/128.0f),//TR
//vec4(1,0,(85 + 16) / 256.0f,112/128.0f),//BR

              
vec4(0,0,0,0),//bl
vec4(0,1,0,1),//tl
vec4(1,1,1,1),//tr
vec4(1,0,1,0),//br

};

int totalVerts_heart= std::size(shape_heart);
 