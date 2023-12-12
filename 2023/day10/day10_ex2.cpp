#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void def_array(int* array, int x, int y) {
    array[0] = x;
    array[1] = y;
}

bool next(char cur, int* pos, int &x, int &y) {
    if (cur == '|' && y < 0)
        def_array(pos, pos[0], pos[1] - 1);
    else if (cur == '|' && y > 0)
        def_array(pos, pos[0], pos[1] + 1);
    else if (cur == '-' && x > 0)
        def_array(pos, pos[0] + 1, pos[1]);
    else if (cur == '-' && x < 0)
        def_array(pos, pos[0] - 1, pos[1]);
    else if (cur == 'F' && y != 0) {
        def_array(pos, pos[0] + 1, pos[1]);
        x = 1;
        y = 0;     
    }
    else if (cur == 'F' && x != 0) {
        def_array(pos, pos[0], pos[1] + 1);
        x = 0;
        y = 1;
    }
    else if (cur == 'L' && x != 0) {
        def_array(pos, pos[0], pos[1] - 1);
        x = 0;
        y = -1;
    }
    else if (cur == 'L' && y != 0) {
        def_array(pos, pos[0] + 1, pos[1]);
        x = 1;
        y = 0;
    }
    else if (cur == '7' && y != 0) {
        def_array(pos, pos[0] - 1, pos[1]);
        x = -1;
        y = 0;
    }
    else if (cur == '7' && x != 0) {
        def_array(pos, pos[0], pos[1] + 1);
        x = 0;
        y = 1;
    }
    else if (cur == 'J' && x != 0) {
        def_array(pos, pos[0], pos[1] - 1);
        x = 0;
        y = -1;
    }
    else if (cur == 'J' && y != 0) {
        def_array(pos, pos[0] - 1, pos[1]);
        x = -1;
        y = 0;
    } else {
        return false;
    }
    return
        true;
}

int main () {
    ifstream myfile("day10_input.txt");
    // ifstream myfile("day10_testInput2-1.txt");
    string input;
    vector<string> diagram, evol;
    int i = 0;
    int start[2], pos1[2], pos2[2];

    if (myfile.is_open()) {
        bool sfound = false;
        while (getline(myfile, input) ) {
            diagram.push_back(input);
            if (!sfound && input.find('S') != string::npos) {
                def_array(start, input.find('S'), i);
                sfound == true;
            }
            i ++;
        }
    }
    evol = diagram;
    int x1 = 0, y1 = 1, x2 = 0, y2 = -1; // input
    // int x1 = 0, y1 = 1, x2 = 1, y2 = 0; // 2-1
    // int x1 = 0, y1 = 1, x2 = -1, y2 = 0; // 2-2
    def_array(pos1, start[0] + x1, start[1] + y1); 
    def_array(pos2, start[0] + x2, start[1] + y2);
    int k = 1;
    while (1) {
        evol[pos1[1]][pos1[0]] = '*';
        evol[pos2[1]][pos2[0]] = '*';
        if (pos1[1] == pos2[1] && pos1[0] == pos2[0])
            break;
        if (!next(diagram[pos1[1]][pos1[0]], pos1, x1, y1)
            || !next(diagram[pos2[1]][pos2[0]], pos2, x2, y2))
            break;
        k ++;
    }
    for (int y = 0; y < evol.size(); y ++) {
        int x = 0;
        if (y == 0 || y == evol.size() - 1) {
            while (x < evol[0].size()) {
                evol[y][x] = 'u';
                x ++;
            }
            continue;
        }
        while (x < evol[0].size() && evol[y][x] != '*' && evol[y][x] != '.') {
            evol[y][x] = 'u';
            x ++;
        }
        x = evol[0].size() - 1;
        while (x > 0 && evol[y][x] != '*' && evol[y][x] != '.') {
            evol[y][x] = 'u';
            x --;
        }
    }
    for (int x = 0; x < evol[0].size(); x ++) {
        int y = 0;
        if (x == 0 || x == evol[0].size() - 1) {
            while (y < evol.size()) {
                evol[y][x] = 'u';
                y ++;
            }
            continue;
        }
        while (y < evol.size() && evol[y][x] != '*' && evol[y][x] != '.' && evol[y][x] != 'u') {
            evol[y][x] = 'u';
            y ++;
        }
        y = evol.size() - 1;
        while (y > 0 && evol[y][x] != '*' && evol[y][x] != '.' && evol[y][x] != 'u') {
            evol[y][x] = 'u';
            y --;
        }
    }



    for (auto e : evol) 
        cerr << e << endl;

    //     while (evol[x] == '*')
    //         x ++;
    //     int f = 0;
    //     while (evol[x] != '*')
    //         f ++;
    //     if (x + f != evol[0].length()) {

    //     }
    // }
    // for (int y = 1; y < evol.size() - 1, y++) {
    //     cerr << e << endl;
    //     for (int x = 1; x < evol[y] - 1; x++) {
    //         if (evol[y][x] == '.') {
    //             i = 1;
    //             for (int y1 = -i; y1;  )
    //         }
    //     }
    // }
    cout << k << endl;
}