#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

vector<array<int, 2>> smudge_lines(vector<string> &pattern) {
    int tot_diff, i;
    int len = pattern[0].length();
    vector<array<int, 2>> ret;
    for (int l = 0; l < pattern.size() - 1; l ++) {
        for (int c = 1; c < pattern.size(); c ++) {
            tot_diff = 0;
            i = 0;
            while (i < len && tot_diff < 3) {
                if (pattern[l][i] != pattern[c][i])
                    tot_diff ++;
                i ++;
            }
            if (tot_diff == 1)
                ret.push_back({l, c});
        }
    }
    return ret;
}


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
    // ifstream myfile("day13_input.txt");
    ifstream myfile("day13_testInput.txt");
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
                vector<array<int, 2>> s = smudge_lines(h_pattern);
                for (auto a : s)
                    cerr << a[0] << " / " << a[1] << endl;
                cerr << endl;
                // sym_sum += note(h_pattern) * 100 + note(v_pattern);
                // h_pattern.clear();
                // v_pattern.clear();
                // l = 0;
            }
        }
    }
    // sym_sum += note(h_pattern) * 100 + note(v_pattern);;
    cout << sym_sum << endl;
}