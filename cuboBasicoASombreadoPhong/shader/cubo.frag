#version 410 core
in vec3 fragColor;
in vec3 posSuper;
in vec3 N;
out vec4 color;


uniform vec3 posCam;

vec3 posLuz = vec3(0.0,2.0,0.0);
vec3 colorLuz = vec3(1.0,1.0,1.0);

float coef_ambiental = 0.2;
float coef_difuso = 0.6;
float coef_especular = 1.0;
float glossines = 20.0;

//vec3 colorBase = vec3(244.0, 127.0, 38.0) / 255.0;
vec3 colorBase = vec3(0.2, 0.0, 1.0);

void main()
{

    
    vec3 L = normalize(posLuz - posSuper.xyz);

    vec3 R = reflect(-L, N);
    vec3 V = normalize(posCam - posSuper.xyz);
    vec3 H = normalize(L + V);
      
    vec3 colorAmbienta = (coef_ambiental * colorBase) ;
    vec3 colorDifuso = coef_difuso * max(dot(N,L),0.0) * colorBase;
    vec3 colorSpecultarH = colorLuz * coef_especular * pow(max(dot(N,H),0.0),glossines);
    vec3 colorSpecultarR = colorLuz * coef_especular * pow(max(dot(R,V),0.0),glossines);

    color = vec4(colorAmbienta + colorDifuso + colorSpecultarR,1.0);



    //color = vec4(fragColor, 1.0);
}