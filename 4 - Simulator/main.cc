#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "connection.h"
#include "battery.h"
#include "capacitor.h"
#include "resistor.h"

using namespace std;

void simulate(vector<Component*> net, int sims, int rows, double time)
{
  for ( Component* c : net )
  {
    cout << right << setw(12) << c->get_name() << " ";
  }
  cout << endl;

  for ( int i {} ; i<int(net.size()) ; ++i )
  {
    cout << " " << right << setw(5) << "Volt" << setw(6) << "Curr" << " ";
  }
  cout << endl;

  int rownr {1};

  for ( int i {1}; i<=sims; ++i)
  {
    for ( Component* c : net )
    {
      c->update(time);
    }
    if ( i == (sims/rows)*rownr )
    {
      for ( Component* c : net )
      {
        cout << " " << right << setw(5) << fixed << setprecision(2) 
             << c->voltage() << " " << setw(5) << c->electricity() << " ";
      }
      cout << endl;
      ++rownr;
    }
  }
}

int main(int argc, char* argv[])
{
  if ( argc != 5 )
  {
    cout << "Skriv rätt!" << endl;
    return 1;
  }

  int simulations {};
  int rows {};
  double time {};
  double charge {};
  
  try
  {
    simulations = stoi(argv[1]);
    rows = stoi(argv[2]);
    time = stod(argv[3]);
    charge = stod(argv[4]);
  }
  catch(invalid_argument e)
  {
    cout << "Skriv giltiga tal!" << endl;
    return 2;
  }
  catch(out_of_range e)
  {
    cout << "Skriv mindre tal!" << endl;
    return 3;
  }

  Connection p, n, r124, r23;
  vector<Component*> krets1;
  krets1.push_back(new Battery("Bat", charge, p, n));
  krets1.push_back(new Resistor("R1", 6.0, p, r124));
  krets1.push_back(new Resistor("R2", 4.0, r124, r23));
  krets1.push_back(new Resistor("R3", 8.0, r23, n));
  krets1.push_back(new Resistor("R4", 12.0, r124, n));
  simulate(krets1, simulations, rows, time);

  while ( !krets1.empty() )
  {
    Component* c = krets1.back();
    krets1.pop_back();
    delete c;
  }
  
  cout << endl;

  Connection p2, n2, l1, r1;
  vector<Component*> krets2;
  krets2.push_back(new Battery("Bat", charge, p2, n2));
  krets2.push_back(new Resistor("R1", 150, p2, l1));
  krets2.push_back(new Resistor("R2", 50, p2, r1));
  krets2.push_back(new Resistor("R3", 100, l1, r1));
  krets2.push_back(new Resistor("R4", 300, l1, n2));
  krets2.push_back(new Resistor("R5", 250, r1, n2));
  simulate(krets2, simulations, rows, time);

  while ( !krets2.empty() )
  {
    Component* c = krets2.back();
    krets2.pop_back();
    delete c;
  }

  cout << endl;

  Connection p3, n3, l2, r2;
  vector<Component*> krets3;
  krets3.push_back(new Battery("Bat", charge, p3, n3));
  krets3.push_back(new Resistor("R1", 150, p3, l2));
  krets3.push_back(new Resistor("R2", 50, p3, r2));
  krets3.push_back(new Capacitor("C3", 1, l2, r2));
  krets3.push_back(new Resistor("R4", 300, l2, n3));
  krets3.push_back(new Capacitor("C5", 0.75, r2, n3));
  simulate(krets3, simulations, rows, time);

  while ( !krets3.empty() )
  {
    Component* c = krets3.back();
    krets3.pop_back();
    delete c;
  }
}
