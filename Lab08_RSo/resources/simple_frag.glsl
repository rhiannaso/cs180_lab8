#version 330 core 
in vec3 fragNor;
in vec3 lightDir;
in vec3 EPos;
out vec4 color;

uniform vec3 MatAmb;
uniform vec3 MatDif;
uniform vec3 MatSpec;
uniform float MatShine;

void main()
{
	vec3 normal = normalize(fragNor);
    vec3 light = normalize(lightDir);
	float dC = max(0, dot(normal, light));
	vec3 V = -1*EPos;
    vec3 H = normalize(lightDir + V);
    float NH = (normal.x*H.x) + (normal.y*H.y) + (normal.z*H.z);
    float NHPow = pow(NH, MatShine);

    color = vec4(MatAmb + (dC*MatDif) + (NHPow*MatSpec), 1.0);
}
