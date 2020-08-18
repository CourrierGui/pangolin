#include <pangolin/shader.hpp>
#include <iostream>

namespace pgl {

	Shader::Shader() = default;

	Shader& Shader::use() {
		glUseProgram(id);
		return *this;
	}

	void Shader::compile(
		const char* vertex_source,
		const char* fragment_source,
		const char* geomery_source)
	{
		unsigned int s_vertex, s_fragment, g_shader;

		// vertex Shader
		s_vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(s_vertex, 1, &vertex_source, NULL);
		glCompileShader(s_vertex);
		check_compile_errors(s_vertex, "VERTEX");

		// fragment Shader
		s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(s_fragment, 1, &fragment_source, NULL);
		glCompileShader(s_fragment);
		check_compile_errors(s_fragment, "FRAGMENT");

		// if geometry shader source code is given, also compile geometry shader
		if (geomery_source != nullptr) {
			g_shader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(g_shader, 1, &geomery_source, NULL);
			glCompileShader(g_shader);
			check_compile_errors(g_shader, "GEOMETRY");
		}

		// shader program
		id = glCreateProgram();
		glAttachShader(id, s_vertex);
		glAttachShader(id, s_fragment);

		if (geomery_source != nullptr)
			glAttachShader(id, g_shader);

		glLinkProgram(id);
		check_compile_errors(id, "PROGRAM");

		// delete the shaders as they're linked into our program now and no longer
		// necessery
		glDeleteShader(s_vertex);
		glDeleteShader(s_fragment);

		if (geomery_source != nullptr)
			glDeleteShader(g_shader);
	}

	void Shader::setFloat(const char *name, float value) {
		glUniform1f(glGetUniformLocation(id, name), value);
	}

	void Shader::setInteger(const char *name, int value) {
		glUniform1i(glGetUniformLocation(id, name), value);
	}

	void Shader::setVector2f(const char *name, float x, float y) {
		glUniform2f(glGetUniformLocation(id, name), x, y);
	}

	void Shader::setVector2f(const char *name, const glm::vec2 &value) {
		glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
	}

	void Shader::setVector3f(const char *name, float x, float y, float z) {
		glUniform3f(glGetUniformLocation(id, name), x, y, z);
	}

	void Shader::setVector3f(const char *name, const glm::vec3 &value) {
		glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
	}

	void Shader::setVector4f(const char *name, float x, float y, float z, float w) {
		glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
	}

	void Shader::setVector4f(const char *name, const glm::vec4 &value) {
		glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
	}

	void Shader::setMatrix4(const char *name, const glm::mat4 &matrix) {
		glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, glm::value_ptr(matrix));
	}

	void Shader::check_compile_errors(
		unsigned int object,
		const std::string& type)
	{
		int success;
		char info_log[1024];

		if (type != "PROGRAM") {
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(object, 1024, nullptr, info_log);
				std::cerr << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
					<< info_log << "\n -- --------------------------------------------------- --\n";
			}
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(object, 1024, nullptr, info_log);
				std::cerr << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
					<< info_log << "\n -- --------------------------------------------------- --\n";;
			}
		}
	}

} /* end of namespace pgl */
