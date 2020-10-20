#include "GamePCH.h"
#include "Shapes.h"

const float meshAttribs_Human[] =
{
    -0.25f,  -0.25f,
     0.25f,   0.25f,
     0.25f,  -0.25f,
};
const int meshPrimType_Human = GL_TRIANGLES;
const int meshNumVerts_Human = sizeof(meshAttribs_Human) / (sizeof(float) * 2);

const float meshAttribs_Enemy[] =
{
    0.0f, 0.0f,
};
const int meshPrimType_Enemy = GL_POINTS;
const int meshNumVerts_Enemy = sizeof(meshAttribs_Enemy) / (sizeof(float) * 2);
