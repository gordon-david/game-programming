#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class Window
{
private:
    const char *&m_Title;
    GLFWwindow *m_Window;
    bool m_Closed;

    static int m_Width, m_Height;
    static bool m_Keys[MAX_KEYS];
    static bool m_Buttons[MAX_BUTTONS];
    static double mx, my;

public:
    Window(const char *name, int width, int height);
    ~Window();
    void Update() const;
    bool closed() const;

    // TODO: do we want a singleton? Instead of these static methods?
    // static Window* INSTANCE;

    static bool isKeyPressed(unsigned int keycode);
    static void getMousePosition(double &x, double &y);
    static bool isMouseButtonPressed(unsigned int keycode);
    static void getWindowDimensions(int &width, int &height);
private:
    bool init();
    friend void key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods);
    friend void mouse_button_callback(GLFWwindow *window, int button, int action,
                                      int mods);
    friend void mouse_position_callback(GLFWwindow *window, double xpos,
                                        double ypos);
    friend void window_size_callback(GLFWwindow *window, int width, int height);
};
