#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Renderer.h"
#include "graphics/Renderable2D.h"
#include "Window.h"
#include "math/Math.h"

#include "utils/fileutils.h"

int Broken()
{
	Math::Vec3 position(0.5f, 0.5f, 0.5f);
	Math::Vec2 size(0.5f, 0.5f);
	Math::Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);

	Window window("title", 800, 600);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    Graphics::Renderable2D renderable = Graphics::Renderable2D(position, size, color);

	Shader shader("res/shaders/Basic.shader");
	Graphics::Renderer renderer = Graphics::Renderer();
    renderer.AddRenderable(renderable);

	while (!window.closed())
	{
        renderer.Clear();
        shader.Bind();
        renderer.Draw();
		window.Update();
	}

    return 0;
}

int main(void)
{
return Broken();
}
