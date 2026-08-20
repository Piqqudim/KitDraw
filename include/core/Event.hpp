#pragma once
#include <variant>
#include <deque>
#include <cstdint>
using namespace std;


namespace KitDraw::core {
    enum class KeyAction : uint8_t { Pressed, Released, Repeated };

    enum class MouseButtonAction: uint8_t {Pressed, Released };

    struct WindowResizeEvent {int width; int height;};
    struct WindowCloseEvent {};
    struct KeyEvent { int keyCode; KeyAction action ;};
    struct MouseButtonEvent { int button; MouseButtonAction action; double x; double y;};
    struct MouseMoveEvent
}