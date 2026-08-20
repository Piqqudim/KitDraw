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
    struct MouseMoveEvent { double x ; double y; };
    struct MouseScrollEvent { double xOffset; double yOffset; };

    using Event = variant<WindowResizeEvent,WindowCloseEvent, KeyEvent, MouseButtonEvent, MouseMoveEvent, MouseScrollEvent>;

    class EventQueue {
        public:
            void push(Event event) { queue_.push_back(move(event));}
            bool empty() const noexcept { return queue_.empty();}
            Event pop(){
                Event front = move(queue_.front());
                queue_.pop_front();
                return front;
            }
        private:
            deque<Event> queue_;
    };
}