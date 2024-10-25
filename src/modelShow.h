#ifndef modelShow_H_
#define modelShow_H_
#include"baseInit.h"

class modelShow:public baseInit {
private:
    uint32_t EBO;
public:
    modelShow(/* args */);
    ~modelShow();

    bool InitGlSource()override;
    void runDrawProcess()override;
    bool unInitResource();
};

#endif