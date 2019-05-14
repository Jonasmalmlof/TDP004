#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <cctype>
using namespace std;

int find_first_pos(string & str)
{
    int position {};
    position = str.find_first_not_of("(\"'!");
    if ( position == int(string::npos) ) 
    {
        return 0;
    }
    return position;
}

int find_last_pos(string & str)
{
    int position {};
    position = str.find_last_not_of(")\"'!.,:;");
    if ( position == int(string::npos) )
    {
        return str.size();
    }
    return position;
}

int find_genus_pos(string & str)
{
    int position {};
    position = str.find("'s");
    if ( position == int(string::npos) ) 
    {
        return str.size();
    }
    return position;
}

int not_a_word(string & str)
{
    bool notaword {false};
    for_each(str.begin(), str.end(), [&str, &notaword](char & c)
            {
                if ( !isalpha(c) )
                {
                    notaword = true;
                }
            });
    if ( notaword == true )
    {
        return 0;
    }
    else
    {
        return str.size();
    }
}

int main(int argc, char* argv[])
{
    string filename {};
    string arg1 {};
    int arg2 {};
    
    if ( argc >= 3 )
    {
        filename = argv[1];
        arg1 = argv[2];
        if ( arg1 == "-o" )
        {
            if ( argc == 3 )
            {
                cerr << "Error: number required after '-o' \n";
                return 0;
            }
            arg2 = stoi(argv[3]);
        }
        if ( arg1 != "-a" && arg1 != "-f" && arg1 != "-o" )
        {
            cerr << "Error: Invalid argument(s). \n";
            return 0;
        }
    }
    else if ( argc == 2 )
    {
        cerr << "Error: Second argument missing or invalid \nUsage: " << argv[0]
             << " FILE [-a] [-f] [-o N] \n";
        return 0;
    }
    else
    {
        cerr << "Error: No arguments given. \nUsage: " << argv[0]
             << " FILE [-a] [-f] [-o N] \n";
        return 0;
    }
    
    ifstream ifs {filename};
    if ( !ifs )
    {
        cerr << "FEL: Kunde inte öppna filen \"" << filename << "\"\n";
        return 0;
    }
    
    vector<string> words;
    copy(istream_iterator<string>{ifs}, istream_iterator<string>{},
                back_inserter(words));

    for_each(words.begin(), words.end(), [&words](string & s)
            { 
            s.erase(0, find_first_pos(s));                              // removes all leading non-alpha characters.
            s.erase(find_last_pos(s)+1, s.size());                      // removes all following non-alpha characters.
            s.erase(find_genus_pos(s), find_genus_pos(s));              // removes genus 's in the word.
            s.erase(not_a_word(s), s.size());                           // removes any word that have non-alpha characters inside it.
            });

    for_each(words.begin(), words.end(), [&words](string & s)
        { transform(s.begin(), s.end(), s.begin(), ::tolower); });       // turns all strings to lowercase.
 
    map<string, int> ordlista {};
    for_each(words.begin(), words.end(), [&words, &ordlista](string & s)
        {   
            if ( s.size() >= 3 )
            {
                ordlista[s]++; 
            }
        });                                                             // adds every word longer than 2 to the wordlist ("ordlista"), or adds 1 to the number of the word.

    
    
    for_each(ordlista.begin(), ordlista.end(), 
            [](const auto &wordPair) {cout << wordPair.first 
                                           << " " << wordPair.second 
                                           << "\n";});                  // prints each word and how many times it occurs.
    
    
    arg2 = arg2;                // MEMBER!
    ifs.close();
}

