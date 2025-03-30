#version 450

layout(location = 0) in vec2 fragOffset;
layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUbo
{
    mat4 projectionMatrix;
    mat4 viewMatrix;
    vec4 ambientLightColor; // w is intensity
    vec3 lightPosition;
    vec4 lightColor;
}
ubo;

void main()
{
    float dis = sqrt(dot(fragOffset, fragOffset)); // dot(vec, vec) = len(vec)²

    // Round shape
    if (dis >= 1.0)
        discard;

    outColor = vec4(ubo.lightColor.xyz, 1.0);
}
