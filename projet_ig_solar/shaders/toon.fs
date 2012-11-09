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
  vec4 texcol0 = texture2D(image0,texcoord+vec2(time*0.000004,0));  
  vec4 texcol1 = texture2D(image1,texcoord+vec2(time*0.000006,0));
  float ia = 0.25;

  vec3 Kd = mix(texcol0.rgb,texcol1.rgb,texcol1.a);
  vec3 Ks = vec3(1,1,1);
  float sd1 = 0.25;
  float sd2 = 0.0;
  float id = 1-ia;
  float prscal = dot(N,L);
  vec3 Id;
  
  if(prscal>=sd2)Id = id*sd1*Kd;
       else Id = id*sd2*Kd;
  if(prscal>=sd1) Id = id*Kd;  
	

  float tst = pow(max(0,dot(normalize(L+V),N)),80);
  vec3 Is;
  vec3 Ia = ia * Kd;  
  if(tst>0.8) Is = 0.5*Ks;
	else Is = vec3(0,0,0);
  if(dot(N,V)>0.18)
      gl_FragColor = vec4(Ia+Id+Is,1);
  else gl_FragColor = vec4(0,0,0,0);
}
