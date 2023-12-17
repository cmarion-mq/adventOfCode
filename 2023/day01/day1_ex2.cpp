#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main () {
    ifstream myfile("day1_input.txt");
    string input;
    map<string, char> digits = {{"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'}, 
        {"five", '5'}, {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}}; 
    int sum = 0;
    string nbr;


    if (myfile.is_open()) {
        // while (myfile) {
            while(getline (myfile, input)) {
                nbr = "";
                for (int i = 0; i < input.length(); i ++) {
                    if (isdigit(input[i]))
                        nbr.push_back(input[i]);
                    else {
                        for (auto d : digits) {
                            if (input.find(d.first, i) == i) {
                                nbr.push_back(d.second);
                                // i += d.first.length() - 1; ne fonctionne pas, du fait de lettres communes a certains chiffres
                                // i += d.first.length() - 2; //fonctionne et limite le passage dans le for, les chiffres n'ont pas plus d'une lettre commune entre début et fin
                                break;
                            }
                        }
                    }
                }
                if (nbr.length() == 1)
                    sum += stoi(nbr + nbr);
                else if ((nbr.length() == 2))
                    sum += stoi(nbr);
                else if (nbr.length() > 2)
                    sum += stoi(string(1, nbr[0]) + string(1, nbr[nbr.length() - 1]));
            }
        // }
    }
    cout << sum << endl;
}