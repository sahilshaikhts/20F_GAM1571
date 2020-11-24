uniform vec2 u_newPos;

uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;

attribute vec2 a_UV;
attribute vec2 a_Position;

varying vec2 UV;

void main()
{
    vec2 pos=u_newPos;

    pos+=a_Position;
    pos*=1;
    pos/=5;
    pos-=1;

    
    //vec2 u_UVScale=vec2(16.0/256.0,16.0/128.0);
    //vec2 u_UVOffset=vec2(83.0/256.0,112.0/128.0);
    
    UV=a_UV*u_UVScale+u_UVOffset;
    
    gl_Position = vec4(pos, 0 ,1);
}
