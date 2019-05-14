/*
    TDP004 2016-11-22 LEKTION
    
    "antag att programmet set ut som:
    
    cout << "Mata in ett flyttal: " << endl;
    double d;
    cin >> d;
    
    Antag att användaren matade in "Ett-komma-fem". 
    Visa hur du gör för att upptäcka problemet och se till så att nästa 
    inmatning har en chans att fungera."
*/
#include <iostream>

using namespace std;

int main()
{
    cout << "Mata in ett flyttal: " << endl;
    double d;
    std::string str {};
    cin >> d;
    if (cin.fail())
    {
        cin.clear();
        cin >> str;
        cerr << "prova att skriva in med nummer istället för med ord" << endl;
    }
    else if ( (d - static_cast<int>(d)) == 0 )
    {
        cout << "du skrev decimalpunkten med ett ','. Skriv det med ett '.' istället." << endl;
    } else {
        cout << "Korrekt! " << d << endl;
    }
}
