#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"baseInit.h"

class cameraTool;
class ShaderGLSLTool;

class lightControl:public baseInit
{
private:
    /* data */
	std::vector<glm::vec3> cubePositions;
	std::vector<float>vertices;
    std::vector<glm::vec3> pointLightPositions;
    uint32_t VBO, cubeVAO;
    uint32_t lightCubeVAO;
public:
    lightControl(/* args */);
    ~lightControl();
    bool InitGlSource()override;
    void runDrawProcess()override; 
    void processInput(GLFWwindow *window);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void setCallBackControl(void*thiz);
    cameraTool* camera = nullptr;
    ShaderGLSLTool* lightingShader = nullptr;
    ShaderGLSLTool* lightCubeShader = nullptr;
    uint32_t diffuseMap; 
    uint32_t specularMap;
    float lastX = windowsWidth / 2.0f;
    float lastY = windowsHeight / 2.0f;
    bool firstMouse = true;
    float deltaTime;	
    float lastFrame;
    glm::vec3 lightPos;
};
