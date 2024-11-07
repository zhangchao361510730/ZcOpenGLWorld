#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

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
    inline void use() const
    { 
        glUseProgram(attachId); 
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    inline void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(attachId, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    inline void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(attachId, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    inline void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(attachId, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    inline void setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(attachId, name.c_str()), 1, &value[0]); 
    }
    inline void setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(attachId, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    inline void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(attachId, name.c_str()), 1, &value[0]); 
    }
    inline void setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(attachId, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    inline void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(attachId, name.c_str()), 1, &value[0]); 
    }
    inline void setVec4(const std::string &name, float x, float y, float z, float w) const
    { 
        glUniform4f(glGetUniformLocation(attachId, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    inline void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(attachId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    inline void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(attachId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    inline void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(attachId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif