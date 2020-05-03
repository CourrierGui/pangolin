#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include <pangolin/mesh.hpp>
#include <pangolin/shader.hpp>

#include <glm/glm.hpp>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const std::string& path, const std::string &directory, bool gamma=false);

class Model {
  public:
    Model(const std::string& path);
    void draw(Shader& shader);

  private:
    std::vector<Texture> loaded_textures;
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    auto loadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& name)
      -> std::vector<Texture>;
};
