#include "Polygon.h"
#include <cmath>
#include <cstddef>
#include <raylib.h>
#include <vector>


Polygon::Polygon(){
}

Polygon::~Polygon(){
  for(Point * p : this->poly_points){
    delete  p;
    p = nullptr;
  }
  this->poly_points.clear();
  for (Stick *s : this->poly_sticks){
    delete s;
    s = nullptr;
  }
  this->poly_sticks.clear();
}

void Polygon::connectPoints(std::vector<Vector2>, float length){
  size_t numpoints =  this->poly_points.size();
  for(size_t i=0; i<numpoints; i++){
    Stick *s = new Stick(*(this->poly_points[i]), *(this->poly_points[(i+1)%numpoints]), length, this->color);
    this->poly_sticks.push_back(s);
  }
  Stick *diag = new Stick(*(this->poly_points[0]), *(this->poly_points[2]), sqrtf(2*powf(length, 2)), this->color);
    this->poly_sticks.push_back(diag);
}

void Polygon::renderPolygon() const{
  for (size_t i = 0; i < this->poly_points.size(); i++) {
    this->poly_points[i]->render();
  }

  for (size_t i = 0; i < this->poly_sticks.size(); i++) {
    this->poly_sticks[i]->render(this->color);
  }
}

void Polygon::update(float dt, Vector2 &force){
  const int NUMITER=3;
   for (int i = 0; i<NUMITER; i++)
  {
    for (Point *p : this->poly_points){
      p->constraint();
    } 

    for (Stick *s : this->poly_sticks){
      s->constraint();
    }
  }
  for (Point *p : this->poly_points){
    p->update(dt, force);
  } 
}

std::vector<Point> Polygon::getAllpolygonpoints(){
  std::vector<Point> temp;
  for(Point *p : poly_points){
    temp.push_back(*p);
  }
  return  temp;
}
std::vector<Stick> Polygon::getAllpolygonsticks(){
  std::vector<Stick> temp;
  for(Stick *p : poly_sticks){
    temp.push_back(*p);
  }
  return  temp;
}

void Polygon::move(Vector2 dir, float speedbydt){
  Vector2 curr_point_pos; 
  for(Point *p : poly_points){
   curr_point_pos = p->getCurrentPos();
   curr_point_pos.x += dir.x*speedbydt;
   curr_point_pos.y += dir.y*speedbydt;
    p->setCurrentPos(curr_point_pos);
  }
  
}
