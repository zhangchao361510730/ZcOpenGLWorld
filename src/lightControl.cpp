#include"lightControl.h"
#include"commonTool/shaderLanguage.h"
#include"commonTool/cameraTool.h"

lightControl::lightControl(/* args */) {
    
}

lightControl::~lightControl() {

}

bool lightControl::InitGlSource() {
	setCallbackFun_ = lightControl::setCallBackControl;

	baseInit::InitGlSource();
	    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    std::string path_fs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/camera.fs");
    std::string path_vs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/camera.vs");
    std::string path_picture = std::string(CMAKE_CURRENT_DIR).append("/pictureResource/container.jpg");
    std::string path_picture2 = std::string(CMAKE_CURRENT_DIR).append("/pictureResource/awesomeface.png");
    shaderTool_ = new ShaderGLSLTool(path_vs.c_str(), path_fs.c_str());
    return true;
}

void lightControl::runDrawProcess() {

} 

void lightControl::framebuffer_size_callback(GLFWwindow* window, int width, int height) {

}

void lightControl::mouse_callback(GLFWwindow* window, double xpos, double ypos) {

}

void lightControl::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}

void lightControl::setCallBackControl(void*thiz) {

}