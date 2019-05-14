/*
    TDP004 Lektion 2016-11-22
    UPPGIFT 2
"Det är givet att 'statistics.txt' enbart innehåller flyttal. Förklara 
vad som är fel i följande kod:"

*/
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ifstream ifs("statistics.txt");

  if ( ! ifs )
  {
     cerr << "Kunde inte öppna 'statistics.txt'." << endl;
     return 1; // terminate program with error code 1
  }

  double nr;
  double sum{0.0};
  int count{0};
  while ( ! ifs.eof() )     
  // den här går körs en gång för mycket och använder 
  // det sista legitima värdet.
  {
     ifs >> nr;
     sum += nr;
     ++count;
  }
  double average = sum / count;
  cout << average << " = " << sum << " / " << count << endl;
  return 0;
}
