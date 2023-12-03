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
    int i;
    int pnb;
    bool part;

    if (myfile.is_open()) {
        while(getline (myfile, input))
            map.push_back(input);
    }
    for (int y = 0; y < map.size(); y ++) {
        for (int x = 0; x < input.length(); x ++) {
            if (isdigit(map[y][x])) {
                i = 0;
                while (isdigit(map[y][x + i]))
                    i ++;
                part = false;
                for (int yi = y - 1; yi <= y + 1; yi ++) {
                    for (int xi = x - 1; xi <= x + i; xi ++) {
                        if (xi >= 0 && yi >= 0 && xi < input.length() && yi < map.size() && !isdigit(map[yi][xi]) && map[yi][xi] != '.') {
                            // cerr << yi << " : " << xi  << " = " << map[yi][xi] << endl;
                            pnb = stoi(map[y].substr(x, i));
                            // cerr << pnb << " : " << map[yi][xi] << endl;
                            part = true;
                            sum += pnb;
                            break;
                        }
                        // if (part)
                        //     break;
                    }
                }
                x += i;
            }
        }
    }
    cout << sum << endl;
}