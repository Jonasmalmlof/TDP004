/*
    Antag att du har en variabel "my_map" av typen std::map<string, int> 
    som du fyllt på med data. Nu skall du sätta in nyckeln "Kaffe" med 
    värdet 536. Om "Kaffe" redan finns i din map skall värdet som redan 
    finns ändras. Visa hur du på enklaste sätt löser problemet. 
*/

#include <map>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    map<string, int> my_map;
    my_map["kaffe"] = 344;
    
    cout << "kaffe: " << my_map["kaffe"] << endl;

    string nyckel {};
    int varde {};
    cout << "ge nyckel (kaffe): " << endl;
    cin >> nyckel;
    cout << "ge värde (valfritt): " << endl;
    cin >> varde;
    my_map[nyckel] = varde;
    cout << nyckel << ": " << my_map["kaffe"] << endl;
}
