#include <pangolin/resource-manager.hpp>
#include <pgl-image/image-loader.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

namespace pgl {
	// Instantiate static variables
	std::map<std::string, Texture2D> ResourceManager::textures;
	std::map<std::string, Shader>    ResourceManager::shaders;
	std::string                      ResourceManager::root;

	void set_root(const std::string& path) {
		unsigned int size = path.size();
		if (path.back() == '/')
			size = path.length()-1;

		ResourceManager::root = path.substr(0, size);
	}

	const std::string& root() {
		return ResourceManager::root;
	}

	ResourceManager::ResourceManager() {}

	Shader& ResourceManager::load_shader(
		const std::string& v_shader_file,
		const std::string& f_shader_file,
		const std::string& g_shader_file,
		const std::string& name)
	{
		shaders[name] = load_shader_from_file(v_shader_file, f_shader_file, g_shader_file);
		return shaders[name];
	}

	Shader& ResourceManager::get_shader(const std::string& name) {
		return shaders[name];
	}

	Texture2D& ResourceManager::load_texture(
		const std::string& file,
		bool alpha,
		const std::string& name)
	{
		textures[name] = load_texture_from_file(file, alpha);
		return textures[name];
	}

	Texture2D& ResourceManager::get_texture(const std::string& name) {
		return textures[name];
	}

	void ResourceManager::clear() {
		// (properly) delete all shaders
		for (auto iter : shaders)
			glDeleteProgram(iter.second.id);
		// (properly) delete all textures
		for (auto iter : textures)
			glDeleteTextures(1, &iter.second.id);
	}

	Shader ResourceManager::load_shader_from_file(
		const std::string& v_shader_file,
		const std::string& f_shader_file,
		const std::string& g_shader_file)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertex_code;
		std::string fragment_code;
		std::string geometry_code;

		try {
			// open files
			std::ifstream vertex_shader_file(v_shader_file);
			std::ifstream fragment_shader_file(f_shader_file);
			std::stringstream v_shader_stream, f_shader_stream;

			// read file's buffer contents into streams
			v_shader_stream << vertex_shader_file.rdbuf();
			f_shader_stream << fragment_shader_file.rdbuf();

			// close file handlers
			vertex_shader_file.close();
			fragment_shader_file.close();

			// convert stream into string
			vertex_code = v_shader_stream.str();
			fragment_code = f_shader_stream.str();

			// if geometry shader path is present, also load a geometry shader
			if (g_shader_file.empty()) {
				std::ifstream geometry_shader_file(g_shader_file);
				std::stringstream g_shader_stream;
				g_shader_stream << geometry_shader_file.rdbuf();
				geometry_shader_file.close();
				geometry_code = g_shader_stream.str();
			}

		} catch (const std::exception& e) {
			std::cerr << "ERROR::SHADER: Failed to read shader files\n";
		}
		const char *v_shader_code = vertex_code.c_str();
		const char *f_shader_code = fragment_code.c_str();
		const char *g_shader_code = geometry_code.c_str();
		// 2. now create shader object from source code
		Shader shader;
		shader.compile(
			v_shader_code, f_shader_code,
			!g_shader_file.empty() ? g_shader_code : nullptr
			);
		return shader;
	}

	Texture2D ResourceManager::load_texture_from_file(
		const std::string& file,
		bool alpha)
	{
		// create texture object
		Texture2D texture;
		if (alpha) {
			texture.internal_format = GL_RGBA;
			texture.image_format = GL_RGBA;
		}

		// load image
		pgl::Image image = image::load_image(file);
		/* unsigned char* data = stbi_load(file.c_str(), &width, &height, &nb_channels, 0); */

		// now generate texture
		texture.generate(image);
		return texture;
	}
} /* end of namespace pgl */
