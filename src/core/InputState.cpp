#include "core/InputState.hpp"
namespace KitDraw::core {
    void InputState::apply(const Event& event){
        std::visit([this](auto&& e){
            using T = std::decay_t<decltype(e)>;
            if constexpr(std::is_same_v<T, KeyEvent>){
                keyDown_[e.keyCode] = (e.action != KeyAction::Released);
            } else if constexpr(std::is_same_v<T, MouseButtonEvent>){
                mouseButtonDown_[e.button] = (e.action == MouseButtonAction::Pressed);
                mouseX_=e.x; mouseY_ = e.y;
            }else if constexpr(std::is_same_v<T, MouseMoveEvent>){
                mouseX_ = e.x; mouseY_ = e.y;
            }
        }, event);
    }

    bool InputState::isKeyDown(int keyCode) const {
        auto it = keyDown_.find(keyCode);
        return it != keyDown_.end() && it->second;
    }

    bool InputState::isMouseButtonDown(int button) const {
        auto it = mouseButtonDown_.find(button);
        return it != mouseButtonDown_.end() && it->second;
    }
}