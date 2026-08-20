#include "Renderer/Layer.hpp"
#include <glbinding/gl/gl.h>
#include <stdexcept>
#include <utility>
#include <iostream>
using namespace std;
using namespace gl;

namespace KitDraw::render {
    Layer::Layer(int width,int height) : width_(width), height_(height){
        glGenTextures(1, &colorTexture_);
        glBindTexture(GL_TEXTURE_2D, colorTexture_);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8, width_, height_,0, GL_RGBA, GL_UNSIGNED_BYTE,nullptr);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D,0);

        glGenFramebuffers(1, &framebuffer_);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, colorTexture_,0);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
            glBindFramebuffer(GL_FRAMEBUFFER,0);
            release();
            //WE need to change it during runtime or production to throw an exception
            cout<<"Layer framebuffer incomplete"<<endl;
        }
        glViewport(0,0, width_, height_);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


    }
    void Layer::release(){
        if(framebuffer_) glDeleteFramebuffers(1, &framebuffer_);
        if(colorTexture_) glDeleteTextures(1, &colorTexture_);
        framebuffer_ = 0;
        colorTexture_ = 0;
        return;
    }
    Layer::~Layer(){release();}
    Layer::Layer(Layer&& other) noexcept:framebuffer_(std::exchange(other.framebuffer_,0)),colorTexture_(std::exchange(other.colorTexture_,0)),width_(other.width_),height_(other.height_){
        return;
    }
    Layer& Layer::operator=(Layer&& other) noexcept{
        if(this!=&other){
            release();
            this->framebuffer_=other.framebuffer_;
            this->colorTexture_=other.colorTexture_;
            this->width_=other.width();
            this->height_=other.height();
        }
        return *this;
    }
    void Layer::bind() const{
        glBindFramebuffer(GL_FRAMEBUFFER,framebuffer_);
        return;
    }
    void Layer::unbind() const{
      glBindFramebuffer(GL_FRAMEBUFFER,0);
      return;
   }
   void Layer::clearTransparent() const{
       glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
       return;
   }
   void Layer::clearToOpaqueColor(const glm::vec4& straightColor) const{
    const glm::vec4& premultiplied=glm::vec4(straightColor.r*straightColor.a,straightColor.a*straightColor.g,straightColor.b*straightColor.a,straightColor.a);
    glClearColor(premultiplied.r,premultiplied.g,premultiplied.b,premultiplied.a);
    glClear(GL_COLOR_BUFFER_BIT);      
    return;
   }
}