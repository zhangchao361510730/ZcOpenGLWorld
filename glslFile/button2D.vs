#version 330 core
layout(location = 0) in vec2 aPos; // 输入顶点坐标
layout(location = 1) in vec3 aColor; // 输入颜色

out vec3 ourColor; // 输出颜色

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(aPos, 0.0, 1.0); // 将顶点坐标传给片段着色器
    ourColor = aColor;
}
