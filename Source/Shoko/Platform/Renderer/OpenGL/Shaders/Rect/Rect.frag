#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform vec4 uColor;
uniform vec2 uSize;
uniform float uRadius;
uniform float uThickness;

float sdRoundedBox(vec2 p, vec2 b, float r) 
{
    vec2 q = abs(p) - b + r;
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;
}

void main() 
{
    vec2 p = (vUV - 0.5) * uSize;
    vec2 b = uSize * 0.5;

    float d = sdRoundedBox(p, b, uRadius);

    float alpha;
    
    if(uThickness > 0.0)
        alpha = 1.0 - smoothstep(-0.5, 0.5, abs(d + uThickness * 0.5) - uThickness * 0.5);
    else
        alpha = 1.0 - smoothstep(-0.5, 0.5, d);

    if(alpha <= 0.0) discard;
    
    FragColor = vec4(uColor.rgb, uColor.a * alpha);
}
