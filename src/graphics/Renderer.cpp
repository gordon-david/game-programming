#include "Renderer.h"
namespace Graphics
{
    void Renderer::Draw(const VertexArray &va, IndexBuffer &ib,
                        const Shader &shader) const
    {
        shader.Bind();
        va.Bind();
        ib.Bind();

        GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer::Clear() { GLCALL(glClear(GL_COLOR_BUFFER_BIT)); }

    void Renderer::AddRenderable(const Graphics::Renderable2D &renderable2D)
    {
        m_RenderablesQueue.push_back(renderable2D);
    }

    void Renderer::flush()
    {
        m_RenderablesQueue.clear();
    }

    void Renderer::Draw()
    {
        for (int i = 0; i < m_RenderablesQueue.size(); i++)
        {
            m_RenderablesQueue[i].Bind();
            unsigned int count = m_RenderablesQueue[i].m_IndexBuffer->GetCount();
            count += 1;
            count -= 1;
            GLCALL(glDrawElements(GL_TRIANGLES, m_RenderablesQueue[i].m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
        }
    }
}