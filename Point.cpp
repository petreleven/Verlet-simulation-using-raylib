#include "Point.h"
#include <raylib.h>
#define RADIUS 15
#define COLOR WHITE

Point::Point(float x ,float y, float mass,
             const int &screen_width, 
             const int &screen_height, Color c, bool ispinned): screen_width(screen_width), screen_height(screen_height){

  this->current_position = {x, y};
  this->prev_position = {x, y};
  this->mass = mass;
  this->color = c;
  this->ispinned= ispinned;
}
Point::~Point(){

}

void Point::constraint(){
  if (ispinned){return;}
  float vel_x = (current_position.x - prev_position.x)*0.09;
  float vel_y = (current_position.y - prev_position.y)*0.09;
  if(this->current_position.x+RADIUS > screen_width){
      this->current_position.x = screen_width-RADIUS;
      this->prev_position.x = current_position.x + vel_x;
  }
  if(this->current_position.x-RADIUS < 0){
    this->current_position.x = 0.f + RADIUS;
    this->prev_position.x = current_position.x + vel_x;
  }
  if(this->current_position.y+RADIUS > screen_height){
      this->current_position.y = screen_height -RADIUS;
      this->prev_position.y = current_position.y + vel_y;
  }
  if(this->current_position.y-RADIUS <0){
      this->current_position.y =0.f+RADIUS;
      this->prev_position.y = current_position.y + vel_y;
  }
}
void Point::update(float dt, Vector2 force){
  if (ispinned){return;}
  float acceleration_x =  force.x / mass;
  float acceleration_y =  force.y / mass;
  Vector2 cached_current_pos = {this->current_position.x, this->current_position.y};
  Vector2 nextpos ;
  nextpos.x = this->current_position.x + (this->current_position.x - this->prev_position.x)
                        + acceleration_x * dt * dt;
  nextpos.y = this->current_position.y + (this->current_position.y - this->prev_position.y)
                        + acceleration_y * dt * dt;
  this->prev_position = cached_current_pos; 
  this->current_position = nextpos;
}

void Point::render(){
  if(ispinned){this->color = RED;}
  else {
    this->color=WHITE;
  }
  DrawCircle(this->current_position.x, this->current_position.y, RADIUS,this->color);
}

Vector2 Point::getCurrentPos(){
  return this->current_position;
}

void Point::setCurrentPos(Vector2 new_pos){
  this->current_position.x = new_pos.x;
  this->current_position.y = new_pos.y;
}
