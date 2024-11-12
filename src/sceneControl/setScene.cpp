#include"setScene.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <string>
#include <iostream>
#include"clientCon.h"
#include"serverCon.h"


setScene::setScene(GLFWwindow* windows_,uint16_t *sceneId):Scene(windows_),sceneId_(sceneId){

}

setScene::~setScene()
{
    
}

void setScene::renderUI() {

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
        if (sceneId_ != nullptr) {
            *sceneId_ = 1;
        } else {
            std::cerr << __FILE__ << " " << __LINE__ << " nullptr" << std::endl;
        }
        isSingleClickMode = !isSingleClickMode;
    }
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImGui::Text(isSingleClickMode ? "Enabled" : "Disabled");

    // 创建服务器按钮
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::Button("Create Server", ImVec2(200, 60))) {
        if (!isServerCreated) {
            isServerCreated = true;
            // 在新线程中启动服务器
            std::thread serverThread(&setScene::startServer, this);
            serverThread.detach();  // 使线程在后台运行
        }
    }
    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImGui::Text(isServerCreated ? "Created" : "Not Created");

    // 连接到服务器按钮
    // ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    // if (ImGui::Button("Connect to Server", ImVec2(200, 60))) {
    //     isConnected = true;
    // }

    // 连接到服务器按钮  std::make_shared<clientCon> clientPtr_;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::Button("Connect to Server", ImVec2(200, 60))) {
        if (!isConnected) {
            SceneManager_->clientPtr_ = std::make_shared<clientCon>(ip, std::stoi(portStr));
            SceneManager_->setClientPtr();
            isConnected = SceneManager_->clientPtr_->connectToServer();
        }
    }

    ImGui::PopStyleVar();
    ImGui::SameLine();
    ImGui::Text(isConnected ? "Connected" : "Not Connected");

    ImGui::End();
}



void setScene::setSceneManager(SceneManager * _SceneManager_) {
        SceneManager_ = _SceneManager_;
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
    strcpy(ip, "127.0.0.1");      // 设置默认 IP 地址
    strcpy(portStr, "8080");      // 设置默认端口字符串
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

void setScene::startServer() {
    // 假设 serverCon 是你创建的服务器类
    SceneManager_->serverPtr_ = std::make_shared<serverCon>(std::stoi(portStr));
    SceneManager_->setServerPtr();
    SceneManager_->serverPtr_->startServer();  // 假设 start() 是服务器启动的函数，负责监听客户端连接
}
