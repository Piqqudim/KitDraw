#include "Renderer/GraphicsContext.hpp"
#include "platform/Window.hpp"
#include "GLFW/glfw3.h"
#include <glbinding/glbinding.h>
#include <glbinding/gl33core/gl.h>

using namespace gl33core;

namespace KitDraw::render{
    GraphicsContext::GraphicsContext(platform::Window& window){
        glfwMakeContextCurrent(window.handle());
        glbinding::initialize(glfwGetProcAddress);
    }

    void GraphicsContext::setViewport(int x, int y, int width, int height){
        glViewport(x, y, width, height);
    }

    void GraphicsContext::clear(float r, float g, float b, float a){
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}// namespace KitDraw::render