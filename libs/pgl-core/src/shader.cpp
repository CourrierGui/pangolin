#include <pgl-core/shader.hpp>
#include <iostream>
#include <pgl-tools/logger.hpp>

namespace pgl {

    shader::shader() = default;

    shader& shader::use() {
        glUseProgram(id);
        return *this;
    }

    void shader::compile(
        const char* vertex_source,
        const char* fragment_source,
        const char* geomery_source)
    {
        unsigned int s_vertex, s_fragment, g_shader;

        // vertex shader
        s_vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(s_vertex, 1, &vertex_source, NULL);
        glCompileShader(s_vertex);
        check_compile_errors(s_vertex, "VERTEX");

        // fragment shader
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

    void shader::setvalue(const char* name, float value) {
        glUniform1f(glGetUniformLocation(id, name), value);
    }

    void shader::setvalue(const char* name, int value) {
        glUniform1i(glGetUniformLocation(id, name), value);
    }

    void shader::setvalue(const char* name, float x, float y) {
        glUniform2f(glGetUniformLocation(id, name), x, y);
    }

    void shader::setvalue(const char* name, const pgl::float2& value) {
        glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
    }

    void shader::setvalue(const char* name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(id, name), x, y, z);
    }

    void shader::setvalue(const char* name, const pgl::float3& value) {
        glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
    }

    void shader::setvalue(const char* name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
    }

    void shader::setvalue(const char* name, const pgl::float4& value) {
        glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
    }

    void shader::setvalue(const char* name, const pgl::float44& matrix) {
        //TODO check if it works
        glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, matrix.elements);
    }

    void shader::check_compile_errors(
        unsigned int object,
        const std::string& type)
    {
        char info_log[1024];
        int success;

        if (type != "PROGRAM") {
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(object, 1024, nullptr, info_log);
                pgl::error() << "Compile time error: type=" << type << '\n'
                    << info_log << '\n';
            }
        } else {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(object, 1024, nullptr, info_log);
                pgl::error() << "Link-time error: type=" << type << '\n'
                    << info_log << '\n';
            }
        }
    }

} /* end of namespace pgl */
