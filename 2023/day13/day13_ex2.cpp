#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

int smudge_lines(vector<string> &pattern) {
    int tot_diff, i, j;
    int len = pattern[0].length();

    for (int l = 0; l < pattern.size() - 1; l ++) {
        for (int c = l + 1; c < pattern.size(); c ++) {
            tot_diff = 0;
            i = 0;
            while (i < len && tot_diff < 3) {
                if (pattern[l][i] != pattern[c][i])
                    tot_diff ++;
                i ++;
            }
            if (tot_diff == 1 && (c - l - 1) % 2 == 0) {
                if (c - l == 1) {
                    i = l - 1;
                    j = l + 2;
                    while(i >= 0 && j < pattern.size() && pattern[i] == pattern[j]) {
                        i--;
                        j++;
                    }
                    if (i == -1 || j == pattern.size())
                        return l + 1;
                } else {
                    i = 1;
                    while (i <= (c - l) / 2 && pattern[l + i] == pattern[c - i])
                        i ++;
                    j = 1;
                    while(l - j >= 0 && c + j < pattern.size() && pattern[l - j] == pattern[c  + j])
                        j ++;
                    if (i == ((c - l) / 2) + 1 && (l - j == -1 || c + j == pattern.size()))
                        return l + i;            
                }

            }
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
                int sh = smudge_lines(h_pattern);
                if (sh) {
                    sym_sum += sh * 100;
                } else {
                    sym_sum += smudge_lines(v_pattern);
                }
                h_pattern.clear();
                v_pattern.clear();
                l = 0;
            }
        }
    }
    int sh = smudge_lines(h_pattern);
    if (sh)
        sym_sum += sh * 100;
    else
        sym_sum += smudge_lines(v_pattern);
    cout << sym_sum << endl;
}