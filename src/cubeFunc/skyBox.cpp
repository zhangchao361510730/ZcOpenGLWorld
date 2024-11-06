#include"skyBox.h"
#include"stb_image.h"
#include<string>

skyBox::skyBox(/* args */)
{
}

skyBox::~skyBox()
{
}

void skyBox::setCameraPtr(cameraTool* camera_) {
    this->camera_ = camera_;
}

bool skyBox::initSkyBox() {
    std::string SkyBoxPath_fs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/skybox.fs");
    std::string SkyBoxPath_vs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/skybox.vs");

    loadSkyVertices();
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size()*sizeof(float), skyboxVertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    std::vector<std::string> faces {
        std::string(CMAKE_CURRENT_DIR).append("/pictureResource/skybox/right.jpg"),
        std::string(CMAKE_CURRENT_DIR).append("/pictureResource/skybox/left.jpg"),
        std::string(CMAKE_CURRENT_DIR).append("/pictureResource/skybox/top.jpg"),
        std::string(CMAKE_CURRENT_DIR).append("/pictureResource/skybox/bottom.jpg"),
        std::string(CMAKE_CURRENT_DIR).append("/pictureResource/skybox/front.jpg"),
        std::string(CMAKE_CURRENT_DIR).append("/pictureResource/skybox/back.jpg")
    };

    cubemapTexture = loadCubemap(faces);
    shaderSkyBox_ = new ShaderGLSLTool(SkyBoxPath_vs.c_str(),SkyBoxPath_fs.c_str());

    shaderSkyBox_->use();
    shaderSkyBox_->setInt("skybox", 0);
    return true;
}

void skyBox::runDrawProcess(glm::mat4 &view,glm::mat4 &projection) {
    glDepthFunc(GL_LEQUAL); 
    shaderSkyBox_->use();
    view = glm::mat4(glm::mat3(camera_->GetViewMatrix())); // remove translation from the view matrix
    shaderSkyBox_->setMat4("view", view);
    shaderSkyBox_->setMat4("projection", projection);
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

void skyBox::unInitResource() {
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    glDeleteProgram(shaderSkyBox_->attachId);
}

uint32_t skyBox::loadCubemap(std::vector<std::string> &faces) {
    uint32_t textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (uint32_t i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    
    //  缩小过滤器 与  放大过滤器 都设置为线性过滤
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

/*
GL_TEXTURE_CUBE_MAP：指明操作的是立方体贴图纹理。
GL_TEXTURE_WRAP_S：表示设置的是 S轴方向的包裹方式，即纹理坐标的横向-纵向-深度-处理方式。
GL_CLAMP_TO_EDGE：表示纹理坐标超出范围时，纹理会被 固定为边缘的像素值，避免出现拉伸或重复纹理的效果。通常用于避免纹理接缝的现象。
*/
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void skyBox::loadSkyVertices() {
    skyboxVertices = {     
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
}