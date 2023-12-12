#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool test(const string &record, const vector<int> &dups) {
    int d, pos = 0, i = 0;
    while (i < record.length()) {
        d = 0;
        while (record[i + d] == '#' && i + d < record.length())
            d ++;
        if (d) {
            if (dups[pos] != d)
                return false;
            pos ++;
        }
        while (record[d + i] == '.' && i < record.length())
            i ++;
        i += d;
    }
    if (pos == dups.size())
        return true;
    return false;
}

int main () {
    ifstream myfile("day12_test.txt");
    string          input;
    int             arr_sum = 0;

    if (myfile.is_open()) {
        while (getline(myfile, input)) {
            string::size_type   sz;
            int                 sep = input.find(' ');
            string              record = input.substr(0, sep);
            vector<int>         dups;
            vector<string>      arrgts;
            while (sep != string::npos) {
                dups.push_back(stoi(input.substr(sep + 1), &sz));
                sep = input.find(',', sep + sz);
            }
            if (record[0] == '?') {
                arrgts.push_back(".");
                arrgts.push_back("#");
            } else {
                arrgts.push_back(record.substr(0, 1));
            }
            for (int i = 1; i < record.length(); i ++) {
                if (record[i] == '?') {
                    vector<string>      temp;
                    for (auto a : arrgts) {
                        temp.push_back(a + '.');
                        temp.push_back(a + '#');
                    }
                    arrgts = temp;
                } else {
                    for (int j = 0; j < arrgts.size(); j++) 
                        arrgts[j] += record[i];
                }
            }
            for (auto a : arrgts) {
                if (test(a, dups))
                    arr_sum ++;
            }
        }
    }


    cout << arr_sum << endl;
}