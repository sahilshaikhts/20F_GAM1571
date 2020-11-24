uniform vec4 u_Color;
uniform sampler2D u_Texture;
varying vec2 UV;
void main()
{
    gl_FragColor = texture2D(u_Texture,UV);
}
