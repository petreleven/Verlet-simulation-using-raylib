#ifndef POLYGON_H
#define POLYGON_H
#include "../Point.h"
#include "../Stick.h"
#include <raylib.h>
#include <vector>


class Polygon{
  public:
    Polygon();
    ~Polygon();
    virtual void renderPolygon() const=0;
    virtual void update(float, Vector2 &);
    void move(Vector2, float);
    std::vector<Point> getAllpolygonpoints();
    std::vector<Stick> getAllpolygonsticks();
    Color color;

  protected:
    std::vector<Point *> poly_points;
    std::vector<Stick *> poly_sticks;
    virtual void connectPoints(std::vector<Vector2>, float);

};




#endif // !POLYGON_H


