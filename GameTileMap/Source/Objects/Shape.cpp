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
 int totalVerts_heart= std::size(shape_heart);
 