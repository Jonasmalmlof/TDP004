/*TDP004  2016-11-22  Seminarium

uppgift 1
"Du vet att användaren matat in en sträng eller ett heltal. Visa hur du utan andra hjälpmedel än medlemmar i std::cin och vanliga if-satser kan läsa in inmatad data till en std::string om inmatningen var en sträng och till en heltalsvariabel om det var ett heltal."           STD::CIN     &&    IF-SATSER
*/
#include <iostream>

using namespace std;

int main()
{
    int tal;
    std::string str {};
    cin >> tal;
    
    if (cin.fail())
    {
        cin.clear();
        cin >> str;
        cout << "string: " << str << "\n";
    }
    else 
    {
        cout << "integer: " << tal << "\n";
    }
}
