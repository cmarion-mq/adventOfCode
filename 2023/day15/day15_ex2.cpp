#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Lens {
    string label;
    int    focal_length;
};

int nb_box_calc(string input) {
    int curr = 0; 
    for (auto c : input) {
        curr += c;
        curr *= 17;
        curr %= 256; 
    }
    return curr;
}

vector<Lens>::iterator lens_exist(vector<Lens> &box, string len) {
    for (auto l = box.begin(); l != box.end(); ++ l) {
        if ((*l).label == len)
            return l;
    }
    return box.end();
}

int main () {
    // ifstream myfile("day15_testInput.txt");
    ifstream myfile("day15_input.txt");
    string                  input, lens;
    map<int, vector<Lens>>  boxes;     
    int                     fp_sum = 0, eq, box_nb;

    if (myfile.is_open()) {
        while (getline(myfile, input, ',')) {
            eq = input.find('=');
            if (eq != string::npos) {
                lens = input.substr(0, eq);
                box_nb = nb_box_calc(lens);
                vector<Lens>::iterator lens_pos = lens_exist(boxes[box_nb], lens);
                if (lens_pos == boxes[box_nb].end())
                    boxes[box_nb].push_back({lens, stoi(input.substr(eq + 1))});
                else
                   (*lens_pos).focal_length = stoi(input.substr(eq + 1));
            } else {
                lens = input.substr(0, input.length() - 1);
                box_nb = nb_box_calc(lens);
                vector<Lens>::iterator lens_pos = lens_exist(boxes[box_nb], lens);
                if (lens_pos != boxes[box_nb].end())
                    boxes[box_nb].erase(lens_pos);
            }
        }
    }
    for (auto b : boxes) {
        int i = 1;
        for (auto l : b.second)
            fp_sum += (b.first + 1) * i ++ * l.focal_length;
    }
    cout << fp_sum << endl;
}