#include "../AllPolygons/Polygon.h"
#include <vector>

class AABB {
  private:
  std::vector<Polygon *> gamescene_polygons;
  public:
  AABB(std::vector<Polygon*>);
  void checkcollisions();

};
