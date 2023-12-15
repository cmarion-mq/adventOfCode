#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void north(vector<string> &platform, int h, int w) {
    int oline;

    for (int x = 0; x < w; x ++) {
        oline = 0;
        for (int y = 0; y < h; y ++) {
            if (platform[y][x] == 'O') {
                if (y > oline) {
                    platform[oline][x] = platform[y][x];
                    platform[y][x] = '.';
                }
                ++ oline;
            }
            if (platform[y][x] == '#') 
                oline = y + 1;
        }
    }
}

void west(vector<string> &platform, int h, int w) {
    int oline;

    for (int y = 0; y < h; y ++) {
        oline = 0;
        for (int x = 0; x < w; x ++) {
            if (platform[y][x] == 'O') {
                if (x > oline) {
                    platform[y][oline] = platform[y][x];
                    platform[y][x] = '.';
                }
                ++ oline;
            }
            if (platform[y][x] == '#') 
                oline = x + 1;
        }
    }
}

void south(vector<string> &platform, int h, int w) {
    int oline;

    for (int x = 0; x < w; x ++) {
        oline = h - 1;
        for (int y = h - 1; y >= 0; y --) {
            if (platform[y][x] == 'O') {
                if (y < oline) {
                    platform[oline][x] = platform[y][x];
                    platform[y][x] = '.';
                }
                -- oline;
            }
            if (platform[y][x] == '#') 
                oline = y - 1;
        }
    }
}

void east(vector<string> &platform, int h, int w) {
    int oline;

    for (int y = 0; y < h; y ++) {
        oline = w - 1;
        for (int x = w - 1; x >= 0; x --) {
            if (platform[y][x] == 'O') {
                if (x < oline) {
                    platform[y][oline] = platform[y][x];
                    platform[y][x] = '.';
                }
                -- oline;
            }
            if (platform[y][x] == '#') 
                oline = x - 1;
        }
    }
}


void cycle(vector<string> &platform, int h, int w) {
    north(platform, h, w);
    west(platform, h, w);
    south(platform, h, w);
    east(platform, h, w);
}

int laod(vector<string> const &platform, int h, int w) {
    int ret = 0;

    for (int y = 0; y < h; y ++) {
        for (int x = 0; x < w; x ++) {
            if (platform[y][x] == 'O') {
                ret += h - y;
            }
        }
    }
    return ret;
}

vector<int> find_rec(const vector<vector<string>> &platform_states) {
    for (int i = 0; i < platform_states.size() - 1; i ++) {
        for (int j = i + 1; j < platform_states.size(); j ++) {
            if (platform_states[i] == platform_states[j]) 
                return {i, j};
        }
    }
    return {0,0};
}

int main () {
    // ifstream myfile("day14_testInput.txt");
    ifstream myfile("day14_input.txt");
    string          input;
    vector<string>  platform;
    vector<vector<string>> platform_states;
    int             h, w, sym_lrr = 0;

    if (myfile.is_open()) {
        while (getline(myfile, input))
            platform.push_back(input);
    }
    h = platform.size();
    w = platform[0].length();
    vector<string>  temp = platform;
    for (int i = 0; i < 200; i++) {
        cycle(platform, h, w);
        platform_states.push_back(platform);
    }
    vector<int> rec = find_rec(platform_states);
    int r_cycle = (1000000000 - rec[0]) % rec[1];

    for (int i = 0; i < rec[0] + r_cycle; i++)
        cycle(temp, h, w);
    cout << laod(temp, h, w) << endl;
}