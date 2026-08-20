#include "Renderer/Camera.hpp"
#include <algorithm>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

namespace KitDraw::render {
    namespace {
        glm::vec2 rotate2D(const glm::vec2& v,const float& radians){
            const float c = cos(radians);
            const float s = sin(radians);
            return { v.x *  c - v.y * s, v.x * s + v.y * c};
        }
    }

    void Camera::setViewportSize(const int& width,const int& height){
        viewportWidth_ = width > 0 ? width: 1;
        viewportHeight_ = height > 0 ? height : 1;
        return;
    }

    void Camera::setZoom(const float& zoom) noexcept { zoom_ = clamp(zoom, kMinZoom, kMaxZoom);}

    void Camera::reset(const glm::vec2& defaultWorldPosition){
        position_ = defaultWorldPosition;
        zoom_ = 1.0f;
        rotation_ = 0.0f;
        return;
    }

    glm::vec2 Camera::screenToWorld(const glm::vec2& screenPoint) const {
        const glm::vec2 rel = (screenPoint - viewportCenter()) / zoom_;
        return position_ + rotate2D(rel, rotation_);
    }

    glm::vec2 Camera::worldToScreen(const glm::vec2& worldPoint) const {
        const glm::vec2 rel = rotate2D(worldPoint - position_, -rotation_);
        return viewportCenter() + rel * zoom_;
    }
     void Camera::panByScreenDelta(const glm::vec2& screenDelta) noexcept {
        position_ -= rotate2D(screenDelta/zoom_, rotation_);
        return;
     }

     void Camera::zoomAt(const glm::vec2& screenPoint,const float& multiplier){
        const glm::vec2 worldBefore = screenToWorld(screenPoint);
        setZoom(zoom_ * multiplier);
        const glm::vec2 rel = (screenPoint - viewportCenter()) / zoom_;
        position_ = worldBefore - rotate2D(rel, rotation_);
     }

     void Camera::rotateAt(const glm::vec2& screenPoint,const float& deltaRadians){
        const glm::vec2 worldBefore = screenToWorld(screenPoint);
        rotation_ += deltaRadians;
        const glm::vec2 rel = (screenPoint - viewportCenter()) / zoom_;
        position_ = worldBefore - rotate2D(rel, rotation_);
     }

     glm::mat4 Camera::viewProjectionMatrix() const {
        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(viewportCenter(), 0.0f));
        view = glm::scale(view, glm::vec3(zoom_, zoom_, 1.0f));
        view = glm::rotate(view,-rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::translate(view,glm::vec3(-position_, 0.0f));

        const glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(viewportWidth_),static_cast<float>(viewportHeight_), 0.0f, -1.0f, 1.0f);
        return projection * view;
     }

     glm::mat4 Camera::inverseViewProjectionMatrix() const { return glm::inverse(viewProjectionMatrix());}

     pair<glm::vec2, glm::vec2> Camera::visibleWorldBounds() const {
        const glm::vec2 c0 = screenToWorld({ 0.0f, 0.0f});
        const glm::vec2 c1 = screenToWorld({static_cast<float>(viewportWidth_), 0.0f});
        const glm::vec2 c2 = screenToWorld({0.0f, static_cast<float>(viewportHeight_)});
        const glm::vec2 c3 = screenToWorld({static_cast<float>(viewportWidth_), static_cast<float>(viewportHeight_)});
        return { glm::min(glm::min(c0,c1), glm::min(c2,c3)), glm::max(glm::max(c0,c1), glm::max(c2,c3))};
     }
}