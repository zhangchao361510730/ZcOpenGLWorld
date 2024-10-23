#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"baseInit.h"

class Camera;
class ShaderGLSLTool;

class lightControl:public baseInit
{
private:
    /* data */
	std::vector<glm::vec3> cubePositions;
	std::vector<float>vertices;
public:
    lightControl(/* args */);
    ~lightControl();
    bool InitGlSource()override;
    void runDrawProcess()override; 
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void setCallBackControl(void*thiz);
    Camera* camera = nullptr;
    ShaderGLSLTool* lightingShader = nullptr;
    ShaderGLSLTool* lightCubeShader = nullptr;
    float lastX = windowsWidth / 2.0f;
    float lastY = windowsHeight / 2.0f;
    bool firstMouse = true;
    float deltaTime;	
    float lastFrame;
    glm::vec3 lightPos;
};
