#include <pangolin/model.hpp>

namespace pgl {

Model::Model(const std::string& path) {
  load_model(path);
}

void Model::draw(resources::Shader& shader) {
  for (auto& mesh: meshes) {
    mesh.draw(shader);
  }
}

void Model::load_model(const std::string& path) {
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(
    path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene
      || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
      || !scene->mRootNode) {
    std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
    return;
  }

  directory = path.substr(0, path.find_last_of('/'));
  process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode* node, const aiScene* scene) {
  for (unsigned int i=0; i<node->mNumMeshes; ++i) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(process_mesh(mesh, scene));
  }

  for (unsigned int i=0; i<node->mNumChildren; ++i) {
    process_node(node->mChildren[i], scene);
  }
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene) {
  std::vector<Vertex>       vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture>      textures;

  for (unsigned int i=0; i<mesh->mNumVertices; ++i) {
    Vertex vertex;
    vertex.position.x = mesh->mVertices[i].x;
    vertex.position.y = mesh->mVertices[i].y;
    vertex.position.z = mesh->mVertices[i].z;

    vertex.normal.x = mesh->mNormals[i].x;
    vertex.normal.y = mesh->mNormals[i].y;
    vertex.normal.z = mesh->mNormals[i].z;

    if(mesh->mTextureCoords[0]) {
      vertex.tex_coords.x = mesh->mTextureCoords[0][i].x;
      vertex.tex_coords.y = mesh->mTextureCoords[0][i].y;
    }
    else
      vertex.tex_coords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);
  }

  for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for(unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  if(mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    //TODO: y'a des copies...
    std::vector<Texture> diffuseMaps = load_material_textures(
      material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = load_material_textures(
      material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  }
  return Mesh(vertices, indices, textures);
}

auto Model::load_material_textures(
  aiMaterial* material,
  aiTextureType type,
  const std::string& name)
  -> std::vector<Texture>
{
  std::vector<Texture> textures;
  for(unsigned int i=0; i<material->GetTextureCount(type); ++i) {
    aiString str;
    material->GetTexture(type, i, &str);
    std::string file = (std::string)str.C_Str();

    bool found = false;
    auto it = loaded_textures.begin();
    for (;it!=loaded_textures.end(); ++it) {
      if (it->name == file) {
        found = true;
        break;
      }
    }
    if (!found) {
      Texture texture;
      texture.id = TextureFromFile(file, directory);
      texture.type = name;
      texture.name = file;
      textures.push_back(texture);
      loaded_textures.push_back(texture);
    } else {
      textures.push_back(*it);
    }
  }
  return textures;
}

unsigned int TextureFromFile(
  const std::string& path,
  const std::string& directory,
  bool gamma)
{
  std::string filename = directory + '/' + path;

  unsigned int texture_id;
  glGenTextures(1, &texture_id);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(
    filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(
      GL_TEXTURE_2D, 0, format, width, height,
      0, format, GL_UNSIGNED_BYTE, data
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else {
    std::cerr << "Texture failed to load at path: " << path << '\n';
    stbi_image_free(data);
  }

  return texture_id;
}

} /* end of namespace pgl */
