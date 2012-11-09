#version 120

uniform sampler2D image0; 
uniform sampler2D image1; 
uniform int time; 
varying vec3 normal;
varying vec3 dirlight;
varying vec3 direye;
varying vec2 texcoord;

void main()
{
  vec3 N = normalize(normal);
  vec3 L = normalize(dirlight);
  vec3 V = normalize(direye);
  vec4 texcol0 = texture2D(image0,texcoord+vec2(-time*0.00002,0));  
  vec4 texcol1 = texture2D(image1,texcoord+vec2(time*0.00002,0));

  vec3 Kd = mix(texcol0.rgb,texcol1.rgb,texcol1.a);
  vec3 Ks = vec3(1,1,1);
  
  vec3 Ia = 0.9 * Kd;
  
  
  gl_FragColor = vec4(Kd,1);
}
