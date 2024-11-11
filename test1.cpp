#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <string>
#define subWindHeight 100
// 当前选中的输入框（0 表示 IP，1 表示端口）
static int activeInput = 0;  // 0 表示 IP，1 表示端口



void renderUI() {
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

int main() {
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Example", NULL, NULL);
    if (window == NULL)
        return -1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

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

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
