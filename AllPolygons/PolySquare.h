#ifndef POLYSQUARE_H        
#define POLYSQUARE_H
#include "Polygon.h"
#include <raylib.h>
#include <vector>


class PolySquare : public Polygon{
private:
  void connectPoints(std::vector<Vector2>, float length) override;
public:
  PolySquare(Color);
  PolySquare(Vector2 origin, float length, Color);
  void renderPolygon() const override;
  void update(float, Vector2 &) override;
};

#endif // !POLYSQUARE_H

