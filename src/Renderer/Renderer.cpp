#include "Renderer/Renderer.hpp"
#include <glbinding/gl/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include<array>

using namespace std;
using namespace gl;
using namespace glm;
namespace KitDraw::render {
    namespace{
        constexpr const char* kVertexSource =R"(
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

uniform sampler2D canvasTexture;

void main(){
    vec4 premultiplied = texture(canvasTexture, vUV);
    float epsilion = 0.0001;
    vec3 straight = premultiplied.rgb / max(premultiplied.a, epsilion);
    fragColor = vec4(straight, premultiplied.a);
            
            
}
)";
}

    Renderer::Renderer(){
      shader_=make_unique<Shader>(kVertexSource,kFragmentSource);
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

    Renderer::~Renderer(){
        if(vbo_) glDeleteBuffers(1, &vbo_);
        if(vao_) glDeleteVertexArrays(1, &vao_);
    }
    void Renderer::drawCanvas(const Layer& composite, const Camera& camera) const {
        mat4 model = scale(mat4(1.0f),vec3((float)composite.width(), (float)composite.height(),1.0f));
        mat4  mvp = camera.viewProjectionMatrix() * model;

        shader_->bind();
        shader_->setUniformMat4("uMVP", mvp);
        shader_->setUniformInt("canvasTexture", 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, composite.colorTextureId());


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindVertexArray(vao_);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glDisable(GL_BLEND);
    }


}