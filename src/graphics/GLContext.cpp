#include "GLContext.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

render::GLContext::~GLContext()
{
    destroy();
}

bool render::GLContext::create(const RendererConfig& config)
{
    if (!glfwInit()) {
        std::cerr << "[GLContext] glfwInit failed\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    this->_window = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
    if (!this->_window) {
        std::cerr << "[GLContext] glfwCreateWindow failed\n";
        glfwTerminate();
        return false;
    }

    this->_width = config.width;
    this->_height = config.height;

    glfwMakeContextCurrent(this->_window);
    glfwSwapInterval(1);
    glfwSetWindowUserPointer(this->_window, this);
    glfwSetFramebufferSizeCallback(this->_window, _framebufferSizeCallback);

    // glad2 (not glad1) API: the generated function is gladLoadGL, taking a
    // GLADloadfunc. Since the target was created without the LOADER option in
    // CMake, we still pass GLFW's proc-address function explicitly.
    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
        std::cerr << "[GLContext] gladLoadGL failed\n";
        return false;
    }

    glViewport(0, 0, this->_width, this->_height);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void render::GLContext::destroy()
{
    if (this->_window) {
        glfwDestroyWindow(this->_window);
        this->_window = nullptr;
    }
    glfwTerminate();
}

void render::GLContext::pollEvents() const
{
    glfwPollEvents();
}

void render::GLContext::swapBuffers() const
{
    glfwSwapBuffers(this->_window);
}

bool render::GLContext::shouldClose() const
{
    return this->_window == nullptr || glfwWindowShouldClose(this->_window);
}

void render::GLContext::requestClose() const
{
    if (this->_window)
        glfwSetWindowShouldClose(this->_window, GLFW_TRUE);
}

void* render::GLContext::getNativeHandle() const
{
    return this->_window;
}

void render::GLContext::_framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    auto* self = static_cast<GLContext*>(glfwGetWindowUserPointer(window));
    if (!self)
        return;

    self->_width = width;
    self->_height = height;
    glViewport(0, 0, width, height);
}
