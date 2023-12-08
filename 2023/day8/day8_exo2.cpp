#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

long findlcm(vector<long> numbers) {
	long ret = numbers[0];
	for(int i = 1; i < numbers.size(); i++)
		ret = lcm(ret, numbers[i]);
	return ret;
}

int main () {
    // ifstream myfile("day8_testInput2.txt");
    ifstream myfile("day8_input.txt");
    string input;
    map<string, vector<string>> dirs;
    vector<vector<string>> ghosts;
    vector<long> reachz;
    vector<string> d;
    string inst;
    bool ex;
    long steps;
    int j;
    
    if (myfile.is_open()) {
        int l = 0;
        while(getline (myfile, input)) {
            if (l == 0)
                inst = input;
            else if (input.length() > 0) {
                dirs[input.substr(0, 3)] = {input.substr(7, 3), input.substr(12, 3)};
                if (input[2] == 'A')
                    ghosts.push_back({input.substr(7, 3), input.substr(12, 3)});
            }
            l ++;
        }
    }
    for (auto ghost : ghosts) {
        d = ghost;
        steps = 1;
        ex = false;
        while (!ex) {
            for (int i = 0; i < inst.length(); i ++) {
                if (inst[i] == 'L')
                    j = 0;
                else
                    j = 1;
                if (d[j][2] == 'Z') {
                    ex = true;
                    break;
                } else
                    d = dirs[d[j]];
                steps ++;
            }
        }
        reachz.push_back(steps);
    }
    cout << findlcm(reachz) << endl;
}

    // while (!ex) {
    //     for (int i = 0; i < inst.length(); i ++) {
    //         // cerr << "&&&&& " << steps << " : " << inst[i] << " &&&&&" << endl;
    //         if (steps > 1) {
    //             ghosts = temp;
    //             temp.clear();
    //         }
    //         z = 0;
    //         for (auto ghost : ghosts) {
    //             // cerr << "*1 " << ghost[0] << " " << ghost[1] << endl;
    //             if (inst[i] == 'L')
    //                 j = 0;
    //             else
    //                 j = 1;
    //             if (ghost[j][2] == 'Z')
    //                 z ++;
    //             // cerr << "*2 " << ghost[j]  << endl;
    //             temp.push_back(dirs[ghost[j]]);
    //         }
    //         if (z == ghosts.size()) {
    //             ex = true;
    //             break;
    //         }
    //         steps ++;
    //     }
    // }
