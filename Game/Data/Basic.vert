uniform vec2 u_newPos;


attribute vec2 a_UV;
attribute vec2 a_Position;

void main()
{
    vec2 pos=u_newPos;
    pos+=a_Position;
    pos/=5;
    pos-=1;

    gl_Position = vec4(pos, 0 ,1);
}
