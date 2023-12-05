#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main () {
    ifstream myfile("day4_input.txt");
    string input;
    int sum = 0;
    vector<int> wnb;
    map<int, int> wcards;
    int c = 1;
    int w;

    if (myfile.is_open()) {
        while(getline (myfile, input)) {
            w = 0;
            wnb.clear();
            for (int i = input.find(':') + 2; i < 39; i += 3) // Input parsing
            // for (int i = input.find(':') + 2; i < 22; i += 3) // Test parsing
                wnb.push_back(stoi(input.substr(i, 2)));
            for (int i = 42; i < 116; i += 3) { // Input parsing
            // for (int i = 25; i < 48; i += 3) { // Test parsing
                if (find(wnb.begin(), wnb.end(), stoi(input.substr(i, 2))) != wnb.end())
                    w++;
            }
            for (int j = c; j <= c + w; j ++) {
                wcards[j] += 1;
                if (j > c)
                    wcards[j] += wcards[c] - 1;
            }
            // for (int j = c + 1; j <= c + w; j ++)
            //     wcards[j] += wcards[c] - 1;
            c ++;
        }
        for (auto wc : wcards)
            sum += wc.second;
        cout << sum << endl;
    }
    
}