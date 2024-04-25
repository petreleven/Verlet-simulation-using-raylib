#include "AllPolygons/PolySquare.h"
#include <raylib.h>
#include "CONSTANTS.h"
#include "./Colliders/AABB.h"
const int SCREENWIDTH = 800;
const int SCREENHEIGHT = 450;
static Vector2 force = {0, 10.f};

enum KEYPRESSED{
  NONE,
  LEFT,
  RIGHT,
  UP,
  DOWN,
};
static KEYPRESSED CURRENTKEYPRESSED;
void checkevents(){
  if(IsKeyDown(KEY_LEFT)){
    CURRENTKEYPRESSED=LEFT;
  }
  else if(IsKeyDown(KEY_RIGHT)){
    CURRENTKEYPRESSED=RIGHT;
  }
  else if (IsKeyDown(KEY_UP)) {
    CURRENTKEYPRESSED = UP;
  }
  else if (IsKeyDown(KEY_DOWN)) {
    CURRENTKEYPRESSED = DOWN;
  }
  else {
   CURRENTKEYPRESSED=NONE;
  }
}
int main(){
  Vector2 origin = {SCREENWIDTH/2.f, 70.f};
  Vector2 origin2 = {SCREENWIDTH/2.f-80, 70.f};
  PolySquare sq = PolySquare(origin, 100, ORANGE);
  Vector2 a = {200, 200};
  Vector2 b = {100, 300};
  Vector2 c = {300, 300};
  PolySquare sq2 = PolySquare(origin2, 100, PURPLE);
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "{}");
  SetTargetFPS(60);
  std::vector<Polygon *> all_game_polygons;
  all_game_polygons.push_back(&sq);
  all_game_polygons.push_back(&sq2);
  AABB collider = AABB(all_game_polygons);
  Vector2 dir = {0,0};
  float speed =60;

  while(!WindowShouldClose())
  {
    //sq.update(GetFrameTime(), force);
    //triangle.update(GetFrameTime(), force);
    checkevents();
    switch (CURRENTKEYPRESSED) {
      case LEFT:
        dir = {-1,0};
        break;
      case RIGHT:
        dir = {1, 0};
        break;
      case UP:
        dir = {0, -1};
        break;
      case DOWN:
        dir = {0, 1};
        break;
      case NONE:
        dir = {0, 0};
        break;
    }
    all_game_polygons[0]->move(dir, GetFrameTime()*speed);
    collider.checkcollisions();
    BeginDrawing();
    ClearBackground(BLACK);
    sq.renderPolygon();
    sq2.renderPolygon();
    //triangle.renderPolygon();
    EndDrawing();
  }
  CloseWindow();
}
