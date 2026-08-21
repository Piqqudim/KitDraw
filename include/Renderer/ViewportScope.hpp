#pragma once
#include "Renderer/GraphicsContext.hpp"
#include <functional>

namespace KitDraw::render {
    class ViewportScope {
        public:
            ViewportScope(GraphicsContext& gfx, int x, int y, int width, int height, int restoreWidth, int restoreHeight):gfx_(gfx), restoreWidth_(restoreWidth),restoreHeight_(restoreHeight){
                gfx_.setViewport(x, y, width, height);
            }

            ~ViewportScope() { gfx_.setViewport(0,0,restoreWidth_,restoreHeight_);}

            ViewportScope(const ViewportScope&) = delete;
            ViewportScope& operator=(const ViewportScope&) = delete;
                
                
                
                private:
                GraphicsContext& gfx_;
                int restoreWidth_, restoreHeight_;
            

    
            };
}