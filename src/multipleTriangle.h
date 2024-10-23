#ifndef multipleTriangle_H_
#define multipleTriangle_H_
#include"baseInit.h"

class multipleTriangle:public baseInit {
private:
    uint32_t EBO;
public:
    multipleTriangle(/* args */);
    ~multipleTriangle();

    bool InitGlSource()override;
    void runDrawProcess()override;
    bool unInitResource();
};

#endif