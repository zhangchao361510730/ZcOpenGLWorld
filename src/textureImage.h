#include"baseInit.h"

class textureImage :public baseInit {
private:
    /* data */
    uint32_t EBO;
    uint32_t texture;
    uint32_t texture2;
public:
    textureImage (/* args */);
    ~textureImage ();

    bool InitGlSource()override;
    void runDrawProcess();
    bool unInitResource();
};

