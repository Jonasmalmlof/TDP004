#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <cctype>
using namespace std;

int find_first_pos(string & str)
{
    // finds the position of the first alphabetic char.
    size_t position {};
    position = str.find_first_not_of("(\"'");
    if ( position == string::npos)                    
    {
        return 0;
    }
    return position;
}

int find_last_pos(string & str)
{
    // find the position of the last alphabetic char.
    size_t position {};
    position = str.find_last_not_of(")\"'!?.,:;");
    if ( position == string::npos )
    {
        return str.size();                                              
    }                                                                   
    return position+1;                                                  
}

int find_genus_pos(string & str)
{   
    // finds the position of any "'s" in the word for removal.
    size_t position {};
    position = str.find("'s");
    if ( position == string::npos || position != str.size()-2 ) 
    {
        return str.size();
    }
    return position;
}

bool not_a_word(string & str)                                           
{   
    // checks if there's non-alpha characters in the middle of the
    // word, with an exception for hyphens.
    bool word {true};
    for_each(str.begin(), str.end(), 
            [&str, &word](char & c)
            {
                if ( !isalpha(c) && c != '-')
                {                                                       
                    word = false;
                }
            });
    // also checks if the word is smaller than three letters long.
    return !word || str.size() < 3;
}

int compare_for_sort( pair<string,int> p1, pair<string,int> p2)
{
    // compares the second values of two pairs, for sorting.
    return p1.second > p2.second;
}

void printList(vector<string> & words, string arg1, int textlength)
{
    if ( arg1 == "-a" || arg1 == "-f" )
    {
        // adds every word still left to map "ordlista"
        // or adds to the word's value.
        map<string, int> ordlista {};
        for_each(words.begin(), words.end(), 
                [&words, &ordlista](string & word)
                {   
                    ordlista[word]++; 
                });

        // returns a pointer to the largest word in the map.
        auto wordlength_point = *max_element(ordlista.begin(),
                                             ordlista.end(),
            [](const pair<string, int> & p1, 
               const pair<string, int> & p2) 
            {
                return p1.first.size() < p2.first.size(); 
            });
        // turns pointer into a more managable variable.
        int wordlength = wordlength_point.first.size();


        // returns pointer to the largest value in the map.
        auto numlength_point = *max_element(ordlista.begin(), 
                                            ordlista.end(),
            [](const pair<string, int> & p1, 
               const pair<string, int> & p2) 
            {
                return p1.second < p2.second; 
            });
        // turns pointer into a more managable variable.
        int numlength = to_string(numlength_point.second).size();


        if ( arg1 == "-a" )
        {
            // prints each word out in the map's default sorting order.
            for_each(ordlista.begin(), ordlista.end(), 
                    [&wordlength, &numlength](const auto &wordPair) 
                    {
                        cout << left << setw(wordlength)
                        << wordPair.first << "  "
                        << right << setw(numlength)
                        << wordPair.second << "\n";
                    });
        }
        else if ( arg1 == "-f" )
        {   
            // copies map to vector of pairs and sorts by second element.
            vector<pair<string,int>> pairvector;
            copy( ordlista.begin(), ordlista.end(), 
                    back_inserter(pairvector));                         
            sort ( pairvector.begin(), pairvector.end(), 
                    compare_for_sort );                                 
            // prints each word and sorts by the number it appears.
            for_each(pairvector.begin(), pairvector.end(),
                    [&pairvector, &wordlength, &numlength]
                        (pair<string,int> i) 
                    {
                        cout << right << setw(wordlength)
                        << i.first << "  " 
                        << left << setw(numlength)
                        << i.second << "\n";
                    });                                                 
        }
    }
    else if ( arg1 == "-o" )
    {
        // prints each word in the *original* order they appear,
        // making each row no longer than the supplied textlength.
        size_t currentlength {0};
        for_each(words.begin(), words.end(),                            
                [&textlength, &currentlength](const string &word)         
                {
                    // check how long the row would be if 
                    // current word was added.
                    // if so: adds a return and prints the word.
                    if ( static_cast<int>(currentlength+word.size()) 
                                                     > textlength ) 
                    {
                        cout << "\n";
                        currentlength = 0;
                    }
                    cout << word << " ";
                    currentlength += word.size()+1;                     
                });
        cout << "\n";
    }
    cout << "\n";
}

int main(int argc, char* argv[])
{
    string filename {};
    string arg1 {};
    int arg2 {0};
    // long if-statement that checks that the command-line was 
    // supplied as requested.
    if ( argc >= 3 )
    {
        filename = argv[1];
        arg1 = argv[2];
        if ( arg1 == "-o" )
        {
            // if there's an -o but no following integer.
            if ( argc == 3 )
            {
                cerr << "Error: number required after '-o' \n";
                return 0;
            }
            arg2 = stoi(argv[3]);
        }
        // if you give incorrect commands.
        if ( arg1 != "-a" && arg1 != "-f" && arg1 != "-o" )
        {
            cerr << "Error: Invalid argument(s). \n";
            return 0;
        }
    }
    // if you supply a filename but nothing else.
    else if ( argc == 2 )
    {
        cerr << "Error: Second argument missing or invalid. \nUsage: " 
             << argv[0] << " FILE [-a] [-f] [-o N] \n";
        return 0;
    }
    // if no if succeeds, it means you didn't supply any variables.
    else
    {
        cerr << "Error: No arguments given. \nUsage: " << argv[0]
             << " FILE [-a] [-f] [-o N] \n";
        return 0;
    }
    
    // if program fails to stream the file to the variable,
    // it means a non-existant filename was supplied.
    ifstream ifs {filename};
    if ( !ifs )
    {
        cerr << "ERROR: Couldn't open the file \"" << filename << "\"\n";
        return 0;
    }
    
    // turns text into a vector of strings.
    vector<string> words;
    copy(istream_iterator<string>{ifs}, istream_iterator<string>{},
            back_inserter(words));

    for_each(words.begin(), words.end(), [&words](string & s)
            { 
                // removes all leading non-alpha characters.
                s.erase(0, find_first_pos(s));                          
                // removes all ending non-alpha characters.
                s.erase(find_last_pos(s), s.size());
                // removes any genus 's in the word.
                s.erase(find_genus_pos(s), s.size());
                // turns all remaining characters to lowercase.
                transform(s.begin(), s.end(), s.begin(), ::tolower);
            });
            
    // erases any string that has non-alpha characters in it
    // or any string that is too short.
    words.erase( remove_if(words.begin(), words.end(), 
            not_a_word), words.end() );
    
    // prints what's left.
    printList(words, arg1, arg2);
    
    // closes the stream, just in case.
    ifs.close();
}
