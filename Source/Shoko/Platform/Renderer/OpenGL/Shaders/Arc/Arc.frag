#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform vec4 uColor;
uniform float uStartAngle;
uniform float uEndAngle;
uniform float uInnerRadius;

void main() 
{
    vec2 uv = vUV * 2.0 - 1.0;
    
    float dist = length(uv);
    if (dist > 1.0 || dist < uInnerRadius) discard;
    
    float angle = atan(-uv.y, uv.x);
    if (angle < 0.0) angle += 6.283185;
    
    bool bInAngle = false;
    if (uStartAngle < uEndAngle)
        bInAngle = (angle >= uStartAngle && angle <= uEndAngle);
    else
        bInAngle = (angle >= uStartAngle || angle <= uEndAngle);

    if(!bInAngle) discard;
    
    FragColor = uColor;
}
