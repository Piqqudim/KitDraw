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

        int width() const noexcept { return framebufferWidth_;}
        int height() const noexcept { return framebufferHeight_;}
        GLFWwindow* handle() const noexcept{ return handle_; }


        private:
        static void onResize(GLFWwindow* w, int width, int height);
        static void onClose(GLFWwindow* w);
        static void onKey(GLFWwindow* w, int key, int scancode, int action, int mods);
        static void onMouseButton(GLFWwindow* w, int button, int action, int mods);
        static void onCursorPos(GLFWwindow* w, double x, double y);
        static void onScroll(GLFWwindow* w, double xoff, double yoff);
        static void onContentScaleChanged(GLFWwindow* w, float xscale, float yscale); 

        void installCallbacks();
        void refreshFramebufferSize();
        void refreshContentScale();

        GLFWwindow* handle_= nullptr;
        core::EventQueue* queue_ = nullptr;
        int framebufferWidth_ = 0;
        int framebufferHeight_ = 0;
        float contentScaleX_ = 1.0f;
        float contentScaleY_ = 1.0f;
    };
}// namespace windows