#include "Knight.hpp"
#include "Game.hpp"
#include <bits/stdc++.h>
using namespace std;

void Knight::calculateAllMoves(pair<int,int> a) {
    validMoves.clear();

    vector<pair<int,int>> moves = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, +2}, {2, -1}, {2, 1}, {1, -2}, {1, 2}
    };

    for(auto &t: moves){
        if(a.first + t.first > -1 && a.first + t.first < 8 && a.second + t.second > -1 && a.second + t.second < 8) {
            validMoves.push_back({a.first + t.first, a.second + t.second});
        }
    }
}
