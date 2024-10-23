#include"lightControl.h"
#include"commonTool/cameraTool.h"
#include"commonTool/shaderLanguage.h"


lightControl::lightControl(/* args */) {
    
}

lightControl::~lightControl() {

}

void lightControl::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
}

bool lightControl::InitGlSource() {
	setCallbackFun_ = lightControl::setCallBackControl;
	baseInit::InitGlSource();
    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    std::string path_fs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/basic_lighting.fs");
    std::string path_vs = std::string(CMAKE_CURRENT_DIR).append("/glslFile/basic_lighting.vs");
    std::string path_fs_cube = std::string(CMAKE_CURRENT_DIR).append("/glslFile/light_cube.fs");
    std::string path_vs_cube = std::string(CMAKE_CURRENT_DIR).append("/glslFile/light_cube.vs");
    // build and compile our shader zprogram
    lightingShader = new ShaderGLSLTool(path_vs.c_str(),path_fs.c_str());
    lightCubeShader = new ShaderGLSLTool(path_vs_cube.c_str(),path_fs_cube.c_str());
    camera = new cameraTool(glm::vec3(0.0f, 0.0f, 3.0f));
    lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    vertices = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    diffuseMap = loadTexture(FileSystem::getPath("resources/textures/container2.png").c_str());
    specularMap = loadTexture(FileSystem::getPath("resources/textures/container2_specular.png").c_str());

    // shader configuration
    // --------------------
    lightingShader->use();
    lightingShader->setInt("material.diffuse", 0);
    lightingShader->setInt("material.specular", 1);

    return true;
}

void lightControl::runDrawProcess() {
    // render loop
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader->use();
        lightingShader->setVec3("viewPos", camera->Position);
        lightingShader->setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index 
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        lightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        lightingShader->setVec3("pointLights[0].position", pointLightPositions[0]);
        lightingShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat("pointLights[0].constant", 1.0f);
        lightingShader->setFloat("pointLights[0].linear", 0.09f);
        lightingShader->setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        lightingShader->setVec3("pointLights[1].position", pointLightPositions[1]);
        lightingShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat("pointLights[1].constant", 1.0f);
        lightingShader->setFloat("pointLights[1].linear", 0.09f);
        lightingShader->setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        lightingShader->setVec3("pointLights[2].position", pointLightPositions[2]);
        lightingShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat("pointLights[2].constant", 1.0f);
        lightingShader->setFloat("pointLights[2].linear", 0.09f);
        lightingShader->setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        lightingShader_>setVec3("pointLights[3].position", pointLightPositions[3]);
        lightingShader_>setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader_>setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader_>setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lightingShader_>setFloat("pointLights[3].constant", 1.0f);
        lightingShader_>setFloat("pointLights[3].linear", 0.09f);
        lightingShader_>setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        lightingShader->setVec3("spotLight.position", camera->Position);
        lightingShader->setVec3("spotLight.direction", camera->Front);
        lightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat("spotLight.constant", 1.0f);
        lightingShader->setFloat("spotLight.linear", 0.09f);
        lightingShader->setFloat("spotLight.quadratic", 0.032f);
        lightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));     

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        // render containers
        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

         // also draw the lamp object(s)
         lightCubeShader.use();
         lightCubeShader.setMat4("projection", projection);
         lightCubeShader.setMat4("view", view);
    
         // we now draw as many light bulbs as we have point lights.
         glBindVertexArray(lightCubeVAO);
         for (unsigned int i = 0; i < 4; i++)
         {
             model = glm::mat4(1.0f);
             model = glm::translate(model, pointLightPositions[i]);
             model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
             lightCubeShader.setMat4("model", model);
             glDrawArrays(GL_TRIANGLES, 0, 36);
         }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
} 

void lightControl::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void lightControl::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    lightControl* thiz = (lightControl*)glfwGetWindowUserPointer(window);
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    
    if (thiz->firstMouse) {
        thiz->lastX = xpos;
        thiz->lastY = ypos;
        thiz->firstMouse = false;
    }

    float xoffset = xpos - thiz->lastX;
    float yoffset = thiz->lastY - ypos; // reversed since y-coordinates go from bottom to top

    thiz->lastX = xpos;
    thiz->lastY = ypos;

    thiz->camera->ProcessMouseMovement(xoffset, yoffset);
}

void lightControl::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    lightControl* thiz = (lightControl*)glfwGetWindowUserPointer(window);
    thiz->camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void lightControl::setCallBackControl(void*thiz) {
	lightControl* thiz_ = (lightControl*)thiz;
    if (thiz_ == nullptr) {
        std::cerr<<__FILE__<<" thiz_ is nullptr"<<std::endl;
    }
    glfwSetFramebufferSizeCallback(thiz_->window, lightControl::framebuffer_size_callback);
    glfwSetCursorPosCallback(thiz_->window, lightControl::mouse_callback);
    glfwSetScrollCallback(thiz_->window, lightControl::scroll_callback);
    glfwSetInputMode(thiz_->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}