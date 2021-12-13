#include <pgl-core/model.hpp>
#include <pgl-tools/logger.hpp>
#include <stb_image.h>

namespace pgl::_3D {

        model::model(const std::string& path)
        {
            load_model(path);
        }

        void model::draw(shader& shader)
        {
            for (auto& mesh: _meshes) {
                mesh.draw(shader);
            }
        }

        void model::load_model(const std::string& path)
        {
            Assimp::Importer importer;
            const aiScene* scene =
                importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

            if (!scene
                || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
                || !scene->mRootNode) {
                pgl::error() << "Assimp: " << importer.GetErrorString() << '\n';
                return;
            }

            _directory = path.substr(0, path.find_last_of('/'));
            process_node(scene->mRootNode, scene);
        }

        void model::process_node(aiNode* node, const aiScene* scene)
        {
            for (unsigned int i=0; i<node->mNumMeshes; ++i) {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                _meshes.push_back(process_mesh(mesh, scene));
            }

            for (unsigned int i = 0; i<node->mNumChildren; ++i)
                process_node(node->mChildren[i], scene);
        }

        mesh model::process_mesh(aiMesh* mesh, const aiScene* scene)
        {
            std::vector<vertex>       vertices;
            std::vector<unsigned int> indices;
            std::vector<texture>      textures;

            for (unsigned int i=0; i<mesh->mNumVertices; ++i) {
                vertex v;
                v.position.x = mesh->mVertices[i].x;
                v.position.y = mesh->mVertices[i].y;
                v.position.z = mesh->mVertices[i].z;

                v.normal.x = mesh->mNormals[i].x;
                v.normal.y = mesh->mNormals[i].y;
                v.normal.z = mesh->mNormals[i].z;

                if(mesh->mTextureCoords[0]) {
                    v.tex_coords.x = mesh->mTextureCoords[0][i].x;
                    v.tex_coords.y = mesh->mTextureCoords[0][i].y;
                } else {
                    v.tex_coords = pgl::float2(0.0f, 0.0f);
                }
                vertices.push_back(v);
            }

            for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
                aiFace face = mesh->mFaces[i];
                for(unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }

            if(mesh->mMaterialIndex > 0) {
                aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

                auto diffuseMaps = load_material_textures(material, aiTextureType_DIFFUSE,
                                                          texture::_type::diffuse);
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

                auto specularMaps = load_material_textures(material, aiTextureType_SPECULAR,
                                                           texture::_type::specular);

                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            }
            return {vertices, indices, textures};
        }

        auto model::load_material_textures(aiMaterial* material,
                                           aiTextureType type,
                                           texture::_type _type)
            -> std::vector<texture>
        {
            std::vector<texture> textures;

            for(unsigned int i=0; i < material->GetTextureCount(type); ++i) {
                aiString str;
                material->GetTexture(type, i, &str);

                bool found = false;
                for (const auto& t: _loaded_textures) {
                    if (!std::strcmp(t.name.data(), str.C_Str())) {
                        found = true;
                        textures.push_back(t);
                        break;
                    }
                }

                if (!found) {
                    texture t;

                    t.id = texture_from_file(str.C_Str(), _directory);
                    t.type = _type;
                    t.name = str.C_Str();

                    textures.push_back(t);
                    _loaded_textures.push_back(t);
                }
            }
            return textures;
        }

        unsigned int texture_from_file(const std::string& path,
                                       const std::string& directory,
                                       [[maybe_unused]]bool gamma)
        {
            std::string filename = directory + '/' + path;

            unsigned int texture_id;
            glGenTextures(1, &texture_id);

            int width, height, nrComponents;
            unsigned char *data = stbi_load(filename.c_str(), &width, &height,
                                            &nrComponents, 0);

            if (data) {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                glBindTexture(GL_TEXTURE_2D, texture_id);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
                             0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                stbi_image_free(data);

            } else {
                pgl::error() << "failed to load texture " << path << '\n';
                stbi_image_free(data);
            }

            return texture_id;
        }

} /* end of namespace pgl::_3D */
