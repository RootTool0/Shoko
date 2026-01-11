R"(
#version 330 core
layout(location = 0) in vec2 aPos;

out vec2 vUV; // передаём UV во фрагментный шейдер

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);

    // Переводим позицию квадрата (0..1) в UV
    // Предположим, что твой quad в локальных координатах 0..1
    vUV = aPos; 
}
)"
