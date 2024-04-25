#include "PolyTriangle.h"
#include "Polygon.h"
#include <cmath>
#include <cstddef>
#include <raylib.h>
#include <vector>


extern int SCREENWIDTH;
extern int SCREENHEIGHT;


PolyTriangle::PolyTriangle(Vector2 a, Vector2 b, Vector2 c, Color color){  
  std::vector<Vector2> trpoints={a,b,c};
  this->color = color;
  this->connectPoints(trpoints, 1);
}

void PolyTriangle::connectPoints(std::vector<Vector2> trpoints, float length){
  for (size_t i = 0;  i< trpoints.size(); i++) {
     Point *p = new Point(trpoints[i].x, trpoints[i].y, 1,
                         SCREENWIDTH, SCREENHEIGHT, GREEN, false);
      this->poly_points.push_back(p);

  }
   

  float ab_length = sqrtf(powf(trpoints[1].x-trpoints[0].x, 2) + 
                          powf(trpoints[1].y-trpoints[0].y,2)
                          );
  float bc_length = sqrtf(powf(trpoints[2].x-trpoints[1].x, 2) + 
                          powf(trpoints[2].y-trpoints[1].y,2)
                          );
  float ca_length = sqrtf(powf(trpoints[0].x-trpoints[2].x, 2) + 
                          powf(trpoints[0].y-trpoints[2].y,2)
                          ); 
  float trainglesidelengths[] = {ab_length, bc_length, ca_length};
  for(size_t i = 0; i<this->poly_points.size(); i++){
    Stick *s = new Stick(*(this->poly_points[i]), 
                         *(this->poly_points[(i+1)%this->poly_points.size()]),
                          trainglesidelengths[i], this->color);
    this->poly_sticks.push_back(s);
  } 
}

void PolyTriangle::renderPolygon() const{
  Polygon::renderPolygon(); 
}

void PolyTriangle::update(float dt, Vector2 &force){
  Polygon::update(dt, force);
}
