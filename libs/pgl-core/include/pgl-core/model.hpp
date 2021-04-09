#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include <pangolin/mesh.hpp>
#include <pangolin/shader.hpp>
#include <pgl-math/impl/vector.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace pgl {
  namespace render3D {

    unsigned int TextureFromFile(
      const std::string& path,
      const std::string &directory, bool gamma=false
      );

    class Model {
      public:
        Model(const std::string& path);
        void draw(Shader& shader);

      private:
        std::vector<Texture> loaded_textures;
        std::vector<Mesh>    meshes;
        std::string          directory;

        void load_model(const std::string& path);
        void process_node(aiNode* node, const aiScene* scene);
        Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
        auto load_material_textures(
          aiMaterial* material,
          aiTextureType type,
          const std::string& name)
          -> std::vector<Texture>;
    };

  } /* end of namespace render3D */
} /* end of namespace pgl */
