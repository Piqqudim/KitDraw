#include "Renderer/Camera.hpp"
#include <algorithm>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

namespace KitDraw::render {
    namespace {
        glm::vec2 rotate2D(glm::vec2 v, float radians){
            const float c = cos(radians);
            const float s = sin(radians);
            return { v.x *  c - v.y * s, v.x * s + v.y * c};
        }
    }

    void Camera::setViewportSize(int width, int height){
        viewportWidth_ = width > 0 ? width: 1;
        viewportHeight_ = height > 0 ? height : 1;
    }

    void Camera::setZoom(float zoom) noexcept { zoom = clamp(zoom, kMinZoom, kMaxZoom);}

    void Camera::reset(glm::vec2 defaultWorldPosition){
        position_ = defaultWorldPosition;
        zoom_ = 1.0f;
        rotation_ = 0.0f;
    }

    glm::vec2 Camera::screenToWorld(glm::vec2 screenPoint) const {
        const glm::vec2 rel = (screenPoint - viewportCenter()) / zoom_;
        return position_ + rotate2D(rel, rotation_);
    }

    glm::vec2 Camera::worldToScreen(glm::vec2 worldPoint) const {
        const glm::vec2 rel = rotate2D(worldPoint - position_, -rotation_);
        return viewportCenter() + rel * zoom_;
    }
}