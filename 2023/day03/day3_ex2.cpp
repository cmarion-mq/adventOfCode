#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main () {
    ifstream myfile("day3_input.txt");
    string input;
    int sum = 0;
    vector<string> map;
    vector<int> parts;
    int i, j;

    if (myfile.is_open()) {
        while(getline (myfile, input))
            map.push_back(input);
    }
    for (int y = 0; y < map.size(); y ++) {
        for (int x = 0; x < input.length(); x ++) {
            if (map[y][x] == '*') {
                parts.clear();
                for (int yi = y - 1; yi <= y + 1; yi ++) {
                    for (int xi = x - 1; xi <= x + 1; xi ++) {
                        if (xi >= 0 && yi >= 0 && xi < input.length() && yi < map.size() && isdigit(map[yi][xi])) {
                            i = 0;
                            while (isdigit(map[yi][xi + i + 1]))
                                i ++;
                            j = 0;
                            while (isdigit(map[yi][xi - j - 1]))
                                j ++;
                            cerr << i << " " << j << " " << map[yi].substr(xi - j, i + j + 1) << endl;
                            parts.push_back(stoi(map[yi].substr(xi - j, i + j + 1)));
                            xi += i;
                        }
                    }               
                }
                if (parts.size() == 2)
                    sum += parts[0] * parts[1];
            }
        }
    }
    cout << sum << endl;
}