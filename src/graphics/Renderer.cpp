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
        /* TODO
        // Dequeue<Renderable>
        while(renderables.not_empty())
            bind vao, ibo, shader // attatch shader reference to renderable, association so 'reference', shader lifecycle dealt with elsewhere
            draw
            unbind all
            pop_front(); // removed from queue
        */
       while(!m_RenderablesQueue.empty())
       {
        Renderable2D renderable = m_RenderablesQueue.back();
        renderable.m_IndexBuffer -> Bind();
        renderable.m_VertexArray -> Bind();
        renderable.m_VertexBuffer -> Bind();
        GLCALL(glDrawElements(GL_TRIANGLES, renderable.m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
        renderable.m_IndexBuffer -> Unbind();
        renderable.m_VertexArray -> Unbind();
        renderable.m_VertexBuffer -> Unbind();
        m_RenderablesQueue.pop_back();
       }
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