#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderGLSLTool {
public:
    uint32_t attachId;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    ShaderGLSLTool(const char* vertexPath, const char* fragmentPath);
    // activate the shader
    // ------------------------------------------------------------------------
    inline void use() 
    { 
        glUseProgram(attachId); 
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    inline void setBool(const std::string &name, bool value) const {         
        glUniform1i(glGetUniformLocation(attachId, name.c_str()), (int)value); 
    }
    
    // ------------------------------------------------------------------------
    inline void setInt(const std::string &name, int value) const { 
        glUniform1i(glGetUniformLocation(attachId, name.c_str()), value); 
    }

    // ------------------------------------------------------------------------
    inline void setFloat(const std::string &name, float value) const { 
        glUniform1f(glGetUniformLocation(attachId, name.c_str()), value); 
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif