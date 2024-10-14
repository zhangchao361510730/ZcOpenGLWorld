#ifndef singleTriangle_H_
#define singleTriangle_H_
#include"baseInit.h"


class singleTriangle :public baseInit
{
private:

public:
    singleTriangle(/* args */);
    ~singleTriangle();

    bool InitGlSource();
    void runDrawProcess();
    bool unInitResource();

};

#endif