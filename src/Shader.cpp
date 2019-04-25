#include <Shader.hpp>

Shader::Shader(const char *vertexPath, const char *fragmentPath) {

  readShader(vertexPath, SHADER_TYPE::VERTEX);
  readShader(fragmentPath, SHADER_TYPE::FRAGMENT);

  compileShader();
}

// constructor using std::string
// ------------------------------------------------------------------------
Shader::Shader(const std::string vertexPath, const std::string fragmentPath) {

  readShader(vertexPath.c_str(), SHADER_TYPE::VERTEX);
  readShader(fragmentPath.c_str(), SHADER_TYPE::FRAGMENT);

  compileShader();
}

void Shader::readShader(char const *const shaderPath,
                        Shader::SHADER_TYPE type) {

  // 1. retrieve the shader source code from shaderPath
  std::string shaderCode;
  std::ifstream shaderFile;

  std::string *shaderCodePtr = nullptr;

  std::string shdrTypename;

  switch (type) {
  case Shader::SHADER_TYPE::VERTEX:
    shdrTypename = "VERTEX";
    shaderCodePtr = &(this->vertexShader);
    break;
  case Shader::SHADER_TYPE::FRAGMENT:
    shdrTypename = "FRAGMENT";
    shaderCodePtr = &(this->fragmentShader);
    break;
  case Shader::SHADER_TYPE::GEOMETRY:
    shdrTypename = "GEOMETRY";
    break;
  }

  // ensure ifstream objects can throw exceptions:
  shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    shaderFile.open(shaderPath);
    std::stringstream shaderStream;
    // read file's buffer contents into streams
    shaderStream << shaderFile.rdbuf();
    // close file handlers
    shaderFile.close();
    // convert stream into string
    shaderCode = shaderStream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::" << shdrTypename << "::FILE_NOT_SUCCESFULLY_READ"
              << std::endl;
  }

  *shaderCodePtr = shaderCode;

  return;
}

void Shader::compileShader() {
  // 2. compile shaders
  unsigned int vertex, fragment;

  // vertex shader
  GLchar const *vShdCode = this->vertexShader.c_str();

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShdCode, nullptr);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");

  // fragment Shader
  GLchar const *fShdCode = this->fragmentShader.c_str();
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShdCode, nullptr);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");

  // shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  checkCompileErrors(ID, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

// activate the shader
// ------------------------------------------------------------------------
void Shader::use() { glUseProgram(ID); }
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z,
                     float w) const {
  glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(unsigned int shader, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
      std::cout
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
      std::cout
          << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
}
