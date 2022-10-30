#include "Window.h"

#include <iostream>

#include "utils/Error.h"

bool Window::m_Keys[MAX_KEYS];
bool Window::m_Buttons[MAX_BUTTONS];
double Window::mx;
double Window::my;
int Window::m_Width, Window::m_Height;

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods)
{
    Window *win = (Window *)glfwGetWindowUserPointer(window);
    win->m_Keys[key] = (action != GLFW_RELEASE);
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods)
{
    Window *win = (Window *)glfwGetWindowUserPointer(window);
    win->m_Buttons[button] = (action != GLFW_RELEASE);
}

void mouse_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    Window *win = (Window *)glfwGetWindowUserPointer(window);
    win->mx = xpos;
    win->my = ypos;
}

void window_size_callback(GLFWwindow *window, int width, int height)
{
    Window *win = (Window *)glfwGetWindowUserPointer(window);
    win->m_Height = height;
    win->m_Width = width;
    glViewport(0, 0, width, height);
}

Window::Window(const char *name, int width, int height)
    // : m_Title(name), m_Height(height), m_Width(width) {
    : m_Title(name)
{
    Window::m_Height = height;
    Window::m_Width = width;
    if (!init())
        glfwTerminate();

    for (int i = 0; i < MAX_KEYS; i++)
        m_Keys[i] = false;

    for (int i = 0; i < MAX_BUTTONS; i++)
        m_Buttons[i] = false;
}

Window::~Window() { glfwTerminate(); }

void Window::Update() const
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

bool Window::init()
{
    GLCALL(int status = glfwInit());
    if (!status)
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        std::cout << "Failed to create GLFW Window!" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    glfwSetWindowUserPointer(m_Window, this);

    glfwSetWindowSizeCallback(m_Window, window_size_callback);
    glfwSetKeyCallback(m_Window, key_callback);
    glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
    glfwSetCursorPosCallback(m_Window, mouse_position_callback);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Could not initialize GLEW!" << std::endl;
        return false;
    }

    GLCALL(std::cout << glGetString(GL_VERSION) << std::endl);
    return true;
}

bool Window::closed() const { return glfwWindowShouldClose(m_Window); }

void Window::close()
{
    glfwDestroyWindow(m_Window);
}

bool Window::isKeyPressed(unsigned int keycode)
{
    if (keycode >= MAX_KEYS)
    {
        std::cout << "Error: keycode input beyond MAX_KEYS" << std::endl;
        return false;
    }

    return m_Keys[keycode];
}

void Window::getMousePosition(double &x, double &y)
{
    x = mx;
    y = my;
}

bool Window::isMouseButtonPressed(unsigned int button)
{
    if (button >= MAX_BUTTONS)
    {
        std::cout << "Error: keycode input beyond MAX_BUTTONS" << std::endl;
        return false;
    }

    return m_Buttons[button];
}

void Window::getWindowDimensions(int &width, int &height)
{
    width = m_Width;
    height = m_Height;
}
