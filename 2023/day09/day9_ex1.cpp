#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

int main () {
    ifstream myfile("day9_input.txt");
    string input;
    int sum = 0;
    vector<int> preds;

    if (myfile.is_open()) {
        while(getline (myfile, input)) {
            string::size_type sz;
            vector<int> v, n, ends;
            int nb_z;
            // vector<vector<int>> nexts;
            for (int i = 0; i < input.length(); i ++) {
                v.push_back(stoi(input.substr(i), &sz));
                i += sz;
            }
            // for (auto e : v)
            //     cerr << e << " ";
            // cerr << endl;
            ends.push_back(*(v.end() - 1));
            while (1) {
                nb_z = 0;
                n.clear();
                for (int i = 1; i < v.size(); i++) {    
                    n.push_back(v[i] - v[i - 1]);
                    if (v[i] - v[i - 1] == 0)
                        nb_z ++;
                }
                ends.push_back(*(n.end() - 1));
                if (nb_z == n.size())
                    break;
                v = n;
            }
            // for (auto e : ends)
            //     cerr << e << endl;
            preds.push_back(reduce(ends.begin(), ends.end()));
        }
    }
    cout << reduce(preds.begin(), preds.end()) << endl;
}