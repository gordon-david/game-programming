#include <GL/glew.h>

#include <iostream>

#ifndef ERROR_H
#define ERROR_H

#ifdef _MSC_VER
#define ASSERT(x) \
  if (!(x)) __debugbreak();
#else
#define ASSERT(x) \
  if (!(x)) __builtin_trap();
#endif

#define GLCALL(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__));

static void GLClearError() {
  while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char *function, const char *file, int line) {
  bool result = true;
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] (" << error << ")"
              << " " << function << " " << file << " " << line << std::endl;

    result = false;
  }
  return result;
}

#endif
