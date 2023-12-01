#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main () {
    ifstream myfile("day1_input.txt");
    string input;
    int sum = 0;
    string nbr;


    if (myfile.is_open()) {
        // while (myfile) {
            while(getline (myfile, input)) {
                nbr = "";
                for (int i = 0; i < input.length(); i ++) {
                    if (isdigit(input[i]))
                        nbr.push_back(input[i]);
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