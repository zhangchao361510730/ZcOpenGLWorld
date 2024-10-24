#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include"shaderLanguage.h"

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    uint32_t id;
    string type;
    string path;
};

class meshTool {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<uint32_t> indices;
    vector<Texture>      textures;
    uint32_t VAO;
    // constructor
    meshTool(vector<Vertex> vertices, vector<uint32_t> indices, vector<Texture> textures);
    // render the mesh
    void runDrawProcess(ShaderGLSLTool &shader);
private:
    // render data 
    uint32_t VBO, EBO;
    // initializes all the buffer objects/arrays
    void setupMesh();
};
#endif