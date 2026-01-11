R"(
#version 330 core

in vec2 vUV;    // приходят UV из вершинного шейдера
out vec4 FragColor;

void main()
{
    // Для примера покажем UV как цвет
    FragColor = vec4(vUV, 0.0, 1.0);
}

)"
