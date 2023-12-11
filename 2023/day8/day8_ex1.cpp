#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main () {
    ifstream myfile("day8_input.txt");
    string input;
    map<string, vector<string>> dirs;
    string inst;
    bool ex = false;
    vector<string> d;
    int steps = 1, j;
    
    if (myfile.is_open()) {
        int l = 0;
        while(getline (myfile, input)) {
            if (l == 0)
                inst = input;
            else if (input.length() > 0)
                dirs[input.substr(0, 3)] = {input.substr(7, 3), input.substr(12, 3)};
            l ++;
        }
    }

    d = dirs["AAA"];
    while (!ex) {
        for (int i = 0; i < inst.length(); i ++) {
            if (inst[i] == 'L')
                j = 0;
            else
                j = 1;
            if (d[j] == "ZZZ") {
                ex = true;
                break;
            } else
                d = dirs[d[j]];
            steps ++;
        }
    }
    cout << steps << endl;
}