#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "graphics/Renderer.h"
#include "graphics/Renderable2D.h"
#include "Window.h"
#include "math/Math.h"

#include "utils/fileutils.h"

float RotateWithMouse(double mouseX, double mouseY, int windowX, int windowY)
{
    float Nx = ((mouseX / windowX) * 2) - 1;
    float Ny = (((windowY - mouseY) / windowY) * 2) - 1;
    float distance = sqrt((Nx * Nx) + (Ny * Ny));
    float result = (Ny < 0) ? acos(Nx / distance) * (180 / M_PI) : -acos(Nx / distance) * (180 / M_PI);

    return result;
}

Math::Vec2 normalizedMousePosition(double mouseX, double mouseY, int windowX, int windowY)
{
    return Math::Vec2(((mouseX / windowX) * 2) - 1, (((windowY - mouseY) / windowY) * 2) - 1);
}

int Loop()
{
    Math::Vec3 position(0.0f, 0.0f, -0.5f);
    Math::Vec2 size(0.5f, 0.5f);
    Math::Vec4 color(0.001f, 0.001f, 0.0001f, 1.0f);

    Window window("title", 800, 600);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    Graphics::Renderable2D renderable = Graphics::Renderable2D(position, size, color);

/*
TODO
    Shader();
    Renderable2D sprite(Vec3 position, Vec2 size, vec4 color, shader);

    Simple2DRenderer r()
    r.submit(sprite);
    r.flush();
*/

    Shader shader("res/shaders/Basic.shader");
    Graphics::Renderer renderer = Graphics::Renderer();
    renderer.AddRenderable(renderable);

    int windowX, windowY;
    double mouseX, mouseY;
    float theta;
    Math::Mat4 mlMatrix;
    Math::Vec3 rotationAxis = Math::Vec3(0.0f, 0.0f, 1.0f);
    Math::Vec3 translation = Math::Vec3(0.0f, 0.0f, 0.0f);
    Math::Vec2 light_pos(0.5f, 0.5f);
    shader.Bind();
    shader.SetUniformVec2("light_pos", light_pos);
    while (!window.closed())
    {
        window.getMousePosition(mouseX, mouseY);
        window.getWindowDimensions(windowX, windowY);
        theta = RotateWithMouse(mouseX, mouseY, windowX, windowY);

        shader.Bind();

        Math::Vec2 temp = normalizedMousePosition(mouseX, mouseY, windowX, windowY);
        translation.x = temp.x;
        translation.y = temp.y;

        std::cout << translation << std::endl;
        mlMatrix = Math::Mat4::translation(translation);
        shader.SetUniformMat4("ml_matrix", mlMatrix);
        shader.SetUniformVec2("mouse", temp);
        renderer.Clear();
        renderer.Draw();
        window.Update();
    }

    return 0;
}

int main(void)
{
    return Loop();
}
