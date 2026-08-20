#pragma once
#include <glm/glm.hpp>

namespace KitDraw::render {
    class Layer {
        public:
            Layer(int width , int height);
            ~Layer();

            Layer(const Layer&) = delete;
            Layer& operator=(const Layer&) = delete;
            Layer(Layer&& other) noexcept;
            Layer& operator=(Layer&& other) noexcept;

            void bind() const;
            void unbind() const;
            void clearTransparent() const;
            void clearToOpaqueColor(const glm::vec4& straightColor) const;

            unsigned int colorTextureId() const noexcept { return colorTexture_;}
            int width() const noexcept {return width_;}
            int height() const noexcept { return height_;}




        private:
            void release();

            unsigned int framebuffer_ = 0;
            unsigned int colorTexture_ = 0;
            int width_ = 0;
            int height_ = 0;
            
    };
}