#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "graphics/Renderer.h"
#include "graphics/Renderable2D.h"
#include "Window.h"
#include "math/Math.h"

#include "utils/fileutils.h"
#include "utils/Image.h"

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

/**
 * @brief builds and binds texture to opengl, requires a window context to be created,
 *
 * @param image
 * @return unsigned int
 */
unsigned int buildTexture(Image::ImageData image)
{
    unsigned int texture;
    GLCALL(glGenTextures(1, &texture));
    GLCALL(glBindTexture(GL_TEXTURE_2D, texture)); // requires vao bound

    if (image.channels < 3 || image.channels > 4)
    {
        std::cout << "ERROR: Failed to bind image, image has unexpected number of channels" << std::endl;
    }
    if (image.channels == 3)
    {
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data));
    }
    else if (image.channels == 4)
    {
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data));
    }
    GLCALL(glGenerateMipmap(GL_TEXTURE_2D));

    return texture;
}

int Loop()
{
    Math::Vec3 position(0.0f, 0.0f, -0.5f);
    Math::Vec2 size(0.5f, 0.5f);
    Math::Vec4 color(0.001f, 0.001f, 0.0001f, 1.0f);

    Window window("title", 800, 600);
    GLCALL(glClearColor(0.8f, 0.2f, 0.2f, 1.0f));

    Graphics::Renderable2D renderable = Graphics::Renderable2D(position, size, color);

    // after context created
    Image::ImageData textureWall = Image::Load("res/textures/wall.jpg");
    Image::ImageData textureHappyFace = Image::Load("res/textures/happy_face.png");
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
    shader.Bind();

    /* Textures */
    // GLCALL(glActiveTexture(GL_TEXTURE0)); // this will ensure future texture binds are in position 0
    int texture0ID = buildTexture(textureWall);
    // GLCALL(glActiveTexture(GL_TEXTURE1)); // this will ensure future texture binds are in position 1
    int texture1ID = buildTexture(textureHappyFace);

    int windowX, windowY;
    double mouseX, mouseY;
    float theta;
    Math::Mat4 mlMatrix;
    Math::Vec3 rotationAxis = Math::Vec3(0.0f, 0.0f, 1.0f);
    Math::Vec3 translation = Math::Vec3(0.0f, 0.0f, 0.0f);
    Math::Vec2 light_pos(0.5f, 0.5f);
    shader.SetUniformVec2("light_pos", light_pos);

    /* bind sample2d uniforms */
    shader.setInt("texture0", 0);
    shader.setInt("texture1", 1);
    while (!window.closed())
    {

        window.getMousePosition(mouseX, mouseY);
        window.getWindowDimensions(windowX, windowY);
        theta = RotateWithMouse(mouseX, mouseY, windowX, windowY);

        shader.Bind();

        GLCALL(glActiveTexture(GL_TEXTURE0)); // this will ensure future texture binds are in position 0
        GLCALL(glBindTexture(GL_TEXTURE_2D, texture0ID)); // requires vao bound
        GLCALL(glActiveTexture(GL_TEXTURE1)); // this will ensure future texture binds are in position 0
        GLCALL(glBindTexture(GL_TEXTURE_2D, texture1ID)); // requires vao bound
        Math::Vec2 temp = normalizedMousePosition(mouseX, mouseY, windowX, windowY);
        translation.x = temp.x;
        translation.y = temp.y;

        mlMatrix = Math::Mat4::translation(translation);
        shader.SetUniformMat4("ml_matrix", mlMatrix);
        shader.SetUniformVec2("mouse", temp);
        renderer.Clear();
        renderer.Draw();
        window.Update();
        if (window.isKeyPressed(GLFW_KEY_Q))
        {
            window.close();
        }
    }
    return 0;
}

int main(void)
{
    return Loop();
}
