#pragma once
#include "Renderer/Shader.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/Layer.hpp"
#include<memory>
using namespace std;
namespace KitDraw::render {
    class Renderer {
        public:
            Renderer();
            ~Renderer();
            Renderer(const Renderer&) = delete;
            Renderer& operator=(const Renderer& ) = delete;

            void drawCanvas(const Layer& composite, const Camera& camera) const;

        private:
            unique_ptr<Shader> shader_;
            unsigned int vao_;
            unsigned int vbo_;
    };
}