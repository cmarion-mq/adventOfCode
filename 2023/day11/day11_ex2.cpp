#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main () {
    ifstream myfile("day11_input.txt");
    string input;
    vector<string>      universe;
    vector<vector<int>> to_see;
    vector<int> ext_line, ext_col;
    long mouv = 0;
    int x, y, h = 0, l;
    if (myfile.is_open()) {
        while (getline(myfile, input)) {
            universe.push_back(input);
            if (input.find('#') == string::npos) 
                ext_line.push_back(h);
            h ++;
        }
    }

    l = input.length();
    for (int xi = 0; xi < l; xi ++) {
        for (int yi = 0; yi < h; yi ++) {
            if (universe[yi][xi] == '#')
                break;
            if (yi == h - 1) 
                ext_col.push_back(xi);
        }
    }

    y = 0;
    for (auto lu : universe) {
        x = lu.find('#');
        while (x != string::npos) {
            to_see.push_back({x, y});
            x = lu.find('#', x + 1);
        }
        y ++;
    }

    for (auto f = to_see.begin(); f < to_see.end() - 1; ++ f) {
        vector<vector<int>> pairs(f +  1, to_see.end());
        for (auto s : pairs) {
            x = 0;
            y = 0;
            for (auto l : ext_line) {
                if (l >= (*f)[1] && l <= s[1])
                    y ++;
            }
            for (auto c : ext_col) {
                if ((s[0] > (*f)[0] && (c >= (*f)[0] && c <= s[0])) || (s[0] < (*f)[0] && (c <= (*f)[0] && c >= s[0])))
                    x ++;
            }
            mouv += abs((*f)[0] - s[0]) + s[1] - (*f)[1] + x * (1000000 - 1) + y * (1000000 - 1);
        }
    }
    cout << mouv << endl;
}