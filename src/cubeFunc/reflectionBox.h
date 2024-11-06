#ifndef H_reflectionBox_H
#define H_reflectionBox_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class reflectionBox
{
private:
    /* data */
    std::vector<float>cubeVertices;
    uint32_t cubeVAO, cubeVBO;
public:
    bool InitReflectionBox();
    reflectionBox(/* args */);
    void loadVertices();
    ~reflectionBox();
};

#endif