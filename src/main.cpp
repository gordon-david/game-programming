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
    float Nx = (((float)mouseX / (float)windowX) * 2) - 1;
    float Ny = (((windowY - mouseY) / (float)windowY) * 2) - 1;
    // float result = Nx > 0 ? acos(sqrt((Nx * Nx) + (Ny * Ny)) / Nx) : 0;
    float distance = sqrt((Nx * Nx) + (Ny * Ny));
    float result = (Ny < 0) ? acos(Nx / distance) * (180 / M_PI) : -acos(Nx / distance) * (180 / M_PI);
    // float result = asin(Ny / distance) * (180/M_PI);

    std::cout
        << Nx << ", " << Ny << std::endl
        << result << std::endl
        << std::endl;

    return result;
}

int Loop()
{
    Math::Vec3 position(0.0f, 0.0f, 0.0f);
    Math::Vec2 size(0.5f, 0.5f);
    Math::Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);

    Window window("title", 800, 600);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    Graphics::Renderable2D renderable = Graphics::Renderable2D(position, size, color);

    Shader shader("res/shaders/Basic.shader");
    Graphics::Renderer renderer = Graphics::Renderer();
    renderer.AddRenderable(renderable);

    int windowX, windowY;
    double mouseX, mouseY;
    float theta;
    Math::Mat4 rotationMatrix;
    Math::Vec3 rotationAxis = Math::Vec3(0.0f, 0.0f, 1.0f);
    while (!window.closed())
    {
        window.getMousePosition(mouseX, mouseY);
        window.getWindowDimensions(windowX, windowY);
        theta = RotateWithMouse(mouseX, mouseY, windowX, windowY);
        std::cout
            // << theta << std::endl
            << std::endl;

        shader.Bind();
        rotationMatrix = Math::Mat4::rotation(theta, rotationAxis);
        shader.SetUniformMat4("ml_matrix", rotationMatrix);
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
