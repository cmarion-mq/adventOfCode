#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {
    ifstream myfile("day2_input.txt");
    string input;
    int sum = 0;
    int j, k;
    int r, g, b;
    int cnb;

    if (myfile.is_open()) {
        while(getline (myfile, input)) {
            j = input.find(':') + 2;
            r = 0;
            g = 0;
            b = 0;
            while(j < input.length()) {
                k = 0;
                while(isdigit(input[j + k]))
                    k ++;
                cnb = stoi(input.substr(j, k - j));
                if (input[j + k + 1] == 'r') {
                    if(cnb > r)
                        r = cnb;
                    j += 6 + k;
                } else if (input[j + k + 1] == 'g') {
                    if(cnb > g)
                        g = cnb;
                    j += 8 + k;
                } else {
                    if(cnb > b)
                        b = cnb; 
                    j += 7 + k;
                }
            }
            sum += r * g * b;
        }
    }
    cout << sum << endl;
}