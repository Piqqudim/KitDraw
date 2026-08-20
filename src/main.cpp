#include "platform/Window.hpp"
#include "Renderer/GraphicsContext.hpp"
#include "Renderer/Camera.hpp"
#include <iostream>
using namespace std;

int main(){
    try {
        KitDraw::platform::Window window(KitDraw::platform::WindowDesc{});
        KitDraw::render::GraphicsContext gfx(window);
        KitDraw::render::Camera camera;
        camera.setViewportSize(window.width(), window.height());

        while(!window.shouldClose()) {
            window.pollEvents();
            gfx.setViewport(0, 0, window.width(), window.height());
            gfx.clear(0.18f,0.18f, 0.18f, 1.0f);
            window.swapBuffers();
        }
    }
     catch (const exception& e) {
        cerr<< "Fatal error :" << e.what() << "\n";
        return 1;
    }
    return 0; 
}