#include <cmath>
#include <string>
#include "component.h"

Component::Component(std::string n, double input_value, Connection &a_value, Connection &b_value)
  : name{n}, value{input_value}, point_a(a_value), point_b(b_value) {}

std::string Component::get_name() const
{
  return name;
}

double Component::voltage() const
{
  return std::abs(point_a.get_value() - point_b.get_value());
}

/*Component::set_point_a(double a_value)
{
  point_a = a_value;
}

Component::set_point_b(double b_value)
{
  point_b = b_value;
  }*/
