#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void full_ref(int* ref, int f, int s) {
    ref[0] = f;
    ref[1] = s;
}

int note(vector<string> pattern) {
    for (auto p : pattern)
        cerr << p << endl;
    cerr << pattern.size() / 2 << endl;
    for (int s = 0; s < pattern.size() - 1; s ++) {
        if (pattern[s] == pattern[s + 1]) {
            int i = s - 1;
            int j = s + 2;
            cerr << " ------ " << endl;
            while(j < pattern.size()) {
                cerr << pattern[i] << " " << pattern[j] << endl;
                if (pattern[i] != pattern[j])
                    break;
                i--;
                j++;
            }
            if (j == pattern.size()) {
                cerr << "test" << endl;
                return s + 1;
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
                int h = note(h_pattern);
                int v = note(v_pattern);
                if (h) {
                    cerr << "h " << h << endl;
                    sym_sum += h * 100;
                }
                if (v) {
                    cerr << "v " << v << endl;
                    sym_sum += v;
                }
                cerr << endl;
                h_pattern.clear();
                v_pattern.clear();
                l = 0;
            }
        }
    }
    int h = note(h_pattern);
    int v = note(v_pattern);
    if (h) {
        cerr << "h " << h << endl;
        sym_sum += h * 100;
    }
    if (v){
        cerr << "v " << v << endl;
        sym_sum += v;
    }
    cerr << endl;
    cout << sym_sum << endl;
}