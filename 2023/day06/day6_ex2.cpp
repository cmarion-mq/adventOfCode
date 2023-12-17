#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    ifstream myfile("day6_input.txt");
    string input;
    vector<long> in(2);
    int w = 0, j = 0;
    
    if (myfile.is_open()) {
        while(getline (myfile, input)) {
            int i = input.find(':') + 1;
            string n;
            while(i < input.length()) {
                while(isdigit(input[i])) {
                    n.push_back(input[i]);
                    i ++;
                }
                i ++;
            }
            in[j] = stol(n);
            j ++;
        }
    }
    for (int t = 1; t <= in[0]; t ++) {
        if ((in[0] - t) * t > in[1])
            w ++;
    }
    cout << w << endl;
}