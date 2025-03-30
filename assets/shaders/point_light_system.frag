#version 450

layout(location = 0) in vec2 fragOffset;
layout(location = 0) out vec4 outColor;

struct PointLight
{
    vec3 position;
    vec4 color; // w = intensity
};

layout(set = 0, binding = 0) uniform GlobalUbo
{
    mat4 projectionMatrix;
    mat4 viewMatrix;
    mat4 inverseViewMatrix;
    vec4 ambientLightColor;
    PointLight pointLights[10];
    int numLights;
}
ubo;

layout(push_constant) uniform Push
{
    vec3 position;
    vec4 color;
    float radius;
}
push;

const float M_PI = 3.141592653589793;

void main()
{
    float dis = sqrt(dot(fragOffset, fragOffset)); // dot(vec, vec) = len(vec)²

    // Round shape
    if (dis >= 1.0)
        discard;

    float cosDis = 0.5 * (cos(dis * M_PI) + 1.0);
    outColor = vec4(push.color.xyz + cosDis, cosDis);
}
