#ifndef POINT_H
#define POINT_H
#include <raylib.h>


class Point{
  private:
    Vector2 current_position = {0,0};
    Vector2 prev_position = {0, 0};
    float mass = 1;
    const int &screen_width;
    const int &screen_height;
  public:
    Point(float x, float y, float mass, const int &screen_width,
          const int &screen_height, Color c, bool ispinned);
    ~Point();
    void update(float dt, Vector2 force);
    void render();
    Vector2 getCurrentPos();
    void setCurrentPos(Vector2 new_pos);
    void constraint();
    bool ispinned = false;
    Color color;
};

#endif
