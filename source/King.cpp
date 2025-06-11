#include "King.hpp"
#include "Game.hpp"
#include "def.hpp"
#include <bits/stdc++.h>
using namespace std;

void King::calculateAllMoves(pii a){
    validMoves.clear();

    vector<pii> moves = {
      {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
    };

    for(pii t: moves){
        if(a.first + t.first > -1 && a.first + t.first < 8 && a.second + t.second > -1 && a.second + t.second < 8) {
            validMoves.push_back({a.first + t.first, a.second + t.second});
        }
    }
}
