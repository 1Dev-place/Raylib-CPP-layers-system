
#include <iostream>
#include <raylib.h>
#include <vector>
#include <functional>
#include <algorithm>


using namespace std;

const int Screen_width = 800;
const int Screen_height = 600;

Color Lightest = { 244, 238, 255, 255 };  // #F4EEFF
Color Lighter = { 209, 186, 255, 255 };   // #D1BAFF
Color Light = { 175, 134, 255, 255 };     // #AF86FF
Color Primary = { 140, 82, 255, 255 };    // #8C52FF
Color Dark = { 98, 57, 179, 255 };        // #6239B3
Color Darker = { 70, 41, 128, 255 };      // #462980





void DrawRoundedRectangle(float x, float y, float width, float height, float radius, Color color) 
{
    DrawCircleSector((Vector2){x + radius, y + radius}, radius, 180, 270, 36, color);
    DrawCircleSector((Vector2){x + width - radius, y + radius}, radius, 270, 360, 36, color);
    DrawCircleSector((Vector2){x + radius, y + height - radius}, radius, 90, 180, 36, color);
    DrawCircleSector((Vector2){x + width - radius, y + height - radius}, radius, 0, 90, 36, color);    
    DrawRectangle(x + radius, y, width - 2 * radius, height, color);
    DrawRectangle(x, y + radius, width, height - 2 * radius, color);
}






class Layers_system
{
private:
bool able_to_add_layers;
struct Layer
{
  function<void()> Func;
  int Layer_number;
  bool operator<(const Layer& other) const {
        return Layer_number < other.Layer_number;
    }
};
vector<Layer> Layers;
public:
Layers_system()
{
    able_to_add_layers = true;
}
void add_to_draw(const std::function<void(void)>& drawFunc, int Layer_number)
{
   if (able_to_add_layers)
  {  
   Layers.push_back({drawFunc, Layer_number}); 
   stable_sort(Layers.begin(), Layers.end());
  }
}
void draw_layers(void)
{
      for (size_t i = 0; i < Layers.size(); i++)
  {
    Layers[i].Func();
  }
  able_to_add_layers = false;
}
};




int main () {

    InitWindow(Screen_width, Screen_height, "Layers system");
    SetTargetFPS(60);

    Layers_system Main_layers_system;
   

     while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(SKYBLUE);

DrawFPS(50,50);

// Examples

Main_layers_system.add_to_draw([]() {DrawRectangle(300,450, 150, 150, RED);}, 4);
Main_layers_system.add_to_draw([]() {DrawCircle(375,525,60,ORANGE);}, 5);
Main_layers_system.add_to_draw([]() {DrawCircle(375,525,40,GREEN);}, 6);
Main_layers_system.add_to_draw([]() {DrawCircle(375,525,20,YELLOW);}, 7);

Main_layers_system.add_to_draw([]() {DrawRoundedRectangle(250,200, 200, 200, 20, Lighter);}, 3);
Main_layers_system.add_to_draw([]() {DrawRoundedRectangle(300,200, 200, 200, 20, Light);}, 2);
Main_layers_system.add_to_draw([]() {DrawRoundedRectangle(350,200, 200, 200, 20, Primary);}, 1);


        Main_layers_system.draw_layers();

        EndDrawing();
    } 
    CloseWindow();
    return 0;
}
