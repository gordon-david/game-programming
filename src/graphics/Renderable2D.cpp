#include "Renderable2D.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Graphics
{
    Renderable2D::Renderable2D(Math::Vec3 position, Math::Vec2 size, Math::Vec4 color)
    : m_Position(position), m_Size(size), m_Color(color)
    {
        float halfWidth = size.x / 2;
        float halfHeight = size.y / 2;


        float *data = new float[(3 + 4 + 2) * 4] {
            // bottom left
            -halfWidth, -halfHeight, 0.0f,
            color.x, color.y, color.z, color.w,
            0.0f, 0.0f,
            // top left
            -halfWidth, halfHeight, 0.0f,
            color.x, color.y, color.z, color.w,
            0.0f, 1.0f,
            // top right
            halfWidth, halfHeight, 0.0f,
            color.x, color.y, color.z, color.w,
            1.0f, 1.0f,
            // bottom right
            halfWidth, -halfHeight, 0.0f,
            color.x, color.y, color.z, color.w,
            1.0f, 0.0f,
        };

        unsigned int indices[] = {0, 1, 2, 2, 3, 0};

        m_VertexArray = new VertexArray();
       m_VertexBuffer = new VertexBuffer((void *)data, (3 + 4 + 2) * 4 * sizeof(float));

        VertexBufferLayout vbLayout = VertexBufferLayout();
        vbLayout.Push<float>(3); // position
        vbLayout.Push<float>(4); // color
        vbLayout.Push<float>(2); // texture coordinates

        m_VertexArray->AddBuffer(*m_VertexBuffer, vbLayout);

        m_IndexBuffer = new IndexBuffer(indices, 6);
    }

    Renderable2D::~Renderable2D()
    {
        delete m_IndexBuffer;
        delete m_VertexArray;
        delete m_VertexBuffer;
    }
    
    void Renderable2D::Bind()
    {
        m_IndexBuffer->Bind();
        m_VertexArray->Bind();
    }
    
    unsigned int Renderable2D::GetIndexBufferCount()
    {
        return m_IndexBuffer->GetCount();
    }

}
