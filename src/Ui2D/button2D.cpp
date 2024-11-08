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

void button2D::setGLFWwindow(GLFWwindow*windows_) {
    window = windows_;
}

bool button2D::InitButton2D() {
    glfwSwapInterval(1); // 开启垂直同步

    // 初始化 ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();

    // 设置 ImGui 样式
    ImGui::StyleColorsDark();

    // 初始化 ImGui 后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    return true;
}

void button2D::runDrawProcess() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // 绘制 ImGui 窗口
    
    ImGui::Begin("Auto-resize Window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Dancing !!!!!!!!!!");
    ImGui::Checkbox("do It", &flag);
    ImGui::End();
}

void button2D::runRender(){
        // 渲染 ImGui 绘制数据
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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