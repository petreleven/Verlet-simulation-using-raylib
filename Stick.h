#ifndef STICk_H
#define STICk_H

#include "Point.h"
#include <raylib.h>
class Stick{
private:
  Point &p0;
  Point &p1;
public:
  Stick(Point &p0, Point &p1, float length);
  Stick(Point &p0, Point &p1, float length, Color);
  ~Stick();
  void render();
  void render(Color );
  void constraint();
  Color color=GREEN;
  float length = 100.;
};

#endif // !STICk_H
