#include <map>
#include <iostream>
#include <string>
using namespace std;

int main()
{
                // uppgift 1
    const map<char, int> my_map {{'I', 1}, 
                                   {'V', 5}, 
                                   {'X', 10}, 
                                   {'L', 50}, 
                                   {'C', 100}, 
                                   {'D', 500}, 
                                   {'M', 1000}};
    
                // uppgift 2
    string roma;
    int deci {0};
    cout << "Roman numerals: ";
    cin >> roma;

    for ( int i=0, max=roma.size(); i != max; ++i )
    {
        if (    ( roma[i] == 'I' && ( roma[i+1] == 'X' || roma[i+1] == 'V' ) ) ||
                ( roma[i] == 'X' && ( roma[i+1] == 'L' || roma[i+1] == 'C' ) ) ||
                ( roma[i] == 'C' && ( roma[i+1] == 'M' || roma[i+1] == 'D' ) ) )
        {
            deci -= my_map.at(roma[i]);
        }
        else 
        {
            deci += my_map.at(roma[i]);
        }
    }
    cout << "Arabic numeral: " << deci << endl;
}
