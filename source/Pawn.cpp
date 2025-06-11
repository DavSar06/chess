#include "Pawn.hpp"
#include "Game.hpp"
#include <bits/stdc++.h>
using namespace std;

void Pawn::calculateAllMoves(pair<int,int> a) {
    validMoves.clear();
    int k = 1;
    int st = 6;
    if(this->getColor() == 'b'){
        k = -1;
        st = 1;
    }

    if(a.first - k > -1 && a.first - k < 8 && !Game::board_[a.first - k][a.second]) validMoves.push_back({a.first - k,a.second});
    if(a.first - 2 * k > -1 && a.first - 2 * k < 8 && !Game::board_[a.first - 2 * k][a.second] && !Game::board_[a.first - k][a.second] && a.first == st) validMoves.push_back({a.first - 2 * k,a.second});
    if(a.second > 0 && Game::board_[a.first - k][a.second - 1] && Game::board_[a.first - k][a.second - 1]->getColor() != Game::board_[a.first][a.second]->getColor()) validMoves.push_back({a.first - k,a.second - 1});
    if(a.second < 7 && Game::board_[a.first - k][a.second + 1] && Game::board_[a.first - k][a.second + 1]->getColor() != Game::board_[a.first][a.second]->getColor()) validMoves.push_back({a.first - k,a.second + 1});

    validateMoves(a);
}
