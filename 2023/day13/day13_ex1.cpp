#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void full_ref(int* ref, int f, int s) {
    ref[0] = f;
    ref[1] = s;
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
                int h_ref[2], v_ref[2];
                for (int i = 0; i < h_pattern.size() - 1; i ++) {
                    if (h_pattern[i] == h_pattern[i + 1]) {
                        full_ref(h_ref, i, i + 1);
                        break;
                    }
                }
                for (int i = 0; i < v_pattern.size(); i ++) {
                        if (v_pattern[i] == v_pattern[i + 1]) {
                            full_ref(v_ref, i, i + 1);
                            break;
                        }
                }
                int f = 0;
                if (h_ref[0] >= h_pattern.size() / 2) {
                    for (auto p : h_pattern)
                        cerr << p << endl;
                    for (int i = h_ref[0] - 1, j = h_ref[1] + 1; j < h_pattern.size(); i--, j++) {
                        if (h_pattern[i] != h_pattern[j])
                            break;    
                        f ++;
                    }
                    if (f == h_pattern.size() - h_ref[1] - 1) {
                        cerr << "h " << h_ref[1] << endl;
                        sym_sum += h_ref[1] * 100;
                    }
                }
                f = 0;
                if (v_ref[0] >= v_pattern.size() / 2) {
                    for (auto p : v_pattern)
                        cerr << p << endl;
                    for (int i = v_ref[0] - 1, j = v_ref[1] + 1; j < v_pattern.size(); i--, j++) {
                        if (v_pattern[i] != v_pattern[j])
                            break;
                        f ++;
                    }
                    if (f == v_pattern.size() - v_ref[1] - 1) {
                        cerr << "v " << v_ref[1] << endl;
                        sym_sum += v_ref[1];
                    }
                }
                h_pattern.clear();
                v_pattern.clear();
                l = 0;
            }
        }
        int h_ref[2], v_ref[2];
        for (int i = 0; i < h_pattern.size() - 1; i ++) {
            if (h_pattern[i] == h_pattern[i + 1]) {
                full_ref(h_ref, i, i + 1);
                break;
            }
        }
        for (int i = 0; i < v_pattern.size(); i ++) {
                if (v_pattern[i] == v_pattern[i + 1]) {
                    full_ref(v_ref, i, i + 1);
                    break;
                }
        }
        int f = 0;
        if (h_ref[0] >= h_pattern.size() / 2) {
            for (int i = h_ref[0] - 1, j = h_ref[1] + 1; i >= 0 && j < h_pattern.size(); i--, j++) {
                if (h_pattern[i] != h_pattern[j])
                    break;
                f ++;
            }
            if (f == h_pattern.size() - h_ref[1] - 1)
                sym_sum += h_ref[1] * 100;
        }
        f = 0;
        if (v_ref[0] >= v_pattern.size() / 2) {
            for (int i = v_ref[0] - 1, j = v_ref[1] + 1; i >= 0 && j < v_pattern.size(); i--, j++) {
                if (v_pattern[i] != v_pattern[j])
                    break;
                f ++;
            }
            if (f == v_pattern.size() - v_ref[1] - 1)
                sym_sum += v_ref[1];
        }
    }
}