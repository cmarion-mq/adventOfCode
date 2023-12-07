#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Gamer {
    string  _hand;
    int     _bid;

    Gamer(string hand, int bid):_hand(hand), _bid(bid) {}

    // overload the operator<
    bool operator < (const Gamer &r) const
    {
        int i = 0;
        bool ret;
        while (_hand[i] == r._hand[i] && i < _hand.length())
            i ++;
        if (r._hand[i] == 'A')
            ret = false;
        else if (_hand[i] == 'A')
            ret = true;
        else if (isalpha(r._hand[i]) && isdigit(_hand[i]))
            ret = false;
        else if (isalpha(_hand[i]) && isdigit(r._hand[i]))
            ret = true;
        else if (isdigit(r._hand[i]) && isdigit(_hand[i]))
            ret = _hand[i] > r._hand[i];
        else {
            if (r._hand[i] == 'K'
                || (r._hand[i] == 'Q' && (_hand[i] == 'J' || _hand[i] == 'T'))
                || (r._hand[i] == 'J' && _hand[i] == 'T'))
                ret = false;
            else
                ret = true;
        }
        // ret ?  (cerr << _hand.substr(i) << " < " << r._hand.substr(i) << endl) : (cerr << _hand.substr(i) << " > " << r._hand.substr(i) << endl);
        return ret;
    }
};

int type (string hand) {
    map<char, int> cards;
    int ret = 0;
    for (int i = 0; i < hand.length(); i++)
        cards[hand[i]] ++;
    
    // cerr << hand << endl;
    // for (auto c : cards)
    //     cerr << c.first << " " << c.second << endl;

    if (cards.size() == 1)
        ret = 1;
    else if (cards.size() == 2) {
        int tc = cards.begin()->second;
        if (tc == 4 || tc == 1)
            ret = 2;
        else
            ret = 3;
    } else if (cards.size() == 3) {
        for (auto c : cards) {
            if (c.second == 3)
                ret = 4;
            else if (c.second == 2)
                ret = 5;
        }
    } else if (cards.size() == 4)
        ret = 6;
    else
        ret = 7;
    // cerr << ret << endl;
    return ret;
}

int main () {
    ifstream myfile("day7_input.txt");
    string input;
    map<int, vector<Gamer>> game;
    int nb_gamer = 0;
    int sum = 0;
    
    if (myfile.is_open()) {
        while(getline (myfile, input)) {
            game[type(input.substr(0, 5))].push_back(Gamer(input.substr(0, 5), stoi(input.substr(6))));
            nb_gamer ++;
        }
    }
    for (auto g : game) {
        cerr << " **** "  << g.first << endl;
        sort(g.second.begin(), g.second.end());
        for (auto r : g.second) {
            cerr << r._hand << endl;
            sum += nb_gamer * r._bid;
            nb_gamer --;
        }
    }
    cout << sum << endl;
}