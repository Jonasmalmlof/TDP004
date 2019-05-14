#include <algorithm>
#include <cmath>
#include <iostream>
#include "aabb.h"
using namespace std;

AABB::AABB()
  : top{}, left{}, bottom{}, right{} {}

// Komplettering: 8-8, konstruktorn måste
// "fixa" värdena om de är fel (d.v.s
// om t.ex. left ligger till höger om right
// så bör ni byta plats på dem osv.)

AABB::AABB(int t, int l, int b, int r)
  : top{t}, left{l}, bottom{b}, right{r} {}

AABB::AABB(Point p1, Point p2)
  : top{p1.y}, left{p1.x}, bottom{p2.y}, right{p2.x} {}

bool AABB::contain(int x, int y) const
{
  return (x>=left && x<=right && y>=top && y<=bottom);
}

bool AABB::contain(Point p) const
{
  return contain(p.x, p.y);
}

bool AABB::intersect(AABB a) const
{
  bool noOverlap = (left > a.get_right() || a.get_left() > right ||
                    top > a.get_bottom() || a.get_top() > bottom);
  return !noOverlap;
}

AABB AABB::min_bounding_box(AABB a) const
{
  return AABB(std::min(top, a.get_top()), std::min(left, a.get_left()),
              std::max(bottom, a.get_bottom()), std::max(right, a.get_right()));
}

bool AABB::will_not_collide(AABB from, Point to)
{
    // Komplettering: new_AABB täcker inte hela intervallet
    // testa följande fall:
    // will_not_collide  300 200 20 20   280 200  100 180 20 20  t
    // Komplettering: 4-6
  AABB new_AABB{std::min(from.get_top(), to.y), std::min(from.get_left(), to.x),
                std::max(from.get_bottom(), to.y), std::max(from.get_right(), to.x)};
  cout << from.get_top() << " " << to.y << "\n"; //<< min(from.get_left(), to.x) << "\n";
  cout << from.get_bottom() << " " << to.y << "\n"; //max(from.get_right(), to.x) << "\n\n"";
  return !AABB::intersect(new_AABB);
}

bool AABB::collision_point(AABB from, Point to, Point &where)
{
/* stega AABB 'from' sakta men säkert mot Point 'to', och kolla om 
 * AABB::intersect(from) blir True. om det blir True, 
 * ta senaste värdet som visade False.
 */
  double x_move {};
  double y_move {};
  double max_move {};
  AABB previous_box {from};
  int i {};
  
  while( previous_box.get_left()!=to.x && previous_box.get_top()!=to.y )
  {
    i += 1;
    x_move = to.x-from.get_left();
    y_move = to.y-from.get_top();
    max_move = std::max(abs(x_move), abs(y_move));

    double x_movement = round(i*x_move/max_move);
    double y_movement = round(i*y_move/max_move);
    
    AABB current_box { from.get_top()+static_cast<int>(y_movement),
        from.get_left()+static_cast<int>(x_movement),
        from.get_bottom()+static_cast<int>(y_movement),
        from.get_right()+static_cast<int>(x_movement) };
    if ( intersect(current_box) )
    {
      where.x = previous_box.get_left();
      where.y = previous_box.get_top();
      return true;
    }
    previous_box = current_box;
  }
  return false;
}

int AABB::get_top() const
{
  return top;
}

int AABB::get_left() const
{
  return left;
}

int AABB::get_right() const
{
  return right;
}

int AABB::get_bottom() const
{
  return bottom;
}

int AABB::get_height() const
{
  return bottom-top;
}

int AABB::get_width() const
{
  return right-left;
}
