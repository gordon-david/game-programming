#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/Error.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Renderable2D.h"

namespace Graphics
{
    class Renderer
    {
    private:
        std::vector<Graphics::Renderable2D> m_RenderablesQueue;

    public:
        void Clear();
        void Draw(const VertexArray &va, IndexBuffer &id,
                  const Shader &shader) const;
        void Draw();

        void AddRenderable(const Graphics::Renderable2D &renderable2D);
        void flush();
    };
}