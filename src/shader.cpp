/*******************************************************************
 ** This code is part of Breakout.
 **
 ** Breakout is free software: you can redistribute it and/or modify
 ** it under the terms of the CC BY 4.0 license as published by
 ** Creative Commons, either version 4 of the License, or (at your
 ** option) any later version.
 ******************************************************************/

#include <pangolin/shader.hpp>
#include <iostream>

Shader& Shader::use() {
  glUseProgram(this->ID);
  return *this;
}

void Shader::compile(
  const char* vertexSource,
  const char* fragmentSource,
  const char* geometrySource)
{
  unsigned int sVertex, sFragment, gShader;
  // vertex Shader
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexSource, NULL);
  glCompileShader(sVertex);
  checkCompileErrors(sVertex, "VERTEX");
  // fragment Shader
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentSource, NULL);
  glCompileShader(sFragment);
  checkCompileErrors(sFragment, "FRAGMENT");
  // if geometry shader source code is given, also compile geometry shader
  if (geometrySource != nullptr) {
    gShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gShader, 1, &geometrySource, NULL);
    glCompileShader(gShader);
    checkCompileErrors(gShader, "GEOMETRY");
  }
  // shader program
  this->ID = glCreateProgram();
  glAttachShader(this->ID, sVertex);
  glAttachShader(this->ID, sFragment);

  if (geometrySource != nullptr)
    glAttachShader(this->ID, gShader);

  glLinkProgram(this->ID);
  checkCompileErrors(this->ID, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(sVertex);
  glDeleteShader(sFragment);

  if (geometrySource != nullptr)
    glDeleteShader(gShader);
}

void Shader::setFloat(const char *name, float value) {
  glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::setInteger(const char *name, int value) {
  glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::setVector2f(const char *name, float x, float y) {
  glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::setVector2f(const char *name, const glm::vec2 &value) {
  glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::setVector3f(const char *name, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::setVector3f(const char *name, const glm::vec3 &value) {
  glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const char *name, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::setVector4f(const char *name, const glm::vec4 &value) {
  glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char *name, const glm::mat4 &matrix) {
  glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
        << infoLog << "\n -- --------------------------------------------------- -- "
        << std::endl;
    }
  }
  else
  {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
        << infoLog << "\n -- --------------------------------------------------- -- "
        << std::endl;
    }
  }
}
