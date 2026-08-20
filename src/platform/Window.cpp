#include<stdexcept>
#include<utility>
#include<iostream>
#include "core/Event.hpp"
#include "platform/Window.hpp"
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include<GLFW/glfw3.h>
using namespace std;
namespace KitDraw::platform {
    namespace{
        core::EventQueue& queueFrom(GLFWwindow* w){
            return *static_cast<core::EventQueue*>(glfwGetWindowUserPointer(w));
        }

        void onResize(GLFWwindow* w, int width, int height){
            queueFrom(w).push(core::WindowResizeEvent{width, height});
        }

        void onClose(GLFWwindow* w){
            queueFrom(w).push(core::WindowCloseEvent{});
        }

        void onKey(GLFWwindow* w, int key, int, int action, int){
            core::KeyAction a = action ==GLFW_PRESS ? core::KeyAction::Pressed: action == GLFW_RELEASE ? core::KeyAction::Released : core::KeyAction::Repeated;
            queueFrom(w).push(core::KeyEvent{key, a});
        }
        void onMouseButton(GLFWwindow* w, int button, int action, int){
            double x, y;
            glfwGetCursorPos(w, &x, &y);
            auto a = action == GLFW_PRESS ? core::MouseButtonAction::Pressed : core::MouseButtonAction::Released;
            queueFrom(w).push(core::MouseButtonEvent { button, a , x, y});
        }

        void onCursorPos(GLFWwindow* w, double x, double y){
            queueFrom(w).push(core::MouseMoveEvent{x, y});
        }

        void onScroll(GLFWwindow* w, double xoff, double yoff){
            queueFrom(w).push(core::MouseScrollEvent{xoff, yoff});
        }
    }
    Window::Window(const WindowDesc& desc, core::EventQueue& queue): queue_(&queue), _width(desc.width), _height(desc.height){
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
            return ;


        }

        glfwMakeContextCurrent(handle_);
        glfwSwapInterval(desc.vsync ? 1 : 0);
        glfwSetWindowUserPointer(handle_, queue_);
        installCallbacks(handle_);


    }

    void Window::installCallbacks(GLFWwindow* handle) {
        glfwSetFramebufferSizeCallback(handle, onResize);
        glfwSetWindowCloseCallback(handle, onClose);
        glfwSetKeyCallback(handle, onKey);
        glfwSetMouseButtonCallback(handle, onMouseButton);
        glfwSetCursorPosCallback(handle, onCursorPos);
        glfwSetScrollCallback(handle, onScroll);
    }

    Window::~Window(){
        if(handle_) glfwDestroyWindow(handle_);
    }

    Window::Window(Window&& other)noexcept:handle_(std::exchange(other.handle_, nullptr)), queue_(std::exchange(other.queue_, nullptr)), _width(other._width), _height(other._height){
        if(handle_) glfwSetWindowUserPointer(handle_, queue_);
    }

    Window& Window::operator=(Window&& other) noexcept{
        if(this != &other){
            if(handle_) glfwDestroyWindow(handle_);
            handle_ = std::exchange(other.handle_, nullptr);
            queue_ = std::exchange(other.queue_, nullptr);
            _width = other._width;
            _height = other._height;
            if(handle_) glfwSetWindowUserPointer(handle_,queue_);
        }
        return *this;
    }

    bool Window::shouldClose() const { return glfwWindowShouldClose(handle_);}
    void Window::pollEvents() { glfwPollEvents();}
    void Window::swapBuffers(){ glfwSwapBuffers(handle_);}



}// namespace KitDraw::Platform