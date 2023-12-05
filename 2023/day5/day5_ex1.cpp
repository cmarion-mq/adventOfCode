#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main () {
    ifstream myfile("day5_input.txt");
    string input;
    vector<long> seeds, res;
    string::size_type sz;
    map<int, map<int, vector<long>>> cats;
    int i = 7;
    int l = 0, c = 0, lc = 0;
    bool in_range;
    
    if (myfile.is_open()) {
        while(getline (myfile, input)) {
            if (l == 0) {
                while(i < input.length()) {
                    seeds.push_back(stol(input.substr(i), &sz));
                    i += sz + 1;
                }
            }
            else if (input.length() > 0 && isdigit(input[0])) {
                i = 0;
                while(i < input.length()) {
                    cats[c][lc].push_back(stol(input.substr(i), &sz));
                    i += sz + 1;
                }
                lc ++;
            } else if (input.length() == 0 && l > 1) {
                c ++;
                lc = 0;
            }
            l ++;
        }
    }
    res  = seeds;
    i = 0;
    for (auto s : seeds) {
        res[i] = seeds[i];
        for (auto c : cats) {
            in_range = false;
            for (auto l : c.second) {
                if (res[i] >= l.second[1] && res[i] <= l.second[1] + l.second[2]) {
                    res[i] = l.second[0] + res[i] - l.second[1];
                    in_range = true;
                    break;
                }
            }
        }
        i ++;
    }
    cout << *min_element(res.begin(), res.end()) << endl;
}