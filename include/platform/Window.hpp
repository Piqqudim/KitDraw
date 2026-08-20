#pragma once
#include<string>
#include "core/Event.hpp"
using namespace std;

struct GLFWwindow;

namespace KitDraw::platform {
    struct WindowDesc {
        int width = 1600;
        int height = 900;
        string title = "KitDraw";
        bool vsync = true;
        
    };

    class Window {
        public:
        explicit Window(const WindowDesc& desc, core::EventQueue& queue);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&& other) noexcept ;
        Window& operator=(Window&& other) noexcept ;

        bool shouldClose() const;
        void pollEvents();
        void swapBuffers();

        int width() const noexcept { return _width;}
        int height() const noexcept { return _height;}
        GLFWwindow* handle() const noexcept{ return handle_; }


        private:
        static void installCallbacks(GLFWwindow* handle);

        GLFWwindow* handle_= nullptr;
        core::EventQueue* queue_ = nullptr;
        int _width = 0;
        int _height = 0;
    };
}// namespace windows