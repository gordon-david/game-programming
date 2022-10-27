#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "../utils/Error.h"
#include "../math/Math.h"

struct ShaderProgramSource {
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader {
 private:
  std::string m_FilePath;
  unsigned int m_RendererID;
  std::unordered_map<std::string, int> m_UniformLocationCache;

 public:
  Shader(const std::string &filepath);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  /* Set a Boolean uniform */
  void setBool(const std::string &name, bool value) const;

  /* Set am Integer uniform */
  void setInt(const std::string &name, int value) const;

  /* Set a Float uniform */
  void setFloat(const std::string &name, float value) const;

  void SetUniform4f(const std::string &name, float v0, float v1, float f2,
                    float f3);

  void SetUniformMat4(const std::string &name, Math::Mat4 &matrix);
	void SetUniformVec2(const std::string &name, Math::Vec2 &vector);

 private:
  int GetUniformLocation(const std::string &name);
  unsigned int CreateShader(const std::string &vertexShader,
                            const std::string &fragmentShader);
  ShaderProgramSource ParseShader(const std::string &filepath);
  unsigned int CompileShader(unsigned int type, const std::string &source);
};

#endif
