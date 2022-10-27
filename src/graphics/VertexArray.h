#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
 private:
  unsigned int m_RendererID;

 public:
  VertexArray();
  ~VertexArray();

  void Bind() const;
  void Unbind() const;

  void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

#endif
