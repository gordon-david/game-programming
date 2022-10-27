#pragma once

#include "../math/Math.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace Graphics
{

    class Renderable2D
    {
    private:
        Math::Vec3 m_Position;
        Math::Vec2 m_Size;
        Math::Vec4 m_Color;

    public:
				/*
				 * Position
				 *
				 *
				 *
				 *
				 */
        Renderable2D(Math::Vec3 position, Math::Vec2 size, Math::Vec4 color);
        ~Renderable2D();

        VertexArray* m_VertexArray;
        IndexBuffer* m_IndexBuffer;
        VertexBuffer* m_VertexBuffer;

        void Bind();

        inline const Math::Vec3 &GetPosition();
        inline const Math::Vec2 &GetSize();
        inline const Math::Vec4 &GetColor();
        unsigned int GetIndexBufferCount();
    };
}
