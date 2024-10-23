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
};
