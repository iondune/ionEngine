#version 150

#define LIGHT_MAX 4

// struct SMaterial
// {
//  vec3 AmbientColor;
//  vec3 DiffuseColor;
// };

struct SLight
{
    vec3 Position;
    vec3 Color;
    float Radius;
};

in vec4 vColor;
in vec3 vNormal;
in vec3 vLight[LIGHT_MAX];
in vec3 vLightColor[LIGHT_MAX];
in vec3 vEye;

uniform int uLightCount;
uniform SLight uLights[LIGHT_MAX];
// uniform SMaterial uMaterial;

out vec4 outColor;

float sq(float v)
{
    return v * v;
}

void main()
{
    vec3 Diffuse = vec3(0);
    vec3 Specular = vec3(0);
    vec3 uMaterialDiffuseColor = vec3(0.95);
    vec3 uMaterialAmbientColor = vec3(0.05);
    vec3 uMaterialSpecularColor = vec3(1.0);
    float uMaterialShininess = 1000.0;

    vec3 nEye = normalize(vEye);

    for (int i = 0; i < LIGHT_MAX && i < uLightCount; ++ i)
    {
        vec3 nLight = normalize(vLight[i]);
        vec3 nNormal = normalize(vNormal);
        vec3 Reflection = reflect(-nLight, nNormal);

        float Shading = clamp(dot(nNormal, nLight), 0.0, 1.0);
        float Distance = length(vLight[i]);
        float Attenuation = 1.0 / sq(Distance / uLights[i].Radius + 1);
        Diffuse += uMaterialDiffuseColor * Shading * Attenuation * uLights[i].Color;

        float Highlight = pow(clamp(dot(nEye, Reflection), 0.0, 1.0), uMaterialShininess);
        Specular += uMaterialSpecularColor * Highlight * Attenuation * uLights[i].Color;
    }

    outColor = vec4(Specular + Diffuse + uMaterialAmbientColor, 1);
}
