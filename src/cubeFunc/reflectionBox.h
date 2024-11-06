#ifndef H_reflectionBox_H
#define H_reflectionBox_H

#include<vector>

class reflectionBox
{
private:
    /* data */
    std::vector<float>cubeVertices;
public:
    reflectionBox(/* args */);
    void loadVertices();
    ~reflectionBox();
};

#endif