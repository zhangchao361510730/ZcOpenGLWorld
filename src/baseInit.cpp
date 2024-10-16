#include"baseInit.h"
#include"globaDefine.h"
#include"GLLSTool/shaderLanguage.h"
#include<string>

baseInit::baseInit():gen(std::random_device{}()) {

}

baseInit::~baseInit() {

}

bool baseInit::InitGlSource() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    std::string path_fs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/shader.fs");
    std::string path_vs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/shader.vs");
    
    window = glfwCreateWindow(windowsWidth, windowsHeight, "jojoOpenGl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, baseInit::framebuffer_size_callback);
    // 这类似一个函数指针绑定，只不过还强制转化了一下
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glfwSetWindowUserPointer(window, (void*)this);
    shaderTool_ = new ShaderGLSLTool(path_vs.c_str(),path_fs.c_str());
    // vertex shader
	return true;
}

void baseInit::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void  baseInit::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    baseInit* thiz = (baseInit*)glfwGetWindowUserPointer(window);
    glViewport(0, 0, width, height);
    std::uniform_real_distribution<float> dis(0.0f, 1.0f); // 定义均匀分布范围
    thiz->r = dis(thiz->gen);
    thiz->b = dis(thiz->gen);
    thiz->g = dis(thiz->gen);
    thiz->a = dis(thiz->gen);
}