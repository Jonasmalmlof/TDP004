#include "battery.h"

void Battery::update(double time)
{
  time=time;
  point_a.set_value(value);
  point_b.set_value(0);
}

double Battery::electricity() const
{
  return 0;
}
