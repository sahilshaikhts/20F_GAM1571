
uniform float time[2];

void main()
{
    gl_FragColor = vec4( time[0], time[1], 0, 1);
}
