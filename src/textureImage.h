#include"baseInit.h"

class textureImage :public baseInit {
private:
    /* data */
    uint32_t EBO;
public:
    textureImage (/* args */);
    ~textureImage ();

    bool InitGlSource()override;
    void runDrawProcess();
    bool unInitResource();
};

