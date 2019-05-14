#ifndef _CAPACITOR_H_
#define _CAPACITOR_H_

#include "component.h"

class Capacitor : public Component
{
public:
  using Component::Component;

  double electricity() const override;
  void update(double);

private:
  double storage {};
};

#endif
