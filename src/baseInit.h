#ifndef BASEINIT_H_
#define BASEINIT_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class baseInit
{
public:
	baseInit();
	~baseInit();

	virtual bool InitGlSource();
};


#endif // !BASEINIT_H_
