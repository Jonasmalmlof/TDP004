#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>
#include "connection.h"

class Component
{
public:
  Component(std::string, double, Connection&, Connection&);
  virtual ~Component() = default;

  std::string get_name() const;
  double voltage() const;
  virtual double electricity() const = 0;
  virtual void update(double) = 0;

protected:
  std::string name {};
  double value {};
  Connection &point_a;
  Connection &point_b;
};

#endif
