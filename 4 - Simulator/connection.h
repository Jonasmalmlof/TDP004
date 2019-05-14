#ifndef _CONNECTION_H_
#define _CONNECTION_H_

class Connection
{
public:
  Connection();
  Connection(double);

  double get_value() const;
  void add_value(double);
  void sub_value(double);
  void set_value(double);

private:
  double charge{};
};

#endif
