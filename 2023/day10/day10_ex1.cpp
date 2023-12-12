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
    } else
        return false;
    return
        true;
}

int main () {
    ifstream myfile("day10_input.txt");
    string input;
    vector<string> diagram, evo;
    int i = 0;
    int start[2], pos1[2], pos2[2];

    if (myfile.is_open()) {
        bool sfound = false;
        while (getline(myfile, input)) {
            diagram.push_back(input);
            if (!sfound && input.find('S') != string::npos) {
                def_array(start, input.find('S'), i);
                sfound == true;
            }
            i ++;
        }
    }
    int x1 = 0, y1 = 1, x2 = 0, y2 = -1;
    def_array(pos1, start[0], start[1] + y1);
    def_array(pos2, start[0], start[1] + y2);
    int k = 1;
    while (1) {
        if (pos1[1] == pos2[1] && pos1[0] == pos2[0])
            break;
        if (!next(diagram[pos1[1]][pos1[0]], pos1, x1, y1)
            || !next(diagram[pos2[1]][pos2[0]], pos2, x2, y2))
            break;
        k ++;
    }
    cerr << k << endl;
}