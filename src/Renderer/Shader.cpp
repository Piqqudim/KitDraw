#include "Renderer/Shader.hpp"
#include <glbinding/gl/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <vector>
#include <utility>
#include<fstream>
#include<iostream>
using namespace gl;
using namespace std;

namespace KitDraw::render {
    namespace{
        GLuint compile(GLenum stage, const string& source){
            GLuint shader = glCreateShader(stage);
            const char* src = source.c_str();
            glShaderSource(shader, 1, &src, nullptr);

            GLint success = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success){
                GLint logLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
                vector<char> log(static_cast<size_t>(logLength));
                glGetShaderInfoLog(shader,logLength, nullptr, log.data());
                glDeleteShader(shader);
                cout<<"Shader compile error:"<<string(log.begin(), log.end()) << endl;
            }
            return shader;
        }
    }// namespace

    Shader::Shader(const string& vertexSource,const std::string& fragmentSource){
        GLuint vs = compile(GL_VERTEX_SHADER,vertexSource);
        GLuint fs = compile(GL_FRAGMENT_SHADER,fragmentSource);

        program_= glCreateProgram();
        glAttachShader(program_, vs);
        glAttachShader(program_, fs);
        glLinkProgram(program_);

        GLint success = 0;
        glGetProgramiv(program_,GL_LINK_STATUS, &success);
        if(!success){
            GLint logLength = 0;
            glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<char> log(static_cast<size_t>(logLength));
            glGetProgramInfoLog(program_, logLength, nullptr, log.data());
            glDeleteShader(vs);
            glDeleteShader(fs);
            glDeleteProgram(program_);
            cout<<"Shader link error:"+ string(log.begin(), log.end())<<endl;
        }
        glDeleteShader(vs);
        glDeleteShader(fs);
        
    }
    Shader::~Shader() { if (program_) glDeleteProgram(program_); }

    Shader::Shader(Shader&& other) noexcept: program_(exchange(other.program_, 0)) {}

    Shader& Shader::operator=(Shader&& other) noexcept {
        if(this != &other){
            if(program_) glDeleteProgram(program_);
            program_ = exchange(other.program_, 0);
        }
        return *this;
    }

    void Shader::bind() const { glUseProgram(program_); }

    void Shader::setUniformMat4(const char* name, const glm::mat4& value) const {
        glUniformMatrix4fv(glGetUniformLocation(program_, name), 1, GL_FALSE, glm::value_ptr(value));
    }
    void Shader::setUniformInt(const char* name, int value) const{
        glUniform1i(glGetUniformLocation(program_, name), value);
    }
    void Shader::setUniformFloat(const char* name, float value) const {
        glUniform1f(glGetUniformLocation(program_, name), value);
    }
    void Shader::setUniformVec2(const char* name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(program_, name), 1, glm::value_ptr(value));
    }
    void Shader::setUniformVec3(const char* name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(program_,name), 1, glm::value_ptr(value));
    }
    void Shader::setUniformVec4(const char* name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(program_, name),1, glm::value_ptr(value));
    }
}