#include <pangolin/shader.hpp>

Shader::Shader(
  const std::string& vertex_path,
  const std::string& fragment_path) {

  std::stringstream vShaderStream, fShaderStream;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    vShaderFile.open(vertex_path);
    fShaderFile.open(fragment_path);
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
  }
  catch (std::ifstream::failure& e) {
    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
  }

  std::string vShaderString = vShaderStream.str();
  std::string fShaderString = fShaderStream.str();

  const char* vShaderCode = vShaderString.c_str();
  const char* fShaderCode = fShaderString.c_str();
  // 2. compile shaders
  unsigned int vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");
  // shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  checkCompileErrors(ID, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() {
  glUseProgram(ID);
}

void Shader::setInt(const std::string& name, int value) {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setBool(const std::string& name, bool value) {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); 
}

void Shader::setVec2f(const std::string& name, float v1, float v2) {
  glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2); 
}

void Shader::setFloat(const std::string& name, float value) {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setVec3(const std::string& name, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z); 
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: "
        << type << "\n"
        << infoLog
        << "\n -- --------------------------------------------------- --\n";
    }
  }
  else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: "
        << type << "\n"
        << infoLog
        << "\n -- --------------------------------------------------- --\n";
    }
  }
}
