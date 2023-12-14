#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main () {
    // ifstream myfile("day14_testInput.txt");
    ifstream myfile("day14_input.txt");
    string          input;
    vector<string>  v_platform;
    int             sym_lrr = 0, l = 0;

    if (myfile.is_open()) {
        while (getline(myfile, input)) {
            if (l == 0) {
                for (int i = 0; i < input.length(); i ++)
                    v_platform.push_back(string(1, input[i]));
            } else {
                for (int i = 0; i < input.length(); i ++)
                    v_platform[i] += input[i];
            }
            l ++;
        }
    }
    for (auto p : v_platform) {
        int i = 0;
        while (i < p.length()) {
            int csr = p.find('#', i) == string::npos ? p.length() : p.find('#', i);        
            int j = i;
            while (i < csr) {
                if (p[i] == 'O') {
                    sym_lrr += p.size() - j;
                    j ++;
                }
                i ++;
            }
            while (csr < p.length() && p[csr] == '#')
                csr ++;
            i = csr;
        }
    }
    cout << sym_lrr << endl;
}