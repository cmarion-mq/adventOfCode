#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {
    ifstream myfile("day2_input.txt");
    string input;
    int sum = 0;
    int i = 1;
    int j;
    int k;
    int cnb;
    bool valid;

    if (myfile.is_open()) {
        while(getline (myfile, input)) {
            j = input.find(':') + 2;
            valid = true;
            while(j < input.length()) {
                k = 0;
                while(isdigit(input[j + k]))
                    k ++;
                cnb = stoi(input.substr(j, k - j));
                if (input[j + k + 1] == 'b') {
                    if(cnb > 14) {
                        valid = !valid;
                        break;
                    }
                    j += 7 + k;
                } else if (input[j + k + 1] == 'r') {
                    if(cnb > 12) {
                        valid = !valid;
                        break;
                    }
                    j += 6 + k;
                } else {
                    if(cnb > 13) {
                        valid = !valid;
                        break;
                    }   
                    j += 8 + k;
                }
            }
            if (valid) {
                cerr << "*i*: " << i << endl;
                sum += i;
            }
            i ++;
        }
    }
    cout << sum << endl;
}