#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool valid_min_max(string input, int &min, int &max)
{
  stringstream inp(input);

  inp>>min;
  inp>>max;
  
  if (!inp || min>max || min<0 || max<0 )           // if inp isn't valid. or min higher than max or either below zero.
  {
    return false;
  }
  
  return true;
}

bool valid_brick_values(string input, int &first_val,
                        int &second_val, int &third_val)
{
  stringstream inp(input);
  
  inp>>first_val;
  inp>>second_val;
  inp>>third_val;

  if( !inp )
  {
    return false;
  }
  
  return true;
}

bool valid_brick(int first, int second, int third, int min, int max)
{
  bool valid_order {false};
  bool within_boundaries {false};
  
  if( first<=second && second<=third )
  {
    valid_order = true;
  }
  else if( second<=third && third<=first )
  {
    valid_order = true;
  }
  else if( third<=first && first<=second )
  {
    valid_order = true;
  }

  if( first<=max && first>=min && second<=max && second>=min
      && third<=max && third>=min )
  {
    within_boundaries = true;
  }
  
  return ( valid_order && within_boundaries );
}

// snyggt!
void set_boundary_values(string values, int &min, int &max)
{
  while ( !valid_min_max(values, min, max) )
  {
    cerr << "Inkorrekta värden.\n";
    cout << "Ange nya min- och maxvärden: ";
    getline(cin, values);
  }
}

void set_brick_values( string values, int &first_val,
                       int &second_val, int &third_val )
{
  while ( !valid_brick_values(values, first_val, second_val, third_val) )
  {
    cerr << "Inkorrekta värden.\n";
    cout << "Ange tre nya värden för brickan: ";
    getline(cin, values);
  }
}

void print_brick_status( int first_val, int second_val,
                         int third_val, int min, int max )
{
  if( valid_brick(first_val, second_val, third_val, min, max) )
  {
    cout << "Korrekt bricka." << endl;
  }
  else
  {
    cout << "Inkorrekt bricka." << endl;
  }
}

int main(int argc, char* argv[])
{
  string filename {};
  int min {};
  int max {};
  string values{};

  if ( argc != 4 )
  {
    cerr << "FEL: Programmet anropas enligt \"" << argv[0]
         << " filnamn minimivärde maximumvärde\"\n";
    cout << "Ange filnamn, minvärde och maxvärde: ";
    cin >> filename;
    getline(cin, values);
    
    set_boundary_values(values, min, max);
  }
  else
  {
    filename = argv[1];

    string arg1 {argv[2]};
    string arg2 {argv[3]};
    values = arg1 + " " + arg2;
    
    set_boundary_values(values, min, max);
  }

  int first_val{};
  int second_val{};
  int third_val{};
  ifstream ifs{};
  
  if ( filename == "-" )
  {
    do
    {
      cout << "Ange brickans tre värden, eller en tom sträng för att avsluta: ";
      getline(cin, values);
      
      if( values.size() != 0 )
      {
        set_brick_values(values, first_val, second_val, third_val);
        print_brick_status(first_val, second_val, third_val, min, max);
      }
    }
    while ( values != "" );
  }
  else
  {
    ifs.open(filename);
    while ( !ifs )
    {
      cerr << "FEL: Kunde inte öppna filen \"" << filename << "\"\n";
      cout << "Ange nytt filnamn: ";
      cin >> filename;
      cin.ignore(100000, '\n');
      ifs.open(filename);
    }
  }

  // string word{};

  while ( getline(ifs, values) )
  {
    stringstream stream(values);

    stream>>first_val;
    stream>>second_val;
    stream>>third_val;

    if( stream )
    {
      print_brick_status(first_val, second_val, third_val, min, max);
    }
    else
    {
      cerr << "Ej en bricka." << endl;
    }
  }
  ifs.close();
}
