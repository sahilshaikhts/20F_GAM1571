uniform float vX;
uniform float vY;

attribute vec2 a_Position;

void main()
{
    vec2 pos=vec2(vX,vY);

    gl_Position = vec4( a_Position+pos, 0 ,1);
}
