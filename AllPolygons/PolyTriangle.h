#ifndef POLYTRIANGLE_H
#define POLYTRIANGLE_H

#include "Polygon.h"
#include <raylib.h>
#include <vector>


class PolyTriangle : public Polygon{
private:
  void connectPoints(std::vector<Vector2>, float) override;
public:
  PolyTriangle(Color);
  PolyTriangle(Vector2 a, Vector2 b, Vector2 c, Color);
  void renderPolygon() const override;
  void update(float, Vector2 &) override;
};

#endif // !POLYTRIANGLE_H

