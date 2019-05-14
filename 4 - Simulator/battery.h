#ifndef _BATTERY_H_
#define _BATTERY_H_

#include "component.h"

class Battery : public Component
{
public:
  using Component::Component;
  

  double electricity() const override;
  void update(double);
};

#endif
