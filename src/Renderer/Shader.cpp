#include "Renderer/Shader.hpp"
#include <glbinding/gl33core/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <vector>
#include <utility>

using namespace gl33core;
using namespace std;

namespace KitDraw::render {
    namespace{
        GLuint compile(GLenum stage, const string& source){
            Gluint shader = glCreateShader(stage);
            const char* src = source.c_str();
            glShaderSource(shader);

            GLint success = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success){
                GLint logLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
                vector<char> log(static_cast<size_t>(logLength));
                glGetShaderInfoLog(shader,logLength, nullpty, log.data());
                glDeleteShader(shader);
                cout<<"Shader compile error:"<<string(log.begin(), log.end()) << endl;
            }
            return shader;
        }
    }// namespace

    Shader::Shader()
}