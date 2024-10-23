#ifndef singleTriangle_H_
#define singleTriangle_H_
#include"baseInit.h"


class singleTriangle :public baseInit
{
private:

public:
    singleTriangle(/* args */);
    ~singleTriangle();

    bool InitGlSource()override;
    void runDrawProcess()override;
    bool unInitResource();

};

#endif