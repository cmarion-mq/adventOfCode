#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main () {
    ifstream myfile("day5_testInput.txt");
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
                            if (b >= s[0] && e <= s[1]) 
                                continue;
                            else if (b >= s[0] && e > s[1] && e <= s[1]) {
                                s[1] = e;
                                break;
                            }
                            else if (b < s[0] && e <= s[1] && e >= s[0]) {
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

    min = 9223372036854775807;
    for (auto s : seeds) {
        cerr << "@@ SEED @@" << endl;
        vector<vector<long>> nseeds;
        nseeds.push_back(s);
        for (auto c : cats) {
            for (auto ns : nseeds) {
                long st[2] = {ns[0], ns[1]};
                in_range = false;
                // cerr << "### CAT ### " << c.first << endl;
                for (auto l : c.second) {
                    // cerr << "***** RANGE ***** " << l.first << endl;
                    if (l.second[1] >= st[0] && l.second[1] + l.second[2] <= st[1]) {
                        ns[0] = l.second[0] + ns[0] - l.second[1];
                        ns[1] = l.second[0] + ns[1] - l.second[1];
                        break;
                    } else if (l.second[1] < st[0] && l.second[1] + l.second[2] > st[1]) {
                        ns[0] = l.second[0];
                        ns[1] = l.second[0] + l.second[2];
                        nseeds.push_back({l.second[0] + st[0] - l.second[1], l.second[0] - 1});
                        nseeds.push_back({l.second[0] + l.second[2] + 1, l.second[0] + st[1] - l.second[1]});
                        break;
                    } else if (l.second[1] >= st[0] && l.second[1] + l.second[2] > st[1] && l.second[1] <= l.second[1] + l.second[2]) {
                        ns[0] = l.second[0];
                        ns[1] = l.second[0] + l.second[2];
                        nseeds.push_back({l.second[0] + l.second[2] + 1, l.second[0] + st[1] - l.second[1]});
                        break;
                    } else if (l.second[1] < st[0] && l.second[1] + l.second[2] <= st[1] && l.second[1] >= l.second[0]) {
                        ns[0] = l.second[0];
                        ns[1] = l.second[0] + l.second[2];
                        nseeds.push_back({l.second[0] + st[0] - l.second[1], l.second[0] - 1});
                    }
                }
                // cerr << sri << " " << endl;
            }
        }
/***************for nseed => look for the min of all ranges***************/
        // if (sri < min)
        //     min = sri;
        // cerr << endl;
    }
    // cerr << "----------------------" << endl;
    cout << min << endl;
}