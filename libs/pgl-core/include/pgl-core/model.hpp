#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include <pgl-core/mesh.hpp>
#include <pgl-core/shader.hpp>
#include <pgl-math/impl/vector.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace pgl {
    namespace _3D {

        unsigned int texture_from_file(const std::string& path,
                                       const std::string &directory,
                                       bool gamma=false);

        class model {
            public:
                model(const std::string& path);
                void draw(Shader& shader);

            private:
                std::vector<texture> _loaded_textures;
                std::vector<mesh>    _meshes;
                std::string          _directory;

                void load_model(const std::string& path);
                void process_node(aiNode* node, const aiScene* scene);
                mesh process_mesh(aiMesh* mesh, const aiScene* scene);

                auto load_material_textures(aiMaterial* material,
                                            aiTextureType type,
                                            const std::string& name)
                    -> std::vector<texture>;
        };

    } /* end of namespace render3D */
} /* end of namespace pgl */
