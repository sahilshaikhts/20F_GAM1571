#include"Math/Vector.h"
#include "GamePCH.h"
#include<iostream>
 vec2 shape_dog[] ={
        vec2(560, 320),

        vec2(500, 360),

        vec2(500, 320),

        vec2(500, 360),

        vec2(500, 390),

        vec2(520, 330),

        vec2(500, 280),

        vec2(400, 290),

        vec2(500, 340),

        vec2(400, 290),

        vec2(400, 320),

        vec2(500, 340),

        vec2(400, 320),

        vec2(380, 300),

        vec2(400, 200),

        vec2(500, 280),

        vec2(470, 210),

        vec2(470, 290),

};
 vec2 shape_heart[] =
 {
     vec2(0.0f,0.05f),
     vec2(-0.05f,0.2f),
     vec2(-0.25f,0.2f),
     vec2(-0.25f,0.0f),
     vec2(0.0f,-0.3f),
     vec2(0.25f,0.0f),
     vec2(0.25f,0.2f),
     vec2(0.05f,0.2f),
     vec2(0.0f,0.05f)
 };
 int totalVerts_heart= std::size(shape_heart);
 int totalVerts_Dog=std::size(shape_dog);
