#include <map>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    const map<int, char> my_map {{1, 'I'},
                                   {5, 'V'},
                                   {10, 'X'},
                                   {50, 'L'},
                                   {100, 'C'},
                                   {500, 'D'},
                                   {1000, 'M'}};
    string roma {};
    int deci {};
    cout << "Arabic numerals: ";
    cin >> deci;
    
    for (auto it = my_map.rbegin(); it != my_map.rend(); ++it )
    {
        while ( ( deci - it->first ) >= 0 )
        {
            
            if (deci - (4 * it->first) < it->first 
                && deci - (4 * it->first) >= 0)
            {
                deci -= (4 * it->first);
                roma += it->second;
                auto tmp = it;
                roma += (--tmp)->second;
            }
            else if (deci - (9 * (it->first / 5) ) < it->first/5
                    && deci - (9 * (it->first / 5) ) >= 0)
            {
                deci -= (9 * ( it->first / 5 ));
                auto tmp = it;
                roma += (++tmp)->second;
                tmp = it;
                roma += (--tmp)->second;
            }
            else 
            {
                deci -= it->first;
                roma += it->second;
            }
        }
    }

    
    cout << "Roman numerals: " << roma << endl;
}
