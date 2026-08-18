#pragma once
#include <string>
#include <glm/glm.hpp>
using namespace std;

namespace KitDraw::render {
    class Shader {
        public:
            Shader(const string& vertexSource, const string& fragmentSource);
            ~Shader();

            Shader(const Shader&) = delete;
            Shader& operator=(const Shader&) = delete;
            Shader(Shader&& other) noexcept;
            Shader& operator=(Shader&& other) noexcept;

            void bind() const;
            void setUniformMat4(const char* name, const glm::mat4& value) const;
            void setUniformInt(const char* name, int value) const;
            void setUniformFloat(const char* name, float value) const;
            void setUniformVec2(const char* name, const glm::vec2& value) const;
            void setUniformVec3(const char* name, const glm::vec3& value) const;
            void setUniformVec4(const char* name, const glm::vec4& value) const;
        private:
            unsigned int program_ = 0;
    };
}