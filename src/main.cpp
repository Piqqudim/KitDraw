#include "panel.hpp"
#include <iostream>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include "GLFW/glfw3.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace gl;
using namespace std;
using namespace KitDraw;
int main(){
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE,1);

    //Create Window
    GLFWwindow* window = glfwCreateWindow(1280,720, "KitDraw", nullptr, nullptr);
    if(!window){
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //Enable Sync
    glfwSwapInterval(1);

    // Initialize glbinding

    glbinding::initialize(glfwGetProcAddress);


    // Check OpenGl
    //
    std::cout << "Opengl Version:"<<glGetString(GL_VERSION)<< "\n";
    std::cout<< "Opengl Vendor"<<glGetString(GL_VENDOR) <<"\n";
    std::cout<< "Opengl Renderer"<<glGetString(GL_RENDERER)<<"\n";



    //Create ImGui Context 
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;


    //keyboard navigations

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;


    //ImGui style
    ImGui::StyleColorsDark();


    //Initialize GLFW backend

    ImGui_ImplGlfw_InitForOpenGL(window, true);


    //Initialize Opengl backend

    ImGui_ImplOpenGL3_Init("#version 330");

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        //Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
       
       DrawTestPanel();
 // Finish ImGui frame
        ImGui::Render();
        //Draw our test panel

       
   

       

        ImDrawData* drawData=ImGui::GetDrawData();
        cout<<"Command List:"<<drawData->CmdListsCount<<"\n";
        cout<<"Vertices:"<<drawData->TotalVtxCount<<"\n";
        //Get framebuffer size
        int width;
        int height;
        glfwGetFramebufferSize(window, &width, &height);

        //OpenGL rendering
        glViewport(0,0, width, height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        cout<<"Width: "<<width<<"\n";
        cout<<"Height: "<<height<<"\n";
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Render ImGui
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        

        //Present
        glfwSwapBuffers(window);
    }
        //CleanUp
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();



        glfwDestroyWindow(window);
        glfwTerminate();

        return 0;
    







}
