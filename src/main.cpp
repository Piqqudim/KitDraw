#include "platform/Window.hpp"
#include "Renderer/GraphicsContext.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/BrushRenderer.hpp"
#include "Renderer/Renderer.hpp"
#include <iostream>
using namespace std;

int main(){
    try {
        KitDraw::platform::Window window(KitDraw::platform::WindowDesc{});
        KitDraw::render::GraphicsContext gfx(window);
        KitDraw::render::Camera camera;
        camera.setViewportSize(window.width(), window.height());

        KitDraw::render::Layer canvas(1920, 1080);
        canvas.bind();
        canvas.clearToOpaqueColor({1.0f, 1.0f, 1.0f, 1.0f});
        canvas.unbind();
        camera.reset({960.0f, 540.0f});

        KitDraw::render::Renderer renderer;
        KitDraw::render::BrushRenderer brushRenderer;

        canvas.bind();
        gfx.setViewport(0, 0, canvas.width(), canvas.height());
    
        canvas.unbind();
       

        while(!window.shouldClose()) {
            window.pollEvents();
            gfx.setViewport(0, 0, window.width(), window.height());
            
            gfx.clear(0.18f,0.18f, 0.18f, 1.0f);
            renderer.drawCanvas(canvas,camera);
            brushRenderer.stampDab(canvas.width(), canvas.height(), {960.0f, 540.0f}, 200.0f, 0.7f,{0.1f,0.3f, 0.8f, 1.0f});
            window.swapBuffers();
        }
    }
     catch (const exception& e) {
        cerr<< "Fatal error :" << e.what() << "\n";
        return 1;
    }
    return 0; 
}