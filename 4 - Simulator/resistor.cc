#include "resistor.h"

void Resistor::update(double time)
{
  if (point_a.get_value() > point_b.get_value())
  {
    double particles {electricity()*time};
    point_b.add_value(particles);
    point_a.sub_value(particles);
  }
  else if(point_b.get_value() > point_a.get_value())
  {
    double particles {electricity()*time};
    point_a.add_value(particles);
    point_b.sub_value(particles);
  }
}

double Resistor::electricity() const
{
  return voltage()/value;
}
