#ifndef _AABB_H_
#define _AABB_H_

struct Point
{
  int x;
  int y;
};

// Komplettering: 5-4

class AABB
{
public:
  AABB();
  AABB(int top, int left, int bottom, int right);
  AABB(Point p1, Point p2);

  bool contain(int x, int y) const;
  bool contain(Point p) const;
  bool intersect(AABB a) const;
  AABB min_bounding_box(AABB a) const;
  bool will_not_collide(AABB from, Point to) ;
  bool collision_point(AABB from, Point to, Point &where);

private:
  int top, left, bottom, right;
  int get_width() const;
  int get_height() const;
  int get_left() const;
  int get_right() const;
  int get_top() const;
  int get_bottom() const;
};

#endif
