#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// 1-4
// 2-1
// 5-1
// 7-1 och 8-2
int main()
{
	int x;
	cout << "Skriv in ett heltal: ";
	cin >> x; 
	cout << "Du skrev in talet: " << x << endl;
	cin.ignore(10000, '\n');
	
	cout << endl << "Skriv in fem heltal: ";
	cin >> x;
	cout << "Du Skrev in talen: " <<  x << ", ";
	cin >> x;
	cout << x << ", ";
	cin >> x;
	cout << x << ", ";
	cin >> x;
	cout << x << ", ";
	cin >> x;
	cout << x << endl;
	cin.ignore(10000, '\n');
	
	double d;
	cout << endl << "Skriv in ett flyttal: ";
	cin >> d;
	cout << "Du skrev in flyttalet: " << fixed << setprecision(3) << d << endl;
	cin.ignore(10000, '\n');
	
	cout << endl << "Skriv in ett heltal och ett flyttal: ";
	cin >> x >> d;
	cout << "Du skrev in heltalet: " << x << endl;
	cout << "Du skrev in flyttalet: " << d << endl;
	cin.ignore(10000, '\n');
	
	char c;
	cout << endl << "Skriv in ett tecken: ";
	cin >> c;
	cout << "Du skrev in tecknet: " << c << endl;
	cin.ignore(10000, '\n');
	
	string s;
	cout << endl << "Skriv in en sträng: ";
	cin >> s;	
	cout << "Strängen '" << s << "' har " << s.size() << " tecken." << endl;
	cin.ignore(10000, '\n');
	
	cout << endl << "Skriv in ett heltal och en sträng: ";
	cin >> x;
    cin >> s;
	cout << "Du skrev in talet |" << x << "| och strängen |" << s << "|." << endl;
	cin.ignore(10000, '\n');
	
	cout << endl << "Skriv in en sträng och ett flyttal: ";
	cin >> s;
    cin >> d;
	cout << "Du skrev in \"" << d << "\" och \"" << s << "\"." << endl;
	cin.ignore(10000, '\n');
	
	cout << endl << "Skriv in en hel rad med text: ";
	getline (cin, s);
	cout << "Du skrev in textraden: '" << s << "'" << endl;
	
	cout << endl << "Skriv in en textrad som slutar med ett negativt heltal: ";
	getline (cin, s, '-');
	cin >> x;
	x = -x;
	cout << "Du skrev in textraden '" << s << "' och heltalet '" << x << "'." <<endl;
	cin.ignore(10000, '\n');
}
