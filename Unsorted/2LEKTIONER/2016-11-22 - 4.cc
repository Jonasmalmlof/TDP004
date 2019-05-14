   /* Visa hur du kan använda std::random_device och 
    * std::uniform_int_distribution för att slå två 6-sidiga tärningar 
    * (en tärning 1-6, två tärningar 2-12). Skriv ut resultatet med 
    * std::cout. Resultatet skall naturligtvis vara sannolikhetsmässigt 
    * korrekt. Det vill säga att slag med en tärning ger samma 
    * sannolikhet att få varje siffra 1-6, medan slag med 2 tärningar 
    * ger högst sannolikhet att slå 7 (6 av 36 kombinationer get summan 
    * 7), lägst att slå 2 och 12 (1 av 36 kombinationer för vardera). 
    * Tänker du till inser du att du inte behöver någon matematik för 
    * att få till detta korrekt, de nämnda std-typerna räcker. 
    */
#include <iostream>
#include <random>
using namespace std;


int main()
{
    random_device dom;
    uniform_int_distribution<int> ran(1,6);
    
    cout << (ran(dom) + ran(dom)) << endl;
}
