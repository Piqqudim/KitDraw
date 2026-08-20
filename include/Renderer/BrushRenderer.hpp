#pragma once
#include "Renderer/Shader.hpp"
#include <glm/glm.hpp>
#include<memory>
using namespace std;
namespace KitDraw::render{
    class BrushRenderer {
        public:
            BrushRenderer();
            ~BrushRenderer();
            BrushRenderer(const BrushRenderer&) = delete;
            BrushRenderer& operator= (const BrushRenderer&) = delete;

            void stampDab(int targetWidth, int targetHeight, glm::vec2 canvasPosition,float diameter, float hardness, glm::vec4 color) const;

            private:
            unique_ptr<Shader> shader_;
            unsigned int vao_ = 0;
            unsigned int vbo_ = 0;

    };
}