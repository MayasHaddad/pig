#version 120

uniform vec4 light;
varying vec3 normal;
varying vec3 dirlight;
varying vec3 direye;
varying vec2 texcoord;

void main()
{
 gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
 normal = gl_NormalMatrix * gl_Normal;
 dirlight = vec3(light-gl_ModelViewMatrix * gl_Vertex);
 direye = vec3(-gl_ModelViewMatrix * gl_Vertex);
 texcoord = vec2(gl_MultiTexCoord0);
}
