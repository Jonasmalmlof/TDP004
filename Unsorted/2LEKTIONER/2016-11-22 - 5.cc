   /* Tittar du i figuren ser du att detta också stämmer. Tolkning 
    * baklänges: Vi har en variabel argv som lagrar en adress (*) till 
    * något som är en adress (*) till något som är ett tecken (char). 
    * Är vi lite flexibla med singular och plural (pekare anger inte 
    * hur många variabler som pekas ut) så blir denna variant samma sak. 
    * Dock inte lika tydlig som den förra. Visa hur du på enklaste sätt 
    * transformerar argc och argv till en std::vector. Vektorn skall 
    * innehålla alla strängar från argv[] som std::string. Titta 
    * framförallt på vilka konstruktorer det finns i std::vector och 
    * std::string.
    */
#include <iostream>
#include <iterator>
#include <vector>


using namespace std;    

int main(int argc, char ** argv)
{
    vector<string> arguments { argv+1, argv+argc };
    copy(begin(arguments), end(arguments), 
        ostream_iterator<string>{cout, "\n"});
}
