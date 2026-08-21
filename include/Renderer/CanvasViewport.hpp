#pragma once
#include <glm/glm.hpp>

namespace KitDraw::render {
    class CanvasViewport{
        public:
            CanvasViewport(float width = 1000.0f, float height = 600.0f);

            void resizeWindow(int windowWidth, int windowHeight);

            bool contains(glm::vec2 windowPosition) const;

            glm::vec2 viewportToWindow(glm::vec2 viewportPosition) const;

            glm::vec2 windowToViewport(glm::vec2 windowPosition) const;

            float x() const noexcept {
                return x_;
            }
            
            float y() const noexcept{
                return y_;
            }

            float width() const noexcept{
                return width_;
            }

            float height() const noexcept {
                return height_;
            }
        private:
            float x_ = 0.0f;
            float y_ = 0.0f;

            float width_ = 1000.0f;
            float height_ = 600.0f;
    };
}