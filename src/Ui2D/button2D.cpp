#include"button2D.h"
#include"globaDefine.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
button2D::button2D(/* args */) {

}

button2D::~button2D() {

}

bool button2D::InitButton2D() {
    glfwSwapInterval(1); // 开启垂直同步

    // 初始化 ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    return true;
}

void button2D::runDrawProcess() {
    // 绘制按钮
    shaderSkyBox_->use();
    // 设置正交投影
    glm::mat4 projection = glm::ortho(0.0f, (float)windowsWidth, (float)windowsHeight, 0.0f);
    GLuint projLoc = glGetUniformLocation(shaderSkyBox_->attachId, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    // 绘制按钮
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void button2D::loadVertices() {
    // 顶点数据：按钮的四个角 
     vertices = {
        // 位置              // 颜色
        0.0f, 0.0f,          0.2f, 0.6f, 0.8f,  // 左下角
        1.0f, 0.0f,          0.2f, 0.6f, 0.8f,  // 右下角
        1.0f, 1.0f,          0.2f, 0.6f, 0.8f,  // 右上角
        0.0f, 1.0f,          0.2f, 0.6f, 0.8f   // 左上角
    };

    // 索引数组，指定顶点顺序
     indices = {
        0, 1, 2, // 第一个三角形
        0, 2, 3  // 第二个三角形
    };
}