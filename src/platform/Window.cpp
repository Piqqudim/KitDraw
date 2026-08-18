#include<GLFW/glfw3.h>
#include<stdexcept>
#include<utility>
#include "platform/Window.hpp"
#include<iostream>
using namespace std;
namespace KitDraw::platform {
    Window::Window(const WindowDesc& desc): _width(desc.width), _height(desc.height){
        static bool glfwInitiated = false;
        if(!glfwInitiated){
            if(!glfwInit()) cout<< "Failed to initialize GLFW\n" ;
            glfwInitiated = true;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);
    #endif

        handle_ = glfwCreateWindow(desc.width, desc.height, desc.title.c_str(), nullptr, nullptr);
        if(!handle_){
            cerr<< "Failed to create GLFW window";
            glfwTerminate();
            return -1;


        }

        glfwMakeContextCurrent(handle_);
        glfwSwapInterval(desc.vsync ? 1 : 0);
        glfwSetWindowUserPointer(handle_, this);

        glfwSetFramebufferSizeCallback(handle_ , [](GLFWwindow* window, int width, int height){
            auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            self->_width = width;
            self-> _height = height;
        });

    }

    Window::~Window(){
        if(handle_) glfwDestroyWindow(handle_);
    }

    bool Window::shouldClose() const { return glfwWindowShouldClose(handle_);}
    void Window::pollEvents() { glfwPollEvents();}
    void Window::swapBuffers(){ glfwSwapBuffers(handle_);}



}// namespace KitDraw::Platform