#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main () {
    // ifstream myfile("day15_testInput.txt");
    ifstream myfile("day15_input.txt");
    string          input;
    int             h_sum = 0;

    if (myfile.is_open()) {
        while (getline(myfile, input, ',')) {
            int curr = 0; 
            for (auto c : input) {
                curr += c;
                curr *= 17;
                curr %= 256; 
            }
            h_sum += curr;
        }
    }
    cout << h_sum << endl;
}