#include <string>
#include <vector>
#include <cstdio>


//Transform Panel

void DrawTransformPanel(){
    static float position[3] = { 0.0f, 0.0f, 0.0f};
    static float rotation[3] = {0.0f , 0.0f, 0.0f};
    static float scale[3] = { 1.0f, 1.0f, 1.0f};

    ImGui::Begin("Transform");

    ImGui::Text("Transform Component");


    ImGui::DragFloat3("Position", position, 0.1f);

    


    
}