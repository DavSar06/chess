#include "Rook.hpp"
#include "Game.hpp"
#include <bits/stdc++.h>
using namespace std;

void Rook::calculateAllMoves(pair<int,int> a){
    validMoves.clear();

    for(int i = 1; i + a.first < 8; i++) {
        validMoves.push_back({a.first + i, a.second});
        if(Game::board_[a.first + i][a.second]) break;
    }

    for(int i = 1; a.first - i > -1; i++) {
        validMoves.push_back({a.first - i, a.second});
        if(Game::board_[a.first - i][a.second]) break;
    }

    for(int i = 1; i + a.second < 8; i++) {
        validMoves.push_back({a.first, a.second + i});
        if(Game::board_[a.first][a.second + i]) break;
    }

    for(int i = 1; a.second - i > -1; i++) {
        validMoves.push_back({a.first, a.second - i});
        if(Game::board_[a.first][a.second - i]) break;
    }
}
