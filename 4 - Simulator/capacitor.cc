#include "capacitor.h"

double Capacitor::electricity() const
{
  return value * (voltage() - storage);
}

void Capacitor::update(double time)
{
  double difference{};
  if (point_a.get_value() > point_b.get_value())
  {
    difference = value * (voltage() - storage) * time;
    storage += difference;
    point_b.add_value(difference);
    point_a.sub_value(difference);
  }
  else if (point_b.get_value() > point_a.get_value())
  {
    difference = value * (voltage() - storage) * time;
    storage += difference;
    point_a.add_value(difference);
    point_b.sub_value(difference);
  }
}
