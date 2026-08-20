#pragma once
#include<string>
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
        explicit Window(const WindowDesc& desc);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&& other) noexcept = delete;
        Window& operator =(Window&& other) noexcept = delete;

        bool shouldClose() const;
        void pollEvents();
        void swapBuffers();

        int width() const noexcept { return _width;}
        int height() const noexcept { return _height;}
        GLFWwindow* handle() const noexcept{ return handle_; }


        private:
        GLFWwindow* handle_= nullptr;
        int _width = 0;
        int _height = 0;
    };
}// namespace windows