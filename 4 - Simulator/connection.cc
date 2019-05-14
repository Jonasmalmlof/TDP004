#include "connection.h"

Connection::Connection() : charge{} {}

Connection::Connection(double d) : charge{d} {}

double Connection::get_value() const
{
  return charge;
}

void Connection::add_value(double add)
{
  charge += add;
}

void Connection::sub_value(double sub)
{
  charge -= sub;
}

void Connection::set_value(double val)
{
  charge = val;
}
