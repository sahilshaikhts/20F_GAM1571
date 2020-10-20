
attribute vec2 a_Position;

uniform vec2 u_ObjectPos;

void main()
{
    vec2 pos = a_Position;
    
    pos *= 1; // Object Scale.

    pos += u_ObjectPos;

    // Transformation from 0->10 Game world space to -1->1 clip space.
    pos /= 5.0;
    pos -= 1.0;

    gl_Position = vec4( pos, 0, 1 );
}
