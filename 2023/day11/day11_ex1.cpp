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
    int mouv = 0;
    int x, y, h = 0, l;
    if (myfile.is_open()) {
        while (getline(myfile, input)) {
            universe.push_back(input);
            if (input.find('#') == string::npos) {
                universe.push_back(input);
                h ++;
            }
            h ++;
        }
    }

    l = input.length();
    for (int xi = 0; xi < l; xi ++) {
        for (int yi = 0; yi < h; yi ++) {
            if (universe[yi][xi] == '#')
                break;
            if (yi == h - 1) {
                for (int yj = 0; yj < h; yj ++) 
                    universe[yj].insert(xi, 1, '.');
                l ++;
                xi ++;
            }
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
        for (auto s : pairs)
            mouv += abs((*f)[0] - s[0]) + s[1] - (*f)[1];
    }
    cout << mouv << endl;
}