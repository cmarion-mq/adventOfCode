#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main () {
    ifstream myfile("day5_input.txt");
    string input;
    vector<vector<long>> seeds;
    string::size_type sz;
    map<int, map<int, vector<long>>> cats;
    int i = 7;
    int l = 0, c = 0, lc = 0;
    bool in_range;
    long min;
    
    if (myfile.is_open()) {
        while(getline (myfile, input)) {
            if (l == 0) {
                long b, e;
                while(i < input.length()) {
                    b = stol(input.substr(i), &sz);
                    i += sz + 1;
                    e = b + stol(input.substr(i), &sz);
                    i += sz + 1;
                    if (seeds.size() == 0)
                        seeds.push_back({b, e});
                    else {
                        int k = 0;
                        for (auto s : seeds){
                            cerr << b << " " << e << " " << seeds.size() << " " << s[0] << " " << s[1] << endl;
                            if (b >= s[0] && e <= s[1]) {
                                continue;
                            }
                            else if (b >= s[0] && e > s[1]) {
                                s[1] = e;
                                break;
                            }
                            else if (b < s[0] && e > s[0]) {
                                s[0] = b;
                                break;
                            }
                            else if (b < s[0] && e > s[1]) {
                                s[0] = b;
                                s[1] = e;
                                break;
                            } else {
                                k ++;
                            }
                        }
                        if (k == seeds.size())
                            seeds.push_back({b, e});
                    }
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
    // for (auto s : seeds) {
    //     cerr << s[0] << ' ' << s[1] << endl; 
    // }
    min = 9223372036854775807;
    for (auto s : seeds) {
        cerr << "@@ SEED @@ " << i << endl;
        for (long sr = s[0]; sr < s[0] + s[1]; sr++) {
            long sri = sr;
            for (auto c : cats) {
                in_range = false;
                // cerr << "### CAT ### " << c.first << endl;
                for (auto l : c.second) {
                    // cerr << "***** RANGE ***** " << l.first << endl;
                    if (sri >= l.second[1] && sri <= l.second[1] + l.second[2]) {
                        sri = l.second[0] + sri - l.second[1];
                        // cerr << "change here " << res[i] << endl;
                        in_range = true;
                        break;
                    }
                }
                // cerr << sri << " " << endl;
            }
            if (sri < min)
                min = sri;
        // cerr << endl;
        }
    }
    // cerr << "----------------------" << endl;
    cout << min << endl;
}