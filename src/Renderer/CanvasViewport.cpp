#include "Renderer/CanvasViewport.hpp"
#include <algorithm>

namespace KitDraw::render {
    CanvasViewport::CanvasViewport(float width, float height): width_(width),height_(height){}

    void CanvasViewport::resizeWindow(int windowWidth, int windowHeight) {
        width_ = std::min(1000.0f, static_cast<float>(windowWidth) - 40.0f);
        height_ = std::min(600.0f, static_cast<float>(windowHeight) - 40.0f);
        x_ = (static_cast<float>(windowHeight) - width_) * 0.5f;
        y_ = (static_cast<float>(windowHeight) - height_) * 0.5f;

        

    }

    bool CanvasViewport::contains(glm::vec2 windowPosition) const {
        return windowPosition.x >= x_ && windowPosition.x< x_ + width_ && windowPosition.y >= y_ && windowPosition.y < y_ + height_;
    }

    glm::vec2 CanvasViewport::windowToViewport(glm::vec2 windowPosition)const {
        return{
            windowPosition.x - x_, windowPosition.y - y_
        };
    }

    glm::vec2 CanvasViewport::viewportToWindow(glm::vec2 viewPosition) const {
        return {
            viewPosition.x + x_, viewPosition.y + y_
        };
    }
}