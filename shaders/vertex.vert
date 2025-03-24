#version 450

/* INPUT */
layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

/* OUTPUT */
layout(location = 0) out vec3 fragColor;

void main()
{
    gl_Position = vec4(inPosition, 0.0, 1.0);
    fragColor = inColor;
}
