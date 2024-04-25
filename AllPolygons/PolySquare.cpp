#include "PolySquare.h"
#include <cstddef>
#include <raylib.h>
#include <vector>
#include "../CONSTANTS.h"

extern const int SCREENWIDTH;
extern const int SCREENHEIGHT;


PolySquare::PolySquare(Vector2 origin, float length, Color color){
  Vector2 a = {origin.x-length/2, origin.y-length/2};
  Vector2 b = {origin.x+length/2, origin.y-length/2};
  Vector2 c = {origin.x+length/2, origin.y+length/2};
  Vector2 d = {origin.x-length/2, origin.y+length/2};
  std::vector<Vector2> coordinates = {a, b, c, d};
  this->color = color;
  this->connectPoints(coordinates, length);
}

void PolySquare::connectPoints(std::vector<Vector2> coordinates, float length){
  for (size_t i = 0 ; i<coordinates.size(); i++){
    Point *p = new Point(coordinates[i].x, coordinates[i].y, 
                         1, SCREENWIDTH, SCREENHEIGHT, GREEN, false);
    this->poly_points.push_back(p);
  }
  Polygon::connectPoints(coordinates, length);

}
void PolySquare::renderPolygon() const{
  Polygon::renderPolygon();
}


void PolySquare::update(float dt, Vector2 &force){
  Polygon::update(dt, force);
}
