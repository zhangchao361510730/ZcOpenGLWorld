#include "cameraControl.h"


cameraControl::cameraControl()
{
}

cameraControl::~cameraControl()
{
}

bool cameraControl::InitGlSource()
{
	setCallbackFun_ = cameraControl::setCallBackControl;
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	bool firstMouse = true;
	yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch = 0.0f;
	lastX = 800.0f / 2.0;
	lastY = 600.0 / 2.0;
	fov = 45.0f;
	// timing
	deltaTime = 0.0f;	// time between current frame and last frame
	lastFrame = 0.0f;


	return false;
}

void cameraControl::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
}

void cameraControl::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
}

void cameraControl::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

void cameraControl::setCallBackControl(void*thiz) {
	cameraControl* thiz_ = (cameraControl*)thiz;
    glfwSetCursorPosCallback(thiz_->window, cameraControl::mouse_callback);
    glfwSetScrollCallback(thiz_->window, cameraControl::scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(thiz_->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void cameraControl::processInput(GLFWwindow* window)
{
}


