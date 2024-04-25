#include "AABB.h" 
#include <cstddef>
#include <raylib.h>


AABB::AABB(std::vector<Polygon *> gamescene_polys){
  this->gamescene_polygons = gamescene_polys;
}


void AABB::checkcollisions(){
  //BASE IMPLEMENTATION ASSUMES WE ARE USING SQUARES;
  Vector2 origin_a;
  float length_a;
  Vector2 origin_b;
  float length_b;
  for (size_t i = 0; i < gamescene_polygons.size(); i++) {
    Point a0 = gamescene_polygons[i]->getAllpolygonpoints()[0];
    Stick sa = gamescene_polygons[i]->getAllpolygonsticks()[0];
    length_a = sa.length;
    origin_a = {a0.getCurrentPos().x+ length_a/2, a0.getCurrentPos().y + length_a/2};
    bool hascollided = false;
    for(size_t j=0; j<gamescene_polygons.size(); j++){
      if(i==j){continue;}
      Point b0 = gamescene_polygons[j]->getAllpolygonpoints()[0];         
      Stick sb = gamescene_polygons[j]->getAllpolygonsticks()[0];
      length_b = sb.length;
      origin_b = {b0.
        getCurrentPos().x + length_b/2 , b0.getCurrentPos().y + length_b/2};
      bool collision_xaxis, collision_yaxis = false;
      //check collison on both x and y axes
      if(origin_a.x + length_a/2 >= origin_b.x-length_b/2 && 
        origin_b.x + length_b/2 >= origin_a.x-length_a/2){
        collision_xaxis = true;
      }
      if(origin_a.y + length_a/2 >= origin_b.y-length_b/2 && 
        origin_b.y + length_b/2 >= origin_a.y-length_a/2){
        collision_yaxis = true;
      }
      bool iscolliding = collision_xaxis && collision_yaxis;
      hascollided |= iscolliding;
    }
    gamescene_polygons[i]->color = hascollided ? RED : GREEN;
  }
}

