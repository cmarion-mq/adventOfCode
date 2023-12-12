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
    // ifstream myfile("day5_testInput.txt");
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
                    e = b + stol(input.substr(i), &sz) - 1;
                    i += sz + 1;
                    seeds.push_back({b, e});
                }
            }
            else if (input.length() > 0 && isdigit(input[0])) {
                i = 0;
                int k = 0;
                while(i < input.length()) {
                    if (k == 2 && stol(input.substr(i), &sz) - 1 > 0)
                        cats[c][lc].push_back(stol(input.substr(i), &sz) - 1);
                    else
                        cats[c][lc].push_back(stol(input.substr(i), &sz));
                    i += sz + 1;
                    k ++;
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
    i = 0; 
    for (auto s : seeds) {
        cerr << "@@ SEED @@ " << i << endl;
        vector<vector<long>> ranges_of_seeds;
        for (auto c : cats) {
            vector<vector<long>> temp_ranges_of_seeds;
            if (c.first == 0)
                ranges_of_seeds.push_back(s);
            for (auto ns : ranges_of_seeds) {
                in_range = false;
                cerr << "### CAT ### " << c.first << endl;
                for (auto l : c.second) {
                    cerr << "***** RANGE ***** " << l.second[0] << endl;
                    cerr << "line " << l.first << " " << l.second[1] << " " 
                    << l.second[1] + l.second[2] << " (" << l.second[2]  << ")"
                    << " ::: " << ns[0] << " " << ns[1] << endl; 
                    if (ns[0] >= l.second[1] && ns[1] <= l.second[1] + l.second[2]) {
                        cerr << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 1 / " << l.second[0] << endl; 
                        temp_ranges_of_seeds.push_back(
                            {l.second[0] + ns[0] - l.second[1], l.second[0] + ns[1] - l.second[1]});
                        in_range = true;
                        break;
                    } else if (ns[0] < l.second[1] && ns[1] > l.second[1] + l.second[2]) {
                        cerr << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 2 / " << l.second[0] << endl; 
                        temp_ranges_of_seeds.push_back(
                            {ns[0], l.second[1] - 1});
                        temp_ranges_of_seeds.push_back(
                            {l.second[0], l.second[0] + l.second[2]});
                        temp_ranges_of_seeds.push_back(
                            {l.second[1] + l.second[2] + 1, ns[1]});
                        in_range = true;
                        break;
                    } else if (ns[0] >= l.second[1] && ns[1] >= l.second[1] + l.second[2] && ns[0] <= l.second[1] + l.second[2]) {
                        cerr << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 3 / " << l.second[0] << endl; 
                        temp_ranges_of_seeds.push_back(
                            {l.second[0] + ns[0] - l.second[1], l.second[0] + l.second[2]});
                        temp_ranges_of_seeds.push_back(
                            {l.second[1] + l.second[2] + 1, ns[1]});
                        in_range = true;
                        break;
                    } else if (ns[0] <= l.second[1] && ns[1] <= l.second[1] + l.second[2] && ns[1] >= l.second[1]) {
                        cerr << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 4 / " << l.second[0] << endl;
                        temp_ranges_of_seeds.push_back(
                            {ns[0], l.second[1] - 1});
                        temp_ranges_of_seeds.push_back(
                            {l.second[0], l.second[0] + ns[1] - l.second[1]});
                        in_range = true;
                        break;
                    }
                }
                if (!in_range)
                    temp_ranges_of_seeds.push_back(ns);
            }
            ranges_of_seeds = temp_ranges_of_seeds;
            for (auto ns : ranges_of_seeds) {
                cerr << ns[0] << " " << ns[1] << endl;
            }
        }
        for (auto ns : ranges_of_seeds) {
            if (ns[0] < min)
                min = ns[0];
            // cerr << ns[0] << " " << ns[1] << endl;
        }
        i ++;
    }
    cerr << "----------------------" << endl;
    cout << min << endl;
}