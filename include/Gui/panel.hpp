#include "imgui.h"
#include<iostream>
using namespace std;
namespace KitDraw{
inline void DrawTestPanel(){
    std::cout<<"Drawing Panel"<<"\n";
    static float speed = 5.0f;
    static bool enabled = true;
    static int counter = 0;

    static char name[128] = "my Entity";
    ImGui::Begin("Test Panel");
    ImGui::Text("Hello from ImGui");

   ImGui::Separator();
    ImGui::Text("Entity Settings");

    ImGui::InputText("Name", name,sizeof(name));

    ImGui::SliderFloat("Speed", &speed, 0.0f, 20.0f);

    ImGui::Checkbox("Enabled", &enabled);

    ImGui::Separator();
    if(ImGui::Button("Click Me")){
        counter++;
    }

    ImGui::SameLine();
    ImGui::Text("Clicked: %d times", counter);

    ImGui::Separator();

    if(ImGui::Button("Reset")){
        speed = 5.0f;
        enabled = true;
        counter = 0;
    }

    ImGui::End();
}
}