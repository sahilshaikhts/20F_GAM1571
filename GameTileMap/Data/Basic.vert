uniform float vX;
uniform float vY;

attribute vec2 a_Position;

void main()
{
    vec2 pos=vec2(vX,vY);
    pos+=a_Position;
    pos/=5;
    pos-=1;

    gl_Position = vec4(pos, 0 ,1);
}
