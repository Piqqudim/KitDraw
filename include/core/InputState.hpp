#pragma once
#include "core/Event.hpp"
#include <unordered_map>
using namespace std;

namespace KitDraw::core {
    class InputState {
        public:
            void apply(const Event& event);
            bool isKeyDown(int keyCode) const;
            bool isMouseButtonDown(int button) const;
            double mouseX() const noexcept { return mouseX_;}
            double mouseY() const noexcept { return mouseY_; }
        private:
            unordered_map<int, bool> keyDown_;
            unordered_map<int, bool> mouseButtonDown_;
            double mouseX_ = 0.0;
            double mouseY_ = 0.0;
    };
}