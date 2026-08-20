#include "platform/Window.hpp"
#include "Renderer/GraphicsContext.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/BrushRenderer.hpp"
#include "Renderer/Renderer.hpp"
#include "core/Event.hpp"
#include "core/InputState.hpp"
#include<glbinding/gl/gl.h>
#include<glbinding/glbinding.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

int main()
{
    try 
    {
        KitDraw::core::EventQueue eventQueue;
        KitDraw::platform::Window window(KitDraw::platform::WindowDesc{}, eventQueue);
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
        KitDraw::core::InputState input;

        bool panning  = false;
        bool painting = false;

        glm::vec2 lastMouseScreen{ 0.0f, 0.0f};

       
        while(!window.shouldClose()) {
            window.pollEvents();
            while(!eventQueue.empty()){
                KitDraw::core::Event event = eventQueue.pop();
                input.apply(event);

                std::visit([&](auto&& e)
                {
                    using T = std::decay_t<decltype(e)>;

                    if constexpr(std::is_same_v<T, KitDraw::core::WindowResizeEvent>)
                    {
                        camera.setViewportSize(e.width, e.height);
                    } 
                    else if constexpr (std::is_same_v<T, KitDraw::core::WindowCloseEvent>)
                    {
                        glfwSetWindowShouldClose(window.handle(), true);
                    } else if constexpr(std::is_same_v<T, KitDraw::core::MouseButtonEvent>)
                    {
                        glm::vec2 screenPos{(float)e.x, (float)e.y};
                        if(e.button == GLFW_MOUSE_BUTTON_MIDDLE)
                        {
                            panning = (e.action == KitDraw::core::MouseButtonAction::Pressed);
                            lastMouseScreen = screenPos;
                        } else if(e.button == GLFW_MOUSE_BUTTON_LEFT)
                        {
                            painting = (e.action == KitDraw::core::MouseButtonAction::Pressed);
                            if(painting)
                            {
                                glm::vec2 canvasPos = camera.screenToWorld(screenPos);
                                 canvas.bind();
                                 gfx.setViewport(0, 0, canvas.width(), canvas.height());
                                  brushRenderer.stampDab(canvas.width(), canvas.height(), canvasPos, 24.0f, 0.7f,{0.0f,0.0f, 0.0f, 1.0f});
                                 canvas.unbind();
       

                            }
                        }
                    } else if constexpr(std::is_same_v<T,KitDraw::core::MouseMoveEvent>)
                    {
                        glm::vec2 screenPos{(float)e.x,(float)e.y};
                        if(panning){
                            camera.panByScreenDelta(screenPos - lastMouseScreen);
                            lastMouseScreen = screenPos;
                        } else if(painting){
                            glm::vec2 canvasPos = camera.screenToWorld(screenPos);
                            canvas.bind();
                            gfx.setViewport(0,0, canvas.width(), canvas.height());
                            brushRenderer.stampDab(canvas.width(), canvas.height(), canvasPos,24.0f, 0.7f, {0.0f, 0.0f, 0.0f, 1.0f});
                            canvas.unbind();
                        } else if constexpr(std::is_same_v<T, KitDraw::core::MouseScrollEvent>){
                            glm::vec2 cursor{(float)input.mouseX(), (float)input.mouseY()};
                            float factor = std::pow(1.1f, (float)e.yoffset);
                            camera.zoomAt(cursor, factor);
                        }
                    }

                    
                },event);
            }
            gfx.setViewport(0, 0, window.width(), window.height());
            
            gfx.clear(0.18f,0.18f, 0.18f, 1.0f);
            renderer.drawCanvas(canvas,camera);
           
            window.swapBuffers();
        }
    }
     catch (const exception& e) 
     {
        cerr<< "Fatal error :" << e.what() << "\n";
        return 1;
    }
    return 0; 
}