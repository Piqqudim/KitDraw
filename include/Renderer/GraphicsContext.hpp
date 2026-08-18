#pragma once

namespace::KitDraw::platform { class Window; }
namespace KitDraw::render {
    class GraphicsContext{
        public:
            explicit GraphicsContext(platform::Window& window);
            void setViewport(int x, int y, int width, int height);
            //with glClearColor(/**by so so value */)
            void clear(float r, float g, float b, float a)
    }
    
}