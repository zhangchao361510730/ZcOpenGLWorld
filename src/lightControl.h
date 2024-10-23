#include"baseInit.h"


class lightControl:public baseInit
{
private:
    /* data */
public:
    lightControl(/* args */);
    ~lightControl();
    bool InitGlSource()override;
    void runDrawProcess()override; 
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void setCallBackControl(void*thiz);
};
