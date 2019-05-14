#include <iostream>
#include <iomanip>

using namespace std;

// Värt att tänka på:
// Tecken per rad, för mer läsbar kod, ha max 80 tecken per rad.
// Indentering, då antalet mellanslag per IDE för en tab kan skilja
// sig åt kan en blandning av tab/mellanslag för att aligna rader göra
// att det ser bra ut i en editor, och oläsbart i en annan.

float tax_amount(float price, float tax);
float total_price(float price, float tax);
float user_input(string input_type, float min, float max = 100000);
void print_table(float first, float last, float step, float tax);

int main()
{
  cout << "INMATNINGSDEL" << endl;
  cout << "=============" << endl;
  
  float first {user_input("forsta pris", 0)};
  float last  {user_input("sista pris", first)};
  float step  {user_input("steglangd", 0.01)};
  float tax   {user_input("momsprocent", 0, 100)};
  
  print_table(first, last, step, tax);
}

float user_input(string input_type, float min, float max)
{
  float val;
  do
  {
    cout << "Mata in " << left << setw(11) << input_type << ": ";
    cin >> val;
    if (val < min)
    {
      cout << "FEL: " << input_type << " minsta tillåtna värde är "
           << min << "." << endl;
    }
    else if (val > max)
    {
      cout << "FEL: " << input_type << " högsta tillåtna värde är "
           << max << "." << endl;
    }
  }
  while (val<min || val > max);
  
  return val;
}

float tax_amount(float price, float tax)
{
  return price * (tax/100);
}

float total_price(float price, float tax)
{
  return price + tax_amount(price, tax);
}

void print_table(float first, float last, float step, float tax)
{
  cout << endl;
  
  cout << "MOMSTABELLEN" << endl;
  cout << "============" << endl;
  cout << right << setw(12) << "Pris" << setw(17)
       << "Moms" << setw(20) << "Pris med moms" << endl;
  cout << "-------------------------------------------------" << endl;
  
  cout << fixed << setprecision(2);
  for (;first<=last; first+=step)
  {
    cout << setw(12) << first << setw(17) << tax_amount(first, tax)
         << setw(20) << total_price(first, tax) << endl;
  }
}
