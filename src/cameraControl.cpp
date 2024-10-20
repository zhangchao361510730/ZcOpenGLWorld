#include "cameraControl.h"


cameraControl::cameraControl()
{
}

cameraControl::~cameraControl()
{
}

bool cameraControl::InitGlSource()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
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

void cameraControl::processInput(GLFWwindow* window)
{
}
