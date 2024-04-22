#ifndef STICk_H
#define STICk_H

#include "Point.h"
class Stick{
private:
  Point &p0;
  Point &p1;
  float length = 100.;
public:
  Stick(Point &p0, Point &p1, float length);
  ~Stick();
  void render();
  void constraint();
};

#endif // !STICk_H
