#ifndef _RESISTOR_H_
#define _RESISTOR_H_

#include "component.h"

class Resistor : public Component
{
public:
  using Component::Component;

  double electricity() const override;
  void update(double);
};

#endif
