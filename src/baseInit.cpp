#include"baseInit.h"
#include"globaDefine.h"

extern const char* fragmentShaderSource;
extern const char* vertexShaderSource;

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
    // vertex shader
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512] = { 0 };
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // 如果着色器语言编译错误,这里应该会显示
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);    // 顶点着色器装载程序
    glAttachShader(shaderProgram, fragmentShader);  // 片段着色器装载程序
    glLinkProgram(shaderProgram); // 链接着色器,有点像C++的程序链接
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);// 检查程序链接错误
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // 链接完毕编译的着色器就没用了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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