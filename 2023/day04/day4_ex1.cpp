#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    ifstream myfile("day4_input.txt");
    string input;
    int sum = 0;
    vector<int> wnb;
    vector<int> point = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int w;
    int nb;

    if (myfile.is_open()) {
        while(getline (myfile, input)) {
            w = 0;
            wnb.clear();
            for (int i = input.find(':') + 2; i < 39; i += 3) 
                wnb.push_back(stoi(input.substr(i, 2)));
            for (int i = 42; i < 116; i += 3) {
                if (find(wnb.begin(), wnb.end(), stoi(input.substr(i, 2))) != wnb.end())
                    w++;
            }
            sum += point[w];
        }
    }
    cout << sum << endl;
}