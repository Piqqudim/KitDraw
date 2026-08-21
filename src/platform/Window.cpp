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

        Window* windowFrom(GLFWwindow* w){
            return static_cast<Window*>(glfwGetWindowUserPointer(w));
        }
    }   
        void Window::refreshFramebufferSize(){
            glfwGetFramebufferSize(handle_, &framebufferWidth_, &framebufferHeight_);
        }

        void Window::refreshContentScale(){
            glfwGetWindowContentScale(handle_,&contentScaleX_, &contentScaleY_);
        }
        void Window::onResize(GLFWwindow* w, int width, int height){
            auto* self = windowFrom(w);
            self->framebufferWidth_ = width;
            self-> framebufferHeight_ = height;
            queueFrom(w).push(core::WindowResizeEvent{width, height});
        }

        void Window:: onClose(GLFWwindow* w){
            queueFrom(w).push(core::WindowCloseEvent{});
        }

        void Window::onKey(GLFWwindow* w, int key, int, int action, int){
            core::KeyAction a = action ==GLFW_PRESS ? core::KeyAction::Pressed: action == GLFW_RELEASE ? core::KeyAction::Released : core::KeyAction::Repeated;
            queueFrom(w).push(core::KeyEvent{key, a});
        }
        void Window::onMouseButton(GLFWwindow* w, int button, int action, int){
           auto* self = windowFrom(w);
           double x, y;
           glfwGetCursorPos(w, &x, &y);


           x *= self->contentScaleX_;
           y*= self-> contentScaleY_;

           auto a = action == GLFW_PRESS ? core::MouseButtonAction::Pressed : core::MouseButtonAction::Released;
           queueFrom(w).push(core::MouseButtonEvent{button, a, x, y});
        }

        

        void Window::onCursorPos(GLFWwindow* w, double x, double y){
            auto* self = windowFrom(w);
            x *= self->contentScaleX_;
            y *= self->contentScaleY_;
            queueFrom(w).push(core::MouseMoveEvent{x, y});
        }

        void Window::onScroll(GLFWwindow* w, double xoff, double yoff){
            queueFrom(w).push(core::MouseScrollEvent{xoff, yoff});
        }

        void Window::onContentScaleChanged(GLFWwindow* w, float xscale, float yscale){
            auto* self = windowFrom(w);
            self->contentScaleX_ =xscale;
            self->contentScaleY_ = yscale;
            return;
        }
    
    Window::Window(const WindowDesc& desc, core::EventQueue& queue): queue_(&queue), framebufferWidth_(desc.width),framebufferHeight_(desc.height){
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

        refreshFramebufferSize();
        refreshContentScale();
        installCallbacks();


    }

    void Window::installCallbacks() {
        glfwSetFramebufferSizeCallback(handle_, onResize);
        glfwSetWindowCloseCallback(handle_, onClose);
        glfwSetKeyCallback(handle_, onKey);
        glfwSetMouseButtonCallback(handle_, onMouseButton);
        glfwSetCursorPosCallback(handle_, onCursorPos);
        glfwSetScrollCallback(handle_, onScroll);
    }

    Window::~Window(){
        if(handle_) glfwDestroyWindow(handle_);
    }

    Window::Window(Window&& other)noexcept:handle_(std::exchange(other.handle_, nullptr)), queue_(std::exchange(other.queue_, nullptr)), framebufferWidth_(other.framebufferWidth_),framebufferHeight_(other.framebufferHeight_){
        if(handle_) glfwSetWindowUserPointer(handle_, queue_);
    }

    Window& Window::operator=(Window&& other) noexcept{
        if(this != &other){
            if(handle_) glfwDestroyWindow(handle_);
            handle_ = std::exchange(other.handle_, nullptr);
            queue_ = std::exchange(other.queue_, nullptr);
            framebufferWidth_ = other.framebufferWidth_;
            framebufferHeight_= other.framebufferHeight_;
            if(handle_) glfwSetWindowUserPointer(handle_,queue_);
        }
        return *this;
    }

    bool Window::shouldClose() const { return glfwWindowShouldClose(handle_);}
    void Window::pollEvents() { glfwPollEvents();}
    void Window::swapBuffers(){ glfwSwapBuffers(handle_);}



}// namespace KitDraw::Platform