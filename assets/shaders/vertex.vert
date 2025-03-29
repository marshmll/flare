#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUv;

layout(push_constant) uniform Push
{
    mat4 modelMatrix;
    mat4 normalMatrix;
}
push;

layout(location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform GlobalUbo
{
    mat4 projectionViewMatrix;
    vec4 ambientLightColor;
    vec3 lightPosition;
    vec4 lightColor;
}
ubo;

void main()
{
    vec4 positionWorld = push.modelMatrix * vec4(inPosition, 1.0);
    gl_Position = ubo.projectionViewMatrix * positionWorld;

    vec3 normalWorldSpace = normalize(mat3(push.normalMatrix) * inNormal);

    vec3 directionToLight = ubo.lightPosition - positionWorld.xyz;
    float attenuation = 1.0 / dot(directionToLight, directionToLight); // dot(vec, vec) = len(vec)²

    vec3 lightColor = ubo.lightColor.xyz * ubo.lightColor.w * attenuation;
    vec3 ambientLight = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w;
    vec3 diffuseLight = lightColor * max(dot(normalWorldSpace, normalize(directionToLight)), 0);

    fragColor = (diffuseLight + ambientLight) * inColor;
}
