#include <cmath>
#include <cstddef>
#include <raylib.h>
#include <vector>
#include "Point.h"
#include "Stick.h"  
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const Vector2 force = {0.f, 100.f};
const int numIterations = 10; // Number of constraint resolution numIterations


struct Engine{
private:
  int radius;
  Vector2 center;
  float speed;
  float angle = 360.f;
  Point *piston;
public:
  Engine(Vector2 center, int radius, float speed) {
    this->center = center;
    this->radius = radius;
    this->speed = speed;
    piston = new Point(center.x, center.y + radius,1,
                       SCREEN_WIDTH, SCREEN_HEIGHT,
                      WHITE, false);

  }
  ~Engine(){
    if(piston!=nullptr){
      delete piston;
    }
  }
  void update(float dt){
    Vector2 currentpos = this->piston->getCurrentPos();
    this->angle += speed * dt;
    Vector2 nextpos = {this->center.x + this->radius*cosf(this->angle) ,
                       this->center.y + this->radius*sinf(this->angle) };
    piston->setCurrentPos(nextpos);
  }
  void render(){
     DrawCircleLines(center.x, center.y, radius, ORANGE);
  }
  Point* getpiston(){
    return piston;
  }

};

void CREATSQ(std::vector<Point *> &all_points, std::vector<Stick *> &all_sticks, 
             Vector2 mousepos){
  Point *sq1 = new Point(mousepos.x,  mousepos.y, 1, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE, false);
  Point *sq2 = new Point(mousepos.x + 100, mousepos.y, 1, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE, false);
  Point *sq3 = new Point(mousepos.x + 100, mousepos.y+100, 1, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE, false);
  Point *sq4 = new Point(mousepos.x, mousepos.y+100, 1, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE, true);
  Stick *sq12 = new Stick(*sq1, *sq2, 90);
  Stick *sq23 = new Stick(*sq2, *sq3, 90);
  Stick *sq34 = new Stick(*sq3, *sq4, 90);
  Stick *sq41 = new Stick(*sq4, *sq1, 90);
  Stick *sq13 = new Stick(*sq1, *sq3, 127.28);
  all_points.push_back(sq1);
  all_points.push_back(sq2);
  all_points.push_back(sq3);
  all_points.push_back(sq4);
  all_sticks.push_back(sq12);
  all_sticks.push_back(sq23);
  all_sticks.push_back(sq34);
  all_sticks.push_back(sq41);
  all_sticks.push_back(sq13);
}
float magnitude(Vector2 u, Vector2 v){
  return sqrtf(powf(v.x - u.x,2) + powf(v.y-u.y, 2));
}

void check_events(std::vector<Point *> &all_points, std::vector<Stick *> &all_sticks ){
  if (IsGestureDetected(GESTURE_TAP)){
    Vector2 mouse = GetMousePosition();
    for (auto p : all_points){
      if ((magnitude(p->getCurrentPos(), mouse)) < 20.f){
        p->ispinned = !p->ispinned;
      }
    }
  }
}

void update(std::vector<Point *> &all_points, std::vector<Stick *> &all_sticks,float dt){
  for (int iter = 0; iter < numIterations; ++iter) {
    for (Point *p : all_points) {
      p->constraint();
    }
    for (Stick *s : all_sticks) {
      s->constraint();
    }
  }
  for(size_t i = 0; i< all_points.size(); i++){
    all_points[i]->update(dt, force);
  }
}

void render_all(std::vector<Point *> &all_points, std::vector<Stick *> all_sticks){
  for (Point *p :all_points){
    p->render();
  }
  for (Stick *s : all_sticks){
    s->render();
  }

}

void CALL_GC(std::vector<Point *> &all_points, std::vector<Stick *> all_sticks){
  for (Stick *s: all_sticks){
    delete  s;
  }
  for(Point *p : all_points){
    delete p;
  }
}

int main(){
  std::vector<Point *> all_points = {};
  std::vector<Stick *> all_sticks = {};
  //Simple triangle
  Engine newengine = Engine({SCREEN_WIDTH/2.f, 100}, 60, 0.6f);
  //Points
  Point *p = newengine.getpiston();
  float span = 60;
  Vector2 pistonposition = p->getCurrentPos();
  Point *a = new Point(pistonposition.x, pistonposition.y + span,1, 
                       SCREEN_WIDTH, SCREEN_HEIGHT,
                       WHITE, false);
  Point *b = new Point(pistonposition.x + 10, pistonposition.y + 2*span, 1, 
                       SCREEN_WIDTH, SCREEN_HEIGHT,
                       WHITE, false);
  Point *c = new Point(pistonposition.x+span, pistonposition.y + 3*span, 1, 
                       SCREEN_WIDTH, SCREEN_HEIGHT,
                       WHITE, false);
  //sq4
  Point *sq1 = new Point(300, 100, 1, 
                       SCREEN_WIDTH, SCREEN_HEIGHT,
                       WHITE, false);

  Point *sq2 = new Point(300+100, 100, 1, 
                       SCREEN_WIDTH, SCREEN_HEIGHT,
                       WHITE, false);
  Point *sq3= new Point(300+100 ,100+100, 1, 
                       SCREEN_WIDTH, SCREEN_HEIGHT,
                       WHITE, true);
  Point *sq4 = new Point(300,100+100, 1, 
                       SCREEN_WIDTH, SCREEN_HEIGHT,
                       WHITE, false);




  //Create sticks;
  Stick *pa = new Stick(*p, *a, span);
  Stick *ab = new Stick(*a, *b, span);
  Stick *bc = new Stick(*b, *c, span);
  Stick *c_sq1 = new Stick(*c, *sq1, span);
  Stick *sq12 = new Stick(*sq1, *sq2, 100);
  Stick *sq23 = new Stick(*sq2, *sq3, 100);
  Stick *sq34 = new Stick(*sq3, *sq4, 100);
  Stick *sq41 = new Stick(*sq4, *sq1, 100);
  Stick *sq13 = new Stick(*sq1, *sq3, 141.42);
  //ADD ALL POINTS
  all_points.push_back(p);
  all_points.push_back(a);
  all_points.push_back(b);
  all_points.push_back(c);
  all_points.push_back(sq1);
  all_points.push_back(sq2);
  all_points.push_back(sq3);
  all_points.push_back(sq4);
  
  //ADD ALL STICKS
  all_sticks.push_back(pa);
  all_sticks.push_back(ab);
  all_sticks.push_back(bc);
  all_sticks.push_back(sq12);
  all_sticks.push_back(sq23);
  all_sticks.push_back(sq34);
  all_sticks.push_back(sq41);
  all_sticks.push_back(sq13);
  all_sticks.push_back(c_sq1);

  

  //RAYLIB
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Verlet simulation");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    check_events(all_points, all_sticks);
    update(all_points, all_sticks,GetFrameTime());
    //newengine.update(GetFrameTime());
    BeginDrawing();
    ClearBackground(BLACK);
    render_all(all_points, all_sticks);
    newengine.render();
    EndDrawing();
  }
  CloseWindow();
  //Deallocate memory
  CALL_GC(all_points, all_sticks);
}


