#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int note(vector<string> pattern) {
    for (int s = 0; s < pattern.size() - 1; s ++) {
        if (pattern[s] == pattern[s + 1]) {
            int i = s - 1;
            int j = s + 2;
            while(i >= 0 && j < pattern.size() && pattern[i] == pattern[j]) {
                i--;
                j++;
            }
            if (i == -1 || j == pattern.size())
                return s + 1;
        }
    }
    return 0;
}

int main () {
    ifstream myfile("day13_input.txt");
    // ifstream myfile("day13_testInput.txt");
    string          input;
    vector<string>  h_pattern, v_pattern;
    int             sym_sum = 0, l = 0;

    if (myfile.is_open()) {
        while (getline(myfile, input)) {
            if (input.size() > 0) {
                h_pattern.push_back(input);
                if (l == 0) {
                    for (int i = 0; i < input.length(); i ++)
                        v_pattern.push_back(string(1, input[i]));
                } else {
                    for (int i = 0; i < input.length(); i ++)
                        v_pattern[i] += input[i];
                }
                l ++;
            } else {
                sym_sum += note(h_pattern) * 100 + note(v_pattern);
                h_pattern.clear();
                v_pattern.clear();
                l = 0;
            }
        }
    }
    sym_sum += note(h_pattern) * 100 + note(v_pattern);;
    cout << sym_sum << endl;
}