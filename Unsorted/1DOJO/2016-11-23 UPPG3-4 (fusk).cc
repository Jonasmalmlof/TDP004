#include <map>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    const map<int, string> my_map {{1, "I"},
                                    {4, "IV"},
                                    {5, "V"},
                                    {9, "IX"},
                                    {10, "X"},
                                    {40, "XL"},
                                    {50, "L"},
                                    {90, "XC"},
                                    {100, "C"},
                                    {400, "CD"},
                                    {500, "D"},
                                    {900, "CM"},
                                    {1000, "M"}};
    string roma {};
    int deci {};
    cout << "Arabic numerals: ";
    cin >> deci;
    
    for (auto it = my_map.rbegin(); it != my_map.rend(); ++it )
    {
        while ( ( deci - it->first ) >= 0 )
        {
            deci -= it->first;
            roma += it->second;
        }
    }
    cout << "Roman numerals: " << roma << endl;
}
