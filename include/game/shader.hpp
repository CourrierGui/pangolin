#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

class Shader {
  private:
    void checkCompileErrors(unsigned int shader, const std::string& type);

  public:
    int ID;
    Shader(const std::string& vertex_path, const std::string& fragment_path);
    void use();
    void setInt(const std::string& name, int value);
    void setBool(const std::string& name, bool value);
    void setFloat(const std::string& name, float value);
    void setVec2f(const std::string& name, float v1, float v2);
    void setMat4(const std::string& name, const glm::mat4& value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec3(const std::string& name, float x, float y, float z);
};
