#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Convert {
    long b_source;
    long e_source;
    long b_dest;
    long e_dest;
    long dec;
    long delta = b_dest - b_source;
};

int main () {
    ifstream myfile("day5_input.txt");
    // ifstream myfile("day5_testInput.txt");

    string input;
    string::size_type       sz;
    vector<vector<long>>    seeds;
    map<int, vector<Convert>>    cats;
    bool test = false;
    long min;
    
    if (myfile.is_open()) {
        int c = 0, i = 7;
        while(getline (myfile, input)) {
            if (!test) {
                long b, e;
                while(i < input.length()) {
                    b = stol(input.substr(i), &sz);
                    i += sz + 1;
                    e = b + stol(input.substr(i), &sz) - 1;
                    i += sz + 1;
                    seeds.push_back({b, e});
                }
                test = true;
            } else {
                if (input.length() > 0 && isdigit(input[0])) {
                i = 0;
                int k = 0;
                long temp[3];
                while(i < input.length()) {
                    temp[k] = stol(input.substr(i), &sz);
                    i += sz + 1;
                    k ++;
                }
                cats[c].push_back({temp[1], temp[1] + temp[2] - 1, temp[0], temp[0] + temp[2] - 1, temp[2]});
                } else if (input.length() == 0)
                    c ++;
            }
        }
    }

    min = 9223372036854775807;
    for (auto s : seeds) {
        cerr << "     @@ SEED " << s[0] << " : " << s[1] << " @@" << endl;
        vector<vector<long>> ranges_of_seeds;
        for (auto c : cats) {
            cerr << "       ### CAT " << c.first << " ###" << endl;
            if (c.first == 1)
                ranges_of_seeds.push_back(s);
            vector<vector<long>> pass_ranges, not_pass_ranges;
            for (auto l : c.second) {
                not_pass_ranges.clear();
                for (auto ns : ranges_of_seeds) {
                    cerr << "seed range : " << ns[0] << " " << ns[1] << endl; 
                    cerr << "***** filter " << l.b_source << " : " << l.e_source << " // " << l.b_dest << " : " << l.e_dest << " *****" << endl;
                    if (ns[0] >= l.b_source && ns[1] <= l.e_source) {
                        cerr << "&&&&&&&&&&&&&&& 1 / ok range : " << ns[0] << " : " << ns[1] << " => " << ns[0] + l.delta << " : " << ns[1] + l.delta << endl;
                        pass_ranges.push_back({ns[0] + l.delta, ns[1] + l.delta});
                    }
                    else if (ns[0] < l.b_source && ns[1] > l.e_source) {
                        not_pass_ranges.push_back({ns[0], l.b_source - 1});
                        cerr << "&&&&&&&&&&&&&&& 2 / bad range : " << ns[0] << " : " << ns[1] << " => " << ns[0] << " : " << l.b_dest - 1 << endl;
                        
                        pass_ranges.push_back({l.b_dest, l.e_dest});
                        cerr << "&&&&&&&&&&&&&&& 2 / ok range : " << ns[0] << " : " << ns[1] << " => " << l.b_dest << " : " << l.e_dest << endl;
                        
                        not_pass_ranges.push_back({l.e_source + 1, ns[1]});
                        cerr << "&&&&&&&&&&&&&&& 2 / bad range : " << ns[0] << " : " << ns[1] << " => " << l.e_dest << " : " << ns[1] << endl;
                    }
                    else if (ns[0] >= l.b_source && ns[1] > l.e_source && ns[0] <= l.e_source) {
                        pass_ranges.push_back({ns[0] + l.delta, l.e_dest});
                        cerr << "&&&&&&&&&&&&&&& 3 / ok range : " << ns[0] << " : " << ns[1] << " => " << ns[0] + l.delta << " : " << l.e_dest << endl;

                        not_pass_ranges.push_back({l.e_source + 1, ns[1]});
                        cerr << "&&&&&&&&&&&&&&& 3 / bad range : " << ns[0] << " : " << ns[1] << " => " << l.e_source + 1 << " : " << ns[1] << endl;
                    }
                    else if (ns[0] < l.b_source && ns[1] <= l.e_source && ns[1] >= l.b_source) {
                        not_pass_ranges.push_back({ns[0], l.b_source - 1});
                        cerr << "&&&&&&&&&&&&&&& 4 / bad range : " << ns[0] << " : " << ns[1] << " => " << ns[0] << " : " << l.b_source - 1 << endl;
                        
                        pass_ranges.push_back({l.b_dest, ns[1] + l.delta});
                        cerr << "&&&&&&&&&&&&&&& 4 / ok range : " << ns[0] << " : " << ns[1] << " => " << l.b_dest << " : " << ns[1] + l.delta << endl;
                    }
                    else
                        not_pass_ranges.push_back(ns);
                }
                ranges_of_seeds = not_pass_ranges;
            }
            for (auto np : not_pass_ranges)
                pass_ranges.push_back(np);
            ranges_of_seeds = pass_ranges;
            cerr << endl;
        }
        cerr << "---------------------------------" << endl;
        for (auto ns : ranges_of_seeds) {
            if (ns[0] < min)
                min = ns[0];
        }
    }
    cout << min << endl;
}