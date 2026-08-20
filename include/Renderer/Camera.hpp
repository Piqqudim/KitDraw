#pragma once 
#include <glm/glm.hpp>
#include <utility>
using namespace std;
namespace KitDraw::render {

    class Camera {
        public:
            void setViewportSize(const int& width,const int& height);
            int viewportWidth() const noexcept { return viewportWidth_;}
            int viewportHeight() const noexcept { return viewportHeight_;}

            //Position of the camera
            void setPosition(const glm::vec2& worldPosition) noexcept {
                position_ = worldPosition;
             }

            glm::vec2 position() const noexcept {
                return position_;
            }

            void setZoom(const float& zoom)noexcept;
            float zoom() const noexcept { return zoom_;}

            void setRotation(const float& radians) noexcept { rotation_ = radians;}
            float rotation() const noexcept { return rotation_; }

            void reset(const glm::vec2& defaultWorldPosition);
            void panByScreenDelta(const glm::vec2& screenDelta)noexcept;
            void zoomAt(const glm::vec2& screenPoint,const float& multiplier);
            void rotateAt(const glm::vec2& screenPoint,const float& deltaRadians);

            glm::vec2 screenToWorld(const glm::vec2& screenPoint) const;
            glm::vec2 worldToScreen(const glm::vec2& worldPoint) const;

            glm::mat4 viewProjectionMatrix()const;
            glm::mat4 inverseViewProjectionMatrix() const;
            pair<glm::vec2, glm::vec2> visibleWorldBounds() const;


             


        private:
            glm::vec2 viewportCenter() const noexcept{
                return { viewportWidth_ * 0.5f, viewportHeight_ * 0.5f};

            }
            int viewportWidth_ = 1;
            int viewportHeight_ = 1;
            glm::vec2 position_{ 0.0f, 0.0f};
            float zoom_ = 1.0f;
            float rotation_ = 0.0f;

            static constexpr float kMinZoom = 0.02f;
            static constexpr float kMaxZoom = 64.0f;
    };
}