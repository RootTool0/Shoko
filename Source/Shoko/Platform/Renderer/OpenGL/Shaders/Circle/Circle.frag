#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform vec4 uColor;
uniform vec2 uSize;
uniform float uThickness;

void main()
{
    vec2 uv = vUV * 2.0 - 1.0;
    float dist = length(uv);

    float pixelSize = 1.0 / min(uSize.x, uSize.y);

    float edge = 1.0;
    float alpha = 1.0 - smoothstep(edge - pixelSize, edge, dist);

    if(uThickness > 0.0)
    {
        float innerEdge = 1.0 - (uThickness * pixelSize * 2.0);
        float innerAlpha = smoothstep(innerEdge - pixelSize, innerEdge, dist);
        alpha *= innerAlpha;
    }

    if(alpha <= 0.0) discard;

    FragColor = vec4(uColor.rgb, uColor.a * alpha);
}
