#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include"meshTool.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
class loadModelTool
{
private:
    /* data */
public:

    ~loadModelTool();

    // model data 
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<meshTool>    meshes;
    std::string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    loadModelTool(std::string const &path, bool gamma = false);

    // draws the model, and thus all its meshes
    void runDrawProcess(ShaderGLSLTool &shader);

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);
    meshTool processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

    uint32_t TextureFromFile(const char *path, const string &directory, bool gamma = false);
};
