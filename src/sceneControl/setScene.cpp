#include"setScene.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <string>



setScene::setScene(GLFWwindow* windows_):Scene(windows_) {

}

setScene::~setScene()
{
    
}

void setScene::renderUI() {
    static char ip[16] = "127.0.0.1";      // 默认 IP 地址
    static char portStr[6] = "8080";       // 默认端口字符串（方便软键盘输入）
    static bool isSingleClickMode = false;
    static bool isServerCreated = false;
    static bool isConnected = false;
    ImGui::SetNextWindowPos(ImVec2(50, subWindHeight));
    ImGui::Begin("MyWindow", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::InputText("IP Address", ip, sizeof(ip));
    ImGui::InputText("Port", portStr, sizeof(portStr));

    // 切换输入按钮
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::Button("Switch Input", ImVec2(200, 60))) {
        activeInput = (activeInput == 0) ? 1 : 0;
    }
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImGui::Text(activeInput == 0 ? "Current: IP" : "Current: Port");

    // 显示软键盘
    if (activeInput == 0) {
        ShowVirtualKeyboard(ip, sizeof(ip));
    } else if (activeInput == 1) {
        ShowVirtualKeyboard(portStr, sizeof(portStr));
    }

    int port = atoi(portStr);

    // 单击模式按钮
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::Button("Single Click Mode", ImVec2(200, 60))) {
        isSingleClickMode = !isSingleClickMode;
    }
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImGui::Text(isSingleClickMode ? "Enabled" : "Disabled");

    // 创建服务器按钮
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::Button("Create Server", ImVec2(200, 60))) {
        isServerCreated = true;
    }
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImGui::Text(isServerCreated ? "Created" : "Not Created");

    // 连接到服务器按钮
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::Button("Connect to Server", ImVec2(200, 60))) {
        isConnected = true;
    }
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImGui::Text(isConnected ? "Connected" : "Not Connected");

    ImGui::End();
}

// 显示虚拟键盘
void setScene::ShowVirtualKeyboard(char* inputBuffer, size_t bufferSize) {
    ImGui::SetNextWindowPos(ImVec2(400, subWindHeight));
     ImGui::Begin("Virtual Keyboard", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    const char* keys = "123456789.0";  // 包含 1-9、0 和小数点
    for (int i = 0; keys[i] != '\0'; i++) {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20)); // 放大按钮
        if (ImGui::Button(std::string(1, keys[i]).c_str(), ImVec2(60, 60))) {
            size_t len = strlen(inputBuffer);
            if (len < bufferSize - 1) {
                inputBuffer[len] = keys[i];
                inputBuffer[len + 1] = '\0';
            }
        }
        ImGui::PopStyleVar();
        if ((i + 1) % 3 == 0) ImGui::NewLine();
        else ImGui::SameLine();
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::Button("Backspace", ImVec2(180, 60)) && strlen(inputBuffer) > 0) {
        inputBuffer[strlen(inputBuffer) - 1] = '\0';
    }
    ImGui::PopStyleVar();

    ImGui::End();
}


void setScene::Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void setScene::Update(float dt) {

}

void setScene::Render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderUI();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void setScene::Cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfwDestroyWindow(window);
    // glfwTerminate();
}