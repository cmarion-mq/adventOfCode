#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    ifstream myfile("day6_input.txt");
    string input;
    vector<vector<int>> in(2,vector<int>(4, 0));
    int w, s = 0;
    
    int j = 0;
    if (myfile.is_open()) {
        string::size_type sz;
        while(getline (myfile, input)) {
            int i = input.find(':') + 1;
            int l = 0;
            while(i < input.length()) {
                in[j][l] = stoi(input.substr(i), &sz);
                i += sz + 1;
                l ++;
            }
            j ++;
        }
    }
    int win[in[0].size()];
    for (int i = 0; i < in[0].size(); i++) {
        w = 0;
        for (int t = 1; t <= in[0][i]; t ++) {
            if ((in[0][i] - t) * t > in[1][i])
                w ++;
        }
        win[i] = w;
    }
    s = win[0];
    for (int i  = 1; i < in[0].size(); i++) 
        s *= win[i];
    cout << s << endl;
}