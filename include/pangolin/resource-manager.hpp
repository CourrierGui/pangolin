#pragma once

#include <map>
#include <string>

#include <glad/glad.h>

#include <pangolin/texture.hpp>
#include <pangolin/shader.hpp>


/**
 * A static singleton ResourceManager class that hosts several
 * functions to load Textures and Shaders. Each loaded texture
 * and/or shader is also stored for future reference by string
 * handles. All functions and resources are static and no
 * public constructor is defined.
 */
class ResourceManager {
  public:
    // resource storage
    static std::map<std::string, Shader>    shaders;
    static std::map<std::string, Texture2D> textures;

    /**
     * loads (and generates) a shader program from file loading vertex,
     * fragment (and geometry) shader's source code. If g_shader_file is not
     * nullptr, it also loads a geometry shader
     */
    static Shader& load_shader(
      const char *v_shader_file,
      const char *f_shader_file,
      const char *g_shader_file,
      const std::string& name
    );

    /**
     * retrieves a stored sader
     */
    static Shader& get_shader(std::string name);

    // loads (and generates) a texture from file
    static Texture2D& load_texture(
      const char *file,
      bool alpha,
      const std::string& name
    );

    // retrieves a stored texture
    static Texture2D& get_texture(std::string name);

    // properly de-allocates all loaded resources
    static void clear();

  private:
    /**
     * private constructor, that is we do not want any actual resource manager
     * objects. Its members and functions should be publicly available
     * (static).
     */
    ResourceManager();

    // loads and generates a shader from file
    static Shader    load_shader_from_file(
      const char *vShaderFile,
      const char *fShaderFile,
      const char *gShaderFile = nullptr
    );

    // loads a single texture from file
    static Texture2D load_texture_from_file(const char *file, bool alpha);
};
