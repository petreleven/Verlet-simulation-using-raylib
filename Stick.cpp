#include "Stick.h"
#include <cmath>
#include <raylib.h>
#define STICKCOLOR  GREEN;
Stick::Stick(Point &p0 , Point &p1, float length):p0(p0), p1(p1){
  this->length = length;
}
Stick::Stick(Point &p0 , Point &p1, float length, Color c):p0(p0), p1(p1), color(c){
  this->length = length;
}
Stick::~Stick(){}

Vector2 getDifference(Vector2 p0, Vector2 p1){
  return Vector2{p1.x-p0.x,
                p1.y-p0.y};
}

float getLength(Vector2 v){
  return sqrtf(v.x *v.x + v.y * v.y);
}

void Stick::render(){
  Vector2 pos0 = this->p0.getCurrentPos();
  Vector2 pos1 = this->p1.getCurrentPos();
  DrawLine(pos0.x, pos0.y, pos1.x, pos1.y, this->color);
}
void Stick::render(Color c){
  Vector2 pos0 = this->p0.getCurrentPos();
  Vector2 pos1 = this->p1.getCurrentPos();
  DrawLine(pos0.x, pos0.y, pos1.x, pos1.y, c);
}




void Stick::constraint(){
  Vector2 diff = getDifference(this->p1.getCurrentPos(), this->p0.getCurrentPos());
  float getLength_ = getLength(diff);
  if (getLength_ == 0.0001f){
    getLength_=1;
  }
  float diffFactor = (this->length - getLength_)/getLength_*0.5;
  Vector2 offset = {diff.x * diffFactor, diff.y * diffFactor};
  Vector2 current_P0 = this->p0.getCurrentPos();
  Vector2 current_P1 = this->p1.getCurrentPos();
  Vector2 new_P0 = {current_P0.x+offset.x , current_P0.y+offset.y};
  Vector2 new_P1 = {current_P1.x-offset.x, current_P1.y-offset.y};
  if(!this->p0.ispinned){
  this->p0.setCurrentPos(new_P0);}
  if(!this->p1.ispinned){
  this->p1.setCurrentPos(new_P1);}
}
