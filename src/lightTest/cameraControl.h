#ifndef cameraControl_H_
#define cameraControl_H_

#include"baseInit.h"
#include"glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"glm/gtc/matrix_transform.hpp"

class cameraControl:public baseInit {
public:
	cameraControl();
	~cameraControl();
	bool InitGlSource()override;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void setCallBackControl(void*thiz);
	void processInput(GLFWwindow* window);
    void runDrawProcess()override;
    bool unInitResource();
private:
	std::vector<glm::vec3> cubePositions;
	std::vector<float>vertices;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	bool firstMouse ;
	float yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch;
	float lastX;
	float lastY;
	float fov;
	// timing
	float deltaTime;	// time between current frame and last frame
	float lastFrame;

    uint32_t EBO;
    uint32_t texture1;
    uint32_t texture2;
};


#endif // !cameraControl_H_


