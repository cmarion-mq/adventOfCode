#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Beam {
    int x;
    int y;
    int dx;
    int dy;

    void mv_up() {
        y -= 1;
        dx = 0;
        dy = -1;
    }

    void mv_down() {
        y += 1;
        dx = 0;
        dy = 1;
    }

    void mv_left() {
        x -= 1;
        dx = -1;
        dy = 0;
    }

    void mv_right() {
        x += 1;
        dx = 1;
        dy = 0;
    }

    bool dir_up() {
        return dx == 0 && dy == -1;
    }

    bool dir_down() {
        return dx == 0 && dy == 1;
    }

    bool dir_left() {
        return dx == -1 && dy == 0;
    }

    bool dir_right() {
        return dx == 1 && dy == 0;
    }    
};

struct Tile {
    char _c;
    bool dir_up;
    bool dir_down;
    bool dir_left;
    bool dir_right;

    bool all_dir() {
        return dir_down && dir_left && dir_right && dir_up;
    }

    void set_tile(int x, int y, char c){
        if (x == -1)
            dir_left = true;
        if (x == 1)
            dir_right = true;
        if (y == -1)
            dir_up = true;
        if (y == 1)
            dir_down = true;
        _c = c;
    }
};

int beam_way(const vector<string> &map, vector<vector<Tile>> &energized, Beam b, bool first_pass) {
    int h = map.size();
    int w = map[0].length();
    while (b.x >= 0 && b.x < w && b.y >= 0 && b.y < h) {
        if (b.x == 0 && b.y == 0) {
            if (!first_pass)
                return 0;
            first_pass = false;
        }
        if (energized[b.y][b.x].dir_up && b.dir_up() || energized[b.y][b.x].dir_down && b.dir_down() 
            || energized[b.y][b.x].dir_left && b.dir_left() || energized[b.y][b.x].dir_right && b.dir_right())
            return 0;
        energized[b.y][b.x].set_tile(b.dx, b.dy, '#');

        if (((map[b.y][b.x] == '/' && b.dir_left()) || (map[b.y][b.x] == '\\' && b.dir_right())) && b.y < h -1)
            b.mv_down();
        else if (((map[b.y][b.x] == '/' && b.dir_right()) || (map[b.y][b.x] == '\\' && b.dir_left())) && b.y > 0)
            b.mv_up();
        else if (((map[b.y][b.x] == '/' && b.dir_up()) || (map[b.y][b.x] == '\\' && b.dir_down())) && b.x < w - 1)
            b.mv_right();
        else if (((map[b.y][b.x] == '/' && b.dir_down()) || (map[b.y][b.x] == '\\' && b.dir_up())) && b.x > 0)
            b.mv_left();
        else if (map[b.y][b.x] == '|' && b.dir_up() && b.y > 0)
            b.mv_up();
        else if (map[b.y][b.x] == '|' && b.dir_down() && b.y < h - 1)
            b.mv_down();
        else if (map[b.y][b.x] == '-' && b.dir_left() && b.x > 0)
            b.mv_left();
        else if (map[b.y][b.x] == '-' && b.dir_right() && b.x < w - 1)
            b.mv_right();
        else if (map[b.y][b.x] == '|' && (b.dir_left() || b.dir_right())) {
            if (b.y > 0)
                beam_way(map, energized, {b.x, b.y, 0, -1}, false);
            if (b.y < h - 1)
                b.mv_down();
        } else if (map[b.y][b.x] == '-' && (b.dir_up() || b.dir_down())) {
            if (b.x > 0)
                beam_way(map, energized, {b.x, b.y, -1, 0}, false);
            if (b.x < w - 1)
                b.mv_right();
        } else if ((b.dir_down() && b.y < w - 1) || (b.dir_up() && b.y > 0) || (b.dir_left() && b.x > 0) || ( b.dir_right() && b.x < h - 1)) {
            b.x += b.dx;
            b.y += b.dy;
        } else
            return 0;
    }
    return 0;
}

int main () {
    // ifstream myfile("day16_testInput.txt");
    ifstream myfile("day16_input.txt");
    string                  input;
    vector<string>          map;
    vector<vector<Tile>>    energized;
    vector<int>             energies;
    int                     j = 0;

    if (myfile.is_open()) {
        while (getline(myfile, input)) {
            map.push_back(input);
            vector<Tile> l;
            energized.push_back(l);
            for (int i = 0; i < input.length(); i ++)
                energized[j].push_back({'.', false, false, false, false});
            j++;
        }
    }
    for (int y = 0; y < map.size(); y = y + map.size() - 1) {
        for (int x = 0; x < map[0].length(); x ++) {
            vector<vector<Tile>> temp = energized;
            if (y == 0)
                beam_way(map, temp, {x, y, 0, 1}, true);
            else
                beam_way(map, temp, {x, y, 0, -1}, true);
            int e_sum = 0;
            for (auto l : temp) {
                for (auto c : l) {
                    if (c._c == '#')
                        e_sum ++; 
                }
            }
            energies.push_back(e_sum);
        }
    }
    for (int x = 0; x < map[0].length(); x = x + map[0].length() - 1) {
        for (int y = 0; y < map.size(); y++) {
            vector<vector<Tile>> temp = energized;
            if (x == 0)
                beam_way(map, temp, {x, y, 1, 0}, true);
            else
                beam_way(map, temp, {x, y, -1, 0}, true);
            int e_sum = 0;
            for (auto l : temp) {
                for (auto c : l) {
                    if (c._c == '#')
                        e_sum ++; 
                }
            }
            energies.push_back(e_sum);
        }
    }
    cout << *max_element(energies.begin(), energies.end()) << endl;
}