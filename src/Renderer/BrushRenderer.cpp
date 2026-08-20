#include "Renderer/BrushRenderer.hpp"
#include <glbinding/gl/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
using namespace gl;
using namespace glm;
using namespace std;

namespace KitDraw::render {
    namespace {
        constexpr const char* kVertexSource = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;
uniform mat4 uMVP;
out vec2 vUV;
void main(){
     vUV = aUV;
     gl_Position = uMVP * vec4(aPos, 0.0, 1.0);
}
)";

        constexpr const char* kFragmentSource =  R"(
#version 330 core
in vec2 vUV;
out vec4 fragColor;
uniform float uHardness;
uniform vec4 uColor;
void main(){
     vec2 centered = vUV * 2.0 - 1.0f;
     float dist = length(centered);
     float alpha = 1.0 - smoothstep(uHardness, 1.0, dist);
     float finalAlpha = uColor.a * alpha;
     fragColor = vec4(uColor.rgb * finalAlpha, finalAlpha);
}
)";
    }
    BrushRenderer::BrushRenderer(){
        shader_= make_unique<Shader>(kVertexSource,kFragmentSource);
        constexpr array<float, 24> vertices = {
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
             1.0f,  1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  0.0f, 1.0f,
      };

      glGenVertexArrays(1, &vao_);
      glGenBuffers(1, &vbo_);
      glBindVertexArray(vao_);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
      glBindVertexArray(0);
    }

    BrushRenderer::~BrushRenderer(){
        if(vbo_) glDeleteBuffers(1, &vbo_);
        if(vao_) glDeleteVertexArrays(1, &vao_);
    }

    void BrushRenderer::stampDab(int targetWidth, int targetHeight, vec2 canvasPosition, float diameter, float hardness, vec4 color) const {
        mat4 projection = ortho(0.0f, (float)targetWidth,(float)targetHeight, 0.0f, -1.0f, 1.0f);
        mat4 model = translate(mat4(1.0f), vec3(canvasPosition, 0.0f));
        model = scale(model, vec3(diameter * 0.5f, diameter * 0.5f, 1.0f));
        mat4 mvp = projection * model;

        shader_->bind();
        shader_-> setUniformMat4("uMVP",mvp);
        shader_-> setUniformFloat("uHardness", hardness);
        shader_-> setUniformVec4("uColor", color);

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glBindVertexArray(vao_);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glDisable(GL_BLEND);
    }
}